#ifndef _DECLARATION_H
#define _DECLARATION_H

#include "basic.h"
#include "expression.h"
#include "type.h"

using namespace std;

class Declaration : public Node
{
public:
    Declaration() {}
};

class VariableDeclaration : public Declaration
{
public:
    Type *type;
    Identifier *name;
    VariableDeclaration(Type *t, Identifier *n) : type(t), name(n) {}
};

class TypeDeclaration : public Declaration
{
public:
    Identifier *name;
    TypeDeclaration(Identifier *v) : name(v) {}
};

#endif