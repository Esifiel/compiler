#include "../ast/expression.hpp"
#include "codegen.hpp"
#include <string>
#include <vector>

using namespace std;

Value *Number::codeGen(CodeGenerator &ctx)
{
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
    Value *var = ctx.GetVar(val);
    if (!var)
    {
        Constant *str = ConstantDataArray::getString(ctx.ctx, val);
        var = new GlobalVariable(*ctx.module, str->getType(), true, GlobalValue::PrivateLinkage, str, val);
        ctx.globals[val] = var;
    }
    return var;
}

Value *Identifier::codeGen(CodeGenerator &ctx)
{

    string varname = *name;
    Value *var = ctx.GetVar(varname);
    if (!var)
        ctx.error(string("variable '") + varname + string("' not found"));
    return ctx.builder.CreateLoad(var);
}

Value *Assignment::codeGen(CodeGenerator &ctx)
{
    string varname = *lv->name;
    Value *var = ctx.GetVar(varname);
    Value *newval = ctx.CreateCast(rv->codeGen(ctx), ((AllocaInst *)var)->getAllocatedType());
    // do a store operations
    ctx.builder.CreateStore(newval, var);
    return newval;
}

Value *FunctionCall::codeGen(CodeGenerator &ctx)
{
    Function *func = ctx.GetFunction(*name->name);

    // set the params
    vector<Value *> args;
    auto arg = func->args().begin();
    for (auto &p : *varlist)
    {
        // type conversion to args type
        Value *tmp = p->codeGen(ctx);
        if (arg != func->args().end())
        {
            tmp = ctx.CreateCast(tmp, arg->getType());
            arg++;
        }
        args.push_back(tmp);
    }

    // build a call instruction
    return ctx.builder.CreateCall(func, args);
}

Value *SimpleExpression::codeGen(CodeGenerator &ctx)
{
    Value *lv = left->codeGen(ctx), *rv = nullptr;
    if (right)
        rv = right->codeGen(ctx);
    else
        return lv;

    return ctx.CreateBinaryExpr(lv, rv, op);
}