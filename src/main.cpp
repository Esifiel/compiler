// main entry of this compiler
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ast/program.hpp"
#include "codegen/codegen.hpp"
#include "utils/visualizer.hpp"

using namespace llvm;
using namespace std;

extern int yyparse();
extern int yydebug;
extern FILE *yyin;
extern Program *program;

string objname;

void err(string s);
void macro_expansion(string filename);

int main(int argc, char *argv[], char **envp)
{
    if (argc != 2)
    {
        cout << "Usage: ./ecc <c source file name>" << endl;
        exit(1);
    }

    // get obj name
    objname = argv[1];
    size_t begin = objname.find_last_of('/') + 1, end = objname.find_last_of('.');
    if (begin < end)
        objname = objname.substr(begin, end - begin);
    else
        objname = objname.substr(begin, objname.length() - begin);

    // macro expansion
    macro_expansion(argv[1]);

    // redirect yyparse
    yyin = fopen((objname + ".i").c_str(), "r");

    // parse the source code
    // yydebug = 1;
    yyparse();
    cout << "[+] parse done." << endl;
    // remove((objname + string(".i")).c_str());

    // do visualization (output json and png)
    // string path = string("./tmp/ast_") + object + string(".json");
    // Visualizer *v = new Visualizer(program, path);
    // v->traverse();
    // delete v;
    // system((string("python3 utils/json2dot.py ") + path).c_str());
    // cout << "[+] visualization done." << endl;

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
    raw_fd_ostream bc(string("./obj/") + objname + string(".bc"), ec, sys::fs::F_None);
    WriteBitcodeToFile(*generator.module, bc);
    bc.flush();
    raw_fd_ostream ll(string("./obj/") + objname + string(".ll"), ec, sys::fs::F_None);
    generator.module->print(ll, nullptr);
    ll.flush();
    cout << "[+] target code generated." << endl;

    return 0;
}

void err(string s)
{
    cerr << "\033[1;31m"
         << "error: "
         << "\033[0m" << s << endl;
    exit(1);
}

// split macro line with blank characters
static vector<string> parse_macro(const string &s)
{
    vector<string> tokens;

    size_t begin = 0, end = s.length() - 1;
    while (begin < end && isspace(s[begin]))
        begin++;
    while (end > begin && isspace(s[end]))
        end--;
    size_t p = begin;
    while (p < end)
    {
        while (p <= end && !isspace(s[p]))
            p++;
        tokens.push_back(s.substr(begin, p - begin));
        begin = p + 1;
        p = begin + 1;
    }

    return tokens;
}

static bool startswith(const string &s, const string &head)
{
    size_t begin = 0, end = s.length() - 1;
    while (begin < end && isspace(s[begin]))
        begin++;
    if (s.substr(begin, head.length()) == head)
        return true;
    else
        return false;
}

void macro_expansion(string filename)
{
    ifstream ifs(filename, ios::in);
    static ofstream ofs(objname + ".i", ios::out);
    if (!ifs.is_open())
        err("open source file failed");
    if (!ofs.is_open())
        err("open output .i file failed");

    string buf;
    vector<string> tokens;
    string path = filename;
    if (path.find('/') != string::npos)
        path = path.substr(0, path.find_last_of('/') + 1);
    else
        path = "./";
    while (getline(ifs, buf))
    {
        if (startswith(buf, "#"))
        {
            tokens = parse_macro(buf);

            if (tokens[0] == "#include")
            {
                if (tokens.size() != 2)
                    err("can not recognize file to be included: " + buf);
                if (tokens[1][0] == '<' && tokens[1][tokens[1].size() - 1] == '>')
                {
                    // TODO: system included file
                }
                else if (tokens[1][0] == '"' && tokens[1][tokens[1].size() - 1] == '"')
                    // recursively expansion
                    macro_expansion(path + tokens[1].substr(1, tokens[1].size() - 2));
                else
                    err("missing <> or \"\" around filename: " + buf);
            }
            else if (tokens[0] == "#define")
            {
            }
            else if (tokens[0] == "#ifdef")
            {
            }
            else if (tokens[0] == "#ifndef")
            {
            }
            else if (tokens[0] == "#else")
            {
            }
            else if (tokens[0] == "#endif")
            {
            }
            else if (tokens[0] == "#pragma")
            {
            }
        }
        else
            ofs << buf << endl;
    }
}