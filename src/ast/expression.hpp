#ifndef _EXPRESSION_HPP_
#define _EXPRESSION_HPP_

#include <stdint.h>
#include <string>
#include <vector>
#include "basic.hpp"

using namespace std;

class CodeGenerator;
class TypeSpecifier;

class Expression : public Node
{
public:
    Expression *left;
    Expression *right;
    Expression *addition;
    enum op_type op;

    // terminal expr
    Expression() : left(nullptr), right(nullptr), addition(nullptr), op(OP_NONE) {}
    // unary expr
    Expression(Expression *l, enum op_type o) : left(l), right(nullptr), addition(nullptr), op(o) {}
    // binary expr
    Expression(Expression *l, Expression *r, enum op_type o) : left(l), right(r), addition(nullptr), op(o) {}
    // trinary expr
    Expression(Expression *l, Expression *r, Expression *a, enum op_type o) : left(l), right(r), addition(a), op(o) {}

    virtual string getName() { return "\"Expression\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

class Number : public Expression
{
public:
    uint8_t buf[8];
    TypeSpecifier *type;
    enum val_type valtype;

    Number(union union_num u, TypeSpecifier *t, enum val_type v) : type(t), valtype(v) { memcpy(buf, &u, 8); }

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
    string name;
    Expression *init;
    bool ispointer;
    Expression *index;

    Identifier(string v) : name(v), init(nullptr), index(nullptr), ispointer(false) {}
    Identifier(string v, Expression *ini, Expression *idx) : name(v), init(ini), index(idx), ispointer(false) {}

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