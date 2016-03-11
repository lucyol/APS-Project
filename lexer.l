%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
%}

num [0-9]+
ident [a-z][a-zA-Z]+

%%

{num}   { yylval.entier = atoi(yytext); return(NUM);}
{ident} { yylval.str = strdup(yytext); return(IDENT);}

"true" {return (TRUE);}
"false" {return (FALSE);}


"add" {return(ADD);}
"sub" {return(SUB);}
"mul" {return(MUL);}
"div" {return(DIV);}

"lt" {return(LT);}
"not" {return(NOT);}
"and" {return(AND);}
"or" {return(OR);}
"eq" {return(EQ);}

"SET" {return(SET);}
"WHILE" {return(WHILE);}
"IF" {return(IF);}

"CONST" {return(CONST);}
"VAR" {return(VAR);}

[ \n\t] {}

. {return yytext[0];}

%%

