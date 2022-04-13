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

class Declaration : public Node
{
public:
    Declaration() {}
    virtual string getName() { return "\"Declaration\""; }
};

class VariableDeclaration : public Declaration
{
public:
    Type *type;
    Identifier *name;
    VariableDeclaration(Type *t, Identifier *n) : type(t), name(n) {}
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
    Type *rettype;
    Identifier *name;
    vector<Parameter *> *params;
    CompoundStatement *stmts;
    FunctionDeclaration(Type *t, Identifier *n, vector<Parameter *> *p, CompoundStatement *s) : rettype(t), name(n), params(p), stmts(s) {}
    virtual string getName() { return "\"FunctionDeclaration\""; }
};

#endif





// var : IDENTIFIER
//     | IDENTIFIER LB expression RB
//     ;

// simple-expression : additive-expression relop additive-expression
//     | additive-expression
//     ;

// relop : LEQ
//     | LT
//     | GT
//     | GEQ
//     | EQ
//     | NEQ
//     | ANDAND
//     | OROR
//     ;

// additive-expression : additive-expression addop term
//     | term
//     ;

// addop : ADD
//     | SUB
//     ;

// term : term mulop factor
//     | factor
//     ;

// mulop : MUL
//     | DIV
//     ;

// factor : LP expression RP
//     | var
//     | call
//     | NUMBER
//     ;

// call : IDENTIFIER LP args RP
//     ;

// args : arg-list
//     |
//     ;

// arg-list : arg-list COMMA expression
//     | expression
//     ;