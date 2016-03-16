all: aps

parser.tab.c: parser.y
	bison -d parser.y

lex.yy.c: lexer.l
	flex lexer.l

%.o: %.c
	gcc -c $<

aps:  parser.tab.c lex.yy.c ast.o ast_print.o
	gcc -o aps $^ -lfl

clean:
	rm -f parser.tab.* lex.yy.c aps *~ *.o exemples/*.out
