#include "visualizer.hpp"
#include "../ast/type.hpp"
#include "../ast/declaration.hpp"
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

string head = "{";
string tail = "}";
string sub = ": [";
string subend = "]";
string sep = ", ";

void Visualizer::traverse()
{
    visitProgram(program);
}

void Visualizer::visitProgram(Program *p)
{
    if (p)
    {
        out << head << p->getName() << sub;
        if (p->decs)
            visitDeclarationList(p->decs);
        out << subend << tail;
    }
}

void Visualizer::visitDeclarationList(vector<Declaration *> *l)
{
    if (l)
    {
        for (auto p = l->begin(); p != l->end(); p++)
        {
            if (p != l->begin())
                out << sep;
            visitDeclaration(*p);
        }
    }
}

void Visualizer::visitDeclaration(Declaration *d)
{
    if (d)
    {
        if (d->getName() == "\"FunctionDeclaration\"")
            visitFunctionDeclaration((FunctionDeclaration *)d);
        else if (d->getName() == "\"VariableDeclaration\"")
            visitVariableDeclaration((VariableDeclaration *)d);
    }
}

void Visualizer::visitVariableDeclaration(VariableDeclaration *d)
{
    if (d)
    {
        out << head << d->getName() << sub;
        visitType(d->type);
        out << sep;
        visitIdentifier(d->name);
        out << subend << tail;
    }
}

void Visualizer::visitFunctionDeclaration(FunctionDeclaration *d)
{
    if (d)
    {
        out << head << d->getName() << sub;
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
        out << subend << tail;
    }
}

void Visualizer::visitType(TypeSpecifier *t)
{
    if (t)
    {
        out << head << t->getName() << sub;
        if (t->getName() == "\"array\"")
            out << ((ArrayType *)t)->size;
        out << subend << tail;
    }
}

void Visualizer::visitIdentifier(Identifier *i)
{
    if (i)
    {
        out << head << i->getName() << sub;
        visitString(i->name);
        out << subend << tail;
    }
}

void Visualizer::visitParameter(Parameter *p)
{
    if (p)
    {
        out << head << p->getName() << sub;
        visitType(p->type);
        if (p->name)
            out << sep;
        visitIdentifier(p->name);
        out << subend << tail;
    }
}

void Visualizer::visitString(string *s)
{
    if (s)
        out << "\"" << *s << "\"";
}

void Visualizer::visitCompoundStatement(CompoundStatement *c)
{
    if (c)
    {
        out << head << c->getName() << sub;
        for (auto p = c->vardecs->begin(); p != c->vardecs->end(); p++)
        {
            if (p != c->vardecs->begin())
                out << sep;
            visitDeclaration(*p);
        }
        if (c->stmts->size() > 0)
            out << sep;
        for (auto p = c->stmts->begin(); p != c->stmts->end(); p++)
        {
            if (p != c->stmts->begin())
                out << sep;
            visitStatement(*p);
        }
        out << subend << tail;
    }
}

void Visualizer::visitStatement(Statement *s)
{
    if (s)
    {
        if (s->getName() == "\"ExpressionStatement\"")
            visitExpressionStatement((ExpressionStatement *)s);
        else if (s->getName() == "\"CompoundStatement\"")
            visitCompoundStatement((CompoundStatement *)s);
        else if (s->getName() == "\"SelectionStatement\"")
            visitSelectionStatement((SelectionStatement *)s);
        else if (s->getName() == "\"WhileStatement\"")
            visitWhileStatement((WhileStatement *)s);
        else if (s->getName() == "\"ForStatement\"")
            visitForStatement((ForStatement *)s);
        else if (s->getName() == "\"ReturnStatement\"")
            visitReturnStatement((ReturnStatement *)s);
    }
}

void Visualizer::visitExpressionStatement(ExpressionStatement *e)
{
    if (e)
    {
        out << head << e->getName() << sub;
        visitExpression(e->expr);
        out << subend << tail;
    }
}

void Visualizer::visitSelectionStatement(SelectionStatement *s)
{
    // selection-stmt : IF LP expression RP statement
    //     | IF LP expression RP ELSE statement
    //     ;
}

void Visualizer::visitReturnStatement(ReturnStatement *r)
{
    if (r)
    {
        out << head << r->getName() << sub;
        visitExpressionStatement(r->res);
        out << subend << tail;
    }
}

void Visualizer::visitExpression(Expression *e)
{
    if (e)
    {
        if (e->getName() == "\"Assignment\"")
            visitAssignment((Assignment *)e);
        else if (e->getName() == "\"Number\"")
            visitNumber((Number *)e);
        // else if (e->getName() == "\"Assignment\"")
        // else if (e->getName() == "\"Assignment\"")
        // else if (e->getName() == "\"Assignment\"")
    }
}

void Visualizer::visitWhileStatement(WhileStatement *w)
{
    if (w)
    {
        out << head << w->getName() << sub;
        out << subend << tail;
    }
}

void Visualizer::visitForStatement(ForStatement *f)
{
    if (f)
    {
        out << head << f->getName() << sub;
        out << subend << tail;
    }
}

void Visualizer::visitAssignment(Assignment *a)
{
    if (a)
    {
        out << head << a->getName() << sub;
        visitIdentifier(a->lv);
        out << sep;
        visitExpression(a->rv);
        out << subend << tail;
    }
}

void Visualizer::visitNumber(Number *n)
{
    if (n)
    {
        out << head << n->getName() << sub;
        switch (n->type)
        {
        case TYPE_CHAR:
            out << n->charView();
            break;
        case TYPE_SHORT:
            out << n->shortView();
            break;
        case TYPE_INT:
            out << n->intView();
            break;
        case TYPE_LONG:
            out << n->longView();
            break;
        case TYPE_FLOAT:
            out << n->floatView();
            break;
        case TYPE_DOUBLE:
            out << n->doubleView();
            break;
        default:
            out << "Unknown number type";
            break;
        }
        out << subend << tail;
    }
}

// expression : var ASSIGN expression
//     | simple-expression
//     ;

// var : IDENTIFIER
//     | IDENTIFIER LB expression RB
//     ;

// simple-expression : additive-expression relop additive-expression
//     | additive-expression
//     ;

// additive-expression : additive-expression addop term
//     | term
//     ;

// term : term mulop factor
//     | factor
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