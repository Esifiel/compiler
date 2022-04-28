#include "../ast/declaration.hpp"
#include "../ast/type.hpp"
#include "codegen.hpp"

Value *VariableDeclaration::codeGen(CodeGenerator &ctx)
{
    for (auto &p : *ids)
    {
        string varname = p->name;
        if (p->size)
        {
            // array type
            ArrayType *array_t = ArrayType::get(type->getType(ctx), ((Number *)(p->size))->longView());
            if (ctx.isglobal)
            {
                GlobalVariable *v = new GlobalVariable(
                    *ctx.module,
                    array_t,
                    true,
                    GlobalValue::PrivateLinkage,
                    0,
                    varname);
                vector<Constant *> elements;
                Expression *q = p->init;
                while (q)
                {
                    elements.push_back(ctx.Num2Constant((Number *)(q->codeGen(ctx))));
                    q = q->left;
                }
                Constant *constarr = ConstantArray::get(array_t, elements);
                v->setInitializer(constarr);
                ctx.blocks.front()[varname] = v;
            }
            else
                ctx.blocks.front()[varname] = ctx.builder.CreateAlloca(array_t, 0, varname.c_str());
        }
        else
        {
            // normal type
            Type *t = type->getType(ctx);
            if (ctx.isglobal)
            {
                // global variable
                GlobalVariable *v = new GlobalVariable(
                    *ctx.module,
                    t,
                    false, // not constant
                    GlobalValue::PrivateLinkage,
                    0,
                    varname);
                if (p->init)
                    // if initializer exist
                    v->setInitializer(ctx.Num2Constant((Number *)(p->init)));
                else
                    // else initialize to 0
                    v->setInitializer(ConstantInt::get(t, 0));
                ctx.blocks.front()[varname] = v;
            }
            else
                // allocate space for new local variable
                ctx.blocks.front()[varname] = ctx.builder.CreateAlloca(t, 0, varname.c_str());
        }
    }

    return nullptr;
}

Value *TypeDeclaration::codeGen(CodeGenerator &ctx)
{
    return nullptr;
}

Value *Parameter::codeGen(CodeGenerator &ctx)
{
    return (Value *)(type->getType(ctx));
}

Value *FunctionDeclaration::codeGen(CodeGenerator &ctx)
{
    // new level block
    ctx.blocks.push_front(map<string, Value *>());

    // check redefinition
    string funcname = id->name;
    if (ctx.functions.find(funcname) != ctx.functions.end())
        ctx.error(string("redefinition of function '") + funcname + string("'"));

    // create function type
    FunctionType *functype;
    if (params)
    {
        // collect args
        vector<Type *> args;
        Parameter *p = params;
        while (p)
        {
            args.push_back((Type *)(p->codeGen(ctx)));
            p = (Parameter *)(p->next);
        }
        // false: is not variable args
        functype = FunctionType::get(rettype->getType(ctx), args, false);
    }
    else
        // no param
        functype = FunctionType::get(rettype->getType(ctx), false);

    // create function
    Function *func = Function::Create(functype, Function::ExternalLinkage, funcname, *ctx.module);

    // add to map and mark as current
    ctx.curFunction = func;
    ctx.functions[funcname] = func;

    // create entry block for the function
    BasicBlock *block = BasicBlock::Create(ctx.ctx, "entry", func);
    // set up the builder insertion
    ctx.builder.SetInsertPoint(block);

    // set arg name and add args into current block
    uint64_t idx = 0;
    Parameter *p = params;
    for (auto &arg : func->args())
    {
        if (p->id->name != "")
            arg.setName(p->id->name);
        ctx.blocks.front()[p->id->name] = ctx.builder.CreateAlloca(p->type->getType(ctx), 0, p->id->name.c_str());
        p = (Parameter *)(p->next);
    }

    // recursively generate
    stmts->codeGen(ctx);

    if (rettype->type == TYPE_VOID)
        ctx.builder.CreateRetVoid();

    // leave the current block
    ctx.curFunction = nullptr;
    ctx.blocks.pop_front();

    return func;
}