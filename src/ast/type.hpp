#ifndef _TYPE_HPP_
#define _TYPE_HPP_

#include "basic.hpp"
#include <vector>

using namespace std;

class CodeGenContext;

class TypeSpecifier : public Node
{
public:
    string name;
    TypeSpecifier(const string &v) : name(v) {}
    ~TypeSpecifier() {}
    virtual string getName() { return "\"TypeSpecifier\""; }
};

class CharType : public TypeSpecifier
{
public:
    CharType() : TypeSpecifier("char") {}
    ~CharType() {}
    string getName() { return "\"CharType\""; }
};

class ShortType : public TypeSpecifier
{
public:
    ShortType() : TypeSpecifier("short") {}
    virtual string getName() { return "\"ShortType\""; }
};

class IntType : public TypeSpecifier
{
public:
    IntType() : TypeSpecifier("int") {}
    virtual string getName() { return "\"IntType\""; }
};

class LongType : public TypeSpecifier
{
public:
    LongType() : TypeSpecifier("long") {}
    virtual string getName() { return "\"LongType\""; }
};

class FloatType : public TypeSpecifier
{
public:
    FloatType() : TypeSpecifier("float") {}
    virtual string getName() { return "\"FloatType\""; }
};

class DoubleType : public TypeSpecifier
{
public:
    DoubleType() : TypeSpecifier("double") {}
    virtual string getName() { return "\"DoubleType\""; }
};

class VoidType : public TypeSpecifier
{
public:
    VoidType() : TypeSpecifier("void") {}
    virtual string getName() { return "\"VoidType\""; }
};

class StructType: public TypeSpecifier
{
    public:
    StructType() : TypeSpecifier("struct") {}
    virtual string getName() { return "\"StructType\""; }
};

class EnumType: public TypeSpecifier
{
    public:
    EnumType() : TypeSpecifier("enum") {}
    virtual string getName() { return "\"EnumType\""; }
};

class UnionType: public TypeSpecifier
{
    public:
    UnionType() : TypeSpecifier("union") {}
    virtual string getName() { return "\"UnionType\""; }
};

class ArrayType : public TypeSpecifier
{
public:
    uint64_t size;
    vector<TypeSpecifier *> elements;
    ArrayType(TypeSpecifier *t, uint64_t s) : TypeSpecifier("array"), size(s) {}
    virtual string getName() { return "\"ArrayType\""; }
};

#endif