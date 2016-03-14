#include <stdio.h>
#include <stdlib.h>

#include "ast.h" 
#include "parser.tab.h"



Prog * make_prog(Block * b){
  Prog * prog = malloc(sizeof(*prog)); 
  prog->block = b; 
  return prog; 
}
 
Block * make_block(Cmds * cmds){
  Block * block = malloc(sizeof(*block)); 
  block->cmds = cmds; 
  return block; 
}

Cmds * make_stat(Stat * s){
  Cmds * stat = malloc(sizeof(*stat)); 
  stat->type = T_STAT; 
  stat->content.stat = s; 
  return stat; 
}

Cmds * make_decCmds(Dec * dec, Cmds * cmds){
  Cmds * cCmds = malloc(sizeof(*cCmds)); 
  cCmds->type = T_DECCMDS; 
  cCmds->content.decCmds.dec = dec; 
  cCmds->content.decCmds.cmds = cmds; 
  return cCmds; 
}

 
Cmds * make_statCmds (Stat * stat, Cmds * cmds){
 Cmds * sCmds = malloc(sizeof(*sCmds)); 
  sCmds->type = T_STATCMDS; 
  sCmds->content.statCmds.stat = stat; 
  sCmds->content.statCmds.cmds = cmds; 
  return sCmds; 
}

Dec * make_dec(int t, char * ident, Type * type, Expr * expr){
  Dec * dec = malloc(sizeof(*dec)); 
  dec->type = t; 
  if(expr == NULL){
    dec->content.var.ident = ident; 
    dec->content.var.type = type; 
  }else{
    dec->content.cons.ident = ident; 
    dec->content.cons.type = type; 
    dec->content.cons.expr = expr; 
  }
  return dec;
} 

Stat * make_set(char * ident, Expr * expr){
  Stat * set = malloc(sizeof(*set)); 
  set->type = T_SET; 
  set->content.set.ident = ident; 
  set->content.set.expr = expr; 
  return set; 
}


Stat * make_if(Expr * cond, Block * b1, Block * b2){
  Stat * _if = malloc(sizeof(*_if)); 
  _if->type = T_IF; 
  _if->content.alt.cond = cond; 
  _if->content.alt.b1 = b1; 
  return _if; 
} 

Stat * make_while(Expr * cond, Block * b){
  Stat * _while = malloc(sizeof(*_while)); 
  _while->type = T_WHILE; 
  _while->content.loop.cond = cond; 
  _while->content.loop.b = b; 
  return _while; 
} 

Expr * make_bool(int bool){
  Expr * b = malloc(sizeof(*b));
  b->type = T_BOOL;  
  b->content.bool = bool;
  return b;  
}

Expr * make_num(int num){
  Expr * n = malloc(sizeof(*n)); 
  n->type = T_NUM; 
  n->content.num = num;
  return n;  
} 

Expr * make_ident(char *ident){
  Expr * id = malloc(sizeof(*id)); 
  id->type = T_IDENT; 
  id->content.ident = ident;
  return id;  
}

Expr * make_un (Expr *expr){
  Expr * not = malloc(sizeof(*not)); 
  not->type = T_UNOP; 
  not->content.unOp.expr = expr; 
  return not; 
}
 
Expr * make_bin(int op, Expr * right, Expr * left){
  Expr * bin = malloc(sizeof(*bin)); 
  bin->type = T_BINOP; 
  bin->content.binOp.right = right; 
  bin->content.binOp.left = left; 
  bin->content.binOp.op = op;
  return bin; 
}

Type * make_type(int type){
  Type * t = malloc(sizeof(*t)); 
  t->type = type; 
  return t;
}
