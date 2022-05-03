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
    Declaration *tail;
    Declaration *next;

    Declaration() : tail(nullptr), next(nullptr) {}

    virtual string getName() { return "\"Declaration\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx) { return nullptr; };
};

class VariableDeclaration : public Declaration
{
public:
    vector<TypeSpecifier *> *types;
    vector<Identifier *> *ids;

    VariableDeclaration(vector<TypeSpecifier *> *t, vector<Identifier *> *i) : types(t), ids(i) {}

    virtual string getName() { return "\"VariableDeclaration\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx) override;
};

class Parameter : public Declaration
{
public:
    TypeSpecifier *type;
    Identifier *id;

    Parameter(TypeSpecifier *t) : type(t), id(nullptr) {}
    Parameter(TypeSpecifier *t, Identifier *i) : type(t), id(i) {}

    virtual string getName() { return "\"Parameter\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx) override;
};

class CompoundStatement;

class FunctionDeclaration : public Declaration
{
public:
    TypeSpecifier *rettype;
    Identifier *id;
    Parameter *params;
    CompoundStatement *stmts;

    FunctionDeclaration(TypeSpecifier *t, Identifier *n, Parameter *p, CompoundStatement *s) : rettype(t), id(n), params(p), stmts(s) {}

    virtual string getName() { return "\"FunctionDeclaration\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx) override;
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