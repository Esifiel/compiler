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
            if (decl->getName() == "\"FunctionDeclaration\"")
                visitFunctionDeclaration((FunctionDeclaration *)decl);
            else if (decl->getName() == "\"VariableDeclaration\"")
                visitVariableDeclaration((VariableDeclaration *)decl);
            else if (decl->getName() == "\"TypeDeclaration\"")
                visitTypeDeclaration((TypeDeclaration *)decl);
            decl = decl->next;
            if (decl)
                out << sep;
        }
    }
}

void Visualizer::visitTypeDeclaration(TypeDeclaration *t)
{
    if (t)
    {
        out << head << t->getName() << sub;
        visitType(t->type);
        out << subend << tail;
    }
}

void Visualizer::visitVariableDeclaration(VariableDeclaration *d)
{
    if (d)
    {
        out << head << d->getName() << sub;
        auto pt = d->types->begin();
        auto pi = d->ids->begin();
        for (; pt != d->types->end() && pi != d->ids->end(); pt++, pi++)
        {
            if (pt != d->types->begin() && pi != d->ids->begin())
                out << sep;
            visitType(*pt);
            out << sep;
            visitIdentifier(*pi);
        }
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
                visitIdentifier(tmp->id);
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
        visitIdentifier(d->id);
        if (d->params)
            out << sep;
        visitParameter(d->params);
        if (d->stmts)
            out << sep;
        visitCompoundStatement(d->stmts);
        out << subend << tail;
    }
}

void Visualizer::visitAggregateType(AggregateType *t)
{
    if (t)
    {
        out << "\"" << t->name << "\"";
        if (t->members && t->members->size() > 0)
            for (auto &p : *t->members)
            {
                out << sep;
                auto pt = p->first->begin();
                auto pi = p->second->begin();
                for (; pt != p->first->end() && pi != p->second->end(); pt++, pi++)
                {
                    visitType(*pt);
                    out << sep;
                    visitIdentifier(*pi);
                }
            }
    }
}

void Visualizer::visitType(TypeSpecifier *t)
{
    if (t)
    {
        out << head << t->getName() << sub;
        if (t->qual)
            visitQualifier(t->qual);
        if (t->type == TYPE_ARRAY)
            out << ((MyArrayType *)t)->size << sep;
        if (t->type == TYPE_ARRAY || t->type == TYPE_POINTER)
            visitType(((IterableType *)t)->basictype);
        if (t->type == TYPE_STRUCT || t->type == TYPE_UNION)
            visitAggregateType((AggregateType *)t);
        out << subend << tail;
    }
}

void Visualizer::visitQualifier(Qualifier *q)
{
    if (q)
    {
        out << head << q->getName() << sub;
        if (q->isconst)
            out << "\"const\"";
        if (q->isconst && q->isvolatile)
            out << sep;
        if (q->isvolatile)
            out << "\"volatile\"";
        if ((q->isconst || q->isvolatile) && q->pcnt)
            out << sep;
        if (q->pcnt)
            out << q->pcnt;
        out << subend << tail;
    }
}

void Visualizer::visitIdentifier(Identifier *i)
{
    if (i)
    {
        out << head << i->getName() << sub << "\"" + i->name + "\"";
        if (i->qual)
        {
            out << sep;
            visitQualifier(i->qual);
        }
        if (i->init)
        {
            out << sep;
            visitExpression(i->init);
        }
        out << subend << tail;
    }
}

void replace(string &src, string sub, string tar);
void Visualizer::visitString(String *s)
{
    if (s)
    {
        string output = s->val;
        replace(output, "\n", "\\\\n");
        replace(output, "\t", "\\\\t");
        replace(output, "\r", "\\\\r");
        replace(output, "\"", "\\\\\"");
        replace(output, ":", " ");
        out << head << s->getName() << sub << "\"" + output + "\"" << subend << tail;
    }
}

void Visualizer::visitCompoundStatement(CompoundStatement *c)
{
    if (c)
    {
        out << head << c->getName() << sub;
        if (c->decl)
            for (Declaration *d = c->decl; d; d = d->next)
            {
                if (d != c->decl)
                    out << sep;
                visitDeclaration(d);
            }
        if (c->decl && c->stmt)
            out << sep;
        Statement *p = c->stmt;
        while (p)
        {
            if (p != c->stmt)
                out << sep;
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
        else if (s->getName() == "\"BreakStatement\"")
            visitBreakStatement((BreakStatement *)s);
        else if (s->getName() == "\"ContinueStatement\"")
            visitContinueStatement((ContinueStatement *)s);
        else if (s->getName() == "\"SwitchCaseStatement\"")
            visitSwitchCaseStatement((SwitchCaseStatement *)s);
        else if (s->getName() == "\"CaseStatement\"")
            visitCaseStatement((CaseStatement *)s);
        else if (s->getName() == "\"LabelStatement\"")
            visitLabelStatement((LabelStatement *)s);
        else if (s->getName() == "\"GotoStatement\"")
            visitGotoStatement((GotoStatement *)s);
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
            if (e->op == OP_CAST)
                visitType(e->left->type);
            else
                visitExpression(e->left);
            out << sep;
            visitOp(e->op);
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
            out << subend << tail;
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
    case OP_ADDRESSOF:
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
        break;
    case OP_SUB:
    case OP_NEGATIVE:
        out << "-";
        break;
    case OP_MUL:
    case OP_DEREFERENCE:
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
    case OP_NOTASSIGN:
        out << "~=";
        break;
    case OP_IFELSE:
        // out << "? :";
        out << "?";
        break;
    case OP_CAST:
        out << "()";
        break;
    case OP_COMMA:
        out << ",";
        break;
    case OP_INDEX:
        out << "[]";
        break;
    case OP_DOT:
        out << ".";
        break;
    case OP_TO:
        out << "->";
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
        visitExpression(w->cond);
        out << sep;
        visitStatement(w->stmt);
        out << subend << tail;
    }
}

void Visualizer::visitForStatement(ForStatement *f)
{
    if (f)
    {
        out << head << f->getName() << sub;
        visitExpression(f->init);
        if ((f->init) && f->cond)
            out << sep;
        visitExpression(f->cond);
        if ((f->init || f->cond) && f->end)
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
        case VAL_NONE:
            out << "\"NaN\"";
            break;
        case VAL_CHAR:
            out << (uint32_t)(n->charView());
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
            out << sep;
            visitExpression(p);
        }
        out << subend << tail;
    }
}

void Visualizer::visitDoWhileStatement(DoWhileStatement *d)
{
    if (d)
    {
        out << head << d->getName() << sub;
        visitStatement(d->stmt);
        out << sep;
        visitExpression(d->cond);
        out << subend << tail;
    }
}

void Visualizer::visitSwitchCaseStatement(SwitchCaseStatement *s)
{
    if (s)
    {
        out << head << s->getName() << sub;
        visitExpression(s->cond);
        out << sep;
        visitStatement(s->stmt);
        out << subend << tail;
    }
}

void Visualizer::visitBreakStatement(BreakStatement *b)
{
    if (b)
        out << head << b->getName() << sub << subend << tail;
}

void Visualizer::visitContinueStatement(ContinueStatement *c)
{
    if (c)
        out << head << c->getName() << sub << subend << tail;
}

void Visualizer::visitCaseStatement(CaseStatement *c)
{
    if (c)
    {
        out << head << c->getName() << sub;
        visitNumber(c->val);
        out << subend << tail;
    }
}

void Visualizer::visitGotoStatement(GotoStatement *s)
{
    if (s)
    {
        out << head << s->getName() << sub;
        out << "\"" + s->label << "\"";
        out << subend << tail;
    }
}

void Visualizer::visitLabelStatement(LabelStatement *s)
{
    if (s)
    {
        out << head << s->getName() << sub;
        out << "\"" + s->label << "\"";
        out << subend << tail;
    }
}