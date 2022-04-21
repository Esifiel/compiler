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
extern Program *program;

int main(int argc, char *argv[], char **envp)
{
    // parse the source code
    yyparse();
    cout << "[+] parse done." << endl;
    
    // do visualization (output json and png)
    string filepath = "./tmp/ast.json";
    Visualizer *v = new Visualizer(program, filepath);
    v->traverse();
    delete v;
    system((string("python3 utils/json2dot.py ") + filepath).c_str());
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
    raw_fd_ostream bc("./test.bc", ec, sys::fs::F_None);
    WriteBitcodeToFile(*generator.module, bc);
    bc.flush();
    raw_fd_ostream ll("./test.ll", ec, sys::fs::F_None);
    generator.module->print(ll, nullptr);
    ll.flush();

    cout << "[+] target code generated." << endl;

    return 0;
}

// getopt