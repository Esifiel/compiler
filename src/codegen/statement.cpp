#include "../ast/statement.hpp"
#include "codegen.hpp"

Value *CompoundStatement::codeGen(CodeGenerator &ctx)
{
    for (auto p = vardecs->begin(); p != vardecs->end(); p++)
        (*p)->codeGen(ctx);
    for (auto p = stmts->begin(); p != stmts->end(); p++)
        (*p)->codeGen(ctx);
}

Value *ExpressionStatement::codeGen(CodeGenerator &ctx)
{
    return expr->codeGen(ctx);
}

Value *SelectionStatement::codeGen(CodeGenerator &ctx)
{
    Value *cmpres = cond->codeGen(ctx);


}

Value *WhileStatement::codeGen(CodeGenerator &ctx)
{

}

Value *ForStatement::codeGen(CodeGenerator &ctx)
{

}

Value *ReturnStatement::codeGen(CodeGenerator &ctx)
{
    if(res->expr)
    // TODO: need a type conversion
        ctx.builder.CreateRet(res->codeGen(ctx));
    else
        ctx.builder.CreateRetVoid();

    return nullptr;
}