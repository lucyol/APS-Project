%error-verbose

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  
#include "ast.h"
#include "ast_print.h"
  
  int yylex(); 
   
  int yyerror(const char *message) {
    fprintf(stderr, "%s\n", message);
    return 0;
  } 

  extern FILE * yyin;
  FILE * yyout; 

  Prog * prog; 
  %}

%union{
  int entier;
  char* str;
  struct _prog * prog; 
  struct _block * block; 
  struct _cmds * cmds; 
  struct _dec * dec; 
  struct _stat * stat; 
  struct _expr * expr; 
  struct _type * type; 
 }


%token ADD SUB MUL DIV
%token LT NOT OR EQ AND
%token WHILE SET IF
%token TRUE FALSE
%token VAR CONST
%token VOID INT BOOL

%token<entier> NUM
%token<str> IDENT

%type<prog>  Prog 
%type<block>  Block 
%type<cmds>  Cmds
%type<dec>  Dec
%type<stat>  Stat
%type<expr>  Expr Op
%type<type>  Type 



%%

Prog: Block { prog = make_prog($1); }
  

Block : '[' Cmds ']' { $$ = make_block($2); }
  

Cmds:
Stat          { $$=make_stat($1);}
|Dec ';' Cmds  { $$=make_decCmds($1,$3); }
|Stat ';' Cmds { $$=make_statCmds($1,$3); }
  

Dec:
VAR IDENT Type        { $$=make_dec(T_VAR,strdup($2),$3,NULL); }
|CONST IDENT Type Expr { $$=make_dec(T_CONST,strdup($2),$3,$4); }
  

Stat:
SET IDENT Expr       { $$=make_set(strdup($2),$3); }  
|IF Expr Block Block  { $$=make_if($2,$3,$4); }
|WHILE Expr Block     { $$=make_while($2,$3); }


Expr:
TRUE       { $$=make_bool(1); }
|FALSE      { $$=make_bool(0); }   
|NUM        { $$=make_num($1); }
|IDENT      { $$=make_ident(strdup($1)); }
|'('Op')'   { $$=$2; }
  

Op:  
NOT Expr      { $$=make_un($2); }
     |AND Expr Expr { $$=make_bin(AND,$2,$3); }   
     |OR Expr Expr  { $$=make_bin(OR,$2,$3); }   
     |EQ Expr Expr  { $$=make_bin(EQ,$2,$3); }   
     |LT Expr Expr  { $$=make_bin(LT,$2,$3); }   
     |ADD Expr Expr { $$=make_bin(ADD,$2,$3); }   
     |SUB Expr Expr { $$=make_bin(SUB,$2,$3); }   
     |DIV Expr Expr { $$=make_bin(DIV,$2,$3); }   
     |MUL Expr Expr { $$=make_bin(MUL,$2,$3); }   
  

Type:
   VOID { $$=make_type(VOID); }
  |INT  { $$=make_type(INT); }
  |BOOL { $$=make_type(BOOL); }
  


%%

     int main(int argc, char * argv[]){

       if(argc < 2){
	 fprintf(stderr, "Il manque un argument\n"); 
	 exit(1); 
       }

       FILE * f ; 

       if(!(f=fopen(argv[1], "r"))){
	   fprintf(stderr, "Erreur a l'ouverture du fichier %s\n", argv[1]); 
	   exit(1); 
	 }

	 yyin = f; 
	 yyparse(); 
	 fclose(f);  

	 if(!(yyout=fopen(strcat(argv[1],".out"), "w"))){
	   fprintf(stderr, "Erreur a l'ouverture du fichier test\n" ); 
	   exit(1); 
	 }

	 print_prog(yyout, prog); 
	 fclose(yyout); 


	 return 0; 
}
  
