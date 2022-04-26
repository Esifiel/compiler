LEX = flex
YACC = bison
CC = g++
NAME = ecc
LLVMFLAGS = `llvm-config --cxxflags --ldflags --system-libs --libs core`
OBJECTS =	./main.o \
			./scanner.o \
			./parser.o \
			./utils/visualizer.o \
			./codegen/program.o \
			./codegen/declaration.o \
			./codegen/type.o \
			./codegen/expression.o \
			./codegen/statement.o \
			./codegen/codegen.o
TARGET = `llvm-config --host-target`

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
	@if [ ! -d tmp ]; then mkdir tmp; fi

	$(CC) -g -o $(NAME) $(OBJECTS) $(LLVMFLAGS)
	
	@cat ../test/quicksort.c | ./$(NAME)
	@clang --target=$(TARGET) ./test.bc -o ./test
	@cd tmp && opt -dot-cfg ../test.ll
	@cd tmp && for i in `find . | grep "^\./\." | grep "\.dot$$"`; do(dot -Tpng $$i -o $$i.png); done
	@./test

clean:
	@rm -f $(NAME)
	@rm -f *.o utils/*.o codegen/*.o
	@rm -f parser.* scanner.*
	@rm -rf tmp
	@rm -f test*
	@rm -f .gdb_history 

FORCE: