LEX = flex
YACC = bison
CC = g++
NAME = ecc

all: $(NAME)

$(NAME):
	$(YACC) -d -o parser.cpp $(NAME).y
	$(LEX) -o scanner.c $(NAME).l
	$(CC) -o $(NAME) parser.cpp scanner.c main.cpp

clean:
	@rm -f $(NAME) $(NAME).output parser* scanner.c