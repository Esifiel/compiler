// traverse AST in pre-order and write to .json file
#include "visualizer.hpp"
#include "../ast/type.h"
#include "../ast/declaration.h"
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

string head = "{";
string tail = "}";
string sub = ": ";
string sep = ", ";

void Visualizer::traverse()
{
    out << head;
    if (program)
        visitProgram(program);
    out << tail << endl;
}

void Visualizer::visitProgram(Program *p)
{
    if (p->decs)
    {
        out << p->getName() << sub;
        out << head;
        visitDeclarationList(p->decs);
        out << tail;
    }
}

void Visualizer::visitDeclarationList(vector<Declaration *> *l)
{
    for (auto p = l->begin(); p != l->end(); p++)
    {
        out << (*p)->getName() << sub;
        out << head;
        visitDeclaration(*p);
        out << tail;
        out << sep;
    }
}

void Visualizer::visitDeclaration(Declaration *d)
{
    if (d->getName() == "FunctionDeclaration")
        visitFunctionDeclaration((FunctionDeclaration *)d);
    else if (d->getName() == "VariableDeclaration")
        visitVariableDeclaration((VariableDeclaration *)d);
}

void Visualizer::visitVariableDeclaration(VariableDeclaration *d)
{
    out << d->type->getName();
    if (d->type->getName() == "array")
    {
        out << sub;
        out << head;
        visitType(d->type);
        out << tail;
    }
    out << sep;
    out << d->name->getName();
}

void Visualizer::visitFunctionDeclaration(FunctionDeclaration *d)
{
    out << d->rettype->getName();
    if (d->rettype->getName() == "array")
    {
        out << sub;
        out << head;
        visitType(d->rettype);
        out << tail;
    }
    out << sep;

    out << d->name->getName();
    out << sep;

    for (auto p = d->params->begin(); p != d->params->end(); p++)
    {
        out << (*p)->getName() << sub;
        out << head;
        visitParameter(*p);
        out << tail;
        out << sep;
    }
    out << sep;
    
    visitCompoundStatement(d->stmts);
}

void Visualizer::visitType(Type *t)
{
    if (t->getName() == "array")
        out << ((ArrayType *)t)->size;
}

void Visualizer::visitIdentifier(Identifier *i)
{
}

void Visualizer::visitCompoundStatement(CompoundStatement *c)
{
}

void Visualizer::visitParameter(Parameter *p)
{
}

// params : param-list
//     | VOID { $$ = new vector<Parameter *>; $$->push_back(new Parameter(new VoidType())); }
//     |
//     ;

// param-list : param-list COMMA param
//     | param
//     ;

// param : type-specifier IDENTIFIER
//     | type-specifier IDENTIFIER LB RB
//     ;

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