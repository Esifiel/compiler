#include "../ast/declaration.hpp"
#include "../ast/type.hpp"
#include "codegen.hpp"

Value *VariableDeclaration::codeGen(CodeGenerator &ctx)
{
    if (ctx.isglobal)
    {
        // global variable
        GlobalVariable *v = new GlobalVariable(
            *ctx.module,
            type->getType(ctx),
            false, // not constant
            GlobalValue::PrivateLinkage,
            0,
            *name->name
        );
        // initialize to 0
        v->setInitializer(ConstantInt::get(type->getType(ctx), 0));
        return v;
    }
    else
        // allocate space for new local variable
        return ctx.builder.CreateAlloca(type->getType(ctx), 0, (*name->name).c_str());
}

Value *TypeDeclaration::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *FunctionDeclaration::codeGen(CodeGenerator &ctx)
{
    // check redefinition
    if(ctx.functions.find(*name->name) != ctx.functions.end())
        ctx.error(string("redefinition of function '") + *name->name + string("'"));

    // create ret value type
    auto functype = FunctionType::get(rettype->getType(ctx), false);
    // create function
    auto func = Function::Create(functype, llvm::Function::ExternalLinkage, *name->name, *ctx.module);
    // add to map and mark as current
    ctx.curFunction = func;
    ctx.functions[*name->name] = func;
    // create entry block for the function
    auto block = BasicBlock::Create(ctx.module->getContext(), "entry", func);
    // set up the builder insertion
    ctx.builder.SetInsertPoint(block);

    // recursively generate
    stmts->codeGen(ctx);

    if (rettype->type == TYPE_VOID)
        ctx.builder.CreateRetVoid();

    ctx.curFunction = nullptr;

    return func;
}