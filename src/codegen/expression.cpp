#include "../ast/expression.hpp"
#include "codegen.hpp"
#include <string>
#include <vector>
#include <algorithm>

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

    if (ctx.isleft)
        // return as left value
        return var;
    else
    {
        // return as right value
        if (var->getType()->getPointerElementType()->isArrayTy())
            // if the variable is ArrayType, return as a pointer type (pointer of first element)
            return ctx.builder.CreateGEP(var, {ctx.builder.getInt32(0), ctx.builder.getInt32(0)});
        return ctx.builder.CreateLoad(var);
    }
}

Value *FunctionCall::codeGen(CodeGenerator &ctx)
{
    Function *func = ctx.GetFunction(((Identifier *)name)->name);

    // set the params
    vector<Value *> args;
    auto arg = func->args().begin();
    auto p = varlist->begin();
    for (; p != varlist->end(); p++)
    {
        // type conversion to args type
        Value *tmp = (*p)->codeGen(ctx);
        if (arg != func->args().end())
        {
            if (tmp->getType()->isArrayTy() && arg->getType()->isPointerTy())
            {
                // pass array to pointer arg
                bool tmpleft = ctx.isleft;
                ctx.isleft = true;
                tmp = (*p)->codeGen(ctx);
                Value *idxlist[] = {ctx.builder.getInt64(0), ctx.builder.getInt64(0)};
                tmp = ctx.builder.CreateGEP(tmp, ArrayRef<Value *>(idxlist, 2));
                ctx.isleft = tmpleft;
            }
            else
                tmp = ctx.CreateCast(tmp, arg->getType());
            arg++;
        }
        args.push_back(tmp);
    }

    // build a call instruction
    return ctx.builder.CreateCall(func, args);
}

extern map<string, AggregateType *> aggrdef;

Value *Expression::codeGen(CodeGenerator &ctx)
{
    string varname;
    Value *var, *oldval, *newval, *lv, *rv;
    Value *idxlist[2];
    bool tmpleft;
    Type *t;
    vector<string> members;
    Expression *expr;

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
    case OP_MUL:
    case OP_DIV:
    case OP_MOD:
        return ctx.CreateBinaryExpr(left->codeGen(ctx), right->codeGen(ctx), op);
    case OP_SUB:
    case OP_ADD:
        // if a variable loaded as right value and is pointer type, it means a pointer addition
        lv = left->codeGen(ctx);
        rv = right->codeGen(ctx);
        if( !lv->getType()->isPointerTy() && \
            !lv->getType()->isArrayTy() && \
            !rv->getType()->isPointerTy() && \
            !rv->getType()->isArrayTy())
            return ctx.CreateBinaryExpr(lv, rv, op);
        else
        {
            if(op == OP_SUB)
                rv = ctx.builder.CreateFNeg(rv);

            if (lv->getType()->isPointerTy())
                return ctx.builder.CreateGEP(lv, rv);
            if (lv->getType()->isArrayTy())
            {
                // TODO: getting array's GEP may need to be refactored as a static function
                idxlist[1] = rv;
                idxlist[0] = ConstantInt::get(idxlist[1]->getType(), 0);
                return ctx.builder.CreateGEP(lv, ArrayRef<Value *>(idxlist, 2));
            }
            if (rv->getType()->isPointerTy())
                return ctx.builder.CreateGEP(rv, lv);
            if (rv->getType()->isArrayTy())
            {
                idxlist[1] = lv;
                idxlist[0] = ConstantInt::get(idxlist[1]->getType(), 0);
                return ctx.builder.CreateGEP(lv, ArrayRef<Value *>(idxlist, 2));
            }
        }
    case OP_ANDAND:
        lv = left->codeGen(ctx);
        rv = right->codeGen(ctx);
        return ctx.CreateBinaryExpr(
            ctx.CreateBinaryExpr(lv, ctx.builder.getInt64(0), OP_NEQ),
            ctx.CreateBinaryExpr(rv, ctx.builder.getInt64(0), OP_NEQ),
            OP_AND);
    case OP_OROR:
        lv = left->codeGen(ctx);
        rv = right->codeGen(ctx);
        return ctx.CreateBinaryExpr(
            ctx.CreateBinaryExpr(lv, ctx.builder.getInt64(0), OP_NEQ),
            ctx.CreateBinaryExpr(rv, ctx.builder.getInt64(0), OP_NEQ),
            OP_OR);
    case OP_NOTNOT:
        lv = left->codeGen(ctx);
        return ctx.CreateBinaryExpr(
            lv,
            lv->getType()->isPointerTy() ? dyn_cast<Value>(ConstantPointerNull::get(dyn_cast<PointerType>(lv->getType()))) : dyn_cast<Value>(ctx.builder.getInt64(0)),
            OP_EQ);
    case OP_NOT:
        return ctx.CreateUnaryExpr(left->codeGen(ctx), OP_NOT);
    // case OP_POSITIVE:
    //     out << "+";
    //
    // case OP_NEGATIVE:
    //     out << "-";
    //     break;
    case OP_INC_REAR:
    case OP_DEC_REAR:
        ctx.isleft = true;
        var = left->codeGen(ctx);
        ctx.isleft = false;
        oldval = ctx.builder.CreateLoad(var);
        newval = ctx.CreateUnaryExpr(oldval, op);
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
        ctx.isleft = true;
        var = left->codeGen(ctx);
        ctx.isleft = false;
        oldval = ctx.builder.CreateLoad(var);
        switch (op)
        {
        case OP_INC_FRONT:
            newval = ctx.CreateUnaryExpr(oldval, OP_INC_FRONT);
            break;
        case OP_DEC_FRONT:
            newval = ctx.CreateUnaryExpr(oldval, OP_DEC_FRONT);
            break;
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
            newval = nullptr;
            break;
        }
        ctx.builder.CreateStore(newval, var);
        return newval;
    case OP_ASSIGN:
        ctx.isleft = true;
        var = left->codeGen(ctx);
        ctx.isleft = false;
        newval = ctx.CreateCast(right->codeGen(ctx), var->getType()->getPointerElementType());
        ctx.builder.CreateStore(newval, var);
        return newval;
    case OP_CAST:
        return ctx.CreateCast(right->codeGen(ctx), ((AggregateType *)(left->type))->getType(ctx));
    case OP_COMMA:
        left->codeGen(ctx);
        return right->codeGen(ctx);
    case OP_INDEX:
        // fetch the iterable type
        tmpleft = ctx.isleft;
        ctx.isleft = true;
        var = left->codeGen(ctx);
        ctx.isleft = tmpleft;
        // pointer or array
        if (var->getType()->getPointerElementType()->isPointerTy())
        {
            var = ctx.builder.CreateLoad(var);
            if (ctx.isleft)
            {
                ctx.isleft = false;
                rv = right->codeGen(ctx);
                ctx.isleft = true;
                return ctx.builder.CreateGEP(var, rv);
            }
            else
                return ctx.builder.CreateLoad(ctx.builder.CreateGEP(var, right->codeGen(ctx)));
        }
        else if (var->getType()->getPointerElementType()->isArrayTy())
        {
            // need left value
            if (ctx.isleft)
            {
                ctx.isleft = false;
                idxlist[1] = right->codeGen(ctx);
                ctx.isleft = true;
                idxlist[0] = ConstantInt::get(idxlist[1]->getType(), 0);
                return ctx.builder.CreateGEP(var, ArrayRef<Value *>(idxlist, 2));
            }
            else
            {
                idxlist[1] = right->codeGen(ctx);
                idxlist[0] = ConstantInt::get(idxlist[1]->getType(), 0);
                var = ctx.builder.CreateGEP(var, ArrayRef<Value *>(idxlist, 2));
                if(var->getType()->getPointerElementType()->isArrayTy())
                    // **all array will be returned as pointer**
                    return ctx.builder.CreateGEP(var, {ctx.builder.getInt64(0), ctx.builder.getInt64(0)});
                else
                    return ctx.builder.CreateLoad(var);
            }
        }
        else
            ctx.error("not supported operand of [] operator");
    case OP_DEREFERENCE:
        break;
    case OP_ADDRESSOF:
        ctx.isleft = true;
        var = left->codeGen(ctx);
        ctx.isleft = false;
        return var;
    case OP_DOT:
    case OP_TO:
        tmpleft = ctx.isleft;
        ctx.isleft = true;
        var = left->codeGen(ctx);
        ctx.isleft = tmpleft;

        // get varname
        expr = left;
        while (expr->getName() != "\"Identifier\"")
            expr = expr->left;

        // find member offset and get pointer
        members = ctx.structtypes[ctx.structvars[((Identifier *)expr)->name]->name];
        if (op == OP_TO)
            // the difference between . and -> on codegen level is only a load inst
            var = ctx.builder.CreateLoad(var);
        var = ctx.builder.CreateGEP(
            var,
            {ctx.builder.getInt32(0),
             ctx.builder.getInt32(find(members.begin(), members.end(), ((Identifier *)right)->name) - members.begin())});
        if (ctx.isleft)
            return var;
        else if (var->getType()->getPointerElementType()->isArrayTy())
            return ctx.builder.CreateGEP(var, {ctx.builder.getInt32(0), ctx.builder.getInt32(0)});
        else
            return ctx.builder.CreateLoad(var);
    case OP_IFELSE:
        var = addition->codeGen(ctx);
        // select inst of LLVM IR
        if(var->getType()->isPointerTy() || var->getType()->getIntegerBitWidth() != 1)
            // logical operator is omitted
            var = ctx.CreateBinaryExpr(
                var,
                var->getType()->isPointerTy() ? dyn_cast<Value>(ConstantPointerNull::get(dyn_cast<PointerType>(lv->getType()))) : dyn_cast<Value>(ctx.builder.getInt64(0)),
                OP_NEQ);
        return ctx.builder.CreateSelect(var, left->codeGen(ctx), right->codeGen(ctx));
    default:
        return nullptr;
    }
}