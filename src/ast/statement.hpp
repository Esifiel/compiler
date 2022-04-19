#ifndef _STATEMENT_HPP_
#define _STATEMENT_HPP_

#include "basic.hpp"
#include "expression.hpp"
#include "declaration.hpp"

using namespace std;

class CodeGenerator;

class Statement : public Node
{
public:
    Statement() {}
    virtual string getName() { return "\"Statement\""; }
};

class VariableDeclaration;

class CompoundStatement : public Statement
{
public:
    vector<VariableDeclaration *> *vardecs;
    vector<Statement *> *stmts;
    CompoundStatement(vector<VariableDeclaration *> *d, vector<Statement *> *s) : vardecs(d), stmts(s) {}
    virtual string getName() { return "\"CompoundStatement\""; }
};

class ExpressionStatement : public Statement
{
public:
    Expression *expr;
    ExpressionStatement() { expr = nullptr; }
    ExpressionStatement(Expression *e) : expr(e) {}
    virtual string getName() { return "\"ExpressionStatement\""; }
};

class SelectionStatement : public Statement
{
public:
    Expression *cond;
    Statement *stmt;
    Statement *elsepart;
    SelectionStatement(Expression *c, Statement *s) : cond(c), stmt(s), elsepart(nullptr) {}
    SelectionStatement(Expression *c, Statement *s, Statement *el) : cond(c), stmt(s), elsepart(el) {}
    virtual string getName() { return "\"SelectionStatement\""; }
};

class IterationStatement : public Statement
{
public:
    Expression *cond;
    CompoundStatement *stmts;
    IterationStatement(Expression *c, CompoundStatement *s) : cond(c), stmts(s) {}
    virtual string getName() { return "\"IterationStatement\""; }
};

class WhileStatement : public IterationStatement
{
public:
    WhileStatement(Expression *c, CompoundStatement *s) : IterationStatement(c, s) {}
    virtual string getName() { return "\"WhileStatement\""; }
};

class ForStatement : public IterationStatement
{
public:
    vector<Expression *> *init;
    vector<Expression *> *end;
    ForStatement(vector<Expression *> *i, Expression *c, vector<Expression *> *e, CompoundStatement *s) : init(i), IterationStatement(c, s), end(e) {}
    virtual string getName() { return "\"ForStatement\""; }
};

class ReturnStatement : public Statement
{
public:
    ExpressionStatement *res;
    ReturnStatement(ExpressionStatement *r) : res(r) {}
    virtual string getName() { return "\"ReturnStatement\""; }
};

#endif