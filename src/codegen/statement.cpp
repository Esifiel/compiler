#include "../ast/statement.hpp"
#include "../ast/declaration.hpp"
#include "codegen.hpp"

Value *CompoundStatement::codeGen(CodeGenerator &ctx)
{
    for (auto &p : *vardecs)
        p->codeGen(ctx);
    Statement *s = stmt;
    while(s)
    {
        s->codeGen(ctx);
        s = s->next;
    }
    
    return nullptr;
}

Value *ExpressionStatement::codeGen(CodeGenerator &ctx)
{
    return expr->codeGen(ctx);
}

Value *IfElseStatement::codeGen(CodeGenerator &ctx)
{
    Value *cmpres = cond->codeGen(ctx);

    return nullptr;
}

Value *SwitchCaseStatement::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *WhileStatement::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *DoWhileStatement::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *ForStatement::codeGen(CodeGenerator &ctx)
{
    // create basic blocks
    BasicBlock *forinit = BasicBlock::Create(ctx.ctx, "for.init", ctx.curFunction);
    BasicBlock *forcond = BasicBlock::Create(ctx.ctx, "for.cond", ctx.curFunction);
    BasicBlock *forloop = BasicBlock::Create(ctx.ctx, "for.loop", ctx.curFunction);
    BasicBlock *forout = BasicBlock::Create(ctx.ctx, "for.out", ctx.curFunction);
    ctx.builder.CreateBr(forinit);

    // init expr
    ctx.builder.SetInsertPoint(forinit);
    init->codeGen(ctx);
    ctx.builder.CreateBr(forcond);

    // conditional branch: true -> go on forloop, false -> go to forout
    ctx.builder.SetInsertPoint(forcond);
    Value *condVal = cond->codeGen(ctx);
    ctx.builder.CreateCondBr(condVal, forloop, forout);

    // loop start
    ctx.builder.SetInsertPoint(forloop);
    stmt->codeGen(ctx);
    // round end
    end->codeGen(ctx);
    ctx.builder.CreateBr(forcond);

    ctx.builder.SetInsertPoint(forout);

    return nullptr;
}

Value *ReturnStatement::codeGen(CodeGenerator &ctx)
{
    if (res)
        // correct the ret val type and do a type cast
        ctx.builder.CreateRet(ctx.CreateCast(res->codeGen(ctx), ctx.curFunction->getReturnType()));
    else
        ctx.builder.CreateRetVoid();

    return nullptr;
}