#ifndef AST_H
#define AST_H


/*Types*/

enum {T_BOOL,T_NUM,T_IDENT,T_UNOP,T_BINOP,T_SET,T_IF,T_WHILE,T_VAR,T_CONST,T_STAT,T_DEC,T_DECCMDS,T_STATCMDS}; 


typedef struct _prog Prog; 
typedef struct _block Block; 
typedef struct _cmds Cmds; 
typedef struct _dec Dec; 
typedef struct _stat Stat; 
typedef struct _expr Expr; 
typedef struct _type Type; 


struct _type{
  int type; 
}; 

struct _expr{
  int type; 
  union{
    int bool; 
    int num; 
    break; 
    char * ident; 
    struct {
      int op;
      Expr * expr; 
    }unOp; 
    struct {
      int op; 
      Expr * right; 
      Expr * left;
    }binOp; 
  }content; 
}; 

struct _stat{
  int type; 
  union{
    struct{
      char * ident; 
      Expr * expr; 
    }set; 
    struct{
      Expr * cond; 
      Block * b1; 
      Block * b2;
    }alt; 
    struct{
      Expr * cond; 
      Block * b; 
    }loop; 
  }content; 
};

struct _dec {
    int type; 
  union{
    struct{
      char * ident;
      Type * type; 
    }var;
    struct{
      char * ident; 
      Type * type; 
      Expr * expr; 
    }cons; 
  }content; 
};

struct _cmds {
  int type; 
  union{
    Stat * stat; 
    struct{
      Dec * dec; 
      struct _cmds * cmds; 
    }decCmds; 
    struct{
      Stat * stat;
      struct _cmds * cmds;
    }statCmds; 
  }content; 
}; 

struct _block {
  Cmds * cmds; 
};  
  
struct _prog{ 
  Block * block; 
}; 


/*Fonctions*/

Prog * make_prog(Block * block); 
Block * make_block(Cmds * cmds); 
Cmds * make_stat(Stat * stat);
Cmds * make_decCmds(Dec * dec, Cmds * cmds); 
Cmds * make_statCmds(Stat * stat, Cmds * cmds); 
Dec * make_dec(int t, char * ident, Type * type, Expr * expr);
Stat * make_set(char * ident, Expr * expr); 
Stat * make_if(Expr * cond, Block * b1, Block * b2); 
Stat * make_while(Expr *cond, Block * b); 
Expr * make_bool(int bool); 
Expr * make_num(int num); 
Expr * make_ident(char *ident); 
Expr * make_un(Expr *expr); 
Expr * make_bin(int op, Expr * right, Expr * left); 
Type * make_type(int type);



#endif

