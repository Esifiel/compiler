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

    Visualizer(Program *p, string s) : program(p), out(s) {}
    ~Visualizer() { out.close(); }

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
    void visitString(String *s);
    void visitStatement(Statement *s);
    void visitExpressionStatement(ExpressionStatement *e);
    void visitIfElseStatement(IfElseStatement *s);
    void visitSwitchCaseStatement(SwitchCaseStatement *s);
    void visitIterationStatement(IterationStatement *i);
    void visitReturnStatement(ReturnStatement *r);
    void visitExpression(Expression *e);
    void visitWhileStatement(WhileStatement *w);
    void visitDoWhileStatement(DoWhileStatement *d);
    void visitForStatement(ForStatement *f);
    void visitNumber(Number *n);
    void visitFunctionCall(FunctionCall *f);
    void visitOp(enum op_type op);
    void visitParameter(Parameter *p);
    void visitBreakStatement(BreakStatement *b);
    void visitContinueStatement(ContinueStatement *c);
    void visitQualifier(Qualifier *q);
    void visitTypeDeclaration(TypeDeclaration *t);
    void visitAggregateType(AggregateType *t);
    void visitCaseStatement(CaseStatement *c);
};

#endif