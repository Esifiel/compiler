#ifndef _VISUALIZER_HPP_
#define _VISUALIZER_HPP_

#include <fstream>
#include <iostream>
#include "../ast/program.hpp"

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

    // traverse AST in pre-order and write to a legal .json file
    void traverse();

private:
    void visitProgram(Program *p);
    void visitDeclarationList(vector<Declaration *> *l);
    void visitDeclaration(Declaration *d);
    void visitVariableDeclaration(VariableDeclaration *d);
    void visitFunctionDeclaration(FunctionDeclaration *d);
    void visitType(TypeSpecifier *t);
    void visitIdentifier(Identifier *i);
    void visitCompoundStatement(CompoundStatement *c);
    void visitParameter(Parameter *p);
    void visitString(string *s);
    void visitStatement(Statement *s);
    void visitExpressionStatement(ExpressionStatement *e);
    void visitSelectionStatement(SelectionStatement *s);
    void visitIterationStatement(IterationStatement *i);
    void visitReturnStatement(ReturnStatement *r);
    void visitExpression(Expression *e);
    void visitWhileStatement(WhileStatement *w);
    void visitForStatement(ForStatement *f);
    void visitAssignment(Assignment *a);
};

#endif