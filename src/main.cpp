// main entry of this compiler
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <map>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ast/program.hpp"
#include "codegen/codegen.hpp"
#include "utils/visualizer.hpp"
#include "macro/macro.hpp"

using namespace llvm;
using namespace std;

extern int yylex();
extern int yyparse();
extern int yydebug;
extern char *yytext;
extern FILE *yyin;
extern Program *program;

bool inyyparse;
bool isedited;
bool normalpass;
bool argspass;
ofstream ofs;

static void err(string s)
{
    cerr << "\033[1;31m"
         << "error: "
         << "\033[0m" << s << endl;
    exit(-1);
}

int main(int argc, char *argv[], char **envp)
{
    if (argc == 1)
    {
        cout << "Usage: ./ecc [-E filename.i] [-o filename.c]" << endl;
        cout << "\t\t-E: output source file with macro expanded" << endl;
        cout << "\t\t-o: output executable file" << endl;
        exit(1);
    }

    bool isoptionE = false, isoptiono = false;
    string filenameE = "a.i", filenameo = "a.out", src = "";
    for (int i = 1; i < argc; i++)
    {
        if (isoptionE)
        {
            isoptionE = false;
            filenameE = argv[i];
        }
        else if (isoptiono)
        {
            isoptiono = false;
            filenameo = argv[i];
        }
        else if (!strcmp(argv[i], "-E"))
            isoptionE = true;
        else if (!strcmp(argv[i], "-o"))
            isoptiono = true;
        else
            src = argv[i];
    }
    if (src == "")
        err("no input file");

    // macro expansion
    inyyparse = false;
    string tmp = src;
    normalpass = true;
    argspass = false;
    while (1)
    {
        isedited = false;
        ofs = ofstream("./tmp.i");
        macro_expansion(tmp, ofs);
        ofs.close();
        // next round
        tmp = filenameE;
        rename("./tmp.i", filenameE.c_str());
        if (!isedited)
        {
            if (normalpass)
            {
                normalpass = false;
                argspass = true;
            }
            else
                break;
        }
    }
    remove("./tmp.i");

    // parse the source code
    // yydebug = 1;
    yyin = fopen(filenameE.c_str(), "r");
    if (!yyin)
        err("open source file error");
    inyyparse = true;
    yyparse();
    cout << "[+] parse done." << endl;
    // if (!isoptionE)
    //     remove(filenameE.c_str());

    // do visualization (output json and png)
    string path = string("./tmp/ast_") + src.substr(src.find_last_of('/') + 1, src.length()) + string(".json");
    Visualizer *v = new Visualizer(program, path);
    v->traverse();
    delete v;
    // system((string("python3 utils/json2dot.py ") + path).c_str());
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
    raw_fd_ostream bc(filenameo + ".bc", ec, sys::fs::F_None);
    WriteBitcodeToFile(*generator.module, bc);
    bc.flush();
    raw_fd_ostream ll(filenameo + ".ll", ec, sys::fs::F_None);
    generator.module->print(ll, nullptr);
    ll.flush();
    cout << "[+] target code generated." << endl;

    // compile the IR
    system(("clang -O3 --target=`llvm-config --host-target` " + filenameo + ".ll -o " + filenameo).c_str());
    cout << "[+] compilation done." << endl;

    return 0;
}