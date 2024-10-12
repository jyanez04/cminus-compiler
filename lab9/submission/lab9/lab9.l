/*              
    Jacob Yanez
    Lab 9: MIPS Code From AST
    May 3, 2024

    This LEX file details the tokens for CMINUS it will give to 
    YACC for parsing.
*/

%{

// keeps track of current line number in file
int lineno = 1;

// enables/disables printing of verbose debug statments
int mydebug = 0;
#include "ast.h"
#include "y.tab.h"

%}


%%

"int"       {return (T_INT);}
"void"      {return (T_VOID);}
"read"      {return (T_READ);}
"write"     {return (T_WRITE);}
"<"         {return (T_LT);}
">"         {return (T_GT);}
"<="        {return (T_LE);}
">="        {return (T_GE);}
"=="        {return (T_E);}
"!="        {return (T_NE);}
"+"         {return (T_PLUS);}
"-"         {return (T_SUB);}
"*"         {return (T_MULT);}
"/"         {return (T_DIV);}
"%"         {return (T_MOD);}
"if"        {return (T_IF);}
"else"      {return (T_ELSE);}
"while"     {return (T_WHILE);}
"return"    {return (T_RETURN);}

[a-zA-Z][a-zA-Z0-9_]*   {
                            // variable names, function names, etc.
                            yylval.string=strdup(yytext);
                            return(T_ID);
                        }

[0-9][0-9]*	            { 
                            yylval.value=atoi((const char *)yytext);
                            return(T_NUM);
                        }

\".*\"                  {
                            yylval.string = strdup(yytext);
                            return(T_STRING);
                        }

\/\/.*                  {/*for detecting comments*/}

[ \t]                   {/*for detecting whitespace*/}

[;,=\-\[\]+*{}/%&|()] 	{return (*yytext);}

\n 		                {/*keeping track of line number*/ lineno++;}

%%

/*
* The last function lex calls at the end of the file. Returns 1 to finish the lex
* portion of the lab
*/
int yywrap(void)
{ return 1;}


