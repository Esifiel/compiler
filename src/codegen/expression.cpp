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
        ctx.globals[val] = var;
    }
    return var;
}

Value *Identifier::codeGen(CodeGenerator &ctx)
{
    string varname = ((Identifier *)name)->getIdName();
    Value *var = ctx.GetVar(varname);
    if (!var)
        ctx.error(string("variable '") + varname + string("' not found"));
    return ctx.builder.CreateLoad(var);
}

Value *FunctionCall::codeGen(CodeGenerator &ctx)
{
    Function *func = ctx.GetFunction(((Identifier *)name)->getIdName());

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
    Value *var;
    Value *newval;

    switch (op)
    {

        // case OP_EQ:
        //     out << "==";
        //     break;
        // case OP_LT:
        //     out << "<";
        //     break;
        // case OP_GT:
        //     out << ">";
        //     break;
        // case OP_LEQ:
        //     out << "<=";
        //     break;
        // case OP_GEQ:
        //     out << ">=";
        //     break;
        // case OP_NEQ:
        //     out << "!=";
        //     break;
        // case OP_ANDAND:
        //     out << "&&";
        //     break;
        // case OP_OROR:
        //     out << "||";
        //     break;
        // case OP_NOTNOT:
        //     out << "!";
        //     break;
        // case OP_AND:
        // case OP_ADDRESS:
        //     out << "&";
        //     break;
        // case OP_OR:
        //     out << "|";
        //     break;
        // case OP_NOT:
        //     out << "~";
        //     break;
        // case OP_XOR:
        //     out << "^";
        //     break;
        // case OP_SL:
        //     out << "<<";
        //     break;
        // case OP_SR:
        //     out << ">>";
        //     break;
        // case OP_ADD:
        //     return lv.val
        // case OP_POSITIVE:
        //     out << "+";
        // case OP_SUB:
        // case OP_NEGTIVE:
        //     out << "-";
        //     break;
        // case OP_MUL:
        // case OP_POINTER:
        //     out << "*";
        //     break;
        // case OP_DIV:
        //     out << "/";
        //     break;
        // case OP_MOD:
        //     out << "%";
        //     break;
        // case OP_INC_FRONT:
        // case OP_INC_REAR:
        //     out << "++";
        //     break;
        // case OP_DEC_FRONT:
        // case OP_DEC_REAR:
        //     out << "--";
        //     break;
    case OP_ASSIGN:
        varname = ((Identifier *)left)->getIdName();
        var = ctx.GetVar(varname);
        newval = ctx.CreateCast(right->codeGen(ctx), ((AllocaInst *)var)->getAllocatedType());
        // do a store operations
        ctx.builder.CreateStore(newval, var);
        return newval;
    // case OP_MULASSIGN:
    //     out << "*=";
    //     break;
    // case OP_DIVASSIGN:
    //     out << "/=";
    //     break;
    // case OP_MODASSIGN:
    //     out << "%=";
    //     break;
    // case OP_ADDASSIGN:
    //     out << "+=";
    //     break;
    // case OP_SUBASSIGN:
    //     out << "-=";
    //     break;
    // case OP_SLASSIGN:
    //     out << "<<=";
    //     break;
    // case OP_SRASSIGN:
    //     out << ">>=";
    //     break;
    // case OP_ANDASSIGN:
    //     out << "&=";
    //     break;
    // case OP_XORASSIGN:
    //     out << "^=";
    //     break;
    // case OP_ORASSIGN:
    //     out << "|=";
    //     break;
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