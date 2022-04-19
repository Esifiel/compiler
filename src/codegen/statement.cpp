#include "../ast/statement.hpp"
#include "codegen.hpp"

Value *CompoundStatement::codeGen(CodeGenerator &ctx)
{

}

Value *ExpressionStatement::codeGen(CodeGenerator &ctx)
{

}

Value *SelectionStatement::codeGen(CodeGenerator &ctx)
{

}

Value *WhileStatement::codeGen(CodeGenerator &ctx)
{

}

Value *ForStatement::codeGen(CodeGenerator &ctx)
{

}

Value *ReturnStatement::codeGen(CodeGenerator &ctx)
{
    ctx.builder.CreateRet(res->codeGen(ctx));

    return nullptr;
}