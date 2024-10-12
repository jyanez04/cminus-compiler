%{
/* 
    Jacob Yanez
   	Lab 9: MIPS Code From AST
   	May 3, 2024

    This YACC file lays out the grammar for the CMINUS language. There
    was syntax directed semantic action added to each production rule
    which creates nodes to construct an Abstract Syntax Tree (AST) for 
    a given CMINUS program. Additionally, there has been some semantic
    action added to support a rudimentary symbol table implementation -- 
    mainly in productions that contain token T_INT and in productions that
    have any sort of types or calculations involved.
*/


/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtable.h"
#include "emit.h"

ASTnode *PROGRAM;

int yylex();



/* added for use in yacc rules below, particularly for stopping the 
*  printing of verbose debug statements
*/
extern int mydebug;

// counter that keeps track of the current line number
extern int lineno;

int LEVEL = 0; // knowing how "deep" we are in blocks
int OFFSET = 0; // accumulating needed runtime space
int G_OFFSET = 0; // accumulation global variable offset
int MAX_OFFSET = 0; // largest offset needed for the current function

// prints out any errors that may occur during parsing, includes line number
void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("YACC PARSE ERROR: %s on line number %d\n", s, lineno);
}


%}

%start Program

%union {
    int value;
    char * string;
    ASTnode *node;
    enum AST_MY_DATA_TYPE d_type;
    enum AST_OPERATORS operator;
}

%token <value> T_NUM
%token <string> T_ID
%token <string> T_STRING
%token T_INT
%token T_VOID
%token T_READ T_WRITE
%token T_LT T_GT T_LE T_GE T_E T_NE
%token T_PLUS T_SUB
%token T_MULT T_DIV T_MOD
%token T_IF T_ELSE
%token T_WHILE
%token T_RETURN

%type <node> Declaration_List Declaration Var_Declaration Var_List Fun_Declaration
%type <node> Params Compound_Stmt Local_Declarations Statement_List Statement
%type <node> Write_Stmt Expression Simple_Expression Additive_Expression Term
%type <node> Factor Var Call Param_List Param Read_Stmt Args Arg_List Assignment_Stmt
%type <node> Return_Stmt Iteration_Stmt Expression_Stmt Selection_Stmt
%type <d_type> Type_Specifier
%type <operator> Addop Relop Multop

%%	/* end specs, begin rules */

Program : Declaration_List  {PROGRAM = $1;}
        ;

Declaration_List    : Declaration   {$$ = $1;}
                    | Declaration Declaration_List
                        {
                            $$ = $1;
                            $$ -> next = $2;
                        }
                    ;

Declaration : Var_Declaration   {$$ = $1;}
            | Fun_Declaration   {$$ = $1;}
            ;

Var_Declaration : Type_Specifier Var_List ';'
                    {
                        // need to update all elements to the list to the type
                        // populate s1 connected list with the defined type
                        ASTnode *p = $2;
                        while (p != NULL)
                        {
                            p -> my_data_type = $1;
                            
                            // if variable is already in the symbol table, BARF
                            if (Search(p -> name, LEVEL, 0) != NULL)
                            {
                                yyerror(p -> name);
                                yyerror("Symbol already defined");
                                exit(1);
                            }
                            if (p -> value == 0)
                            {
                                // if variable is a scalar
                                p -> symbol = Insert(p -> name, p -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                                OFFSET += 1;
                            }
                            else
                            {
                                // if variable is an array
                                p -> symbol = Insert(p -> name, p -> my_data_type, SYM_ARRAY, LEVEL, p -> value, OFFSET);
                                OFFSET += p -> value;
                            }
                            p = p -> s1;
                        }
                        $$ = $2;
                    }
                ;

    /**ASTCreateNode(enum ASTtype mytype)*/
Var_List    : T_ID 
                    {
                        $$ = ASTCreateNode(A_VARDEC);
                        $$ -> name = $1;
                        // value is -1 if not an array
                    }
            | T_ID '[' T_NUM ']'    
                    {  
                        $$ = ASTCreateNode(A_VARDEC);
                        $$ -> name = $1;
                        $$ -> value = $3;
                    }
            | T_ID ',' Var_List 
                    {
                        $$ = ASTCreateNode(A_VARDEC);
                        $$ -> name = $1;
                        $$ -> s1 = $3;
                        // value is -1 if not an array
                    }
            | T_ID '[' T_NUM ']' ',' Var_List   
                    {
                        $$ = ASTCreateNode(A_VARDEC);
                        $$ -> name = $1;
                        $$ -> value = $3;
                        $$ -> s1 = $6;
                    }
            ;

Type_Specifier  : T_INT     {$$ = A_INTTYPE;}
                | T_VOID    {$$ = A_VOIDTYPE;}
                ;

Fun_Declaration : Type_Specifier T_ID
                    {
                        // check to see if function is defined in symbol table
                        if (Search($2, LEVEL, 0) != NULL)
                        {
                            // function is already defined, BARF
                            yyerror($2);
                            yyerror("Function name already in use");
                            exit(1);
                        }
                        // function name is not in symbol table, insert it
                        Insert($2, $1, SYM_FUNCTION, LEVEL, 0, 0);

                        // setup offsets before entering function
                        G_OFFSET = OFFSET;
                        OFFSET = 2;
                        MAX_OFFSET = OFFSET;
                    } 
                    '(' Params ')' 
                    {
                        /* obtain symbol table entry for current function and declare
                        its param values to be those pointed to by Params
                        */
                        Search($2, LEVEL, 0) -> fparms = $5;
                    }
                    Compound_Stmt
                    {
                        $$ = ASTCreateNode(A_FUNCTIONDEC);
                        $$ -> name = $2;
                        $$ -> my_data_type = $1;
                        $$ -> s1 = $5;
                        $$ -> s2 = $8;

                        $$ -> symbol = Search($2, LEVEL, 0);

                        /* officially set offset of current function to the total that was
                        calculated throughout the offset
                        */
                        $$ -> symbol -> offset = MAX_OFFSET;

                        OFFSET = G_OFFSET; // resets offset for global variables
                    }
                ;

Params  : T_VOID        {$$ = NULL;}
        | Param_List    {$$ = $1;}
        ;

Param_List  : Param {$$ = $1;}
            | Param ',' Param_List
                {
                    $$ = $1;
                    $$ -> next = $3;
                }
            ;

Param   : Type_Specifier T_ID 
                {
                    // if param with same name as another is declared for a function
                    if (Search($2, LEVEL + 1, 0) != NULL)
                    {
                        yyerror($2);
                        yyerror("Duplicate parameter in function definition");
                        exit(1);
                    }

                    $$ = ASTCreateNode(A_PARAM);
                    $$ -> name = $2;
                    $$ -> my_data_type = $1;

                    $$ -> symbol = Insert($$ -> name, $$ -> my_data_type, SYM_SCALAR, LEVEL + 1, 1, OFFSET);
                    OFFSET += 1;
                }
        | Type_Specifier T_ID '[' ']' 
                        {
                            if (Search($2, LEVEL + 1, 0) != NULL)
                            {
                                yyerror($2);
                                yyerror("Duplicate parameter in function definition");
                                exit(1);
                            }

                            $$ = ASTCreateNode(A_PARAM);
                            $$ -> name = $2;
                            $$ -> my_data_type = $1;
                            // value is -1 if parameter is an array
                            $$ -> value = -1;

                            $$ -> symbol = Insert($$ -> name, $$ -> my_data_type, SYM_ARRAY, LEVEL + 1, 1, OFFSET);
                            OFFSET += 1;
                        }
        ;

Compound_Stmt   : '{' {LEVEL++;}
                    Local_Declarations Statement_List '}' 
                    {
                        $$ = ASTCreateNode(A_COMPOUND);
                        $$ -> s1 = $3;
                        $$ -> s2 = $4;
                        // display state of symbol table after exiting the function
                        if (mydebug)
                        {
                            Display();
                        }
                        if (OFFSET > MAX_OFFSET)
                        {
                            MAX_OFFSET = OFFSET;
                        }

                        // delete symbols that were defined under this function's scope
                        OFFSET -= Delete(LEVEL);
                        LEVEL--;
                    }
                ;

Local_Declarations  : /*empty*/ {$$ = NULL;}
                    | Var_Declaration Local_Declarations
                        {
                            $$ = $1;
                            $$ -> next = $2;
                        }
                    ;

Statement_List  : /*empty*/ {$$ = NULL;}
                | Statement Statement_List
                    {
                        $$ = $1;
                        $$ -> next = $2;
                    }
                ;

Statement   : Expression_Stmt   {$$ = $1;}
            | Compound_Stmt     {$$ = $1;}
            | Selection_Stmt    {$$ = $1;}
            | Iteration_Stmt    {$$ = $1;}
            | Assignment_Stmt   {$$ = $1;}
            | Return_Stmt       {$$ = $1;}
            | Read_Stmt         {$$ = $1;}
            | Write_Stmt        {$$ = $1;}
            ;

Expression_Stmt : Expression ';'    
                    {
                        $$ = ASTCreateNode(A_EXPRSTAT);
                        $$ -> s1 = $1;
                    }
                | ';' {$$ = ASTCreateNode(A_EXPRSTAT);}
                ;

Expression  : Simple_Expression {$$ = $1;}
            ;

Simple_Expression   : Additive_Expression   {$$ = $1;}
                    | Additive_Expression Relop Additive_Expression
                        {
                            if ($1 -> my_data_type != $3 -> my_data_type)
                            {
                                yyerror("Type mismatch in comparison");
                                exit(1);
                            }
                            $$ = ASTCreateNode(A_EXPR);
                            $$ -> s1 = $1;
                            $$ -> s2 = $3;
                            $$ -> operator = $2;
                            // synthesize data type of expression
                            $$ -> my_data_type = $1 -> my_data_type;
                            $$ -> name = CreateTemp();
                            // insert temp symbol into symbol table
                            $$ -> symbol = Insert($$ -> name, $1 -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                            OFFSET += 1;
                        }
                    ;

Relop   : T_LE  {$$ = A_LE;}
        | T_LT  {$$ = A_LT;}
        | T_GT  {$$ = A_GT;}
        | T_GE  {$$ = A_GE;}
        | T_E   {$$ = A_E;}
        | T_NE  {$$ = A_NE;}
        ;

Additive_Expression : Term  {$$ = $1;}
                    | Additive_Expression Addop Term
                    {
                        if ($1 -> my_data_type != $3 -> my_data_type)
                        {
                            yyerror("Type mismatch in calculation");
                            exit(1);
                        }
                        $$ = ASTCreateNode(A_EXPR);
                        $$ -> s1 = $1;
                        $$ -> s2 = $3;
                        $$ -> operator = $2;
                        // synthesize data type of expression
                        $$ -> my_data_type = $1 -> my_data_type;
                        // create temporary symbol to store result of expression
                        $$ -> name = CreateTemp();
                        // insert temp symbol into symbol table
                        $$ -> symbol = Insert($$ -> name, $1 -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                        OFFSET += 1;
                    }
                    ;

Addop   : T_PLUS    {$$ = A_PLUS;}
        | T_SUB     {$$ = A_MINUS;}
        ;

Term    : Factor                {$$ = $1;}
        | Term Multop Factor    
            {
                if ($1 -> my_data_type != $3 -> my_data_type)
                {
                    yyerror("Type mismatch in calculation");
                    exit(1);
                }
                $$ = ASTCreateNode(A_EXPR);
                $$ -> s1 = $1;
                $$ -> s2 = $3;
                $$ -> operator = $2;
                // synthesize data type of expression
                $$ -> my_data_type = $1 -> my_data_type;
                // create temporary symbol to store result of expression
                $$ -> name = CreateTemp();
                // insert temp symbol into symbol table
                $$ -> symbol = Insert($$ -> name, $1 -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                OFFSET += 1;
            }
        ;

Multop  : T_MULT    {$$ = A_TIMES;}
        | T_DIV     {$$ = A_DIVIDE;}
        | T_MOD     {$$ = A_MOD;}
        ;

Factor  : '(' Expression ')'    {$$ = $2;}
        | T_NUM
            {
                $$ = ASTCreateNode(A_NUM);
                $$ -> value = $1;
                // data type of numbers will be int
                $$ -> my_data_type = A_INTTYPE;
            }
        | Var                   {$$ = $1;}
        | Call                  {$$ = $1;}
        | T_SUB Factor          
            {
                // treat neg. nums. as expression with one argument
                $$ = ASTCreateNode(A_EXPR);
                $$ -> operator = A_UMINUS;
                $$ -> s1 = $2;
            }
        ;

Call    : T_ID '(' Args ')' 
                {
                    struct SymbTab *p;
                    p = Search($1, 0, 0);
                    if (p == NULL)
                    {
                        // called function that is not defined
                        yyerror($1);
                        yyerror("Called function that is not defined");
                        exit(1);
                    }
                    // name checks out, but is it a function?
                    if (p -> SubType != SYM_FUNCTION)
                    {
                        yyerror($1);
                        yyerror("is not defined as a function");
                        exit(1);
                    }
                    
                    /* verify formal parameters and actual arguments are
                    the same type and length*/ 

                    if (checkParams($3, p -> fparms) == 0)
                    {
                        yyerror($1);
                        yyerror("arguments do not match declared formal parameters");
                        exit(1);
                    }

                    $$ = ASTCreateNode(A_CALL);
                    $$ -> name = $1;
                    $$ -> s1 = $3;
                    $$ -> symbol = p;
                    // declare type of function call (for type checking)
                    $$ -> my_data_type = p -> Declared_Type;
                }
        ;

Args    : /*empty*/ {$$ = NULL;}
        | Arg_List  {$$ = $1;}
        ;

Arg_List    : Expression
                        {
                            $$ = ASTCreateNode(A_ARG);
                            $$ -> s1 = $1;
                            // create temp symbol for the argument and store it in the symbol table
                            $$ -> name = CreateTemp();
                            $$ -> symbol = Insert($$ -> name, $1 -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                            OFFSET += 1;
                        }
            | Expression ',' Arg_List
                        {
                            $$ = ASTCreateNode(A_ARG);
                            $$ -> s1 = $1;
                            $$ -> next = $3;
                            // create temp symbol for the argument and store it in the symbol table
                            $$ -> name = CreateTemp();
                            $$ -> symbol = Insert($$ -> name, $1 -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                            OFFSET += 1;
                        }
            ;

Selection_Stmt  : T_IF '(' Expression ')' Statement
                    {
                        // s2 is a node that "contains" the if body and the else body
                        $$ = ASTCreateNode(A_IF);
                        $$ -> s1 = $3;
                        $$ -> s2 = ASTCreateNode(A_IFBODY);
                        $$ -> s2 -> s1 = $5; // if body
                        // no else body
                    }
                | T_IF '(' Expression ')' Statement T_ELSE Statement
                    {
                        $$ = ASTCreateNode(A_IF);
                        $$ -> s1 = $3;
                        $$ -> s2 = ASTCreateNode(A_IFBODY);
                        $$ -> s2 -> s1 = $5; // if body
                        // else body is assigned to s2 -> s2
                        $$ -> s2 -> s2 = $7;
                    }
                ;

Iteration_Stmt  : T_WHILE '(' Expression ')' Statement
                    {
                        $$ = ASTCreateNode(A_WHILE);
                        $$ -> s1 = $3;
                        $$ -> s2 = $5;
                    }
                ;

Return_Stmt : T_RETURN ';' {$$ = ASTCreateNode(A_RETURN);}
            | T_RETURN Expression ';'
                {
                    $$ = ASTCreateNode(A_RETURN);
                    $$ -> s1 = $2;
                }
            ;

Read_Stmt   : T_READ Var ';' 
                {
                    $$ = ASTCreateNode(A_READ);
                    $$ -> s1 = $2;
                }
            ;

Write_Stmt  : T_WRITE Expression ';'
                {
                    $$ = ASTCreateNode(A_WRITE);
                    $$ -> s1 = $2;
                }
            | T_WRITE T_STRING ';'
                {
                    $$ = ASTCreateNode(A_WRITE);
                    $$ -> name = $2;
                }
            ;

Assignment_Stmt : Var '=' Simple_Expression ';'
                    {
                        if ($1 -> my_data_type != $3 -> my_data_type)
                        {
                            yyerror("Conflicting types at assignment statment");
                            exit(1);
                        }
                        $$ = ASTCreateNode(A_ASSIGN);
                        $$ -> s1 = $1;
                        $$ -> s2 = $3;
                        $$ -> name = CreateTemp();
                        $$ -> symbol = Insert($$ -> name, $1 -> my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
                        OFFSET += 1;
                    }
                ;

Var : T_ID {
                struct SymbTab *p;
                p = Search($1, LEVEL, 1);
                if (p == NULL)
                {
                    // reference to a symbol NOT in table
                    yyerror($1);
                    yyerror("Symbol used but not defined");
                    exit(1);
                }
                if (p -> SubType != SYM_SCALAR)
                {
                    // reference to a non-scalar variable
                    yyerror($1);
                    yyerror("Incorrect symbol type usage");
                    exit(1);
                }
                $$ = ASTCreateNode(A_VAR);
                $$ -> name = $1;
                $$ -> symbol = p;
                $$ -> my_data_type = p -> Declared_Type;
            }
    | T_ID '[' Expression ']' 
            {  
                struct SymbTab *p;
                p = Search($1, LEVEL, 1);
                if (p == NULL)
                {
                    // reference to a symbol NOT in table
                    yyerror($1);
                    yyerror("Symbol used but not defined");
                    exit(1);
                }
                if (p -> SubType != SYM_ARRAY)
                {
                    // reference to a non-scalar variable
                    yyerror($1);
                    yyerror("Incorrect symbol type usage");
                    exit(1);
                }
                $$ = ASTCreateNode(A_VAR);
                $$ -> name = $1;
                $$ -> s1 = $3;
                $$ -> symbol = p;
                $$ -> my_data_type = p -> Declared_Type;
            }
    ;

%%	/* end of rules, start of program */

/*
* call main parsing function used by yacc
*/
int main(int argc, char *argv[])
{
    FILE *fp;
    int i;
    char s[100];

    // option -d turn on debug
    // option -o output file name
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0)
        {
            mydebug = 1;
        }
        if (strcmp(argv[i], "-o") == 0)
        {
            strcpy(s, argv[i + 1]);
            strcat(s, ".asm");
            //printf("File name is %s\n", s);
        }
    }

    fp = fopen(s, "w");
    if (fp == NULL)
    {
        printf("cannot open %s\n", s);
        exit(1);
    }

    yyparse();

    if (mydebug)
    {
        printf("Finished parsing\n");
    }
    
    if (mydebug) 
    {
        Display(); // shows our global variables and functions
    }

    if (mydebug)
    {
        printf("\n\n AST PRINT \n\n");
    }

    if (mydebug)
    {
        ASTprint(0, PROGRAM);
    }
    EMIT(PROGRAM, fp);
}
