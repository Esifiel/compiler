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
    Value *var = ctx.module->getGlobalVariable(val, true);
    if (!var)
    {
        Constant *str = ConstantDataArray::getString(ctx.ctx, val);
        var = new GlobalVariable(*ctx.module, str->getType(), true, GlobalValue::PrivateLinkage, str, val);
    }
    // return a string variable as char * but not char array
    return ctx.builder.CreateGEP(var, {ctx.builder.getInt32(0), ctx.builder.getInt32(0)});
}

Value *Identifier::codeGen(CodeGenerator &ctx)
{
    Value *var = ctx.GetVar(name);
    if (!var)
        ctx.error("variable '" + name + "' not found");

    if (ctx.isleft)
    {
        // return as left value
        return var;
    }
    else
    {
        // return as right value
        if (var->getType()->getPointerElementType()->isArrayTy())
            // if the variable is ArrayType, return as a pointer type (pointer of first element)
            return ctx.builder.CreateGEP(var, {ctx.builder.getInt32(0), ctx.builder.getInt32(0)});
        return ctx.builder.CreateLoad(var);
    }
}

static void replace(string &src, string sub, string tar)
{
    string::size_type pos = 0;
    int curpos = 0;
    while((pos = src.find(sub, curpos)) != string::npos)
    {
        src.replace(pos, sub.length(), tar);
        curpos = pos + tar.length();
    }
}

Value *FunctionCall::codeGen(CodeGenerator &ctx)
{
    if(((Identifier *)name)->name == "va_arg")
    {
        Type *type;
        string type_name = ((String *)(*varlist)[1])->val;
        replace(type_name, " ", "");
        if(type_name == "char")
            type = ctx.builder.getInt8Ty();
        else if(type_name == "short")
            type = ctx.builder.getInt16Ty();
        else if(type_name == "int")
            type = ctx.builder.getInt32Ty();
        else if(type_name == "long")
            type = ctx.builder.getInt64Ty();
        else if(type_name == "float")
            type = ctx.builder.getFloatTy();
        else if(type_name == "double")
            type = ctx.builder.getDoubleTy();
        else if(type_name == "char*")
            type = ctx.builder.getInt8PtrTy();
        else if(type_name == "short*")
            type = Type::getInt16PtrTy(ctx.ctx);
        else if(type_name == "int*")
            type = Type::getInt32PtrTy(ctx.ctx);
        else if(type_name == "long*")
            type = Type::getInt64PtrTy(ctx.ctx);
        else if(type_name == "float*")
            type = Type::getFloatTy(ctx.ctx);
        else if(type_name == "double*")
            type = Type::getDoublePtrTy(ctx.ctx);
        else
            ctx.error("not supported type for va_arg yet");
        return ctx.builder.CreateVAArg((*varlist)[0]->codeGen(ctx), type);
    }
    else if(((Identifier *)name)->name == "va_start")
    {
        Function *func = ctx.GetFunction(((Identifier *)name)->name);
        vector<Value *> args;
        args.push_back(ctx.builder.CreatePointerCast((*varlist)[0]->codeGen(ctx), ctx.builder.getInt8PtrTy()));
        return ctx.builder.CreateCall(func, args);
    }
    else
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
                    tmp = ctx.builder.CreateGEP(tmp, {ctx.builder.getInt64(0), ctx.builder.getInt64(0)});
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
}

extern map<string, AggregateType *> aggrdef;

Value *Expression::codeGen(CodeGenerator &ctx)
{
    string varname;
    Value *var, *oldval, *newval, *lv, *rv, *cond;
    Value *idxlist[2];
    bool tmpleft;
    Type *t;
    vector<string> members;
    Expression *expr;
    AggregateType *stype;
    BasicBlock *ifcond, *ifthen, *ifelse, *ifout, *cur;

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
    case OP_SUB:
    case OP_ADD:
        return ctx.CreateBinaryExpr(left->codeGen(ctx), right->codeGen(ctx), op);
    case OP_ANDAND:
    case OP_OROR:
        // short circuit logic
        ifthen = BasicBlock::Create(ctx.ctx, "if.then", ctx.curFunction);
        ifout = BasicBlock::Create(ctx.ctx, "if.out", ctx.curFunction);
        var = ctx.builder.CreateAlloca(Type::getInt1Ty(ctx.ctx), 0, "tmp");
        
        cond = ctx.CreateBinaryExpr(left->codeGen(ctx), ctx.builder.getInt64(0), OP_NEQ);
        ctx.builder.CreateStore(cond, var);
        if(op == OP_ANDAND)
            ctx.builder.CreateCondBr(cond, ifthen, ifout);
        else if(op == OP_OROR)
            ctx.builder.CreateCondBr(cond, ifout, ifthen);

        ctx.builder.SetInsertPoint(ifthen);
        cond = ctx.CreateBinaryExpr(right->codeGen(ctx), ctx.builder.getInt64(0), OP_NEQ);
        ctx.builder.CreateStore(cond, var);
        ctx.builder.CreateBr(ifout);

        ctx.builder.SetInsertPoint(ifout);

        return ctx.builder.CreateLoad(var);
    case OP_NOTNOT:
        lv = left->codeGen(ctx);
        return ctx.CreateBinaryExpr(
            lv,
            lv->getType()->isPointerTy() ? dyn_cast<Value>(ConstantPointerNull::get(dyn_cast<PointerType>(lv->getType()))) : dyn_cast<Value>(ctx.builder.getInt64(0)),
            OP_EQ);
    case OP_NOT:
        return ctx.CreateUnaryExpr(left->codeGen(ctx), OP_NOT);
    case OP_POSITIVE:
    case OP_NEGATIVE:
        var = left->codeGen(ctx);
        cond = ctx.CreateBinaryExpr(
            var,
            var->getType()->isIntegerTy() ? dyn_cast<Constant>(ctx.builder.getInt64(0)) : dyn_cast<Constant>(ConstantFP::get(ctx.ctx, APFloat(0.0))),
            op == OP_POSITIVE ? OP_GEQ : OP_LEQ);
        return ctx.builder.CreateSelect(
            cond,
            var,
            var->getType()->isIntegerTy() ? ctx.builder.CreateNeg(var) : ctx.builder.CreateFNeg(var));
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
    case OP_NOTASSIGN:
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
        case OP_NOTASSIGN:
            newval = ctx.CreateUnaryExpr(oldval, OP_NOT);
            break;
        default:
            newval = nullptr;
            break;
        }
        newval = ctx.CreateCast(newval, var->getType()->getPointerElementType());
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
                if (var->getType()->getPointerElementType()->isArrayTy())
                    // **all array will be returned as pointer**
                    return ctx.builder.CreateGEP(var, {ctx.builder.getInt64(0), ctx.builder.getInt64(0)});
                else
                    return ctx.builder.CreateLoad(var);
            }
        }
        else
            ctx.error("variable '" + ((Identifier *)left)->name + "' is not subscriptable");
    case OP_DEREFERENCE:
        var = left->codeGen(ctx);
        if (var->getType()->isPointerTy())
            return ctx.builder.CreateLoad(var);
        else if (var->getType()->isArrayTy())
            return ctx.builder.CreateExtractValue(var, 0);
        else
            ctx.error("'" + ((Identifier *)left)->name + "' is not iterable");
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

        stype = ctx.structvars[((Identifier *)expr)->name];
        if (op == OP_TO)
            // the difference between . and -> on codegen level is only a load inst
            var = ctx.builder.CreateLoad(var);

        if (stype->type == TYPE_STRUCT)
        {
            // find member offset and get pointer
            members = ctx.structtypes[stype->name];
            var = ctx.builder.CreateGEP(
                var,
                {ctx.builder.getInt32(0),
                 ctx.builder.getInt32(find(members.begin(), members.end(), ((Identifier *)right)->name) - members.begin())});
        }
        else if (stype->type == TYPE_UNION)
        {
            // get pointer of the memory space
            var = ctx.builder.CreateGEP(var, {ctx.builder.getInt32(0), ctx.builder.getInt32(0)});
            // cast to the member's pointer
            var = ctx.builder.CreatePointerCast(var, ctx.uniontypes[stype->name][((Identifier *)right)->name]->getPointerTo());
        }
        else
            ctx.error("'" + ((Identifier *)expr)->name + "' is not a struct or union type");

        if (ctx.isleft)
            return var;
        else if (var->getType()->getPointerElementType()->isArrayTy())
            return ctx.builder.CreateGEP(var, {ctx.builder.getInt32(0), ctx.builder.getInt32(0)});
        else
            return ctx.builder.CreateLoad(var);
    case OP_IFELSE:
        var = addition->codeGen(ctx);
        // select inst of LLVM IR
        if (var->getType()->isPointerTy() || var->getType()->getIntegerBitWidth() != 1)
            // logical operator is omitted
            var = ctx.CreateBinaryExpr(
                var,
                var->getType()->isPointerTy() ? dyn_cast<Value>(ConstantPointerNull::get(dyn_cast<PointerType>(lv->getType()))) : dyn_cast<Value>(ctx.builder.getInt64(0)),
                OP_NEQ);
        return ctx.builder.CreateSelect(var, left->codeGen(ctx), right->codeGen(ctx));
    default:
        ctx.error("not supported operand");
        break;
    }
    return nullptr;
}