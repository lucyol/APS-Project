#include <stdlib.h>
#include <stdio.h>

#include "ast_print.h"


void print_prog(FILE * out, Prog * prog){
  fprintf(out, "prog(");
  print_block(out,prog->block);  
  fprintf(out, ")\n"); 
}

void print_block(FILE * out, Block * b){
  fprintf(out,"["); 
  print_cmds(out,b->cmds); 
  fprintf(out,"]");
}

void print_cmds(FILE * out, Cmds * c){
  switch(c->type){
  case T_STAT: 
    print_stat(out, c->content.stat); 
    break; 
  case T_STATCMDS: 
    print_stat(out, c->content.statCmds.stat); 
    fprintf(out, ","); 
    print_cmds(out, c->content.statCmds.cmds); 
    break; 
  case T_DECCMDS:
    print_dec(out, c->content.decCmds.dec); 
    fprintf(out, ","); 
    print_cmds(out, c->content.decCmds.cmds);  
    break; 
  default: 
    break; 
  }
  fprintf(out, ")"); 
}

void print_dec(FILE * out, Dec * d){
  switch(d->type){
  case T_VAR : 
    fprintf(out, "var(%s,",d->content.var.ident); 
    print_type(out, d->content.var.type); 
    break; 
  case T_CONST: 
    fprintf(out,"const(%s,", d->content.cons.ident); 
    print_type(out, d->content.cons.type); 
    print_expr(out, d->content.cons.expr);
    break; 
  default: 
    break;   
  } 
  fprintf(out,")"); 
}

void print_stat(FILE * out, Stat * s){

  switch(s->type){
  case T_SET : 
    fprintf(out, "set(%s,", s->content.set.ident); 
    print_expr(out, s->content.set.expr); 
    break; 
  case T_IF: 
    fprintf(out, "if("); 
    print_expr(out, s->content.alt.cond); 
    fprintf(out, ","); 
    print_block(out, s->content.alt.b1); 
    fprintf(out, ","); 
    print_block(out, s->content.alt.b2); 
    break; 
  case T_WHILE:
    fprintf(out, "while("); 
    print_expr(out, s->content.loop.cond); 
    fprintf(out, ","); 
    print_block(out, s->content.loop.b); 
    break; 
  default: 
    break; 
  }
  fprintf(out, ")"); 
}

void print_expr(FILE * out, Expr * e){
  switch(e->type){
  case T_BOOL:
    if(e->content.bool == 1)
      fprintf(out, "true");
    else
      fprintf(out, "false"); 
    break; 
  case T_NUM: 
    fprintf(out, "%d", e->content.num); 
    break; 
  case T_IDENT: 
    fprintf(out, "%s", e->content.ident); 
    break; 
  case T_UNOP: 
    fprintf(out, "app(not,["); 
    print_expr(out, e->content.unOp.expr); 
    fprintf(out,"])"); 
    break; 
  case T_BINOP: 
    fprintf(out, "app("); 
    switch(e->content.binOp.op){
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
    print_expr(out, e->content.binOp.left); 
    fprintf(out, ","); 
    print_expr(out, e->content.binOp.right); 
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
