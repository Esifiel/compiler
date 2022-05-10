#ifndef _STATEMENT_HPP_
#define _STATEMENT_HPP_

#include "basic.hpp"
#include "expression.hpp"
#include <vector>

using namespace std;

class CodeGenerator;

class Statement : public Node
{
public:
    Statement *tail;
    Statement *next;

    Statement() : tail(nullptr), next(nullptr) {}

    virtual string getName() { return "\"Statement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx) { return nullptr; }
};

class VariableDeclaration;

class CompoundStatement : public Statement
{
public:
    vector<VariableDeclaration *> *vardecs;
    Statement *stmt;

    CompoundStatement(vector<VariableDeclaration *> *d, Statement *s) : vardecs(d), stmt(s) {}

    virtual string getName() { return "\"CompoundStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class ExpressionStatement : public Statement
{
public:
    Expression *expr;

    ExpressionStatement() : expr(nullptr) {}
    ExpressionStatement(Expression *e) : expr(e) {}

    virtual string getName() { return "\"ExpressionStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class SelectionStatement : public Statement
{
public:
    Expression *cond;
    Statement *stmt;

    SelectionStatement(Expression *c, Statement *s) : cond(c), stmt(s) {}

    virtual string getName() { return "\"SelectionStatement\""; }
};

class IfElseStatement : public SelectionStatement
{
public:
    IfElseStatement(Expression *c, Statement *s) : SelectionStatement(c, s) {}

    virtual string getName() { return "\"IfElseStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class IterationStatement : public Statement
{
public:
    Expression *cond;
    Statement *stmt;

    IterationStatement(Expression *c, Statement *s) : cond(c), stmt(s) {}

    virtual string getName() { return "\"IterationStatement\""; }
};

class WhileStatement : public IterationStatement
{
public:
    WhileStatement(Expression *c, Statement *s) : IterationStatement(c, s) {}

    virtual string getName() { return "\"WhileStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class DoWhileStatement : public IterationStatement
{
public:
    DoWhileStatement(Expression *c, Statement *s) : IterationStatement(c, s) {}

    virtual string getName() { return "\"DoWhileStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class ForStatement : public IterationStatement
{
public:
    Expression *init;
    Expression *end;

    ForStatement(Expression *i, Expression *c, Expression *e, Statement *s) : init(i), IterationStatement(c, s), end(e) {}

    virtual string getName() { return "\"ForStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class ReturnStatement : public Statement
{
public:
    Expression *res;

    ReturnStatement() : res(nullptr) {}
    ReturnStatement(Expression *r) : res(r) {}

    virtual string getName() { return "\"ReturnStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class SwitchCaseStatement : public SelectionStatement
{
public:
    SwitchCaseStatement(Expression *c, Statement *s) : SelectionStatement(c, s) {}

    virtual string getName() { return "\"SwitchCaseStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class BreakStatement : public Statement
{
public:
    BreakStatement() {}

    virtual string getName() { return "\"BreakStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class ContinueStatement : public Statement
{
public:
    ContinueStatement() {}

    virtual string getName() { return "\"ContinueStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class CaseStatement : public Statement
{
public:
    Expression *val;
    Statement *stmt;

    CaseStatement(Expression *e, Statement *s) : val(e), stmt(s) {}

    virtual string getName() { return "\"CaseStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class GotoStatement : public Statement
{
public:
    string label;

    GotoStatement(string s) : label(s) {}

    virtual string getName() { return "\"GotoStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class LabelStatement : public Statement
{
public:
    string label;

    LabelStatement(string s) : label(s) {}

    virtual string getName() { return "\"LabelStatement\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

#endif