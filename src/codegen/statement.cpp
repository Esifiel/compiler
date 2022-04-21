#include "../ast/statement.hpp"
#include "codegen.hpp"

Value *CompoundStatement::codeGen(CodeGenerator &ctx)
{
    for (auto p = vardecs->begin(); p != vardecs->end(); p++)
        (*p)->codeGen(ctx);
    for (auto p = stmts->begin(); p != stmts->end(); p++)
        (*p)->codeGen(ctx);
    
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
    // create 3 basic blocks
    BasicBlock *forinit = BasicBlock::Create(ctx.ctx, "forinit", ctx.curFunction);
    BasicBlock *forloop = BasicBlock::Create(ctx.ctx, "forloop", ctx.curFunction);
    BasicBlock *forout = BasicBlock::Create(ctx.ctx, "forout", ctx.curFunction);

    // init expr
    ctx.builder.SetInsertPoint(forinit);
    for(auto p = init->begin(); p != init->end(); p++)
        (*p)->codeGen(ctx);

    // loop start
    ctx.builder.SetInsertPoint(forloop);
    stmts->codeGen(ctx);

    ctx.dump();

    // round end
    for(auto p = end->begin(); p != end->end(); p++)
        (*p)->codeGen(ctx);

    // conditional branch: true -> go on forloop, false -> go to forout
    Value *condVal = cond->codeGen(ctx);
    ctx.builder.CreateCondBr(condVal, forloop, forout);

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