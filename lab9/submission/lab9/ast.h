/*
   Jacob Yanez
   Lab 9: MIPS Code From AST
   May 3, 2024

   This is a header file that contains the definitions of the many 
   structures used in the AST construction process. Enumerates AST 
   node types, operators used in expressions, data types used in the 
   AST, and several methods used in displaying the AST.
*/

#include <stdio.h>
#include <malloc.h>
#include "symtable.h"

#ifndef AST_H
#define AST_H
int mydebug;

/* define the enumerated types for the AST.  This is used to tell us what 
sort of production rule we came across */

enum ASTtype {
    A_FUNCTIONDEC,
    A_VARDEC,
    A_COMPOUND,
    A_WRITE,
    A_NUM,
    A_EXPR,
    A_PARAM,
    A_VAR,
    A_READ,
    A_CALL,
    A_ARG,
    A_ASSIGN,
    A_RETURN,
    A_WHILE,
    A_IF,
    A_EXPRSTAT,
    A_IFBODY
};

// Math Operators

enum AST_OPERATORS {
   A_PLUS,
   A_MINUS,
   A_TIMES,
   A_DIVIDE,
   A_MOD,
   A_LE,
   A_LT,
   A_GT,
   A_GE,
   A_E,
   A_NE,
   A_UMINUS
};

enum AST_MY_DATA_TYPE {
   A_INTTYPE,
   A_VOIDTYPE
};

/* define a type AST node which will hold pointers to AST structs that will
   allow us to represent the parsed code 
*/

typedef struct ASTnodetype
{
     enum ASTtype type;
     enum AST_OPERATORS operator;
     char * name;
     int value;
     enum AST_MY_DATA_TYPE my_data_type;
     // added pointer to the AST node's respective symbol table entry
     struct SymbTab *symbol;
     char *label;
     struct ASTnodetype *s1,*s2, *next ; /* used for holding IF and WHILE components -- not very descriptive */
} ASTnode;


/* uses malloc to create an ASTnode and passes back the heap address of the newley created node */
ASTnode *ASTCreateNode(enum ASTtype mytype);

void PT(int howmany);


/*  Print out the abstract syntax tree */
void ASTprint(int level,ASTnode *p);

int checkParams(ASTnode *args, ASTnode *params);

#endif // of AST_H
