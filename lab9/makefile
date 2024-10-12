#
#	Jacob Yanez
#	Lab 9 makefile
#	May 3, 2024
# 

all: lab9

lab9: lab9.l lab9.y symtable.c symtable.h ast.c ast.h emit.c emit.h
	lex lab9.l		# makes lex.yy.c
	yacc -d lab9.y	# makes y.tab.c
	gcc ast.c symtable.c lex.yy.c emit.c y.tab.c -o lab9

clean:
	rm -f lab9