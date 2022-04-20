#include "../ast/expression.hpp"
#include "codegen.hpp"

Value *Number::codeGen(CodeGenerator &ctx)
{
    // switch (type)
    // {
    // case VAL_CHAR:
    //     return ConstantInt::get(Type::getInt8Ty(ctx.ctx), charView());
    // case VAL_SHORT:
    //     return ConstantInt::get(Type::getInt16Ty(ctx.ctx), shortView());
    // case VAL_INT:
    //     return ConstantInt::get(Type::getInt32Ty(ctx.ctx), intView());
    // case VAL_LONG:
    //     return ConstantInt::get(Type::getInt64Ty(ctx.ctx), longView());
    // case VAL_FLOAT:
    //     return ConstantFP::get(Type::getFloatTy(ctx.ctx), floatView());
    // case VAL_DOUBLE:
    //     return ConstantFP::get(Type::getDoubleTy(ctx.ctx), doubleView());
    // default:
    //     return nullptr;
    // }
    Type *rettype = ctx.curFunction->getReturnType();
    if (rettype->isIntegerTy())
    {
        switch (rettype->getIntegerBitWidth())
        {
        case 8:
            return ConstantInt::get(Type::getInt8Ty(ctx.ctx), charView());
        case 16:
            return ConstantInt::get(Type::getInt16Ty(ctx.ctx), shortView());
        case 32:
            return ConstantInt::get(Type::getInt32Ty(ctx.ctx), intView());
        case 64:
            return ConstantInt::get(Type::getInt64Ty(ctx.ctx), longView());
        default:
            return nullptr;
        }
    }
    else if (rettype->isFloatTy())
        return ConstantFP::get(Type::getFloatTy(ctx.ctx), floatView());
    else if (rettype->isFloatTy())
        return ConstantFP::get(Type::getDoubleTy(ctx.ctx), doubleView());
    else
        return nullptr;
}

Value *String::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *Identifier::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *Parameter::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *Assignment::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *FunctionCall::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *SimpleExpression::codeGen(CodeGenerator &ctx)
{
    // Value *lv = left->codeGen(), *rv = nullptr;
    // if (right)
    //     rv = right->codeGen();
    // else
    //     return lv;

    // switch (op)
    // {
    // case OP_EQ:
    //     return
    // case OP_LT:

    // case OP_GT:
    // case OP_LEQ:
    // case OP_GEQ:
    // case OP_NEQ:
    // case OP_ANDAND:
    // case OP_OROR:
    //     break;
    // default:
    //     return nullptr;
    // }
}