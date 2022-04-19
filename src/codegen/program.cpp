#include "../ast/program.hpp"
#include "codegen.hpp"

using namespace llvm;

Value *Program::codeGen(CodeGenerator &ctx)
{
    for (auto p = decs->begin(); p != decs->end(); p++)
    {
        cout << "program" << endl;
        (*p)->codeGen(ctx);
    }

    return nullptr;
}