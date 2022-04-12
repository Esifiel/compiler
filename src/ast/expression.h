#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <stdint.h>
#include <string>
#include "basic.h"
#include "type.h"

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
    string name;
    Identifier(const string &v) : name(v) {}
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

#endif