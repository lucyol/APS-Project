#include <stdlib.h>
#include <stdio.h>

#include "ast_print.h"


void print_prog(FILE * out, Prog * prog){
  print_block(out,prog->block);  
}

void print_block(FILE * out, Block * b){
  fprintf(out,"["); 
  print_cmds(out,b->cmds); 
  fprintf(out,"]");
}

void print_cmds(FILE * out, Cmds * c){
  switch(c->type){
  case T_STAT: 
    print_stat(out, c->stat); 
    break; 
  case T_STATCMDS: 
    print_stat(out, c->statCmds.stat); 
    fprintf(out, ","); 
    print_cmds(out, c->statCmds.cmds); 
    break; 
  case T_DECCMDS:
    print_dec(out, c->decCmds.dec); 
    fprintf(out, ","); 
    print_dec(out, c->decCmds.cmds);  
    break; 
  default: 
    break; 
  }
  fprintf(out, ")"); 
}

void print_dec(FILE * out, Dec * d){
  switch(d->type){
  case T_VAR : 
    fprintf(out, "var(%s,",d->var.ident); 
    print_type(out, d->var.type); 
    break; 
  case T_CONST: 
    fprintf(out,"const(%s,", d->cons.ident); 
    print_type(out, d->cons.type); 
    print_expr(out, d->cons.expr);
    break; 
  default: 
    break;   
  } 
  fprintf(out,")"); 
}

void print_stat(FILE * out, Stat * s){

  switch(s->type){
  case T_SET : 
    fprintf(out, "set(%s,", s->set.ident); 
    print_expr(out, s->set.expr); 
    break; 
  case T_IF: 
    fprintf(out, "if("); 
    print_expr(out, s->alt.cond); 
    fprintf(out, ","); 
    print_block(out, s->alt.b1); 
    fprintf(out, ","); 
    print_block(out, s->alt.b2); 
    break; 
  case T_WHILE:
    fprintf(out, "while("); 
    print_expr(out, s->loop.cond); 
    fprintf(out, ","); 
    print_block(out, s->loop.b); 
    break; 
  default: 
    break; 
  }
  fprintf(out, ")"); 
}

void print_expr(FILE * out, Expr * e){
  switch(e->type){
  case T_BOOL:
    if(e->bool == true)
      fprintf(out, "true");
    else
      fprintf(out, "false"); 
    break; 
  case T_NUM: 
    fprintf(out, "%d", e->num); 
    break; 
  case T_IDENT: 
    fprintf(out, "%s", e->ident); 
    break; 
  case T_UNOP: 
    fprintf(out, "app(not,["); 
    print_expr(out, e->unOp.expr); 
    fprintf("])"); 
    break; 
  case T_BINOP: 
    fprintf(out, "app("); 
    switch(e->binOp.op){
    case ADD: 
      fprintf(out, "add,["); 
      break; 
    case SUB: 
      fprintf(out, "sub,["); 
      break; 
    case MUL: 
      fprintf(out, "mul,["); 
      break; 
    case DIV: 
      fprintf(out, "div,["); 
      break; 
    case AND: 
      fprintf(out, "and,["); 
      break; 
    case OR: 
      fprintf(out, "or,["); 
      break;
    case LT: 
      fprintf(out, "lt,["); 
      break; 
    case EQ: 
      fprintf(out, "eq,["); 
    break; 
    }
    print_expr(out, e->binOP.left); 
    fprintf(out, ","); 
    print_expr(out, e->binOp.right); 
    fprintf(out, "])"); 
    break; 
  default: 
    break; 
  }
}


void print_type(FILE * out, Type * t){
  if(t->type == INT){
    fprintf(out, "int"); 
  }else if(t->type == BOOL){
    fprintf(out, "bool");
  }
}
