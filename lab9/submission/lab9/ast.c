/*
    Jacob Yanez
    Lab 9: MIPS Code From AST
    May 3, 2024

    This code is a utility program used to define/create an AST node and  
    print out (display structure of) the AST. Implemented PT() function and 
    ASTprint() function as well. Also implemented a function that ensures
    the formal parameters and the arguments of a call of the same function
    have the same structure and data types.
*/

#include <stdio.h>
#include <malloc.h>
#include "ast.h" 


/* uses malloc to create an ASTnode and passes back the heap address of the newly created node */
//  PRE:    AST Node Type
//  POST:   PTR To heap memory and ASTnode set and all other pointers set to NULL
ASTnode *ASTCreateNode(enum ASTtype mytype)

{
    ASTnode *p;
    p = (ASTnode *)malloc(sizeof(ASTnode));
    p -> type = mytype;
    p -> s1 = NULL;
    p -> s2 = NULL;
    p -> next = NULL;
    p -> value = 0;
    return(p);
}

/*  Helper function to print tabbing */
//PRE:  Number of spaces desired
//POST: Number of spaces printed on standard output

void PT(int howmany)
{
    int i;
    for (i = 0; i < howmany; i++)
    {
        printf(" ");
    }
}

//  PRE:    A declaration type
//  POST:   A character string that is the name of the type
//  Typically used in formatted printing
char * ASTtypeToString(enum ASTtype mytype)
{
    switch (mytype)
    {
        case A_INTTYPE:
            return "INT";
        case A_VOIDTYPE:
            return "VOID";
        default:
            return "ERROR";
    }
}



/*  Print out the abstract syntax tree */
// PRE:   PRT to an AST tree
// POST:  indented output using AST order printing with indentation
void ASTprint(int level, ASTnode *p)
{
   int i;
   if (p == NULL) return;
   else
    {
        // switch block figures out what tree node we are currently at in our traversal
        switch (p -> type) {
            case A_VARDEC:
                PT(level);
                printf("VARIABLE %s ", ASTtypeToString(p -> my_data_type));
                /*
                if vardec's value is not -1, then the declaration is an array -- so
                display the variable with [] next to the ID, like ID[]
                */
                if(p -> value > 0)
                {
                    printf("%s[%d] level %d offset %d\n", p -> name, p -> value, p -> symbol -> level, p -> symbol -> offset);
                }
                // otherwise just print ID of the variable
                else
                {
                    printf("%s level %d offset %d\n", p -> name, p -> symbol -> level, p -> symbol -> offset);
                }
                ASTprint(level, p -> s1); // next variable in declaration list (on same line)
                ASTprint(level, p -> next); // next statement
                break;
            case A_FUNCTIONDEC:
                PT(level);
                printf("FUNCTION %s %s level %d offset %d\n", ASTtypeToString(p -> my_data_type), p -> name, p -> symbol -> level, p -> symbol -> offset);
                ASTprint(level + 1, p -> s1); // parameters
                ASTprint(level + 1, p -> s2); // function block (compound statement)
                ASTprint(level, p -> next);
                break;
            case A_COMPOUND:
                PT(level);
                printf("COMPOUND STATEMENT\n");
                ASTprint(level + 1, p -> s1); // local declarations
                ASTprint(level + 1, p -> s2); // statement list
                ASTprint(level, p -> next);
                break;
            case A_WRITE:
                PT(level);
                if (p -> name != NULL)
                {
                    // writing a simple string
                    printf("WRITE string %s\n", p -> name);
                }
                else
                {
                    // writing an expression
                    printf("WRITE expression\n");
                    ASTprint(level + 1, p -> s1); // descend down expression tree
                }
                ASTprint(level, p -> next); // next statement
                break;
            case A_NUM:
                PT(level);
                printf("NUMBER value %d\n", p -> value);
                break;
            case A_EXPR:
                PT(level);
                printf("EXPRESSION operator ");
                // switch block decides what operator to print out
                switch (p -> operator)
                {
                    case A_PLUS:
                        printf("+\n");
                        break;
                    case A_MINUS:
                        printf("-\n");
                        break;
                    case A_TIMES:
                        printf("*\n");
                        break;
                    case A_DIVIDE:
                        printf("/\n");
                        break;
                    case A_MOD:
                        printf("%\n");
                        break;
                    case A_LE:
                        printf("<=\n");
                        break;
                    case A_LT:
                        printf("<\n");
                        break;
                    case A_GT:
                        printf(">\n");
                        break;
                    case A_GE:
                        printf(">=\n");
                        break;
                    case A_E:
                        printf("==\n");
                        break;
                    case A_NE:
                        printf("!=\n");
                        break;
                    case A_UMINUS:
                        printf("UNARY MINUS\n");
                        break;
                    default:
                        printf("unknown operator in expression in ASTprint\n");
                }
                ASTprint(level + 1, p -> s1); // left side of expression
                ASTprint(level + 1, p -> s2); // right side of expression
                ASTprint(level, p -> next); // next statement
                break;
            case A_PARAM:
                PT(level);
                printf("PARAMETER %s ", ASTtypeToString(p -> my_data_type));
                /*
                if param node value is -1, then the parameter is an array
                */
                if (p -> value == -1)
                {
                    printf("%s[] level %d offset %d\n", p -> name, p -> symbol -> level, p -> symbol -> offset);
                }
                // otherwise, just print the parameter's name
                else
                {
                    printf("%s level %d offset %d\n", p -> name, p -> symbol -> level, p -> symbol -> offset);
                }
                ASTprint(level, p -> next); // next parameter
                break;
            case A_READ:
                PT(level);
                printf("READ\n");
                ASTprint(level + 1, p -> s1); // expand on what is being read
                ASTprint(level, p -> next); // next statement
                break;
            case A_VAR:
                PT(level);
                printf("VAR %s level %d offset %d\n", p -> name, p -> symbol -> level, p -> symbol -> offset);
                /*
                if the VAR contains an expression within its square brackets,
                print brackets and the expression within
                */
                if (p -> s1 != NULL)
                {
                    PT(level + 1);
                    printf("[\n");
                    ASTprint(level + 2, p -> s1); // expression
                    PT(level + 1);
                    printf("]\n");
                }
                break;
            case A_CALL:
                PT(level);
                printf("FUNCTION CALL %s\n", p -> name);
                PT(level + 1);
                printf("(\n");
                ASTprint(level + 2, p -> s1); // call for arguments
                PT(level + 1);
                printf(")\n");
                break;
            case A_ARG:
                PT(level);
                printf("CALL ARGUMENT\n");
                ASTprint(level + 1, p -> s1); // expression for argument
                ASTprint(level, p -> next); // next argument
                break;
            case A_ASSIGN:
                PT(level);
                printf("ASSIGNMENT\n");
                ASTprint(level + 1, p -> s1); // traverse var tree
                ASTprint(level + 1, p -> s2); // traverse expression tree
                ASTprint(level, p -> next); // next statement
                break;
            case A_RETURN:
                PT(level);
                // if returning some kind of expression
                if (p -> s1 != NULL)
                {
                    printf("RETURN expression\n");
                    ASTprint(level + 1, p -> s1);
                }
                // if returning plainly
                else
                {
                    printf("RETURN\n");
                }
                ASTprint(level, p -> next); // next statement
                break;
            case A_WHILE:
                PT(level);
                printf("WHILE\n");
                ASTprint(level + 1, p -> s1); // traverse expression (conditional statement)
                PT(level + 1);
                printf("WHILE body\n");
                ASTprint(level + 2, p -> s2); // traverse while body (compound statement)
                ASTprint(level, p -> next); // next statement
                break;
            case A_EXPRSTAT:
                PT(level);
                printf("EXPRESSION STATEMENT\n");
                ASTprint(level + 1, p -> s1); // traverse expression
                ASTprint(level, p -> next); // next statement
                break;
            case A_IF:
                PT(level);
                printf("IF statement\n");
                ASTprint(level + 1, p -> s1); // traverse expression (conditional statement)
                PT(level + 1);
                printf("IF body\n");
                ASTprint(level + 2, p -> s2 -> s1); // traverse positive if body
                // if there is an else statement
                if (p -> s2 -> s2 != NULL)
                {
                    PT(level + 1);
                    printf("ELSE body\n");
                    ASTprint(level + 2, p -> s2 -> s2); // traverse negative (else) body
                }
                ASTprint(level, p -> next); // next statement
                break;
            default:
                printf("unknown AST Node type %d in ASTprint\n", p -> type);
       }
    }
}

/*Ensures that the arguments to a call of a function match the structure (order and length)
and types of the formal parameters of the same function*/
// PRE: pointers to the arg tree and param tree
// POST: 1 if args and params are the same, 0 if not
int checkParams(ASTnode *args, ASTnode *params)
{
    if (args == NULL && params == NULL)
    {
        return 1;
    }
    if (args == NULL || params == NULL)
    {
        return 0;
    }
    // neither arg or param is null
    if (args -> s1 -> my_data_type != params -> my_data_type)
    {
        return 0;
    }
    return 1 * checkParams(args -> next, params -> next);
}


/* dummy main program so I can compile for syntax error independently   
main()
{
}
/* */
