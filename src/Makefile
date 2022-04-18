LEX = flex
YACC = bison
CC = g++
NAME = ecc
LLVMFLAGS = `llvm-config --cxxflags --ldflags --system-libs --libs core`
OBJECTS =	./main.o \
			./scanner.o \
			./parser.o \
			./codegen/program.o \
			./codegen/declaration.o \
			./utils/visualizer.o \

.PHONY: all

all: $(NAME)

parser.cpp: $(NAME).y
	$(YACC) -dv -o $@ $<

parser.hpp: parser.cpp

scanner.cpp: $(NAME).l parser.hpp
	$(LEX) -o $@ $<

%.o: %.cpp
	$(CC) -c $(LLVMFLAGS) -o $@ $<

$(NAME): $(OBJECTS) FORCE
	$(CC) -o $(NAME) $(OBJECTS) $(LLVMFLAGS)
	
	@cat ../test/quicksort.c | ./$(NAME)

clean:
	@rm -f $(NAME)
	@rm -f *.o utils/*.o codegen/*.o
	@rm -f parser.* scanner.*
	@rm -f tmp/*

FORCE: