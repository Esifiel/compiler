#include "../ast/program.hpp"
#include "codegen.hpp"

using namespace llvm;

Value *Program::codeGen(CodeGenerator &ctx)
{
    for (auto p = decs->begin(); p != decs->end(); p++)
    {
        if ((*p)->getName() == "\"VariableDeclaration\"")
        {
            ctx.isglobal = true;
            (*p)->codeGen(ctx);
            ctx.isglobal = false;
        }
        else if ((*p)->getName() == "\"FunctionDeclaration\"")
        {
            Value *ret = (*p)->codeGen(ctx);
            verifyFunction(*(Function *)ret, &errs());
        }
    }

    return nullptr;
}