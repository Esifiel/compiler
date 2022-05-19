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
	@if [ ! -d tmp ]; then mkdir tmp; fi
	@if [ ! -d obj ]; then mkdir obj; fi

	$(CC) -g3 -o $(NAME) $(OBJECTS) $(LLVMFLAGS)
	
	@./$(NAME) -o obj/quicksort ../test/quicksort.c
	@./$(NAME) -o obj/matrix-multiplication ../test/matrix-multiplication.c
	@./$(NAME) -o obj/auto-advisor ../test/auto-advisor.c
	
	# @cd tmp && opt -dot-cfg ../obj/quicksort.ll
	# @cd tmp && opt -dot-cfg ../obj/matrix-multiplication.ll
	# @cd tmp && opt -dot-cfg ../obj/auto-advisor.ll

	@./$(NAME) -o obj/1 ../test/1.c
	@./obj/1

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
	@rm -f *.ll *.bc *.i *.out