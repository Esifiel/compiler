LEX = flex
YACC = bison
CC = g++
NAME = ecc
LLVMFLAGS = `llvm-config --cxxflags --ldflags --system-libs --libs core`
DEPENDENCE = $(shell find . | grep .cpp$)

.PHONY: all clean

all: $(NAME) FORCE

parser.cpp: $(NAME).y FORCE
	$(YACC) -dv -o $@ $<

parser.hpp: parser.cpp FORCE

scanner.cpp: $(NAME).l parser.hpp FORCE
	$(LEX) -o $@ $<

%.o: %.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $<

$(NAME): $(DEPENDENCE) scanner.cpp parser.cpp FORCE
	$(CC) -o $(NAME) $(DEPENDENCE) $(LLVMFLAGS)
	
	@cat ../test/quicksort.c | ./$(NAME)
	@cat tmp/ast.json

clean:
	@rm -f $(NAME)
	@rm -f *.o
	@rm -f parser.* scanner.c
	@rm -f tmp/*

FORCE: