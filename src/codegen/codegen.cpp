#include "../ast/expression.hpp"
#include "../ast/type.hpp"
#include "codegen.hpp"

// initialize the context
CodeGenerator::CodeGenerator() : builder(ctx)
{
    module = new Module("main", ctx);
    functions.clear();
    blocks.clear();
    curFunction = nullptr;
    isglobal = false;
    // top level (global) blocks
    blocks.push_front(map<string, Value *>());

    // add some sys function

    // printf
    vector<Type *> args;
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
}

// destructor
CodeGenerator::~CodeGenerator()
{
    blocks.clear();
    functions.clear();
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
    if (!blocks.empty())
        for (auto &p : blocks)
            if (p.find(name) != p.end())
                return p[name];
    return nullptr;
    // error(string("variable '") + name + string("' not found"));
}

Value *CodeGenerator::CreateUnaryExpr(Value *a, enum op_type op)
{
    switch (op)
    {
    case OP_INC_FRONT:
    case OP_INC_REAR:
        return builder.CreateBinOp(Instruction::BinaryOps::Add, a, ConstantInt::get(a->getType(), 1));
    case OP_DEC_FRONT:
    case OP_DEC_REAR:
        return builder.CreateBinOp(Instruction::BinaryOps::Sub, a, ConstantInt::get(a->getType(), 1));
    default:
        error("operand type not supoorted.");
    }
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
        return builder.CreateBinOp(Instruction::BinaryOps::And, a, b);
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
        return isfloatpoint ? builder.CreateBinOp(Instruction::BinaryOps::FDiv, a, b) : builder.CreateBinOp(Instruction::BinaryOps::SDiv, a, b);
    case OP_MOD:
        return builder.CreateBinOp(Instruction::BinaryOps::SRem, a, b);
    case OP_SL:
        return builder.CreateBinOp(Instruction::BinaryOps::Shl, a, b);
    case OP_SR:
        // may be not ok if always arithmetic shift right
        return builder.CreateBinOp(Instruction::BinaryOps::AShr, a, b);
    default:
        error("operand type not supoorted.");
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

// Constant *CodeGenerator::Expr2Constant(Expression *expr)
// {
//     if (expr->op != OP_NONE)
//         error("Expr2Constant: not a leaf expression");

//     if (expr->left->getName() == "\"Number\"")
//         return Num2Constant((Number *)(expr->left));
//     else if (expr->left->getName() == "\"Identifier\"")
//         // if variable not exists, it means based on current context we cannot calculate the expression
//         return (Constant *)GetVar(((Identifier *)(expr->left))->getIdName());
//     else
//         // not a recognized type of expression
//         return nullptr;
// }

// // calculate an expr based on current context
// Constant *CodeGenerator::CalculateExpr(Expression *expr)
// {
//     Constant *lv = nullptr, *rv = nullptr;
//     // get left value
//     if (expr->left)
//         if (expr->left->op != OP_NONE)
//             lv = CalculateExpr(expr->left);
//         else
//             lv = Expr2Constant(expr->left);
//     // get right value
//     if (expr->right)
//         if (expr->right->op != OP_NONE)
//             rv = CalculateExpr(expr->right);
//         else
//             rv = Expr2Constant(expr->right);