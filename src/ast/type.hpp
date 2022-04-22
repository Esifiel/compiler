#ifndef _TYPE_HPP_
#define _TYPE_HPP_

#include "basic.hpp"
#include "../codegen/codegen.hpp"
#include <llvm/IR/Type.h>
#include <vector>

using namespace std;
using namespace llvm;

enum type_type {
    TYPE_CHAR,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_VOID,
    TYPE_STRUCT,
    TYPE_ENUM,
    TYPE_UNION,
    TYPE_ARRAY
};

class TypeSpecifier : public Node
{
public:
    enum type_type type;
    bool isunsigned;

    TypeSpecifier(enum type_type t) : type(t) { isunsigned = false; }

    virtual string getName() { return "\"TypeSpecifier\""; }
    virtual Type *getType(CodeGenerator &ctx) = 0;
};

class CharType : public TypeSpecifier
{
public:
    CharType() : TypeSpecifier(TYPE_CHAR) {}

    virtual string getName() { return "\"CharType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return ctx.builder.getInt8Ty(); }
};

class ShortType : public TypeSpecifier
{
public:
    ShortType() : TypeSpecifier(TYPE_SHORT) {}

    virtual string getName() { return "\"ShortType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return ctx.builder.getInt16Ty(); }
};

class IntType : public TypeSpecifier
{
public:
    IntType() : TypeSpecifier(TYPE_INT) {}

    virtual string getName() { return "\"IntType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return ctx.builder.getInt32Ty(); }
};

class LongType : public TypeSpecifier
{
public:
    LongType() : TypeSpecifier(TYPE_LONG) {}

    virtual string getName() { return "\"LongType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return ctx.builder.getInt64Ty(); }
};

class FloatType : public TypeSpecifier
{
public:
    FloatType() : TypeSpecifier(TYPE_FLOAT) {}

    virtual string getName() { return "\"FloatType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return ctx.builder.getFloatTy(); }
};

class DoubleType : public TypeSpecifier
{
public:
    DoubleType() : TypeSpecifier(TYPE_DOUBLE) {}

    virtual string getName() { return "\"DoubleType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return ctx.builder.getDoubleTy(); }
};

class VoidType : public TypeSpecifier
{
public:
    VoidType() : TypeSpecifier(TYPE_VOID) {}

    virtual string getName() { return "\"VoidType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return ctx.builder.getVoidTy(); }
};

class StructType : public TypeSpecifier
{
public:
    StructType() : TypeSpecifier(TYPE_STRUCT) {}

    virtual string getName() { return "\"StructType\""; }
};

class EnumType : public TypeSpecifier
{
public:
    EnumType() : TypeSpecifier(TYPE_ENUM) {}

    virtual string getName() { return "\"EnumType\""; }
};

class UnionType : public TypeSpecifier
{
public:
    UnionType() : TypeSpecifier(TYPE_UNION) {}

    virtual string getName() { return "\"UnionType\""; }
};

class Expression;

class ArrayListType : public TypeSpecifier
{
public:
    uint64_t size;
    vector<Expression *> *elements;

    ArrayListType(vector<Expression *> *e, uint64_t s) : TypeSpecifier(TYPE_ARRAY), elements(e), size(s) {}

    virtual string getName() { return "\"ArrayListType\""; }
    virtual Type *getType(CodeGenerator &ctx) {
        switch(type)
        {
            case TYPE_CHAR:
                return ctx.builder.getInt8Ty();    
            case TYPE_SHORT:
                return ctx.builder.getInt16Ty();
            case TYPE_INT:
                return ctx.builder.getInt32Ty();
            case TYPE_LONG:
                return ctx.builder.getInt64Ty();
            case TYPE_FLOAT:
                return ctx.builder.getFloatTy();
            case TYPE_DOUBLE:
                return ctx.builder.getDoubleTy();
            default:
                return nullptr;
        }
    }
};

#endif