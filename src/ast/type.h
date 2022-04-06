#ifndef _TYPE_H_
#define _TYPE_H_

#include "basic.h"

using namespace std;

class Type : public Node
{
public:
    string name;
    Type(const string &v) : name(v) {}
};

class CharType : public Type
{
public:
    CharType() : Type("char") {}
};

class ShortType : public Type
{
public:
    ShortType() : Type("short") {}
};

class IntType : public Type
{
public:
    IntType() : Type("int") {}
};

class LongType : public Type
{
public:
    LongType() : Type("long") {}
};

class FloatType : public Type
{
public:
    FloatType() : Type("float") {}
};

class DoubleType : public Type
{
public:
    DoubleType() : Type("double") {}
};

#endif