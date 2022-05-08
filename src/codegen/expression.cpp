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
        if(var->getType()->getPointerElementType()->isArrayTy())
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
    for (; p != varlist->end();p++)
    {
        // type conversion to args type
        Value *tmp = (*p)->codeGen(ctx);
        if(arg != func->args().end())
        {
            if(tmp->getType()->isArrayTy() && arg->getType()->isPointerTy())
            {
                // pass array to pointer arg
                bool tmpleft = ctx.isleft;
                ctx.isleft = true;
                tmp = (*p)->codeGen(ctx);
                Value *idxlist[] = {ConstantInt::get(Type::getInt64Ty(ctx.ctx), 0), ConstantInt::get(Type::getInt64Ty(ctx.ctx), 0)};
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

Value *Expression::codeGen(CodeGenerator &ctx)
{
    string varname;
    Value *var, *oldval, *newval, *lv, *rv;
    Value *idxlist[2];
    bool tmpleft;
    Type *t;
    vector<string> members;

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
    case OP_SUB:
    case OP_MUL:
    case OP_DIV:
    case OP_MOD:
        return ctx.CreateBinaryExpr(left->codeGen(ctx), right->codeGen(ctx), op);
    case OP_ADD:
        // if a variable loaded as right value and is pointer type, it means a pointer addition
        lv = left->codeGen(ctx);
        if (lv->getType()->isPointerTy())
            return ctx.builder.CreateGEP(lv, right->codeGen(ctx));
        if(lv->getType()->isArrayTy())
        {
            // TODO: getting array's GEP may need to be refactored as a static function
            idxlist[1] = right->codeGen(ctx);
            idxlist[0] = ConstantInt::get(idxlist[1]->getType(), 0);
            return ctx.builder.CreateGEP(lv, ArrayRef<Value *>(idxlist, 2));
        }
        rv = right->codeGen(ctx);
        if (rv->getType()->isPointerTy())
            return ctx.builder.CreateGEP(rv, lv);
        if(rv->getType()->isArrayTy())
        {
            idxlist[1] = lv;
            idxlist[0] = ConstantInt::get(idxlist[1]->getType(), 0);
            return ctx.builder.CreateGEP(lv, ArrayRef<Value *>(idxlist, 2));
        }
        return ctx.CreateBinaryExpr(lv, rv, op);
    case OP_ANDAND:
    case OP_OROR:
        lv = left->codeGen(ctx);
        rv = right->codeGen(ctx);
        return ctx.CreateBinaryExpr(
            ctx.CreateBinaryExpr(lv, ConstantInt::get(Type::getInt64Ty(ctx.ctx), 0), OP_NEQ),
            ctx.CreateBinaryExpr(rv, ConstantInt::get(Type::getInt64Ty(ctx.ctx), 0), OP_NEQ),
            op
        );
    case OP_NOTNOT:
        return ctx.CreateBinaryExpr(lv, ConstantInt::get(Type::getInt64Ty(ctx.ctx), 0), OP_EQ);
    case OP_NOT:
        return ctx.CreateUnaryExpr(lv, OP_NOT);
    // case OP_POSITIVE:
    //     out << "+";
    //
    // case OP_NEGTIVE:
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
        if(right)
            newval = ctx.CreateUnaryExpr(oldval, op);
        else
            newval = ctx.CreateBinaryExpr(oldval, right->codeGen(ctx), op);
        ctx.builder.CreateStore(newval, var);
        return newval;
    case OP_ASSIGN:
        ctx.isleft = true;
        var = left->codeGen(ctx);
        ctx.isleft = false;
        newval = ctx.CreateCast(right->codeGen(ctx), var->getType()->getPointerElementType());
        ctx.builder.CreateStore(newval, var);
        return newval;
    // case OP_IFELSE:
    //     out << "? :";
    //     break;
    // case OP_CAST:
    //     out << "()";
    //     break;
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
                return ctx.builder.CreateLoad(ctx.builder.CreateGEP(var, ArrayRef<Value *>(idxlist, 2)));
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
        varname = ((Identifier *)left)->name;
        var = ctx.GetVar(varname);
        // find member offset and get pointer
        members = ctx.structtypes[ctx.structvars[varname]->name];
        var = ctx.builder.CreateGEP(
            var,
            {
                ctx.builder.getInt32(0),
                ctx.builder.getInt32(find(members.begin(), members.end(), ((Identifier *)right)->name) - members.begin())
            }
        );
        if(ctx.isleft)
            return var;
        else
            if(var->getType()->getPointerElementType()->isArrayTy())
                return ctx.builder.CreateGEP(var, {ctx.builder.getInt32(0), ctx.builder.getInt32(0)});
            else
                return ctx.builder.CreateLoad(var);
    case OP_TO:
        
    default:
        return nullptr;
    }
}