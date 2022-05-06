#ifndef _TYPE_HPP_
#define _TYPE_HPP_

#include "basic.hpp"
#include "../codegen/codegen.hpp"
#include <llvm/IR/Type.h>
#include <vector>

using namespace std;
using namespace llvm;

class Qualifier : public Node
{
public:
    bool isconst, isvolatile;
    uint64_t pcnt;

    Qualifier() : isconst(false), isvolatile(false), pcnt(0) {}
    Qualifier(uint64_t i) : isconst(false), isvolatile(false), pcnt(i) {}
    virtual string getName() { return "\"Qualifier\""; }
};

class TypeSpecifier : public Node
{
public:
    enum type_type type;
    bool isunsigned;
    Qualifier *qual;

    TypeSpecifier(enum type_type t) : type(t), isunsigned(false), qual(nullptr) {}
    TypeSpecifier(enum type_type t, Qualifier *q) : type(t), isunsigned(false), qual(q) {}

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
    IntType(Qualifier *q) : TypeSpecifier(TYPE_INT, q) {}

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

class IterableType : public TypeSpecifier
{
public:
    TypeSpecifier *basictype;

    IterableType(TypeSpecifier *bt, enum type_type type) : basictype(bt), TypeSpecifier(type) {}
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

class AggregateType : public TypeSpecifier
{
public:
    string name;
    vector<pair<TypeSpecifier *, vector<Identifier *> *> *> *members;

    AggregateType(enum type_type t) : name(""), members(nullptr), TypeSpecifier(t) {} 

    virtual string getName() { return "\"AggregateType\""; }
};

class MyStructType : public AggregateType
{
public:
    MyStructType() : AggregateType(TYPE_STRUCT) {}

    virtual string getName() { return "\"MyStructType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return nullptr; }
};

class UnionType : public AggregateType
{
public:
    UnionType() : AggregateType(TYPE_UNION) {}

    virtual string getName() { return "\"UnionType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return nullptr; }
};

class EnumType : public TypeSpecifier
{
public:
    string name;
    
    EnumType() : TypeSpecifier(TYPE_ENUM) {}

    virtual string getName() { return "\"EnumType\""; }
    virtual Type *getType(CodeGenerator &ctx) { return nullptr; }
};

#endif