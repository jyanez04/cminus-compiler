/*
    Lab 9: MIPS Code from AST
    Jacob Yanez
    May 3, 2024

    This program traverses the AST that was created in previous labs and
    outputs MIPS code to a file given by a command line argument. Multiple
    functions have been added to this file that handle specific parts of the
    AST, such as if statements, while loops, and expressions.

    TO BE GRADED AT LEVEL E
*/

#include "ast.h"
#include "emit.h"
#include <string.h>
#include <stdlib.h>

int TEMP = 0;

char* funcName;

/* PRE: - pointer to a file
        - string that labels a MIPS instruction
        - string that contains the MIPS instruction to be executed
        - string that comments on the MIPS instruction
   POST: a line of MIPS code that prints to the given file
*/
void emit(FILE* fp, char* label, char* command, char* comment)
{
    if (strcmp("", comment) == 0)
    {
        if (strcmp("", label) == 0)
        {
            fprintf(fp, "\t%s\t\t\n", command);
        }
        else
        {
            fprintf(fp, "%s:\t%s\t\t\n", label, command);
        }
    }
    else
    {
        if (strcmp("", label) == 0)
        {
            fprintf(fp, "\t%s\t\t# %s\n", command, comment);
        }
        else
        {
            fprintf(fp, "%s:\t%s\t\t# %s\n", label, command, comment);
        }
    }
} // emit

/* PRE: - pointer to function declaration family
        - pointer to a file
   POST: MIPS code printed to the given file that facilitates
            param assignment, stack framing, etc.
*/
void emit_function(ASTnode* p, FILE* fp)
{
    char s[100];
    funcName = p -> name;
    emit(fp, p -> name, "", "function definition");

    // carve out the stack for activation record
    emit(fp, "", "move $a1, $sp", "activation record carve out copy SP");
    sprintf(s, "subi $a1, $a1, %d", p -> symbol -> offset * WSIZE);
    emit(fp, "", s, "activation record carve out copy size of function");
    emit(fp, "", "sw $ra, ($a1)", "store return address");
    sprintf(s, "sw $sp, %d($a1)", WSIZE);
    emit(fp, "", s, "store the old stack pointer");
    emit(fp, "", "move $sp, $a1", "make SP the current activation record");
    fprintf(fp, "\n\n");

    // copy parameters to the formal from registers $t0 ...
    ASTnode* iterator = p -> s1;
    int registerCounter = 0;
    while (iterator != NULL)
    {
        char s[100];
        sprintf(s, "sw $t%d, %d($sp)", registerCounter, (registerCounter + 2) * WSIZE);
        emit(fp, "", s, "copy temp to formal param");
        registerCounter += 1;
        iterator = iterator -> next;
    }

    // generate the compound statement
    EMIT_AST(p -> s2, fp);

    // create an implicit return depending if we are in main or not
    // restore RA and SP before return
    emit(fp, "", "li $a0, 0", "return has no specific value, set to 0");
    emit(fp, "", "lw $ra, ($sp)", "restore old environment RA");
    sprintf(s, "lw $sp, %d($sp)", WSIZE);
    emit(fp, "", s, "return from function, store SP");
    fprintf(fp, "\n");

    if (strcmp(p -> name, "main") == 0)
    {
        // exit the system
        emit(fp, "", "li $v0, 10", "exit from main, we are done");
        emit(fp, "", "syscall", "exit everything");
    }
    else
    {
        // jump back to caller
        emit(fp, "", "jr $ra", "jump back to caller");
    }
} // emit_function

/* PRE: - pointer to A_WRITE family
        - pointer to a file
   POST: MIPS code to generate WRITE string or write a number depending on args
*/ 
void emit_write(ASTnode* p, FILE* fp)
{
    char s[100];
    
    // if writing string
    if (p -> name != NULL)
    {
        // load address of label into $a0 and call print string
        sprintf(s, "la $a0, %s", p -> label);
        emit(fp, "", s, "the string address");
        emit(fp, "", "li $v0, 4", "about to print string");
        emit(fp, "", "syscall", "call write string");
        fprintf(fp, "\n\n");
    }
    // writing an expression instead
    else
    {
        emit_expr(p -> s1, fp); // now a0 has expression value
        emit(fp, "", "li $v0, 1", "about to print a number");
        emit(fp, "", "syscall", "call write number");
        fprintf(fp, "\n\n");
    }
} // emit_write

/* PRE: - pointer to A_READ family
        - pointer to a file
   POST: MIPS code to read in a value and place it in the VAR of READ
*/ 
void emit_read(ASTnode* p, FILE* fp)
{
    emit_var(p -> s1, fp); // $a0 will be the location of the variable
    emit(fp, "", "li $v0, 5", "about to read in a value");
    emit(fp, "", "syscall", "read in value, $v0 now has read-in value");
    emit(fp, "", "sw $v0, ($a0)", "store read-in value to memory");
    fprintf(fp, "\n\n");
} // emit_read

/* PRE: - pointer to expression family
        - pointer to a file
   POST: MIPS code that sets $a0 to the value of the expression
*/
void emit_expr(ASTnode* p, FILE* fp)
{
    char s[100];

    // base cases
    switch (p -> type)
    {
        case A_NUM:
            sprintf(s, "li $a0, %d", p -> value);
            emit(fp, "", s, "expression is a constant");
            return;
            break;
        case A_VAR:
            emit_var(p, fp); // $a0 is the memory location
            emit(fp, "", "lw $a0, ($a0)", "expression is a VAR");
            return;
            break;
        case A_EXPR:
            break;
        case A_CALL:
            emit_call(p, fp);
            return;
            break;
        default:
            printf("emit_expr switch should never be here\n");
            exit(1);
            break;
    }
    // recursive case
    emit_expr(p -> s1, fp); // $a0 ultimately holds the value of LHS
    if (p -> operator == A_UMINUS) // expression is a unary operation
    {
        emit(fp, "", "sub $a0, $0, $a0", "subtract from 0 to get negative");
    }
    else // expression is a binary operation
    {
        sprintf(s, "sw $a0, %d($sp)", p -> symbol -> offset * WSIZE); // store LHS value in the temp. space made by the outer EXPR box
        emit(fp, "", s, "store LHS value");
        emit_expr(p -> s2, fp); // $a0 now holds result of RHS
        emit(fp, "", "move $a2, $a0", "store RHS into $a2");
        sprintf(s, "lw $a0, %d($sp)", p -> symbol -> offset * WSIZE); // load stored LHS back into $a0
        emit(fp, "", s, "load stored LHS back into $a0");
        
        // at this point, $a0 is LHS and $a2 is RHS
        switch (p -> operator)
        {
            case A_PLUS:
                emit(fp, "", "add $a0, $a0, $a2", "perform addition"); // $a0 holds result of operation
                break;
            case A_MINUS:
                emit(fp, "", "sub $a0, $a0, $a2", "perform subtraction");
                break;
            case A_TIMES:
                emit(fp, "", "mult $a0, $a2", "perform multiplication");
                emit(fp, "", "mflo $a0", "store mult result in $a0");
                break;
            case A_DIVIDE:
                emit(fp, "", "div $a0, $a2", "perform division");
                emit(fp, "", "mflo $a0", "store div result in $a0");
                break;
            case A_MOD:
                emit(fp, "", "div $a0, $a2", "perform division in prep for modulo");
                emit(fp, "", "mfhi $a0", "store mod result in $a0");
                break;
            case A_LT:
                emit(fp, "", "slt $a0, $a0, $a2", "perform less-than operation");
                break;
            case A_GT:
                emit(fp, "", "slt $a0, $a2, $a0", "perform greater-than operation");
                break;
            case A_E:
                emit(fp, "", "slt $t1, $a0, $a2", "");
                emit(fp, "", "slt $t2, $a2, $a0", "");
                emit(fp, "", "nor $a0, $t1, $t2", "");
                emit(fp, "", "andi $a0, $a0, 1", "");
                break;
            case A_NE:
                emit(fp, "", "slt $t1, $a0, $a2", "");
                emit(fp, "", "slt $t2, $a2, $a0", "");
                emit(fp, "", "or $a0, $t1, $t2", "");
                emit(fp, "", "andi $a0, $a0, 1", "");
                break;
            case A_LE:
                emit(fp, "", "add $a2, $a2, 1", "");
                emit(fp, "", "slt $a0, $a0, $a2", "");
                break;
            case A_GE:
                emit(fp, "", "sub $a2, $a2, 1", "");
                emit(fp, "", "slt $a0, $a2, $a0", "");
                break;
            default:
                printf("Operator switch should not be here\n");
                exit(1);
                break;
        }
    }
} // emit_expr

/* PRE: - pointer to ASSIGN, pointer to output file
        - pointer to a file
   POST: MIPS code printed to the file that stores the RHS
            expression to the variable on the LHS
*/ 
void emit_assign(ASTnode* p, FILE* fp)
{
    char s[100];
    // evaluate LHS of assignment

    emit_expr(p -> s2, fp); // $a0 will be value of expression
    sprintf(s, "sw $a0, %d($sp)", p -> symbol -> offset * WSIZE);
    emit(fp, "", s, "store LHS into temp space created by A_ASSIGN");

    emit_var(p -> s1, fp);
    sprintf(s, "lw $a1, %d($sp)", p -> symbol -> offset * WSIZE);
    emit(fp, "", s, "");
    emit(fp, "", "sw $a1, ($a0)", "");
    fprintf(fp, "\n\n");
}

/* PRE: - pointer to VAR family
        - pointer to a file
   POST: $a0 has exact memory location of VAR
*/
void emit_var(ASTnode* p, FILE* fp)
{
    char s[100];

    // if var is an array
    if (p -> s1 != NULL)
    {
        // p is an array, so calculate internal offset with help from emit_expr
        emit_expr(p -> s1, fp);
        emit(fp, "", "move $t1, $a0", "store index expression result into $t1");
        sprintf(s, "sll $t1, $t1, %d", LOG_SIZE);
        emit(fp, "", s, "multiply expression result by 4 to get internal array offset");
    }
    else
    {
        /*
        p is NOT an array, so set internal offset to 0.
        This is like saying, "accessing a scalar is the same
        as accessing the first element (the base) of an array" (where internal offset == 0).
        This is done to simplify the following if statement in the sense
        that no extra check is needed to see whether p is global again.
        */ 
	    emit(fp, "", "li $t1, 0", "var is a scalar");
    }

    // at this point, $a1 has internal offset, 0 or not

    // if global
    if (p -> symbol -> level == 0)
    {
	    sprintf(s, "la $a0, %s", p -> name);
	    emit(fp, "", s, "emit global var (array or scalar)");
	    emit(fp, "", "add $a0, $a0, $t1", "add internal offset to base address");
    }
    else
    {
	    sprintf(s, "la $a0, %d($sp)", p -> symbol -> offset * WSIZE);
	    emit(fp, "", s, "get base address of local array or scalar");
	    emit(fp, "", "add $a0, $a0, $t1", "add internal offset to base address");
    }

} // emit_var

/* PRE: - pointer to A_WHILE family
        - pointer to a file
   POST: MIPS code printed to the file that facilitates
            while loop functionality, such as jumping to
            labels and such
*/
void emit_while(ASTnode* p, FILE* fp)
{
    char s[100];
    char* startLabel = CreateLabel();
    char* exitLabel = CreateLabel();
    emit(fp, startLabel, "", "top of while");
    emit_expr(p -> s1, fp);
    // $a0 now has result of conditional expression
    sprintf(s, "beq $a0, 0, %s", exitLabel);
    emit(fp, "", s, "exit out of while loop if condition is 0");
    EMIT_AST(p -> s2, fp); // dive into while body
    sprintf(s, "j %s", startLabel);
    emit(fp, "", s, "jump back to top of while");
    emit(fp, exitLabel, "", "end of while");
} // emit_while

/* PRE: - pointer to A_IF family
        - pointer to a file
   POST: MIPS code printed to the file that facilitates
            if statement functionality such as jumping to labels
            based of a MIPS beq instruction
*/
void emit_if(ASTnode* p, FILE* fp)
{
    char s[100];
    char* negativeState = CreateLabel();
    char* endLabel = CreateLabel();
    emit_expr(p -> s1, fp);
    // $a0 should have result of conditional expression
    sprintf(s, "beq $a0, 0, %s", negativeState);
    emit(fp, "", s, "jump to negative (else or null)");
    // expression was 1 (true) at this point so dive into positive compound statement
    EMIT_AST(p -> s2 -> s1, fp);
    sprintf(s, "j %s", endLabel);
    emit(fp, "", s, "exit if");
    emit(fp, negativeState, "", "else (or null) section");
    EMIT_AST(p -> s2 -> s2, fp);
    emit(fp, endLabel, "", "end of if");

} // emit_if

/* PRE: - pointer to A_CALL family
        - pointer to a file
   POST: MIPS code printed to the file that facilitates
            calling a function such as argument copying and jumping
            to a label using the jal MIPS instruction
*/ 
void emit_call(ASTnode* p, FILE* fp)
{
    char s[100];
    if (p -> s1 != NULL)
    {
        emit_args(p -> s1, fp);
    }

    sprintf(s, "jal %s", p -> name);
    emit(fp, "", s, "call function");
} // emit_call

/* PRE: - pointer to ARGLIST family
        - pointer to a file
   POST: MIPS code that assigns arg values to registers $t0, $t1, ...
*/
void emit_args(ASTnode* p, FILE* fp)
{
    char s[100];
    ASTnode* start = p;
    int registerCounter = 0;

    // copy arg values to their respective places in memory
    while (p != NULL)
    {
        emit_expr(p -> s1, fp);
        // $a0 is now value of arg
        sprintf(s, "sw $a0, %d($sp)", p -> symbol -> offset * WSIZE);
        emit(fp, "", s, "store arg value into space reserved for it by function");
        p = p -> next;
    }

    p = start;

    // assign args to $t0, $t1, ...
    while (p != NULL)
    {
        sprintf(s, "lw $a0, %d($sp)", p -> symbol -> offset * WSIZE);
        emit(fp, "", s, "");
        sprintf(s, "move $t%d, $a0", registerCounter);
        emit(fp, "", s, "");
        registerCounter += 1;
        p = p -> next;
    }
} // emit_args

/* PRE: - pointer to A_RETURN family
        - pointer to a file
   POST: MIPS code that facilitates function returning
*/
void emit_return(ASTnode* p, FILE* fp)
{
    char s[100];
    if (p -> s1 == NULL)
    {
        emit(fp, "", "li $a0, 0", "return has no specific value, set to 0");
    }
    else
    {
        emit_expr(p -> s1, fp);
    }
    
    emit(fp, "", "lw $ra, ($sp)", "restore old environment RA");
    sprintf(s, "lw $sp, %d($sp)", WSIZE);
    emit(fp, "", s, "return from function, store SP");
    fprintf(fp, "\n");

    if (strcmp(funcName, "main") == 0)
    {
        // exit the system
        emit(fp, "", "li $v0, 10", "exit from main, we are done");
        emit(fp, "", "syscall", "exit everything");
    }
    else
    {
        // jump back to caller
        emit(fp, "", "jr $ra", "jump back to caller");
    }
} // emit_return

/* PRE: - pointer to A_EXPRSTAT family
        - pointer to a file
   POST: MIPS code that facilitates expression statements
*/
void emit_exprstat(ASTnode* p, FILE* fp)
{
    if (p -> s1 != NULL)
    {
        emit_expr(p -> s1, fp);
    }
} // emit_exprstat

/* PRE: - pointer to top of AST tree
        - pointer to a file
   POST: MIPS code that eventually lays out the entire .asm output file
            by calling EMIT_GLOBALS, EMIT_STRINGS, etc.
*/
void EMIT(ASTnode *p, FILE *fp)
{
    if (p == NULL)
    {
        return;
    }
    if (fp == NULL)
    {
        return;
    }
    fprintf(fp, "# MIPS CODE GENERATED BY Compilers Class\n\n");
    fprintf(fp, ".data\n\n");
    EMIT_STRINGS(p, fp);
    fprintf(fp, "\n");
    fprintf(fp, ".align 2\n\n");
    EMIT_GLOBALS(p, fp);
    fprintf(fp, "\n");
    fprintf(fp, ".text\n\n");
    fprintf(fp, ".globl main\n\n");
    EMIT_AST(p, fp);
} // EMIT

/* PRE: - pointer to top of AST tree
        - pointer to a file
   POST: MIPS code printed to a file that lists the global variables
            in the .data section
*/
void EMIT_GLOBALS(ASTnode *p, FILE *fp)
{
    if (p == NULL)
    {
        return;
    }
    if (fp == NULL)
    {
        return;
    }
    if (p -> type == A_VARDEC && p -> symbol -> level == 0)
    {
        fprintf(fp, "%s: .space %d # global variable\n", p -> name, p -> symbol -> mysize * WSIZE);
    }
    EMIT_GLOBALS(p -> s1, fp);
    EMIT_GLOBALS(p -> next, fp);
} // EMIT_GLOBALS

/* PRE: - pointer to the top of the AST tree
        - pointer to a file
   POST: MIPS code that outputs all strings in the program in the
            .data section
*/
void EMIT_STRINGS(ASTnode *p, FILE *fp)
{
    if (p == NULL)
    {
        return;
    }
    if (fp == NULL)
    {
        return;
    }
    if (p -> type == A_WRITE)
    {
        if (p -> name != NULL)
        {
            p -> label = CreateLabel();
            fprintf(fp, "%s: .asciiz %s\n", p -> label, p -> name);
        }
    }
    EMIT_STRINGS(p -> s1, fp);
    EMIT_STRINGS(p -> s2, fp);
    EMIT_STRINGS(p -> next, fp);
} // EMIT_STRINGS

/* PRE: - pointer to top of AST tree
        - pointer to a file
   POST: MIPS code that handles all of the features of this CMINUS compiler
*/
void EMIT_AST(ASTnode* p, FILE* fp)
{
    if (p == NULL || fp == NULL)
    {
        return;
    }

    switch (p -> type)
    {
        case A_VARDEC:
            EMIT_AST(p -> next, fp);
            break;
        case A_FUNCTIONDEC:
            emit_function(p, fp);
            EMIT_AST(p -> next, fp);
            break;
        case A_COMPOUND:
            // no action for s1, vardec already in stack size
            EMIT_AST(p -> s2, fp);
            EMIT_AST(p -> next, fp);
            break;
        case A_WRITE:
            // deal with using helper function
            emit_write(p, fp);
            EMIT_AST(p -> next, fp);
            break;
        case A_READ:
            emit_read(p, fp);
            EMIT_AST(p -> next, fp);
            break;
        case A_ASSIGN:
            emit_assign(p, fp);
            EMIT_AST(p -> next, fp);
            break;
        case A_WHILE:
            emit_while(p, fp);
            EMIT_AST(p -> next, fp);
            break;
        case A_IF:
            emit_if(p, fp);
            EMIT_AST(p -> next, fp);
            break;
        case A_RETURN:
            emit_return(p, fp);
            break;
        case A_EXPRSTAT:
            emit_exprstat(p, fp);
            EMIT_AST(p -> next, fp);
            break;
        default:
            printf("EMIT_AST case %d not implemented\n", p -> type);
            exit(1);
    }
} // EMIT_AST

/* PRE: NONE
   POST: string in the format of _Lxxx where xxx represents a number determined
            by a global counter
*/
char* CreateLabel()
{
    char buf[100];
    char *s;
    sprintf(buf, "_L%d", TEMP++);
    s = strdup(buf);
    return s;
} // CreateLabel