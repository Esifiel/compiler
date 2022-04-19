#include "../ast/program.hpp"
#include "codegen.hpp"

using namespace llvm;

Value *Program::codeGen(CodeGenerator &ctx)
{
    auto functype = FunctionType::get(ctx.builder.getInt32Ty(), false);
    auto func = Function::Create(functype, llvm::Function::ExternalLinkage, "main", *ctx.module);
    auto block = BasicBlock::Create(ctx.module->getContext(), "entry", func);
    ctx.builder.SetInsertPoint(block);

    for (auto p = decs->begin(); p != decs->end(); p++)
    {
        
    }
    ctx.builder.CreateRet(ctx.builder.getInt32(0));


    verifyFunction(*func, &errs());

    return nullptr;
}