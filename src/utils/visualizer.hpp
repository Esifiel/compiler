#ifndef _VISUALIZER_HPP_
#define _VISUALIZER_HPP_

#include "../ast/program.h"
#include <fstream>
#include <iostream>

class Visualizer
{
public:
    Program *program;
    ofstream out;

    Visualizer(Program *p, string s) : program(p)
    {
        out.open(s.c_str());
    }
    ~Visualizer()
    {
        out.close();
    }

    void traverse();

private:
    void visitProgram(Program *p);
    void visitDeclarationList(vector<Declaration *> *l);
    void visitDeclaration(Declaration *d);
    void visitVarDeclaration(VariableDeclaration *d);
    void visitFunDeclaration(FunctionDeclaration *d);
};

#endif