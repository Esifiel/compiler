#include "../ast/expression.hpp"
#include "codegen.hpp"
#include <string>
#include <vector>

using namespace std;

Value *Number::codeGen(CodeGenerator &ctx)
{
    return ctx.Num2Constant(this);
}

Value *String::codeGen(CodeGenerator &ctx)
{
    Value *var = ctx.GetVar(val);
    if (!var)
    {
        Constant *str = ConstantDataArray::getString(ctx.ctx, val);
        var = new GlobalVariable(*ctx.module, str->getType(), true, GlobalValue::PrivateLinkage, str, val);
        ctx.blocks.front()[val] = var;
    }
    return var;
}

Value *Identifier::codeGen(CodeGenerator &ctx)
{
    Value *var = ctx.GetVar(name);
    if (!var)
        ctx.error(string("variable '") + name + string("' not found"));
    return ctx.builder.CreateLoad(var);
}

Value *FunctionCall::codeGen(CodeGenerator &ctx)
{
    Function *func = ctx.GetFunction(((Identifier *)name)->name);

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

Value *Expression::codeGen(CodeGenerator &ctx)
{
    string varname;
    Value *var, *oldval, *newval;

    switch (op)
    {
    case OP_EQ:
    case OP_LT:
    case OP_GT:
    case OP_LEQ:
    case OP_GEQ:
    case OP_NEQ:
    case OP_AND:
    case OP_OR:
    case OP_XOR:
    case OP_SL:
    case OP_SR:
    case OP_ADD:
    case OP_SUB:
    case OP_MUL:
    case OP_DIV:
    case OP_MOD:
        return ctx.CreateBinaryExpr(left->codeGen(ctx), right->codeGen(ctx), op);
        // case OP_ANDAND:
        //     out << "&&";
        //     break;
        // case OP_OROR:
        //     out << "||";
        //     break;
        // case OP_NOTNOT:
        //     out << "!";
        //     break;

        // case OP_ADDRESS:
        //     out << "&";
        //     break;

        // case OP_NOT:
        //
        //     return lv.val
        // case OP_POSITIVE:
        //     out << "+";
        //
        // case OP_NEGTIVE:
        //     out << "-";
        //     break;
        //
        // case OP_POINTER:
    case OP_INC_REAR:
    case OP_DEC_REAR:
        varname = ((Identifier *)left)->name;
        var = ctx.GetVar(varname);
        oldval = ctx.builder.CreateLoad(var);
        switch (op)
        {
        case OP_INC_REAR:
            newval = ctx.CreateUnaryExpr(oldval, OP_INC_REAR);
            break;
        case OP_DEC_REAR:
            newval = ctx.CreateUnaryExpr(oldval, OP_DEC_REAR);
            break;
        default:
            return nullptr;
        }
        ctx.builder.CreateStore(newval, var);
        return oldval;
    case OP_INC_FRONT:
    case OP_DEC_FRONT:
    case OP_MULASSIGN:
    case OP_DIVASSIGN:
    case OP_MODASSIGN:
    case OP_ADDASSIGN:
    case OP_SUBASSIGN:
    case OP_SLASSIGN:
    case OP_SRASSIGN:
    case OP_ANDASSIGN:
    case OP_XORASSIGN:
    case OP_ORASSIGN:
        varname = ((Identifier *)left)->name;
        var = ctx.GetVar(varname);
        oldval = ctx.builder.CreateLoad(var);
        switch (op)
        {
        case OP_INC_FRONT:
            newval = ctx.CreateUnaryExpr(oldval, OP_INC_FRONT);
        case OP_DEC_FRONT:
            newval = ctx.CreateUnaryExpr(oldval, OP_DEC_FRONT);
        case OP_MULASSIGN:
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), OP_MUL);
            break;
        case OP_DIVASSIGN:
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), OP_DIV);
            break;
        case OP_MODASSIGN:
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), OP_MOD);
            break;
        case OP_ADDASSIGN:
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), OP_ADD);
            break;
        case OP_SUBASSIGN:
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), OP_SUB);
            break;
        case OP_SLASSIGN:
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), OP_SL);
            break;
        case OP_SRASSIGN:
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), OP_SR);
            break;
        case OP_ANDASSIGN:
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), OP_AND);
            break;
        case OP_XORASSIGN:
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), OP_XOR);
            break;
        case OP_ORASSIGN:
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), OP_OR);
            break;
        default:
            return nullptr;
        }
        ctx.builder.CreateStore(newval, var);
        return newval;
    case OP_ASSIGN:
        varname = ((Identifier *)left)->name;
        var = ctx.GetVar(varname);
        newval = ctx.CreateCast(right->codeGen(ctx), ((AllocaInst *)var)->getAllocatedType());
        ctx.builder.CreateStore(newval, var);
        return newval;
    // case OP_IFELSE:
    //     out << "? :";
    //     break;
    // case OP_CAST:
    //     out << "()";
    //     break;
    // case OP_COMMA:
    //     out << ",";
    //     break;
    default:
        return nullptr;
    }
}

// Value *SimpleExpression::codeGen(CodeGenerator &ctx)
// {
//     Value *lv = left->codeGen(ctx), *rv = nullptr;
//     if (right)
//         rv = right->codeGen(ctx);
//     else
//         return lv;

//     return ctx.CreateBinaryExpr(lv, rv, op);
// }