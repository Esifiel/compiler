// traverse AST in pre-order and write to a legal .json file
#include "visualizer.hpp"
#include "../ast/type.hpp"
#include "../ast/declaration.hpp"
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
    out << tail;
}

void Visualizer::visitProgram(Program *p)
{
    out << p->getName() << sub << head;
    if (p->decs)
        visitDeclarationList(p->decs);
    out << tail;
}

void Visualizer::visitDeclarationList(vector<Declaration *> *l)
{
    for (auto p = l->begin(); p != l->end(); p++)
    {
        if (p != l->begin())
            out << sep;
        visitDeclaration(*p);
    }
}

void Visualizer::visitDeclaration(Declaration *d)
{
    out << d->getName() << sub << head;
    if (d->getName() == "\"FunctionDeclaration\"")
        visitFunctionDeclaration((FunctionDeclaration *)d);
    else if (d->getName() == "\"VariableDeclaration\"")
        visitVariableDeclaration((VariableDeclaration *)d);
    out << tail;
}

void Visualizer::visitVariableDeclaration(VariableDeclaration *d)
{
    visitType(d->type);
    out << sep;
    visitIdentifier(d->name);
}

void Visualizer::visitFunctionDeclaration(FunctionDeclaration *d)
{
    visitType(d->rettype);
    out << sep;
    visitIdentifier(d->name);
    out << sep;

    for (auto p = d->params->begin(); p != d->params->end(); p++)
    {
        if (p != d->params->begin())
            out << sep;
        visitParameter(*p);
    }
    out << sep;

    visitCompoundStatement(d->stmts);
}

void Visualizer::visitType(Type *t)
{
    out << t->getName() << sub << head;
    if (t->getName() == "\"array\"")
        out << ((ArrayType *)t)->size;
    out << tail;
}

void Visualizer::visitIdentifier(Identifier *i)
{
    out << i->getName() << sub << head;
    out << tail;
}

void Visualizer::visitParameter(Parameter *p)
{
    out << p->getName() << sub << head;
    out << tail;
}

void Visualizer::visitCompoundStatement(CompoundStatement *c)
{
    out << c->getName() << sub << head;
    out << tail;
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