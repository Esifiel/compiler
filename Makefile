LEX = flex
YACC = bison
CC = gcc
OBJECT = main

$(OBJECT): y.tab.o lex.yy.o
	$(CC) lex.yy.o y.tab.o -o $(OBJECT) -lm
	# @./$(OBJECT)

y.tab.c y.tab.h: hw.y
	$(YACC) --yacc -dv hw.y

y.tab.o: y.tab.c
	$(CC) -c y.tab.c
 
lex.yy.c: hw.l
	$(LEX) hw.l

lex.yy.o: lex.yy.c y.tab.h
	$(CC) -c lex.yy.c
 
clean:
	@rm -f $(OBJECT) *.o lex.yy.c y.output y.tab.c y.tab.h