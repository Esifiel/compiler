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
			./codegen/type.o \
			./codegen/expression.o \
			./codegen/statement.o \
			./codegen/codegen.o \
			./utils/visualizer.o
HEADS = 	./ast/basic.hpp \
			./ast/declaration.hpp \
			./ast/expression.hpp \
			./ast/program.hpp \
			./ast/statement.hpp \
			./ast/type.hpp \
			./codegen/codegen.hpp \
			./utils/visualizer.hpp
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
	$(CC) -g -o $(NAME) $(OBJECTS) $(LLVMFLAGS)
	
	@cat ../test/quicksort.c | ./$(NAME)
	@clang --target=$(TARGET) ./test.bc -o ./test 
	@cd tmp && opt -dot-cfg ../test.ll
	@cd tmp && for i in `find . | grep "^\./\." | grep "\.dot$$"`; do(dot -Tpng $$i -o $$i.png); done

clean:
	@rm -f $(NAME)
	@rm -f *.o utils/*.o codegen/*.o
	@rm -f parser.* scanner.*
	@rm -f tmp/*
	@rm -f test*
	@rm -f .gdb_history 

FORCE: