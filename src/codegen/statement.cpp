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
    if(expr)
        expr->codeGen(ctx);
    return nullptr;
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
    if(cmpres->getType()->isPointerTy() || cmpres->getType()->getIntegerBitWidth() != 1)
        // logical comparision is ommitted
        cmpres = ctx.CreateBinaryExpr(
            cmpres,
            cmpres->getType()->isPointerTy() ? dyn_cast<Value>(ConstantPointerNull::get(dyn_cast<PointerType>(cmpres->getType()))) : ConstantInt::get(cmpres->getType(), 0),
            OP_NEQ);
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

Value *WhileStatement::codeGen(CodeGenerator &ctx)
{
    BasicBlock *whilecond = BasicBlock::Create(ctx.ctx, "while.cond", ctx.curFunction);
    BasicBlock *whileloop = BasicBlock::Create(ctx.ctx, "while.loop", ctx.curFunction);
    BasicBlock *whileout = BasicBlock::Create(ctx.ctx, "while.out", ctx.curFunction);
    ctx.builder.CreateBr(whilecond);
    ctx.loopctx.push_back(pair<BasicBlock *, BasicBlock *>(whilecond, whileout));

    ctx.builder.SetInsertPoint(whilecond);
    Value *cmpres = cond->codeGen(ctx);
    if(cmpres->getType()->isPointerTy() || cmpres->getType()->getIntegerBitWidth() != 1)
        // logical comparision is ommitted
        cmpres = ctx.CreateBinaryExpr(
            cmpres,
            cmpres->getType()->isPointerTy() ? dyn_cast<Value>(ConstantPointerNull::get(dyn_cast<PointerType>(cmpres->getType()))) : ConstantInt::get(cmpres->getType(), 0),
            OP_NEQ);
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
    BasicBlock *dowhilecond = BasicBlock::Create(ctx.ctx, "dowhile.cond", ctx.curFunction);
    BasicBlock *dowhileloop = BasicBlock::Create(ctx.ctx, "dowhile.loop", ctx.curFunction);
    BasicBlock *dowhileout = BasicBlock::Create(ctx.ctx, "dowhile.out", ctx.curFunction);
    ctx.loopctx.push_back(pair<BasicBlock *, BasicBlock *>(dowhilecond, dowhileout));

    // do loop first
    ctx.builder.CreateBr(dowhileloop);
    ctx.builder.SetInsertPoint(dowhileloop);
    stmt->codeGen(ctx);
    ctx.builder.CreateBr(dowhilecond);

    ctx.builder.SetInsertPoint(dowhilecond);
    Value *cmpres = cond->codeGen(ctx);
    if(cmpres->getType()->isPointerTy() || cmpres->getType()->getIntegerBitWidth() != 1)
        // logical comparision is ommitted
        cmpres = ctx.CreateBinaryExpr(
            cmpres,
            cmpres->getType()->isPointerTy() ? dyn_cast<Value>(ConstantPointerNull::get(dyn_cast<PointerType>(cmpres->getType()))) : ConstantInt::get(cmpres->getType(), 0),
            OP_NEQ);
    ctx.builder.CreateCondBr(cmpres, dowhileloop, dowhileout);

    ctx.builder.SetInsertPoint(dowhileout);
    ctx.loopctx.pop_back();

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
        if(condVal->getType()->isPointerTy() || condVal->getType()->getIntegerBitWidth() != 1)
            // logical comparision is ommitted
            condVal = ctx.CreateBinaryExpr(
                condVal,
                condVal->getType()->isPointerTy() ? dyn_cast<Value>(ConstantPointerNull::get(dyn_cast<PointerType>(condVal->getType()))) : ConstantInt::get(condVal->getType(), 0),
                OP_NEQ);
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


Value *SwitchCaseStatement::codeGen(CodeGenerator &ctx)
{
    // SwitchInst *sw = ctx.builder.CreateSwitch();

    // sw->addCase();

    return nullptr;
}

Value *CaseStatement::codeGen(CodeGenerator &ctx)
{
    

    return nullptr;
}

Value *GotoStatement::codeGen(CodeGenerator &ctx)
{
    if(ctx.labels.find(label) != ctx.labels.end())
        ctx.builder.CreateBr(ctx.labels[label]);
    else
        ctx.error(string("label '") + label + string("' is not defined"));

    return nullptr;
}

Value *LabelStatement::codeGen(CodeGenerator &ctx)
{
    if(ctx.labels.find(label) != ctx.labels.end())
        ctx.error(string("redefinition of label '") + label + string("'"));

    BasicBlock *labelblock = BasicBlock::Create(ctx.ctx, label, ctx.curFunction);
    ctx.labels[label] = labelblock;

    return nullptr;
}