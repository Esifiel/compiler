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
        visitDeclaration(p->decl);
        out << subend << tail;
    }
}

void Visualizer::visitDeclaration(Declaration *d)
{
    if (d)
    {
        Declaration *decl = d;
        while (decl)
        {
            if (d->getName() == "\"FunctionDeclaration\"")
                visitFunctionDeclaration((FunctionDeclaration *)decl);
            else if (d->getName() == "\"VariableDeclaration\"")
                visitVariableDeclaration((VariableDeclaration *)decl);
            decl = decl->next;
            if (decl)
                out << sep;
        }
    }
}

void Visualizer::visitVariableDeclaration(VariableDeclaration *d)
{
    if (d)
    {
        out << head << d->getName() << sub;
        visitType(d->type);
        out << sep;
        for (auto &p : *d->ids)
            visitIdentifier(p);
        out << subend << tail;
    }
}

void Visualizer::visitParameter(Parameter *p)
{
    if (p)
    {
        out << head << p->getName() << sub;
        Parameter *tmp = p;
        while (tmp)
        {
            visitType(tmp->type);
            if (tmp->id)
            {
                out << sep;
                visitExpression(tmp->id);
            }
            tmp = (Parameter *)tmp->next;
            if (tmp)
                out << sep;
        }
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
        visitExpression(d->name);
        if (d->params)
            out << sep;
        visitParameter(d->params);
        if (d->stmts)
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
        if (t->getName() == "\"ArrayListType\"")
            out << ((ArrayListType *)t)->size;
        out << subend << tail;
    }
}

void Visualizer::visitIdentifier(Identifier *i)
{
    if (i)
    {
        out << head << i->getName() << sub;
        visitExpression(i->name);
        out << subend << tail;
    }
}

void replace(string &src, string sub, string tar);
void Visualizer::visitString(String *s)
{
    if (s)
    {
        string output = "\"" + s->val + "\"";
        replace(output, "\n", "\\n");
        replace(output, "\t", "\\t");
        replace(output, "\r", "\\r");
        replace(output, "\"", "\\\"");
        out << head << s->getName() << sub << output << subend << tail;
    }
}

void Visualizer::visitCompoundStatement(CompoundStatement *c)
{
    if (c)
    {
        out << head << c->getName() << sub;
        for (auto &p : *c->vardecs)
        {
            if (p != (*c->vardecs)[0])
                out << sep;
            visitDeclaration(p);
        }
        if (c->vardecs->size() > 0 && c->stmt != nullptr)
            out << sep;
        Statement *p = c->stmt;
        while (p)
        {
            visitStatement(p);
            p = p->next;
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
        else if (s->getName() == "\"IfElseStatement\"")
            visitIfElseStatement((IfElseStatement *)s);
        else if (s->getName() == "\"SwitchCaseStatement\"")
            visitSwitchCaseStatement((SwitchCaseStatement *)s);
        else if (s->getName() == "\"WhileStatement\"")
            visitWhileStatement((WhileStatement *)s);
        else if (s->getName() == "\"DoWhileStatement\"")
            visitDoWhileStatement((DoWhileStatement *)s);
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

void Visualizer::visitIfElseStatement(IfElseStatement *s)
{
    if (s)
    {
        out << head << s->getName() << sub;
        visitExpression(s->cond);
        out << sep;
        visitStatement(s->stmt);
        if (s->stmt->next)
        {
            out << sep;
            visitStatement(s->stmt->next);
        }
        out << subend << tail;
    }
}

void Visualizer::visitReturnStatement(ReturnStatement *r)
{
    if (r)
    {
        out << head << r->getName() << sub;
        visitExpression(r->res);
        out << subend << tail;
    }
}

void Visualizer::visitExpression(Expression *e)
{
    if (e)
    {
        if (e->getName() == "\"Number\"")
            visitNumber((Number *)e);
        else if (e->getName() == "\"FunctionCall\"")
            visitFunctionCall((FunctionCall *)e);
        else if (e->getName() == "\"Identifier\"")
            visitIdentifier((Identifier *)e);
        else if (e->getName() == "\"String\"")
            visitString((String *)e);
        else
        {
            out << head << e->getName() << sub;
            visitOp(e->op);
            out << sep;
            visitExpression(e->left);
            if (e->right)
            {
                out << sep;
                visitExpression(e->right);
            }
            if (e->addition)
            {
                out << sep;
                visitExpression(e->addition);
            }
        }
    }
}

void Visualizer::visitOp(enum op_type op)
{
    out << head << "\"op\"" << sub << "\"";
    switch (op)
    {
    case OP_EQ:
        out << "==";
        break;
    case OP_LT:
        out << "<";
        break;
    case OP_GT:
        out << ">";
        break;
    case OP_LEQ:
        out << "<=";
        break;
    case OP_GEQ:
        out << ">=";
        break;
    case OP_NEQ:
        out << "!=";
        break;
    case OP_ANDAND:
        out << "&&";
        break;
    case OP_OROR:
        out << "||";
        break;
    case OP_NOTNOT:
        out << "!";
        break;
    case OP_AND:
    case OP_ADDRESS:
        out << "&";
        break;
    case OP_OR:
        out << "|";
        break;
    case OP_NOT:
        out << "~";
        break;
    case OP_XOR:
        out << "^";
        break;
    case OP_SL:
        out << "<<";
        break;
    case OP_SR:
        out << ">>";
        break;
    case OP_ADD:
    case OP_POSITIVE:
        out << "+";
    case OP_SUB:
    case OP_NEGTIVE:
        out << "-";
        break;
    case OP_MUL:
    case OP_POINTER:
        out << "*";
        break;
    case OP_DIV:
        out << "/";
        break;
    case OP_MOD:
        out << "%";
        break;
    case OP_INC_FRONT:
    case OP_INC_REAR:
        out << "++";
        break;
    case OP_DEC_FRONT:
    case OP_DEC_REAR:
        out << "--";
        break;
    case OP_ASSIGN:
        out << "=";
        break;
    case OP_MULASSIGN:
        out << "*=";
        break;
    case OP_DIVASSIGN:
        out << "/=";
        break;
    case OP_MODASSIGN:
        out << "%=";
        break;
    case OP_ADDASSIGN:
        out << "+=";
        break;
    case OP_SUBASSIGN:
        out << "-=";
        break;
    case OP_SLASSIGN:
        out << "<<=";
        break;
    case OP_SRASSIGN:
        out << ">>=";
        break;
    case OP_ANDASSIGN:
        out << "&=";
        break;
    case OP_XORASSIGN:
        out << "^=";
        break;
    case OP_ORASSIGN:
        out << "|=";
        break;
    case OP_IFELSE:
        out << "? :";
        break;
    case OP_CAST:
        out << "()";
        break;
    case OP_COMMA:
        out << ",";
        break;
    default:
        break;
    }
    out << "\"" << subend << tail;
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
        visitExpression(f->init);
        if (f->init && (f->cond || f->end || f->stmt))
            out << sep;
        visitExpression(f->cond);
        if ((f->init || f->cond) && (f->end || f->stmt))
            out << sep;
        visitExpression(f->end);
        if ((f->init || f->cond || f->end) && f->stmt)
            out << sep;
        visitStatement(f->stmt);
        out << subend << tail;
    }
}

void Visualizer::visitNumber(Number *n)
{
    if (n)
    {
        out << head << n->getName() << sub;
        switch (n->valtype)
        {
        case VAL_CHAR:
            out << n->charView();
            break;
        case VAL_SHORT:
            out << n->shortView();
            break;
        case VAL_INT:
            out << n->intView();
            break;
        case VAL_LONG:
            out << n->longView();
            break;
        case VAL_FLOAT:
            out << n->floatView();
            break;
        case VAL_DOUBLE:
            out << n->doubleView();
            break;
        default:
            out << "Unknown number type";
            break;
        }
        out << subend << tail;
    }
}

void Visualizer::visitFunctionCall(FunctionCall *f)
{
    if (f)
    {
        out << head << f->getName() << sub;
        visitExpression(f->name);
        for (auto &p : *f->varlist)
        {
            if (p != (*f->varlist)[0])
                out << sep;
            visitExpression(p);
        }
        out << subend << tail;
    }
}

void Visualizer::visitDoWhileStatement(DoWhileStatement *d)
{

}

void Visualizer::visitSwitchCaseStatement(SwitchCaseStatement *s)
{

}