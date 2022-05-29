#ifndef _TYPE_HPP_
#define _TYPE_HPP_

#include "basic.hpp"
#include <llvm/IR/Type.h>
#include <vector>
#include <iostream>

using namespace std;
using namespace llvm;

class CodeGenerator;

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
    enum linkage_type linkage;

    TypeSpecifier(enum type_type t) : type(t), isunsigned(false), qual(nullptr), linkage(LINKAGE_NONE) {}
    TypeSpecifier(enum type_type t, Qualifier *q) : type(t), isunsigned(false), qual(q), linkage(LINKAGE_NONE) {}
    TypeSpecifier(bool flag) : type(TYPE_NONE), isunsigned(flag), qual(nullptr), linkage(LINKAGE_NONE) {}
    TypeSpecifier(enum linkage_type link) : type(TYPE_NONE), isunsigned(false), qual(nullptr), linkage(link) {}

    virtual string getName() { return "\"TypeSpecifier\""; }
    virtual Type *getType(CodeGenerator &ctx) { return nullptr; }
    virtual TypeSpecifier *getRootType() { return nullptr; }
    virtual uint64_t getSize() { return 0; }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return false; }
};

class CharType : public TypeSpecifier
{
public:
    CharType() : TypeSpecifier(TYPE_CHAR) {}

    virtual string getName() { return "\"CharType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize() { return sizeof(char); }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return false; }
};

class ShortType : public TypeSpecifier
{
public:
    ShortType() : TypeSpecifier(TYPE_SHORT) {}

    virtual string getName() { return "\"ShortType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize() { return sizeof(short); }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return false; }
};

class IntType : public TypeSpecifier
{
public:
    IntType() : TypeSpecifier(TYPE_INT) {}
    IntType(Qualifier *q) : TypeSpecifier(TYPE_INT, q) {}

    virtual string getName() { return "\"IntType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize() { return sizeof(int); }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return false; }
};

class LongType : public TypeSpecifier
{
public:
    LongType() : TypeSpecifier(TYPE_LONG) {}

    virtual string getName() { return "\"LongType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize() { return sizeof(long); }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return false; }
};

class FloatType : public TypeSpecifier
{
public:
    FloatType() : TypeSpecifier(TYPE_FLOAT) {}

    virtual string getName() { return "\"FloatType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize() { return sizeof(float); }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return false; }
};

class DoubleType : public TypeSpecifier
{
public:
    DoubleType() : TypeSpecifier(TYPE_DOUBLE) {}

    virtual string getName() { return "\"DoubleType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize() { return sizeof(double); }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return false; }
};

class VoidType : public TypeSpecifier
{
public:
    VoidType() : TypeSpecifier(TYPE_VOID) {}

    virtual string getName() { return "\"VoidType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize() { return sizeof(char); }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return false; }
};

class IterableType : public TypeSpecifier
{
public:
    TypeSpecifier *basictype;

    IterableType(TypeSpecifier *bt, enum type_type type) : basictype(bt), TypeSpecifier(type) {}

    virtual TypeSpecifier *getRootType() { return basictype->getRootType(); }
    virtual uint64_t getSize() = 0;
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return true; }
};

class MyArrayType : public IterableType
{
public:
    uint64_t size;

    MyArrayType(TypeSpecifier *t) : IterableType(t, TYPE_ARRAY), size(0) {}
    MyArrayType(TypeSpecifier *t, uint64_t sz) : IterableType(t, TYPE_ARRAY), size(sz) {}

    virtual string getName() { return "\"MyArrayType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return basictype->getRootType(); }
    virtual uint64_t getSize() { return size * basictype->getSize(); }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return true; }
};

class MyPointerType : public IterableType
{
public:
    MyPointerType(TypeSpecifier *t) : IterableType(t, TYPE_POINTER) {}

    virtual string getName() { return "\"MyPointerType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return basictype->getRootType(); }
    virtual uint64_t getSize() { return sizeof(void *); }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return true; }
};

class Identifier;

class AggregateType : public TypeSpecifier
{
public:
    string name;
    vector<pair<vector<TypeSpecifier *> *, vector<Identifier *> *> *> *members;

    AggregateType(enum type_type t) : name(""), members(nullptr), TypeSpecifier(t) {}
    AggregateType(AggregateType *a) : name(a->name), members(nullptr), TypeSpecifier(a->type) {}

    virtual string getName() { return "\"AggregateType\""; }
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize() = 0;
    virtual bool isAggregateType() { return true; }
    virtual bool isIterableType() { return false; }
    pair<TypeSpecifier *, Identifier *> getMemberDef(Identifier *id);
};

class MyStructType : public AggregateType
{
public:
    MyStructType() : AggregateType(TYPE_STRUCT) {}
    MyStructType(MyStructType *a) : AggregateType(a) {}

    virtual string getName() { return "\"MyStructType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize();
    virtual bool isAggregateType() { return true; }
    virtual bool isIterableType() { return false; }
};

class UnionType : public AggregateType
{
public:
    UnionType() : AggregateType(TYPE_UNION) {}
    UnionType(UnionType *a) : AggregateType(a) {}

    virtual string getName() { return "\"UnionType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize();
    virtual bool isAggregateType() { return true; }
    virtual bool isIterableType() { return false; }
};

class Enumerator {
public:
    string name;
    int val;
    bool hasinit;

    Enumerator(string s) : name(s), val(0), hasinit(false) {}
    Enumerator(string s, int v) : name(s), val(v), hasinit(true) {}
};

class EnumType : public TypeSpecifier
{
public:
    string name;
    vector<Enumerator *> *enumlist;

    EnumType() : name(""), TypeSpecifier(TYPE_ENUM) {}
    EnumType(string s) : name(s), enumlist(nullptr), TypeSpecifier(TYPE_ENUM) {}
    EnumType(vector<Enumerator *> *e) : name(""), enumlist(e), TypeSpecifier(TYPE_ENUM) {}
    EnumType(string s, vector<Enumerator *> *e) : name(s), enumlist(e), TypeSpecifier(TYPE_ENUM) {}

    virtual string getName() { return "\"EnumType\""; }
    virtual Type *getType(CodeGenerator &ctx);
    virtual TypeSpecifier *getRootType() { return this; }
    virtual uint64_t getSize() { return sizeof(int); }
    virtual bool isAggregateType() { return false; }
    virtual bool isIterableType() { return false; }
};

#endif