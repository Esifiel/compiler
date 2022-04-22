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
    OP_ADDRESS, OP_POINTER,
    OP_POSITIVE, OP_NEGTIVE,
    OP_ASSIGN, OP_MULASSIGN, OP_DIVASSIGN, OP_MODASSIGN, OP_ADDASSIGN, OP_SUBASSIGN,
    OP_SLASSIGN, OP_SRASSIGN, OP_ANDASSIGN, OP_XORASSIGN, OP_ORASSIGN,
    OP_IFELSE,
    OP_CAST,
    OP_COMMA
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

class Node
{
public:
    Node() {}
    virtual ~Node() {}
    virtual string getName() = 0;
    virtual llvm::Value *codeGen(CodeGenerator &context) { return nullptr; };
};

#endif