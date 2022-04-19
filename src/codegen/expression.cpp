#include "../ast/expression.hpp"
#include "codegen.hpp"

Value *Number::codeGen(CodeGenerator &ctx)
{
    cout << "number" << type << endl;
    switch (type)
    {
    case VAL_CHAR:
        return ConstantInt::get(Type::getInt8Ty(ctx.ctx), charView());
    case VAL_SHORT:
        return ConstantInt::get(Type::getInt16Ty(ctx.ctx), shortView());
    case VAL_INT:
        return ConstantInt::get(Type::getInt32Ty(ctx.ctx), intView());
    case VAL_LONG:
        return ConstantInt::get(Type::getInt64Ty(ctx.ctx), longView());
    case VAL_FLOAT:
        return ConstantFP::get(Type::getFloatTy(ctx.ctx), floatView());
    case VAL_DOUBLE:
        return ConstantFP::get(Type::getDoubleTy(ctx.ctx), doubleView());
    default:
        return nullptr;
    }
}

Value *String::codeGen(CodeGenerator &ctx)
{
}

Value *Identifier::codeGen(CodeGenerator &ctx)
{
}

Value *Parameter::codeGen(CodeGenerator &ctx)
{
}

Value *Assignment::codeGen(CodeGenerator &ctx)
{
}

Value *FunctionCall::codeGen(CodeGenerator &ctx)
{
}

Value *SimpleExpression::codeGen(CodeGenerator &ctx)
{
}