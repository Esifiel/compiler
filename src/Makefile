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
			./codegen/codegen.o \
			./macro/macro.o
TARGET = `llvm-config --host-target`

.PHONY: all $(NAME)

.PRECIOUS: all $(NAME)

all: $(NAME)

parser.cpp: $(NAME).y
	$(YACC) -dvt --debug -o $@ $<

parser.hpp: parser.cpp

scanner.cpp: $(NAME).l parser.hpp
	$(LEX) -o $@ $<

-include *.d
%.o: %.cpp
	$(CC) -g3 -c $(LLVMFLAGS) -MMD -o $@ $<

$(NAME): $(OBJECTS)
	$(CC) -g3 -o $(NAME) $(OBJECTS) $(LLVMFLAGS)

	@./$(NAME) ../test/1.c
	@./a.out

	# @cd tmp && for i in `find . | grep "^\./\." | grep "\.dot$$"`; do(dot -Tpng $$i -o $$i.png); done

clean:
	@rm -f $(NAME)
	@rm -f *.o utils/*.o codegen/*.o macro/*.o
	@rm -f *.d utils/*.d codegen/*.d macro/*.d
	@rm -f parser.* scanner.*
	@rm -rf tmp
	@rm -rf obj
	@rm -f .gdb_history ../test/.gdb_history
	@cd ../test && make clean && cd ../src
	@rm -f *.ll *.bc *.i *.out *.json

test:
	$(CC) -g3 -o $(NAME) $(OBJECTS) $(LLVMFLAGS)

	@./$(NAME) -o quicksort ../test/quicksort.c
	@./$(NAME) -o matrix-multiplication ../test/matrix-multiplication.c
	@./$(NAME) -o auto-advisor ../test/auto-advisor.c

	# @cd tmp && opt -dot-cfg ../quicksort.ll
	# @cd tmp && opt -dot-cfg ../matrix-multiplication.ll
	# @cd tmp && opt -dot-cfg ../auto-advisor.ll

	@../test/tester/quicksort/linux-amd64 ./quicksort
	@../test/tester/matrix-multiplication/linux-amd64 ./matrix-multiplication
	@../test/tester/auto-advisor/linux-amd64 ./auto-advisor