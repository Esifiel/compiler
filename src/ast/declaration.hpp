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

class CodeGenContext;

class Declaration : public Node
{
public:
    Declaration() {}
    virtual string getName() { return "\"Declaration\""; }
};

class VariableDeclaration : public Declaration
{
public:
    TypeSpecifier *type;
    Identifier *name;
    VariableDeclaration(TypeSpecifier *t, Identifier *n) : type(t), name(n) {}
    virtual string getName() { return "\"VariableDeclaration\""; }
};

class TypeDeclaration : public Declaration
{
public:
    Identifier *name;
    TypeDeclaration(Identifier *v) : name(v) {}
    virtual string getName() { return "\"TypeDeclaration\""; }
};

class CompoundStatement;

class FunctionDeclaration : public Declaration
{
public:
    TypeSpecifier *rettype;
    Identifier *name;
    vector<Parameter *> *params;
    CompoundStatement *stmts;
    FunctionDeclaration(TypeSpecifier *t, Identifier *n, vector<Parameter *> *p, CompoundStatement *s) : rettype(t), name(n), params(p), stmts(s) {}
    virtual string getName() { return "\"FunctionDeclaration\""; }
};

#endif