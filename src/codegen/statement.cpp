#include "../ast/statement.hpp"
#include "../ast/declaration.hpp"
#include "codegen.hpp"

Value *CompoundStatement::codeGen(CodeGenerator &ctx)
{
    // new level block
    ctx.blocks.push_front(map<string, Value *>());

    if (vardecs)
        for (auto &p : *vardecs)
            p->codeGen(ctx);

    for(Statement *s = stmt; s; s = s->next)
        s->codeGen(ctx);

    // leave the current block
    ctx.blocks.pop_front();

    return nullptr;
}

Value *ExpressionStatement::codeGen(CodeGenerator &ctx)
{
    return expr->codeGen(ctx);
}

Value *IfElseStatement::codeGen(CodeGenerator &ctx)
{
    BasicBlock *ifcond = BasicBlock::Create(ctx.ctx, "if.cond", ctx.curFunction);
    BasicBlock *ifthen = BasicBlock::Create(ctx.ctx, "if.then", ctx.curFunction);
    BasicBlock *ifelse = BasicBlock::Create(ctx.ctx, "if.else", ctx.curFunction);
    BasicBlock *ifout = BasicBlock::Create(ctx.ctx, "if.out", ctx.curFunction);
    ctx.builder.CreateBr(ifcond);

    // branch condition
    ctx.builder.SetInsertPoint(ifcond);
    Value *cmpres = cond->codeGen(ctx);
    ctx.builder.CreateCondBr(cmpres, ifthen, ifelse);

    // if-statement
    ctx.builder.SetInsertPoint(ifthen);
    stmt->codeGen(ctx);
    // if current block has not terminated, go if.out
    if(!ctx.builder.GetInsertBlock()->getTerminator())
        ctx.builder.CreateBr(ifout);

    // else-part
    ctx.builder.SetInsertPoint(ifelse);
    if (stmt->next)
        stmt->next->codeGen(ctx);
    if(!ctx.builder.GetInsertBlock()->getTerminator())
        ctx.builder.CreateBr(ifout);
    
    // go out
    ctx.builder.SetInsertPoint(ifout);

    return nullptr;
}

Value *SwitchCaseStatement::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *WhileStatement::codeGen(CodeGenerator &ctx)
{
    BasicBlock *whilecond = BasicBlock::Create(ctx.ctx, "while.cond", ctx.curFunction);
    BasicBlock *whileloop = BasicBlock::Create(ctx.ctx, "while.loop", ctx.curFunction);
    BasicBlock *whileout = BasicBlock::Create(ctx.ctx, "while.out", ctx.curFunction);
    ctx.builder.CreateBr(whilecond);
    ctx.loopctx.push_back(pair<BasicBlock *, BasicBlock *>(whilecond, whileout));

    ctx.builder.SetInsertPoint(whilecond);
    Value *cmpres = cond->codeGen(ctx);
    ctx.builder.CreateCondBr(cmpres, whileloop, whileout);

    ctx.builder.SetInsertPoint(whileloop);
    stmt->codeGen(ctx);
    ctx.builder.CreateBr(whilecond);

    ctx.builder.SetInsertPoint(whileout);
    ctx.loopctx.pop_back();

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
    BasicBlock *forend = BasicBlock::Create(ctx.ctx, "for.end", ctx.curFunction);
    BasicBlock *forout = BasicBlock::Create(ctx.ctx, "for.out", ctx.curFunction);
    ctx.builder.CreateBr(forinit);
    ctx.loopctx.push_back(pair<BasicBlock *, BasicBlock *>(forend, forout));

    // init expr
    ctx.builder.SetInsertPoint(forinit);
    if (init)
        init->codeGen(ctx);
    ctx.builder.CreateBr(forcond);

    // conditional branch: true -> go on forloop, false -> go to forout
    ctx.builder.SetInsertPoint(forcond);
    if (cond)
    {
        Value *condVal = cond->codeGen(ctx);
        ctx.builder.CreateCondBr(condVal, forloop, forout);
    }
    else
        ctx.builder.CreateBr(forloop);

    // loop start
    ctx.builder.SetInsertPoint(forloop);
    stmt->codeGen(ctx);
    ctx.builder.CreateBr(forend);

    // round end
    ctx.builder.SetInsertPoint(forend);
    if (end)
        end->codeGen(ctx);
    ctx.builder.CreateBr(forcond);

    // go out
    ctx.builder.SetInsertPoint(forout);
    ctx.loopctx.pop_back();

    return nullptr;
}

Value *ReturnStatement::codeGen(CodeGenerator &ctx)
{
    // BasicBlock *returnblock = BasicBlock::Create(ctx.ctx, "return.block", ctx.curFunction);
    // ctx.builder.CreateBr(returnblock);
    // ctx.builder.SetInsertPoint(returnblock);

    if (res)
        // correct the ret val type and do a type cast
        ctx.builder.CreateRet(ctx.CreateCast(res->codeGen(ctx), ctx.curFunction->getReturnType()));
    else
        ctx.builder.CreateRetVoid();

    return nullptr;
}

Value *BreakStatement::codeGen(CodeGenerator &ctx)
{
    ctx.builder.CreateBr(ctx.loopctx.back().second);

    return nullptr;
}

Value *ContinueStatement::codeGen(CodeGenerator &ctx)
{
    ctx.builder.CreateBr(ctx.loopctx.back().first);

    return nullptr;
}
