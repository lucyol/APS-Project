
parser: parser.y
	bison -d parser.y

lexer: lexer.l
	flex lexer.l

ast: ast.c ast.h
	gcc -c ast.c

aps: parser lexer ast
	gcc -o aps ast.o lex.yy.c parser.tab.c -lfl

clean:
	rm -f parser.tab.* lex.yy.c aps *~ *.o
