#include "../ast/declaration.hpp"
#include "../ast/type.hpp"
#include "codegen.hpp"

Value *VariableDeclaration::codeGen(CodeGenerator &ctx)
{
    Value *v = ctx.builder.CreateAlloca(type->getType(ctx), 0, (*name->name).c_str());
    (v);

}

Value *TypeDeclaration::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *FunctionDeclaration::codeGen(CodeGenerator &ctx)
{
    // create ret value type
    auto functype = FunctionType::get(rettype->getType(ctx), false);
    // create function
    auto func = Function::Create(functype, llvm::Function::ExternalLinkage, *name->name, *ctx.module);
    ctx.curFunction = func;
    // create entry block for the function
    auto block = BasicBlock::Create(ctx.module->getContext(), "entry", func);
    // set up the builder insertion
    ctx.builder.SetInsertPoint(block);

    stmts->codeGen(ctx);

    if(rettype->type == TYPE_VOID)
        ctx.builder.CreateRetVoid();

    ctx.curFunction = nullptr;

    return func;
}