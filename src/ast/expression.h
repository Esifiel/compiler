#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <stdint.h>
#include <string>
#include "basic.h"

using namespace std;

class Expression : public Node
{
public:
    Expression() {}
};

class Char : public Expression
{
public:
    int8_t val;
    Char(int8_t v) : val(v) {}
};

class Short : public Expression
{
public:
    int16_t val;
    Short(int16_t v) : val(v) {}
};

class Int : public Expression
{
public:
    int32_t val;
    Int(int32_t v) : val(v) {}
};

class Long : public Expression
{
public:
    int64_t val;
    Long(int64_t v) : val(v) {}
};

class Float : public Expression
{
public:
    float val;
    Float(float v) : val(v) {}
};

class Double : public Expression
{
public:
    double val;
    Double(double v) : val(v) {}
};

class Identifier : public Expression
{
public:
    string name;
    Identifier(const string &v) : name(v) {}
};

class Assignment : public Expression
{
public:
    Identifier *lv;
    Expression *rv;
    Assignment(Identifier *l, Expression *r) : lv(l), rv(r) {}
};

#endif