#ifndef _EXPRESSION_HPP_
#define _EXPRESSION_HPP_

#include <stdint.h>
#include <string>
#include <vector>
#include <iostream>
#include "basic.hpp"
#include "type.hpp"

using namespace std;

class CodeGenerator;

class Expression : public Node
{
public:
    Expression *left;
    Expression *right;
    Expression *addition;
    enum op_type op;
    TypeSpecifier *type;

    // terminal expr
    Expression() : left(nullptr), right(nullptr), addition(nullptr), op(OP_NONE), type(nullptr) {}
    // unary expr
    Expression(Expression *l, enum op_type o) : left(l), right(nullptr), addition(nullptr), op(o), type(nullptr) {}
    // binary expr
    Expression(Expression *l, Expression *r, enum op_type o) : left(l), right(r), addition(nullptr), op(o), type(nullptr) {}
    // trinary expr
    Expression(Expression *l, Expression *r, Expression *a, enum op_type o) : left(l), right(r), addition(a), op(o), type(nullptr) {}
    // for type casting
    Expression(TypeSpecifier *t) : left(nullptr), right(nullptr), addition(nullptr), op(OP_NONE), type(t) {}

    virtual string getName() { return "\"Expression\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class Number : public Expression
{
public:
    uint8_t buf[8];
    enum val_type valtype;

    Number() : valtype(VAL_NONE) {}
    Number(union union_num u, TypeSpecifier *t, enum val_type v) : Expression(t), valtype(v) { memcpy(buf, &u, 8); }

    virtual string getName() { return "\"Number\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);

    uint8_t charView() { return *(uint8_t *)buf; }
    uint16_t shortView() { return *(uint16_t *)buf; }
    uint32_t intView() {
        switch (valtype)
        {
        case VAL_CHAR:
            return (uint32_t)charView();
        case VAL_SHORT:
            return (uint32_t)shortView();
        case VAL_LONG:
            // return (uint32_t)intView();
            return 0;
        case VAL_FLOAT:
            return (uint32_t)floatView();
        case VAL_DOUBLE:
            return (uint32_t)doubleView();
        case VAL_INT:
        default:
            return *(uint32_t *)buf;
        }
    }
    uint64_t longView()
    {
        switch (valtype)
        {
        case VAL_CHAR:
            return (uint64_t)charView();
        case VAL_SHORT:
            return (uint64_t)shortView();
        case VAL_INT:
            return (uint64_t)intView();
        case VAL_FLOAT:
            return (uint64_t)floatView();
        case VAL_DOUBLE:
            return (uint64_t)doubleView();
        case VAL_LONG:
        default:
            return *(uint64_t *)buf;
        }
    }
    float_t floatView() { return *(float_t *)buf; }
    double_t doubleView()
    {
        switch (valtype)
        {
        case VAL_CHAR:
            return (double_t)charView();
        case VAL_SHORT:
            return (double_t)shortView();
        case VAL_INT:
            return (double_t)intView();
        case VAL_LONG:
            return (double_t)longView();
        case VAL_FLOAT:
            return (double_t)floatView();
        case VAL_DOUBLE:
        default:
            return *(double_t *)buf;
        }
    }
    bool isInteger() { return valtype == VAL_CHAR || valtype == VAL_SHORT || valtype == VAL_INT || valtype == VAL_LONG; }
    bool isFloat() { return !isInteger(); }
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
    string name;
    Expression *init;
    Qualifier *qual;

    Identifier(string v) : name(v), init(nullptr), qual(nullptr) {}
    Identifier(string v, Expression *ini) : name(v), init(ini), qual(nullptr) {}

    virtual string getName() { return "\"Identifier\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class FunctionCall : public Expression
{
public:
    Expression *name;
    vector<Expression *> *varlist;

    FunctionCall(Expression *n, vector<Expression *> *l) : name(n), varlist(l) {}

    virtual string getName() { return "\"FunctionCall\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

#endif