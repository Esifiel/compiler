#include "../ast/program.hpp"
#include "codegen.hpp"

using namespace llvm;

Value *Program::codeGen(CodeGenerator &ctx)
{
    for (Declaration *p = decl; p; p = p->next)
    {
        if (p->getName() == "\"VariableDeclaration\"")
        {
            ctx.isglobal = true;
            p->codeGen(ctx);
            ctx.isglobal = false;
        }
        else if (p->getName() == "\"FunctionDeclaration\"")
        {
            Value *ret = p->codeGen(ctx);
            verifyFunction(*(Function *)ret, &errs());
        }
        else
            p->codeGen(ctx);
    }

    // backpatching
    for (auto &gotolabel : ctx.dummy)
    {
        if(ctx.labels.find(gotolabel.second) == ctx.labels.end())
            ctx.error(string("label '") + gotolabel.second + string("' is not defined"));

        ctx.builder.SetInsertPoint(gotolabel.first);
        ctx.builder.CreateBr(ctx.labels[gotolabel.second]);
    }

    return nullptr;
}