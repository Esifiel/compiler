#include "../ast/statement.hpp"
#include "../ast/declaration.hpp"
#include "codegen.hpp"

static bool isDummy(CodeGenerator &ctx)
{
    if (ctx.builder.GetInsertBlock()->getTerminator())
        return true;
    else
        return false;
}

Value *CompoundStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        // new level block
        ctx.blocks.push_front(map<string, Value *>());

        for (Declaration *p = decl; p; p = p->next)
            p->codeGen(ctx);

        for (Statement *s = stmt; s; s = s->next)
            s->codeGen(ctx);

        // leave the current block
        ctx.blocks.pop_front();
    }

    return nullptr;
}

Value *ExpressionStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        if (expr)
            expr->codeGen(ctx);
    }
    return nullptr;
}

Value *IfElseStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        BasicBlock *ifcond = BasicBlock::Create(ctx.ctx, "if.cond", ctx.curFunction);
        BasicBlock *ifthen = BasicBlock::Create(ctx.ctx, "if.then", ctx.curFunction);
        BasicBlock *ifelse = BasicBlock::Create(ctx.ctx, "if.else", ctx.curFunction);
        BasicBlock *ifout = BasicBlock::Create(ctx.ctx, "if.out", ctx.curFunction);
        ctx.builder.CreateBr(ifcond);

        // branch condition
        ctx.builder.SetInsertPoint(ifcond);
        Value *cmpres = cond->codeGen(ctx);
        if (cmpres->getType()->isPointerTy() || cmpres->getType()->getIntegerBitWidth() != 1)
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
        if (!ctx.builder.GetInsertBlock()->getTerminator())
            ctx.builder.CreateBr(ifout);

        // else-part
        ctx.builder.SetInsertPoint(ifelse);
        if (stmt->next)
            stmt->next->codeGen(ctx);
        if (!ctx.builder.GetInsertBlock()->getTerminator())
            ctx.builder.CreateBr(ifout);

        // go out
        ctx.builder.SetInsertPoint(ifout);
    }

    return nullptr;
}

Value *WhileStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        BasicBlock *whilecond = BasicBlock::Create(ctx.ctx, "while.cond", ctx.curFunction);
        BasicBlock *whileloop = BasicBlock::Create(ctx.ctx, "while.loop", ctx.curFunction);
        BasicBlock *whileout = BasicBlock::Create(ctx.ctx, "while.out", ctx.curFunction);
        ctx.builder.CreateBr(whilecond);
        ctx.jumpctx.push_back(pair<BasicBlock *, BasicBlock *>(whilecond, whileout));

        ctx.builder.SetInsertPoint(whilecond);
        Value *cmpres = cond->codeGen(ctx);
        if (cmpres->getType()->isPointerTy() || cmpres->getType()->getIntegerBitWidth() != 1)
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
        ctx.jumpctx.pop_back();
    }

    return nullptr;
}

Value *DoWhileStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        BasicBlock *dowhilecond = BasicBlock::Create(ctx.ctx, "dowhile.cond", ctx.curFunction);
        BasicBlock *dowhileloop = BasicBlock::Create(ctx.ctx, "dowhile.loop", ctx.curFunction);
        BasicBlock *dowhileout = BasicBlock::Create(ctx.ctx, "dowhile.out", ctx.curFunction);
        ctx.jumpctx.push_back(pair<BasicBlock *, BasicBlock *>(dowhilecond, dowhileout));

        // do loop first
        ctx.builder.CreateBr(dowhileloop);
        ctx.builder.SetInsertPoint(dowhileloop);
        stmt->codeGen(ctx);
        ctx.builder.CreateBr(dowhilecond);

        ctx.builder.SetInsertPoint(dowhilecond);
        Value *cmpres = cond->codeGen(ctx);
        if (cmpres->getType()->isPointerTy() || cmpres->getType()->getIntegerBitWidth() != 1)
            // logical comparision is ommitted
            cmpres = ctx.CreateBinaryExpr(
                cmpres,
                cmpres->getType()->isPointerTy() ? dyn_cast<Value>(ConstantPointerNull::get(dyn_cast<PointerType>(cmpres->getType()))) : ConstantInt::get(cmpres->getType(), 0),
                OP_NEQ);
        ctx.builder.CreateCondBr(cmpres, dowhileloop, dowhileout);

        ctx.builder.SetInsertPoint(dowhileout);
        ctx.jumpctx.pop_back();
    }

    return nullptr;
}

Value *ForStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        // create basic blocks
        BasicBlock *forinit = BasicBlock::Create(ctx.ctx, "for.init", ctx.curFunction);
        BasicBlock *forcond = BasicBlock::Create(ctx.ctx, "for.cond", ctx.curFunction);
        BasicBlock *forloop = BasicBlock::Create(ctx.ctx, "for.loop", ctx.curFunction);
        BasicBlock *forend = BasicBlock::Create(ctx.ctx, "for.end", ctx.curFunction);
        BasicBlock *forout = BasicBlock::Create(ctx.ctx, "for.out", ctx.curFunction);
        ctx.builder.CreateBr(forinit);
        ctx.jumpctx.push_back(pair<BasicBlock *, BasicBlock *>(forend, forout));

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
            if (condVal->getType()->isPointerTy() || condVal->getType()->getIntegerBitWidth() != 1)
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
        ctx.jumpctx.pop_back();
    }

    return nullptr;
}

Value *ReturnStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        BasicBlock *retblock = BasicBlock::Create(ctx.ctx, "return", ctx.curFunction);
        ctx.builder.CreateBr(retblock);
        ctx.builder.SetInsertPoint(retblock);

        if (res)
        {
            Value *retval = res->codeGen(ctx);
            if (retval->getType() != ctx.curFunction->getReturnType())
            {
                // correct the ret val type and do a type cast
                ctx.warning("return value will be casted to the function return type");
                retval = ctx.CreateCast(retval, ctx.curFunction->getReturnType());
            }
            ctx.builder.CreateRet(retval);
        }
        else
            ctx.builder.CreateRetVoid();
    }

    return nullptr;
}

Value *BreakStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        if (ctx.jumpctx.size() == 0)
            ctx.error("keyword break used outside of iteration or switch");
        ctx.builder.CreateBr(ctx.jumpctx.back().second);
    }

    return nullptr;
}

Value *ContinueStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        if (ctx.jumpctx.size() == 0)
            ctx.error("keyword continue used outside of iteration or switch");
        ctx.builder.CreateBr(ctx.jumpctx.back().first);
    }

    return nullptr;
}

Value *SwitchCaseStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        BasicBlock *switchcond = BasicBlock::Create(ctx.ctx, "switch.cond", ctx.curFunction);
        BasicBlock *switchout = BasicBlock::Create(ctx.ctx, "switch.out", ctx.curFunction);
        ctx.builder.CreateBr(switchcond);
        ctx.jumpctx.push_back(pair<BasicBlock *, BasicBlock *>(switchcond, switchout));

        ctx.builder.SetInsertPoint(switchcond);
        Value *condexp = cond->codeGen(ctx);
        SwitchInst *swinst = ctx.builder.CreateSwitch(condexp, nullptr);

        if (((CompoundStatement *)stmt)->decl)
            ctx.warning("variable or type declaration inside switch statement will never be executed");

        bool hasdefault = false;
        for (Statement *p = ((CompoundStatement *)stmt)->stmt; p; p = p->next)
        {
            if (p->getName() == "\"CaseStatement\"")
            {
                if (((CaseStatement *)p)->val)
                {
                    BasicBlock *switchcase = BasicBlock::Create(ctx.ctx, "switch.case", ctx.curFunction);
                    swinst->addCase(
                        dyn_cast<ConstantInt>(
                            ctx.CreateCast(
                                ctx.Num2Constant(((CaseStatement *)p)->val), condexp->getType())),
                        switchcase);
                    if (!ctx.builder.GetInsertBlock()->getTerminator())
                        ctx.builder.CreateBr(switchcase);
                    ctx.builder.SetInsertPoint(switchcase);
                }
                else
                {
                    if (!hasdefault)
                    {
                        hasdefault = true;
                        BasicBlock *switchdefault = BasicBlock::Create(ctx.ctx, "switch.default", ctx.curFunction);
                        swinst->setDefaultDest(switchdefault);
                        if (!ctx.builder.GetInsertBlock()->getTerminator())
                            ctx.builder.CreateBr(switchdefault);
                        ctx.builder.SetInsertPoint(switchdefault);
                    }
                    else
                        ctx.error("redefinition of default block");
                }
            }
            else if (p->getName() == "\"ContinueStatement\"")
                ctx.error("keyword continue used in switch statement");
            else
                p->codeGen(ctx);
        }
        // default is ignored
        if (!hasdefault)
        {
            BasicBlock *switchdefault = BasicBlock::Create(ctx.ctx, "switch.default", ctx.curFunction);
            swinst->setDefaultDest(switchdefault);
            if (!ctx.builder.GetInsertBlock()->getTerminator())
                ctx.builder.CreateBr(switchdefault);
            ctx.builder.SetInsertPoint(switchdefault);
        }
        if (!ctx.builder.GetInsertBlock()->getTerminator())
            ctx.builder.CreateBr(switchout);

        ctx.builder.SetInsertPoint(switchout);
        ctx.jumpctx.pop_back();
    }

    return nullptr;
}

Value *CaseStatement::codeGen(CodeGenerator &ctx)
{
    // this method should never be called
    if (val)
        ctx.error("keyword case used outside of switch statement");
    else
        ctx.error("keyword default used outside of switch statement");

    return nullptr;
}

Value *GotoStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        if (ctx.labels.find(label) != ctx.labels.end())
            ctx.builder.CreateBr(ctx.labels[label]);
        else
        {
            BasicBlock *gotoblock = BasicBlock::Create(ctx.ctx, "goto", ctx.curFunction);
            ctx.builder.CreateBr(gotoblock);
            // do not set insert point here
            // leave empty and prepare for backpatching
            ctx.dummy.push_back(pair<BasicBlock *, string>(gotoblock, label));
        }
    }

    return nullptr;
}

Value *LabelStatement::codeGen(CodeGenerator &ctx)
{
    if (!isDummy(ctx))
    {
        if (ctx.labels.find(label) != ctx.labels.end())
            ctx.error(string("redefinition of label '") + label + string("'"));

        BasicBlock *labelblock = BasicBlock::Create(ctx.ctx, label, ctx.curFunction);
        ctx.labels[label] = labelblock;
        ctx.builder.CreateBr(labelblock);
        ctx.builder.SetInsertPoint(labelblock);
    }

    return nullptr;
}