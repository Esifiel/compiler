#ifndef _BASIC_HPP_
#define _BASIC_HPP_

#include <string>
#include <llvm/IR/Value.h>

using namespace std;

class CodeGenerator;

union union_num
{
    uint8_t charValue;
    uint16_t shortValue;
    uint32_t intValue;
    uint64_t longValue;
    float_t floatValue;
    double_t doubleValue;
};

enum op_type
{
    OP_NONE,
    OP_EQ, OP_LT, OP_GT, OP_LEQ, OP_GEQ, OP_NEQ,
    OP_ANDAND, OP_OROR, OP_NOTNOT,
    OP_AND, OP_OR, OP_NOT, OP_XOR, OP_SL, OP_SR,
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD,
    OP_INC_FRONT, OP_DEC_FRONT, OP_INC_REAR, OP_DEC_REAR,
    OP_ADDRESSOF, OP_DEREFERENCE,
    OP_POSITIVE, OP_NEGATIVE,
    OP_ASSIGN, OP_MULASSIGN, OP_DIVASSIGN, OP_MODASSIGN, OP_ADDASSIGN, OP_SUBASSIGN,
    OP_SLASSIGN, OP_SRASSIGN, OP_ANDASSIGN, OP_XORASSIGN, OP_ORASSIGN, OP_NOTASSIGN,
    OP_IFELSE,
    OP_CAST,
    OP_COMMA,
    OP_INDEX,
    OP_DOT, OP_TO
};

enum val_type
{
    VAL_NONE,
    VAL_CHAR,
    VAL_SHORT,
    VAL_INT,
    VAL_LONG,
    VAL_FLOAT,
    VAL_DOUBLE
};

enum type_type
{
    TYPE_NONE,
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
    TYPE_ARRAY,
    TYPE_POINTER,
    TYPE_QUALIFIER
};

class Node
{
public:
    Node() {}
    virtual string getName() = 0;
    virtual llvm::Value *codeGen(CodeGenerator &context) { return nullptr; };
};

#endif