#include "../ast/declaration.hpp"
#include "../ast/type.hpp"
#include "codegen.hpp"

Value *VariableDeclaration::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *TypeDeclaration::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *FunctionDeclaration::codeGen(CodeGenerator &ctx)
{
    auto functype = FunctionType::get(rettype->getType(ctx), false);
    cout << "function" << endl;
    auto func = Function::Create(functype, llvm::Function::ExternalLinkage, *name->name, *ctx.module);
    cout << "function" << endl;
    auto block = BasicBlock::Create(ctx.module->getContext(), "entry", func);
    cout << "function" << endl;
    ctx.builder.SetInsertPoint(block);

    cout << "function" << endl;
    stmts->codeGen(ctx);

    verifyFunction(*func, &errs());

    return nullptr;
}