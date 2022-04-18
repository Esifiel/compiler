#include "../ast/program.hpp"
#include "codegen.hpp"

Value *Program::codeGen(CodeGenerator &ctx)
{
    for (auto p = decs->begin(); p != decs->end(); p++)
        (*p)->codeGen(ctx);
    return nullptr;
}