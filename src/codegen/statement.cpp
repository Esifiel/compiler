#include "../ast/statement.hpp"
#include "codegen.hpp"

Value *CompoundStatement::codeGen(CodeGenerator &ctx)
{
    for (auto &p : *vardecs)
        p->codeGen(ctx);
    for (auto &p : *stmts)
        p->codeGen(ctx);
    
    return nullptr;
}

Value *ExpressionStatement::codeGen(CodeGenerator &ctx)
{
    return expr->codeGen(ctx);
}

Value *SelectionStatement::codeGen(CodeGenerator &ctx)
{
    Value *cmpres = cond->codeGen(ctx);

    return nullptr;
}

Value *WhileStatement::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *ForStatement::codeGen(CodeGenerator &ctx)
{
    // create basic blocks
    BasicBlock *forinit = BasicBlock::Create(ctx.ctx, "forinit", ctx.curFunction);
    BasicBlock *forcond = BasicBlock::Create(ctx.ctx, "forcond", ctx.curFunction);
    BasicBlock *forloop = BasicBlock::Create(ctx.ctx, "forloop", ctx.curFunction);
    BasicBlock *forout = BasicBlock::Create(ctx.ctx, "forout", ctx.curFunction);
    ctx.builder.CreateBr(forinit);

    // init expr
    ctx.builder.SetInsertPoint(forinit);
    for (auto &p : *init)
        p->codeGen(ctx);
    ctx.builder.CreateBr(forcond);

    // conditional branch: true -> go on forloop, false -> go to forout
    ctx.builder.SetInsertPoint(forcond);
    Value *condVal = cond->codeGen(ctx);
    ctx.builder.CreateCondBr(condVal, forloop, forout);

    // loop start
    ctx.builder.SetInsertPoint(forloop);
    stmts->codeGen(ctx);
    // round end
    for (auto &p : *end)
        p->codeGen(ctx);
    ctx.builder.CreateBr(forcond);

    ctx.builder.SetInsertPoint(forout);

    return nullptr;
}

Value *ReturnStatement::codeGen(CodeGenerator &ctx)
{
    if (res->expr)
        // correct the ret val type and do a type cast
        ctx.builder.CreateRet(ctx.CreateCast(res->codeGen(ctx), ctx.curFunction->getReturnType()));
    else
        ctx.builder.CreateRetVoid();

    return nullptr;
}