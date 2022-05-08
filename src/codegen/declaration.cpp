#include "../ast/declaration.hpp"
#include "../ast/type.hpp"
#include "codegen.hpp"

Value *VariableDeclaration::codeGen(CodeGenerator &ctx)
{
    auto pt = types->begin();
    auto pi = ids->begin();
    
    for (; pt != types->end() && pi != ids->end(); pt++, pi++)
    {
        string varname = (*pi)->name;

        // if type is a undefined struct type, declare a opaque type first
        if((*pt)->getRootType()->type == TYPE_STRUCT && !ctx.module->getTypeByName(((AggregateType *)(*pt)->getRootType())->name))
        {
            TypeDeclaration td = TypeDeclaration((*pt)->getRootType());
            td.codeGen(ctx);
        }

        // do declaration
        if ((*pt)->type == TYPE_ARRAY)
        {
            // array type
            ArrayType *array_t = (ArrayType *)((*pt)->getType(ctx));
            if (ctx.isglobal)
            {
                GlobalVariable *v = new GlobalVariable(
                    *ctx.module,
                    array_t,
                    (*pi)->qual && (*pi)->qual->isconst ? true : false, // const attribute
                    GlobalValue::PrivateLinkage,
                    0,
                    varname);
                vector<Constant *> elements;
                for (Expression *q = (*pi)->init; q; q = q->left)
                    elements.push_back(ctx.Num2Constant((Number *)q));
                Constant *constarr = ConstantArray::get(array_t, elements);
                v->setInitializer(constarr);
                ctx.blocks.front()[varname] = v;
            }
            else
                // TODO: local variable initialize not supported yet
                ctx.blocks.front()[varname] = ctx.builder.CreateAlloca(array_t, 0, varname.c_str());
        }
        else if((*pt)->type == TYPE_STRUCT)
        {
            // struct type
            MyStructType *mst = (MyStructType *)*pt;
            StructType *stype = ctx.module->getTypeByName(mst->name);
            if (ctx.isglobal)
            {
                GlobalVariable *v = new GlobalVariable(
                    *ctx.module,
                    stype,
                    (*pi)->qual && (*pi)->qual->isconst ? true : false, // const attribute
                    GlobalValue::PrivateLinkage,
                    0,
                    varname);
                vector<Constant *> elements;
                for (Expression *q = (*pi)->init; q; q = q->left)
                    elements.push_back(ctx.Num2Constant((Number *)q));
                Constant *constarr = ConstantStruct::get(stype, elements);
                v->setInitializer(constarr);
                ctx.blocks.front()[varname] = v;
            }
            else
                ctx.blocks.front()[varname] = ctx.builder.CreateAlloca(stype, 0, varname.c_str());
        }
        else
        {
            // normal type
            Type *t = (*pt)->getType(ctx);
            if (ctx.isglobal)
            {
                // global variable
                GlobalVariable *v = new GlobalVariable(
                    *ctx.module,
                    t,
                    (*pt)->qual && (*pt)->qual->isconst ? true : false,
                    GlobalValue::PrivateLinkage,
                    0,
                    varname);
                if ((*pi)->init)
                    // if initializer exist
                    v->setInitializer((Constant *)(*pi)->init->codeGen(ctx));
                else
                    // else initialize to 0
                    v->setInitializer(ConstantInt::get(t, 0));
                ctx.blocks.front()[varname] = v;
            }
            else
            {
                // allocate space for new local variable
                ctx.blocks.front()[varname] = ctx.builder.CreateAlloca(t, 0, varname.c_str());
                if((*pi)->init)
                    ctx.builder.CreateStore(ctx.CreateCast((*pi)->init->codeGen(ctx), t), ctx.blocks.front()[varname]);
            }
        }

        // collect struct type variable
        if((*pt)->getRootType()->type == TYPE_STRUCT)
            ctx.structvars[varname] = (AggregateType *)((*pt)->getRootType());
    }

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
        for (Parameter *p = params; p; p = (Parameter *)(p->next))
            args.push_back((Type *)(p->codeGen(ctx)));
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

    // create entry and end block for the function
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
        // allocate for arg
        ctx.blocks.front()[p->id->name] = ctx.builder.CreateAlloca(p->type->getType(ctx), 0, p->id->name.c_str());
        // store arg
        ctx.builder.CreateStore(&arg, ctx.blocks.front()[p->id->name]);
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

Value *TypeDeclaration::codeGen(CodeGenerator &ctx)
{
    if(type->type == TYPE_STRUCT)
    {
        MyStructType *mst = (MyStructType *)type;
        ctx.structtypes[mst->name] = vector<string>();
        // create struct type for assigned name
        StructType *stype = StructType::create(ctx.ctx, mst->name);
        if(mst->members)
        {
            // set members
            vector<Type *> elements;
            for(auto &p : *mst->members)
            {
                for(auto &q : *p->first)
                    elements.push_back(q->getType(ctx));
                // record field name in context
                for(auto &q : *p->second)
                    ctx.structtypes[mst->name].push_back(q->name);
            }
            stype->setBody(elements);
        }
        // if no member, just a forward declaration, set as opaque type (default)
    }

    return nullptr;
}