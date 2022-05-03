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

.PHONY: all $(NAME)

.PRECIOUS: all $(NAME)

all: $(NAME)

parser.cpp: $(NAME).y
	$(YACC) -dvt --debug -o $@ $<

parser.hpp: parser.cpp

scanner.cpp: $(NAME).l parser.hpp
	$(LEX) -o $@ $<

%.o: %.cpp
	$(CC) -c $(LLVMFLAGS) -o $@ $<

$(NAME): $(OBJECTS)
	@if [ ! -d tmp ]; then mkdir tmp; fi
	@if [ ! -d obj ]; then mkdir obj; fi

	$(CC) -g -o $(NAME) $(OBJECTS) $(LLVMFLAGS)
	
	@./$(NAME) ../test/quicksort.c
	@clang --target=$(TARGET) ./obj/quicksort.bc -o ./obj/quicksort
	@cd tmp && opt -dot-cfg ../obj/quicksort.ll

	@./$(NAME) ../test/matrix-multiplication.c
	@clang --target=$(TARGET) ./obj/matrix-multiplication.bc -o ./obj/matrix-multiplication
	@cd tmp && opt -dot-cfg ../obj/matrix-multiplication.ll

	@cd tmp && for i in `find . | grep "^\./\." | grep "\.dot$$"`; do(dot -Tpng $$i -o $$i.png); done

	@./obj/matrix-multiplication

clean:
	@rm -f $(NAME)
	@rm -f *.o utils/*.o codegen/*.o
	@rm -f parser.* scanner.*
	@rm -rf tmp
	@rm -rf obj
	@rm -f .gdb_history 