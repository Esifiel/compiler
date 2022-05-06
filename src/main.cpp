// main entry of this compiler
#include <iostream>
#include <string>
#include <stdlib.h>
#include "ast/program.hpp"
#include "codegen/codegen.hpp"
#include "utils/visualizer.hpp"

using namespace llvm;
using namespace std;

extern int yyparse();
extern int yydebug;
extern FILE *yyin;
extern Program *program;

int main(int argc, char *argv[], char **envp)
{
    if (argc == 1)
    {
        cout << "Usage: ./ecc <c source file name>" << endl;
        exit(1);
    }

    // get obj name
    string object = argv[1];
    size_t begin = object.find_last_of('/') + 1, end = object.find_last_of('.');
    if (begin < end)
        object = object.substr(begin, end - begin);
    else
        object = object.substr(begin, object.length() - begin);

    // redirect yyparse
    yyin = fopen(argv[1], "r");

    // parse the source code
    // yydebug = 1;
    yyparse();
    cout << "[+] parse done." << endl;
    remove((object + string(".i")).c_str());

    // do visualization (output json and png)
    string path = string("./tmp/ast_") + object + string(".json");
    Visualizer *v = new Visualizer(program, path);
    v->traverse();
    delete v;
    system((string("python3 utils/json2dot.py ") + path).c_str());
    cout << "[+] visualization done." << endl;

    // init llvm
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();

    CodeGenerator generator;
    // set host target
    generator.module->setTargetTriple(sys::getDefaultTargetTriple());
    // emit tagret code
    program->codeGen(generator);
    generator.dump();

    // save the llvm bit code and plaintext IR
    error_code ec;
    raw_fd_ostream bc(string("./obj/") + object + string(".bc"), ec, sys::fs::F_None);
    WriteBitcodeToFile(*generator.module, bc);
    bc.flush();
    raw_fd_ostream ll(string("./obj/") + object + string(".ll"), ec, sys::fs::F_None);
    generator.module->print(ll, nullptr);
    ll.flush();
    cout << "[+] target code generated." << endl;

    return 0;
}