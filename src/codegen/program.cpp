#include "../ast/program.hpp"
#include "codegen.hpp"

using namespace llvm;

Value *Program::codeGen(CodeGenerator &ctx)
{
    for (auto p = decs->begin(); p != decs->end(); p++)
    {
        Value *ret = (*p)->codeGen(ctx);
        if ((*p)->getName() == "\"FunctionDeclaration\"")
            verifyFunction(*(Function *)ret, &errs());
    }

    return nullptr;
}