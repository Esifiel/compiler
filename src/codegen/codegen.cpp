#include "../ast/expression.hpp"
#include "../ast/type.hpp"
#include "codegen.hpp"
#include <stdio.h>

// initialize the context
CodeGenerator::CodeGenerator() : builder(ctx), curFunction(nullptr), isglobal(false), isleft(false)
{
    module = new Module("main", ctx);
    functions.clear();
    blocks.clear();
    structtypes.clear();
    structvars.clear();
    // top level (global) blocks
    blocks.push_front(map<string, Value *>());

    // add some libc variable and function
    vector<Type *> args;
    GlobalVariable *v;
    // printf
    args.clear();
    args.push_back(Type::getInt8PtrTy(ctx));
    // true: is variable args
    FunctionType *functype = FunctionType::get(Type::getInt32Ty(ctx), args, true);
    Function *func = Function::Create(functype, Function::ExternalLinkage, "printf", module);
    func->setCallingConv(CallingConv::C);
    functions["printf"] = func;

    // scanf
    args.clear();
    args.push_back(Type::getInt8PtrTy(ctx));
    functype = FunctionType::get(Type::getInt32Ty(ctx), args, true);
    func = Function::Create(functype, Function::ExternalLinkage, "scanf", module);
    func->setCallingConv(CallingConv::C);
    functions["scanf"] = func;

    // puts
    args.clear();
    args.push_back(Type::getInt8PtrTy(ctx));
    functype = FunctionType::get(Type::getInt32Ty(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "puts", module);
    func->setCallingConv(CallingConv::C);
    functions["puts"] = func;

    // strlen
    args.clear();
    args.push_back(Type::getInt8PtrTy(ctx));
    functype = FunctionType::get(Type::getInt32Ty(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "strlen", module);
    func->setCallingConv(CallingConv::C);
    functions["strlen"] = func;

    // strcmp
    args.clear();
    args.push_back(Type::getInt8PtrTy(ctx));
    args.push_back(Type::getInt8PtrTy(ctx));
    functype = FunctionType::get(Type::getInt32Ty(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "strcmp", module);
    func->setCallingConv(CallingConv::C);
    functions["strcmp"] = func;

    // strcpy
    args.clear();
    args.push_back(Type::getInt8PtrTy(ctx));
    args.push_back(Type::getInt8PtrTy(ctx));
    functype = FunctionType::get(Type::getInt8PtrTy(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "strcpy", module);
    func->setCallingConv(CallingConv::C);
    functions["strcpy"] = func;

    // calloc
    args.clear();
    args.push_back(Type::getInt64Ty(ctx));
    args.push_back(Type::getInt64Ty(ctx));
    functype = FunctionType::get(Type::getInt8PtrTy(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "calloc", module);
    func->setCallingConv(CallingConv::C);
    functions["calloc"] = func;

    // malloc
    args.clear();
    args.push_back(Type::getInt64Ty(ctx));
    functype = FunctionType::get(Type::getInt8PtrTy(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "malloc", module);
    func->setCallingConv(CallingConv::C);
    functions["malloc"] = func;

    // read
    args.clear();
    args.push_back(Type::getInt32Ty(ctx));
    args.push_back(Type::getInt8PtrTy(ctx));
    args.push_back(Type::getInt64Ty(ctx));
    functype = FunctionType::get(Type::getInt64Ty(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "read", module);
    func->setCallingConv(CallingConv::C);
    functions["read"] = func;

    // fgets
    args.clear();
    args.push_back(Type::getInt8PtrTy(ctx));
    args.push_back(Type::getInt64Ty(ctx));
    args.push_back(Type::getInt8PtrTy(ctx));
    functype = FunctionType::get(Type::getInt8PtrTy(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "fgets", module);
    func->setCallingConv(CallingConv::C);
    functions["fgets"] = func;

    // stdin
    v = new GlobalVariable(
        *module,
        Type::getInt8PtrTy(ctx),
        false,
        GlobalValue::ExternalLinkage,
        0,
        "stdin");
    blocks.front()["stdin"] = v;

    // atoi
    args.clear();
    args.push_back(Type::getInt8PtrTy(ctx));
    functype = FunctionType::get(Type::getInt32Ty(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "atoi", module);
    func->setCallingConv(CallingConv::C);
    functions["atoi"] = func;

    // free
    args.clear();
    args.push_back(Type::getInt8PtrTy(ctx));
    functype = FunctionType::get(Type::getVoidTy(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "free", module);
    func->setCallingConv(CallingConv::C);
    functions["free"] = func;

    // exit
    args.clear();
    args.push_back(Type::getInt32Ty(ctx));
    functype = FunctionType::get(Type::getInt32Ty(ctx), args, false);
    func = Function::Create(functype, Function::ExternalLinkage, "exit", module);
    func->setCallingConv(CallingConv::C);
    functions["exit"] = func;
}

// destructor
CodeGenerator::~CodeGenerator()
{
    blocks.clear();
    functions.clear();
    structtypes.clear();
    structvars.clear();
    delete module;
}

void CodeGenerator::dump()
{
    cout << endl
         << "--------------------IR begin--------------------" << endl;
    module->print(outs(), nullptr);
    cout << "--------------------IR end---------------------" << endl
         << endl;
}

void CodeGenerator::error(string msg)
{
    cerr << "\033[1;31m"
         << "error: "
         << "\033[0m" << msg << endl;
    exit(1);
}

void CodeGenerator::warning(string msg)
{
    cerr << "\033[1;35m"
         << "warning: "
         << "\033[0m" << msg << endl;
}

// simplified type casting
Value *CodeGenerator::CreateCast(Value *V, Type *DestTy)
{
    Type *src = V->getType(), *dst = DestTy;
    if (src == dst)
        return V;
    else if (src->isIntegerTy() && dst->isIntegerTy())
        return builder.CreateIntCast(V, dst, false, "");
    else if (src->isFloatingPointTy() && dst->isFloatingPointTy())
        return builder.CreateFPCast(V, DestTy, "");
    else if (src->isFloatingPointTy())
        return builder.CreateFPToSI(V, DestTy);
    else if (dst->isFloatingPointTy())
        return builder.CreateSIToFP(V, DestTy);
    else if (src->isPointerTy() && dst->isPointerTy())
        return builder.CreatePointerCast(V, DestTy);
    else if (src->isIntegerTy() && dst->isPointerTy())
        return builder.CreateIntToPtr(V, DestTy);
    else if (src->isPointerTy() && dst->isIntegerTy())
        return builder.CreatePtrToInt(V, DestTy);
    else
        // error("type casting failed.");
        return builder.CreateIntCast(V, DestTy, false, "");
}

// search for variables
Value *CodeGenerator::GetVar(string name)
{
    if (!blocks.empty())
        for (auto &p : blocks)
            if (p.find(name) != p.end())
                return p[name];
    // if not local, find in global
    return module->getGlobalVariable(name);
}

Value *CodeGenerator::CreateUnaryExpr(Value *a, enum op_type op)
{
    if (a->getType()->isPointerTy())
        switch (op)
        {
        case OP_INC_FRONT:
        case OP_INC_REAR:
            return builder.CreateGEP(a, builder.getInt64(1));
        case OP_DEC_FRONT:
        case OP_DEC_REAR:
            return builder.CreateGEP(a, builder.getInt64(-1));
        default:
            error("operator type not supoorted for pointer type");
            return nullptr;
        }
    else
        switch (op)
        {
        case OP_INC_FRONT:
        case OP_INC_REAR:
            return builder.CreateBinOp(Instruction::BinaryOps::Add, a, ConstantInt::get(a->getType(), 1));
        case OP_DEC_FRONT:
        case OP_DEC_REAR:
            return builder.CreateBinOp(Instruction::BinaryOps::Sub, a, ConstantInt::get(a->getType(), 1));
        case OP_NOT:
            if (a->getType()->isFloatingPointTy())
                error("bitwise not requires integer operands");
            return builder.CreateUnOp(Instruction::UnaryOps::FNeg, a);
        default:
            cout << op << endl;
            error("operator type not supoorted for general operands");
            return nullptr;
        }
}

// multi types compare instruction
Value *CodeGenerator::CreateBinaryExpr(Value *a, Value *b, enum op_type op)
{
    if (a->getType()->isPointerTy() || b->getType()->isPointerTy())
    {
        // a->getType()->print(outs());
        // b->getType()->print(outs());

        // if is pointer operation
        switch (op)
        {
        case OP_ADD:
            if (a->getType()->isIntegerTy() && b->getType()->isPointerTy())
                return builder.CreateGEP(b, a);
            else if (a->getType()->isPointerTy() && b->getType()->isIntegerTy())
                return builder.CreateGEP(a, b);
            else
                error("+ not supported for the types");
        case OP_SUB:
            if (a->getType()->isIntegerTy() && b->getType()->isPointerTy())
                return builder.CreateGEP(b, builder.CreateNeg(a));
            else if (a->getType()->isPointerTy() && b->getType()->isIntegerTy())
                return builder.CreateGEP(a, builder.CreateNeg(b));
            else if (a->getType()->isPointerTy() && b->getType()->isPointerTy())
                // two pointer diff
                return builder.CreatePtrDiff(a, b);
            else
                error("- not supported for the types");
        case OP_EQ:
            return builder.CreateICmp(
                CmpInst::ICMP_EQ,
                builder.CreatePtrDiff(a, b),
                builder.getInt64(0));
        case OP_NEQ:
            return builder.CreateICmp(
                CmpInst::ICMP_NE,
                builder.CreatePtrDiff(a, b),
                builder.getInt64(0));
        case OP_LT:
            return builder.CreateICmp(
                CmpInst::ICMP_ULT,
                builder.CreatePtrToInt(a, Type::getInt64Ty(ctx)),
                builder.CreatePtrToInt(b, Type::getInt64Ty(ctx)));
        case OP_GT:
            return builder.CreateICmp(
                CmpInst::ICMP_UGT,
                builder.CreatePtrToInt(a, Type::getInt64Ty(ctx)),
                builder.CreatePtrToInt(b, Type::getInt64Ty(ctx)));
        case OP_LEQ:
            return builder.CreateICmp(
                CmpInst::ICMP_ULE,
                builder.CreatePtrToInt(a, Type::getInt64Ty(ctx)),
                builder.CreatePtrToInt(b, Type::getInt64Ty(ctx)));
        case OP_GEQ:
            return builder.CreateICmp(
                CmpInst::ICMP_UGE,
                builder.CreatePtrToInt(a, Type::getInt64Ty(ctx)),
                builder.CreatePtrToInt(b, Type::getInt64Ty(ctx)));
        default:
            cout << op << endl;
            error("operator type not supported for pointer type");
            return nullptr;
        }
    }
    else
    {
        // type casting if at least one of operands is float point
        bool isfloatpoint = a->getType()->isFloatingPointTy() || b->getType()->isFloatingPointTy();
        if (isfloatpoint)
        {
            a = CreateCast(a, Type::getDoubleTy(ctx));
            b = CreateCast(b, Type::getDoubleTy(ctx));
        }
        // type casting to the longer type
        else
        {
            unsigned int bits = max(a->getType()->getIntegerBitWidth(), b->getType()->getIntegerBitWidth());
            a = CreateCast(a, Type::getIntNTy(ctx, bits));
            b = CreateCast(b, Type::getIntNTy(ctx, bits));
        }

        switch (op)
        {
        case OP_EQ:
            return isfloatpoint ? builder.CreateFCmp(CmpInst::FCMP_OEQ, a, b) : builder.CreateICmp(CmpInst::ICMP_EQ, a, b);
        case OP_LT:
            return isfloatpoint ? builder.CreateFCmp(CmpInst::FCMP_OLT, a, b) : builder.CreateICmp(CmpInst::ICMP_SLT, a, b);
        case OP_GT:
            return isfloatpoint ? builder.CreateFCmp(CmpInst::FCMP_OGT, a, b) : builder.CreateICmp(CmpInst::ICMP_SGT, a, b);
        case OP_LEQ:
            return isfloatpoint ? builder.CreateFCmp(CmpInst::FCMP_OLE, a, b) : builder.CreateICmp(CmpInst::ICMP_SLE, a, b);
        case OP_GEQ:
            return isfloatpoint ? builder.CreateFCmp(CmpInst::FCMP_OGE, a, b) : builder.CreateICmp(CmpInst::ICMP_SGE, a, b);
        case OP_NEQ:
            return isfloatpoint ? builder.CreateFCmp(CmpInst::FCMP_ONE, a, b) : builder.CreateICmp(CmpInst::ICMP_NE, a, b);
        case OP_AND:
            if (isfloatpoint)
                error("bitwise and requires integer operands");
            return builder.CreateBinOp(Instruction::BinaryOps::And, a, b);
        case OP_OR:
            if (isfloatpoint)
                error("bitwise or requires integer operands");
            return builder.CreateBinOp(Instruction::BinaryOps::Or, a, b);
        case OP_XOR:
            if (isfloatpoint)
                error("bitwise xor requires integer operands");
            return builder.CreateBinOp(Instruction::BinaryOps::Xor, a, b);
        case OP_ADD:
            return isfloatpoint ? builder.CreateBinOp(Instruction::BinaryOps::FAdd, a, b) : builder.CreateBinOp(Instruction::BinaryOps::Add, a, b);
        case OP_SUB:
            return isfloatpoint ? builder.CreateBinOp(Instruction::BinaryOps::FSub, a, b) : builder.CreateBinOp(Instruction::BinaryOps::Sub, a, b);
        case OP_MUL:
            return isfloatpoint ? builder.CreateBinOp(Instruction::BinaryOps::FMul, a, b) : builder.CreateBinOp(Instruction::BinaryOps::Mul, a, b);
        case OP_DIV:
            return isfloatpoint ? builder.CreateBinOp(Instruction::BinaryOps::FDiv, a, b) : builder.CreateBinOp(Instruction::BinaryOps::SDiv, a, b);
        case OP_MOD:
            if (b->getType()->isFloatingPointTy())
                error("modulation operand should be an integer");
            return builder.CreateBinOp(Instruction::BinaryOps::SRem, a, b);
        case OP_SL:
            if (isfloatpoint)
                error("shift-left requires integer operands");
            return builder.CreateBinOp(Instruction::BinaryOps::Shl, a, b);
        case OP_SR:
            // TODO: may be not ok if always arithmetic shift right
            if (isfloatpoint)
                error("shift-right requires integer operands");
            return builder.CreateBinOp(Instruction::BinaryOps::AShr, a, b);
        default:
            cout << op << endl;
            error("operator type not supoorted for general operands");
            return nullptr;
        }
    }
}

// search for function
Function *CodeGenerator::GetFunction(string name)
{
    if (functions.find(name) != functions.end())
        return functions[name];
    else
    {
        error(string("function '") + name + string("' not found"));
        return nullptr;
    }
}

Constant *CodeGenerator::Num2Constant(Number *num)
{
    Type *type = num->type->getType(*this);
    if (type->isIntegerTy())
    {
        switch (type->getIntegerBitWidth())
        {
        case 8:
            return ConstantInt::get(type, num->charView());
        case 16:
            return ConstantInt::get(type, num->shortView());
        case 32:
            return ConstantInt::get(type, num->intView());
        case 64:
            return ConstantInt::get(type, num->longView());
        default:
            return nullptr;
        }
    }
    else if (type->isFloatTy())
        return ConstantFP::get(type, num->floatView());
    else if (type->isDoubleTy())
        return ConstantFP::get(type, num->doubleView());
    else
        return nullptr;
}