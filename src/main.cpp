// main entry of this compiler
#include <iostream>
#include <string>
#include <stdlib.h>
#include "ast/program.hpp"
#include "codegen/codegen.hpp"
#include "utils/visualizer.hpp"

using namespace std;

extern int yyparse();
extern Program *program;

int main(int argc, char *argv[], char **envp)
{
    // parse the source code
    yyparse();
    cout << "[+] parse done." << endl;
    
    // do visualization (json and png)
    string filepath = "./tmp/ast.json";
    Visualizer *v = new Visualizer(program, filepath);
    v->traverse();
    delete v;
    system((string("python3 utils/json2dot.py ") + filepath).c_str());
    cout << "[+] visualization done." << endl;

    // emit tagret code
    CodeGenerator generator;
    program->codeGen(generator);
    cout << "[+] target code generated." << endl;

    return 0;
}

// getopt