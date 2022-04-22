#ifndef _DECLARATION_HPP_
#define _DECLARATION_HPP_

#include "basic.hpp"
#include "expression.hpp"
#include "statement.hpp"
#include "type.hpp"
#include <vector>
#include <stdint.h>
#include <iostream>

using namespace std;

class CodeGenerator;

class Declaration : public Node
{
public:
    Declaration *next;

    Declaration() {}
    Declaration(Declaration *d) : next(d) {}

    virtual string getName() { return "\"Declaration\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx) { return nullptr; };
};

class VariableDeclaration : public Declaration
{
public:
    TypeSpecifier *type;
    vector<Identifier *> *ids;

    VariableDeclaration(TypeSpecifier *t, vector<Identifier *> *i) : type(t), ids(i) {}

    virtual string getName() { return "\"VariableDeclaration\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx) override;
};

class Parameter : public Declaration
{
public:
    TypeSpecifier *type;
    Expression *id;

    Parameter(TypeSpecifier *t) : type(t), id(nullptr) {}
    Parameter(TypeSpecifier *t, Expression *i) : type(t), id(i) {}

    virtual string getName() { return "\"Parameter\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx) override;

    string getIdName() { return ((Identifier *)id)->getIdName(); }
};

class CompoundStatement;

class FunctionDeclaration : public Declaration
{
public:
    TypeSpecifier *rettype;
    Expression *name;
    Parameter *params;
    CompoundStatement *stmts;

    FunctionDeclaration(TypeSpecifier *t, Expression *n, Parameter *p, CompoundStatement *s) : rettype(t), name(n), params(p), stmts(s) {}

    virtual string getName() { return "\"FunctionDeclaration\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx) override;

    string getFunctionName() { return ((String *)(((Identifier *)name)->name))->val; }
};

class TypeDeclaration : public Declaration
{
public:
    Identifier *name;

    TypeDeclaration(Identifier *v) : name(v) {}

    virtual string getName() { return "\"TypeDeclaration\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx) override;
};

#endif