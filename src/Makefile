LEX = flex
YACC = bison
CC = g++
NAME = ecc
DEPENDENCE = $(shell find . | grep .cpp)

.PHONY: all clean

all: $(NAME)

parser.cpp: $(NAME).y FORCE
	$(YACC) -d -o parser.cpp $(NAME).y

scanner.cpp: $(NAME).l FORCE
	$(LEX) -o scanner.cpp $(NAME).l

$(NAME): $(DEPENDENCE) scanner.cpp parser.cpp FORCE
	$(CC) -o $(NAME) $(DEPENDENCE)
	
	@cat ../test/quicksort.c | ./$(NAME)
	@cat tmp/program.json

clean: FORCE
	@rm -f $(NAME)
	@rm -f *.o
	@rm -f parser.* scanner.c
	@rm -f tmp/*

FORCE: