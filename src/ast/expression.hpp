#ifndef _EXPRESSION_HPP_
#define _EXPRESSION_HPP_

#include <stdint.h>
#include <string>
#include "basic.hpp"
#include "type.hpp"

using namespace std;

class CodeGenerator;

class Expression : public Node
{
public:
    Expression() {}
    virtual string getName() { return "\"Expression\""; }
};

union union_num
{
    uint8_t charValue;
    uint16_t shortValue;
    uint32_t intValue;
    uint64_t longValue;
    float_t floatValue;
    double_t doubleValue;
};

enum val_type
{
    TYPE_CHAR,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_DOUBLE
};

class Number : public Expression
{
public:
    uint8_t buf[8];
    enum val_type type;
    Number(union union_num u, enum val_type t) : type(t) { memcpy(buf, &u, 8); }
    virtual string getName() { return "\"Number\""; }
    uint8_t charView() { return *(uint8_t *)buf; }
    uint16_t shortView() { return *(uint16_t *)buf; }
    uint32_t intView() { return *(uint32_t *)buf; }
    uint64_t longView() { return *(uint64_t *)buf; }
    float_t floatView() { return *(float_t *)buf; }
    double_t doubleView() { return *(double_t *)buf; }
};

class Identifier : public Expression
{
public:
    string *name;
    uint64_t idx;
    Identifier(string *v) : name(v) { idx = -1; }
    Identifier(string *v, uint64_t i) : name(v), idx(i) {}
    virtual string getName() { return "\"Identifier\""; }
};

class Parameter : public Expression
{
public:
    TypeSpecifier *type;
    Identifier *name;
    Parameter(TypeSpecifier *t) : type(t) {}
    Parameter(TypeSpecifier *t, Identifier *n) : type(t), name(n) {}
    virtual string getName() { return "\"Parameter\""; }
};

class Assignment : public Expression
{
public:
    Identifier *lv;
    Expression *rv;
    Assignment(Identifier *l, Expression *r) : lv(l), rv(r) {}
    virtual string getName() { return "\"Assignment\""; }
};

class FunctionCall : public Expression
{
public:
    Identifier *name;
    vector<Expression *> *varlist;
    FunctionCall(Identifier *n, vector<Expression *> *l) : name(n), varlist(l) {}
    virtual string getName() { return "\"FunctionCall\""; }
};

class SimpleExpression : public Expression
{
public:
    Expression *left;
    string *op;
    Expression *right;
    SimpleExpression(Expression *l) : left(l)
    {
        op = nullptr;
        right = nullptr;
    }
    SimpleExpression(Expression *l, string *o, Expression *r) : left(l), op(o), right(r) {}
    virtual string getName() { return "\"SimpleExpression\""; }
};

#endif