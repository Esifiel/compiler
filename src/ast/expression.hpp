#ifndef _EXPRESSION_HPP_
#define _EXPRESSION_HPP_

#include <stdint.h>
#include <string>
#include "basic.hpp"
#include "type.hpp"

using namespace std;

class Expression : public Node
{
public:
    Expression() {}
    virtual string getName() { return "\"Expression\""; }
};

class Char : public Expression
{
public:
    int8_t val;
    Char(int8_t v) : val(v) {}
    virtual string getName() { return "\"Char\""; }
};

class Short : public Expression
{
public:
    int16_t val;
    Short(int16_t v) : val(v) {}
    virtual string getName() { return "\"Short\""; }
};

class Int : public Expression
{
public:
    int32_t val;
    Int(int32_t v) : val(v) {}
    virtual string getName() { return "\"Int\""; }
};

class Long : public Expression
{
public:
    int64_t val;
    Long(int64_t v) : val(v) {}
    virtual string getName() { return "\"Long\""; }
};

class Float : public Expression
{
public:
    float val;
    Float(float v) : val(v) {}
    virtual string getName() { return "\"Float\""; }
};

class Double : public Expression
{
public:
    double val;
    Double(double v) : val(v) {}
    virtual string getName() { return "\"Double\""; }
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
    Type *type;
    Identifier *name;
    Parameter(Type *t) : type(t) {}
    Parameter(Type *t, Identifier *n) : type(t), name(n) {}
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

class FunctionCall : public Expression {
    public:
    FunctionCall() {}
    virtual string getName() { return "\"FunctionCall\""; }
};

class SimpleExpression : public Expression
{
public:
    SimpleExpression() {}
    virtual string getName() { return "\"SimpleExpression\""; }
};

#endif

// simple-expression : additive-expression relop additive-expression
//     | additive-expression
//     ;