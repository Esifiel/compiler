#include <iostream>
#include "ast/program.h"

using namespace std;

extern int yyparse();
extern Program *program;

int main(int argc, char *argv[], char **envp)
{
    yyparse();
    cout << program << endl;
    // getopt
    
    return 0;
}