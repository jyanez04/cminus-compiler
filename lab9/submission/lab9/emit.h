/*
    Lab 9 Header File
    Jacob Yanez
    May 3, 2024

    This header file declares all of the functions used in emit.c
*/

#ifndef EMIT_H
#define EMIT_H
#include "ast.h"

#define WSIZE 4
#define LOG_SIZE 2

void EMIT(ASTnode *p, FILE *fp);
void EMIT_GLOBALS(ASTnode *p, FILE *fp);
void EMIT_STRINGS(ASTnode *p, FILE *fp);
void EMIT_AST(ASTnode* p, FILE* fp);

void emit_expr(ASTnode* p, FILE* fp);
void emit_read(ASTnode* p, FILE* fp);
void emit_var(ASTnode* p, FILE* fp);
void emit_function(ASTnode* p, FILE* fp);
void emit_while(ASTnode* p, FILE* fp);
void emit_if(ASTnode* p, FILE* fp);
void emit_call(ASTnode* p, FILE* fp);
void emit_args(ASTnode* p, FILE* fp);
void emit_exprstat(ASTnode* p, FILE* fp);
void emit_return(ASTnode* p, FILE* fp);
void emit(FILE* fp, char* label, char* command, char* comment);

char* CreateLabel();

#endif