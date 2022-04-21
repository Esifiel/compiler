#ifndef _EXPRESSION_HPP_
#define _EXPRESSION_HPP_

#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include "basic.hpp"

using namespace std;

class Expression : public Node
{
public:
    Expression() {}

    virtual string getName() { return "\"Expression\""; }
};

union union_num
{
    uint8_t charValue;
    uint16_t shortValue;
    uint32_t intValue;
    uint64_t longValue;
    float_t floatValue;
    double_t doubleValue;
};

enum val_type
{
    VAL_CHAR,
    VAL_SHORT,
    VAL_INT,
    VAL_LONG,
    VAL_FLOAT,
    VAL_DOUBLE
};

class CodeGenerator;

class Number : public Expression
{
public:
    uint8_t buf[8];
    enum val_type type;

    Number(union union_num u, enum val_type t) : type(t) { memcpy(buf, &u, 8); }
    
    virtual string getName() { return "\"Number\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
    
    uint8_t charView() { return *(uint8_t *)buf; }
    uint16_t shortView() { return *(uint16_t *)buf; }
    uint32_t intView() { return *(uint32_t *)buf; }
    uint64_t longView() { return *(uint64_t *)buf; }
    float_t floatView() { return *(float_t *)buf; }
    double_t doubleView() { return *(double_t *)buf; }
};

class String : public Expression
{
public:
    string val;

    String(string s) : val(s) {}
    
    virtual string getName() { return "\"String\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class Identifier : public Expression
{
public:
    string *name;
    uint64_t idx;

    Identifier(string *v) : name(v) { idx = -1; }
    Identifier(string *v, uint64_t i) : name(v), idx(i) {}

    virtual string getName() { return "\"Identifier\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class Assignment : public Expression
{
public:
    Identifier *lv;
    Expression *rv;

    Assignment(Identifier *l, Expression *r) : lv(l), rv(r) {}
    
    virtual string getName() { return "\"Assignment\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class FunctionCall : public Expression
{
public:
    Identifier *name;
    vector<Expression *> *varlist;

    FunctionCall(Identifier *n, vector<Expression *> *l) : name(n), varlist(l) {}

    virtual string getName() { return "\"FunctionCall\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

enum op_type {
    NONE,

    OP_EQ,
    OP_LT,
    OP_GT,
    OP_LEQ,
    OP_GEQ,
    OP_NEQ,
    OP_ANDAND,
    OP_OROR,

    OP_AND,
    OP_OR,
    OP_NOT,
    OP_XOR,
    
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD
};

class SimpleExpression : public Expression
{
public:
    Expression *left;
    enum op_type op;
    Expression *right;

    SimpleExpression(Expression *l) : left(l)
    {
        op = NONE;
        right = nullptr;
    }
    SimpleExpression(Expression *l, enum op_type o, Expression *r) : left(l), op(o), right(r) {}

    virtual string getName() { return "\"SimpleExpression\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

#endif