#ifndef AST_PRINT_H
#define AST_PRINT_H

#include "ast.h"
#include "parser.tab.h"

void print_prog(FILE * out, Prog *  p); 
void print_block(FILE * out, Block * b); 
void print_cmds(FILE * out, Cmds * c); 
void print_dec(FILE * out, Dec * d);
void print_stat(FILE * out, Stat * s);  
void print_expr(FILE * out, Expr * e);
void print_type(FILE * out, Type * t);

#endif
