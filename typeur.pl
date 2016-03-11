
type(true, bool).
type(false, bool).

type(and(X,Y),bool):- type(X,bool),type(Y,bool).
type(non(X), bool):- type(X,bool).
type(or(X,Y),bool):- type(X,bool),type(Y,bool).
type(eq(X,Y),bool):- type(X,bool),type(Y,bool).

type(N, int):- integer(N).
type(N,T,L) :- getType(N,T,L).


type(lt(X,Y),bool):- type(X,int),type(Y,int).
type(eq(X,Y),bool):- type(X,int),type(Y,int).
type(add(X,Y),int):- type(X,int),type(Y,int).
type(mul(X,Y),int):- type(X,int),type(Y,int).
type(mysub(X,Y),int):- type(X,int),type(Y,int).
type(div(X,Y),int):- type(X,int),type(Y,int).

type(myif(X,T,E),void).
type(mywhile(X,B),void).
type(set,void).

type(set(X,Z),void):-ident(X),type(Z,int).
type(set(X,Z),void):-ident(X),type(Z,bool).

getType(X, T,[assoc(X,T)|_]).
getType(X,T,[assoc(Y,_)|L]):-X \== Y,getType(X,T,L).
