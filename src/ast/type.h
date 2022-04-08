#ifndef _TYPE_H_
#define _TYPE_H_

#include "basic.h"
#include <vector>

using namespace std;

class Type : public Node
{
public:
    string name;
    Type(const string &v) : name(v) {}
    ~Type() {}
    virtual string getName() { return "Type"; }
};

class CharType : public Type
{
public:
    CharType() : Type("char") {}
    ~CharType() {}
    string getName() { return "CharType"; }
};

class ShortType : public Type
{
public:
    ShortType() : Type("short") {}
    virtual string getName() { return "ShortType"; }
};

class IntType : public Type
{
public:
    IntType() : Type("int") {}
    virtual string getName() { return "IntType"; }
};

class LongType : public Type
{
public:
    LongType() : Type("long") {}
    virtual string getName() { return "LongType"; }
};

class FloatType : public Type
{
public:
    FloatType() : Type("float") {}
    virtual string getName() { return "FloatType"; }
};

class DoubleType : public Type
{
public:
    DoubleType() : Type("double") {}
    virtual string getName() { return "DoubleType"; }
};

class VoidType : public Type
{
public:
    VoidType() : Type("void") {}
    virtual string getName() { return "VoidType"; }
};

class StructType: public Type
{
    public:
    StructType() : Type("struct") {}
    virtual string getName() { return "StructType"; }
};

class EnumType: public Type
{
    public:
    EnumType() : Type("enum") {}
    virtual string getName() { return "EnumType"; }
};

class UnionType: public Type
{
    public:
    UnionType() : Type("union") {}
    virtual string getName() { return "UnionType"; }
};

class ArrayType : public Type
{
public:
    uint64_t size;
    vector<Type *> elements;
    ArrayType(Type *t, uint64_t s) : Type("array"), size(s) {}
    virtual string getName() { return "ArrayType"; }
};

#endif