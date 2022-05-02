#ifndef _TYPE_HPP_
#define _TYPE_HPP_

#include "basic.hpp"
#include "../codegen/codegen.hpp"
#include <llvm/IR/Type.h>
#include <vector>

using namespace std;
using namespace llvm;

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

class IterableType : public TypeSpecifier
{
public:
    TypeSpecifier *basictype;
    uint64_t dim;

    IterableType(TypeSpecifier *bt, enum type_type type) : basictype(bt), TypeSpecifier(type), dim(0) {}
};

class MyArrayType : public IterableType
{
public:
    uint64_t size;

    MyArrayType(TypeSpecifier *t) : IterableType(t, TYPE_ARRAY), size(0) {}
    MyArrayType(TypeSpecifier *t, uint64_t sz) : IterableType(t, TYPE_ARRAY), size(sz) {}

    virtual string getName() { return "\"MyArrayType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return ArrayType::get(basictype->getType(ctx), size); }
};

class MyPointerType : public IterableType
{
public:
    MyPointerType(TypeSpecifier *t) : IterableType(t, TYPE_POINTER) {}

    virtual string getName() { return "\"MyPointerType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return PointerType::get(basictype->getType(ctx), 0); }
};

#endif