#include <iostream>
#include "ast/program.hpp"
#include "codegen/codegen.hpp"
#include "utils/visualizer.hpp"

using namespace std;

extern int yyparse();
extern Program *program;

int main(int argc, char *argv[], char **envp)
{
    yyparse();
    
    Visualizer *v = new Visualizer(program, "./tmp/ast.json");
    v->traverse();
    delete v;

    cout << "Done. Bye~" << endl;
    // getopt
    
    return 0;
}