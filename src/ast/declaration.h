#ifndef _DECLARATION_H_
#define _DECLARATION_H_

#include "basic.h"
#include "expression.h"
#include "statement.h"
#include "type.h"
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


// compound-stmt : LC local-declarations statement-list RC
//     ;

// local-declarations : local-declarations var-declaration
//     |
//     ;

// statement-list : statement-list statement
//     |
//     ;

// statement : expression-stmt
//     | compound-stmt
//     | selection-stmt
//     | iteration-stmt
//     | return-stmt
//     ;

// expression-stmt : expression DELIM
//     | DELIM
//     ;

// selection-stmt : IF LP expression RP statement
//     | IF LP expression RP ELSE statement
//     ;

// iteration-stmt : WHILE LP expression RP statement
//     ;

// return-stmt : RETURN DELIM
//     | RETURN expression DELIM
//     ;

// expression : var ASSIGN expression
//     | simple-expression
//     ;

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