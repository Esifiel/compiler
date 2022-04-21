#include "../ast/expression.hpp"
#include "codegen.hpp"

// initialize the context
CodeGenerator::CodeGenerator() : builder(ctx)
{
    module = new Module("main", ctx);
    functions.clear();
    locals.clear();
    globals.clear();
    curFunction = nullptr;
    isglobal = false;

    // add some sys function
    // printf
    vector<Type *> args;
    args.push_back(Type::getInt8PtrTy(ctx));
    FunctionType *functype = FunctionType::get(Type::getInt32Ty(ctx), args, true);
    Function *func = Function::Create(functype, Function::ExternalLinkage, "printf", module);
    func->setCallingConv(CallingConv::C);
    functions["printf"] = func;
}

void CodeGenerator::dump()
{
    cout << endl
         << "--------------------IR begin--------------------" << endl;
    module->print(outs(), nullptr);
    cout << "--------------------IR end---------------------" << endl;
}

void CodeGenerator::error(string msg)
{
    cerr << "\033[31m"
         << "error: "
         << "\033[0m" << msg << endl;
    exit(1);
}

// simplified type casting
Value *CodeGenerator::CreateCast(Value *V, Type *DestTy)
{
    if (V->getType() == DestTy)
        return V;
    else if (V->getType()->isIntegerTy() && DestTy->isIntegerTy())
        return builder.CreateIntCast(V, DestTy, false, "");
    else if (V->getType()->isFloatingPointTy() && DestTy->isFloatingPointTy())
        return builder.CreateFPCast(V, DestTy, "");
    else if (V->getType()->isFloatingPointTy())
        return builder.CreateFPToSI(V, DestTy);
    else if (DestTy->isFloatingPointTy())
        return builder.CreateSIToFP(V, DestTy);
    else
        // error("type casting failed.");
        return builder.CreateIntCast(V, DestTy, false, "");
}

// search for variables
Value *CodeGenerator::GetVar(string name)
{
    if (locals.find(name) != locals.end())
        return locals[name];
    else if (globals.find(name) != globals.end())
        return globals[name];
    else
        error(string("variable '") + name + string("' not found"));
}

// multi types compare instruction
Value *CodeGenerator::CreateBinaryExpr(Value *a, Value *b, enum op_type op)
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
    case OP_ANDAND:
        return nullptr;
    case OP_OROR:
        return nullptr;
    case OP_AND:
        return isfloatpoint ? builder.CreateBinOp(Instruction::BinaryOps::FAdd, a, b) : builder.CreateBinOp(Instruction::BinaryOps::Add, a, b);
    case OP_OR:
        return builder.CreateBinOp(Instruction::BinaryOps::Or, a, b);
    case OP_NOT:
        return nullptr;
    case OP_XOR:
        return builder.CreateBinOp(Instruction::BinaryOps::Xor, a, b);
    case OP_ADD:
        return isfloatpoint ? builder.CreateBinOp(Instruction::BinaryOps::FAdd, a, b) : builder.CreateBinOp(Instruction::BinaryOps::Add, a, b);
    case OP_SUB:
        return isfloatpoint ? builder.CreateBinOp(Instruction::BinaryOps::FSub, a, b) : builder.CreateBinOp(Instruction::BinaryOps::Sub, a, b);
    case OP_MUL:
        return isfloatpoint ? builder.CreateBinOp(Instruction::BinaryOps::FMul, a, b) : builder.CreateBinOp(Instruction::BinaryOps::Mul, a, b);
    case OP_DIV:
        return builder.CreateBinOp(Instruction::BinaryOps::FDiv, a, b);
    case OP_MOD:
        return builder.CreateBinOp(Instruction::BinaryOps::FRem, a, b);
    default:
        return nullptr;
    }
}

// search for function
Function *CodeGenerator::GetFunction(string name)
{
    if (functions.find(name) != functions.end())
        return functions[name];
    else
        error(string("function '") + name + string("' not found"));
}