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
        if ((!ctx.isglobal && ctx.blocks.front().find(varname) != ctx.blocks.front().end()) ||
            ctx.isglobal && ctx.module->getGlobalVariable(varname))
            ctx.error("redefinition of variable '" + varname + "'");

        // if type is a undefined struct type, declare a opaque type first
        if (((*pt)->getRootType()->type == TYPE_STRUCT || (*pt)->getRootType()->type == TYPE_UNION) && ((AggregateType *)*pt)->members)
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
                    (*pt)->qual && (*pt)->qual->isconst ? true : false, // const attribute
                    (*pt)->linkage == LINKAGE_EXTERNAL ? GlobalValue::ExternalLinkage : (*pt)->linkage == LINKAGE_INTERNAL ? GlobalValue::InternalLinkage : GlobalValue::PrivateLinkage,
                    0,
                    varname);

                // not supported multi-dimension array initialization

                vector<Constant *> elements;
                for (Expression *q = (*pi)->init; q; q = q->left)
                    elements.push_back(ctx.Num2Constant((Number *)q));
                // remaining initialize to 0
                Value *zero = ctx.CreateCast(ctx.builder.getInt32(0), (*pt)->getType(ctx));
                while (elements.size() < ((MyArrayType *)(*pt))->size)
                    elements.push_back((Constant *)zero);

                Constant *constarr = ConstantArray::get(array_t, elements);
                v->setInitializer(constarr);
                ctx.blocks.back()[varname] = v;
            }
            else
            {
                ctx.blocks.front()[varname] = ctx.builder.CreateAlloca(array_t, 0, varname.c_str());
                // TODO: initalize an array
                Value *var = ctx.CreateCast(ctx.blocks.front()[varname], (*pt)->getRootType()->getType(ctx)->getPointerTo());
                // a[] = {0}
                if((*pi)->init && (*pi)->init->getName() == "\"Number\"" && ((Number *)((*pi)->init))->longView() == 0)
                {
                    if(((MyArrayType *)(*pt))->size < 100)
                        for(int i = 0; i < ((MyArrayType *)(*pt))->size; i++)
                            ctx.builder.CreateStore(ctx.CreateCast(ctx.builder.getInt32(0), array_t->getElementType()), ctx.builder.CreateGEP(var, ctx.builder.getInt32(i)));
                }
                else
                {
                    int idx = 0;
                    for (Expression *p = (*pi)->init; p; p = p->left, idx++)
                    {
                        Value *initval = p->codeGen(ctx);
                        if (initval)
                            ctx.builder.CreateStore(ctx.CreateCast(initval, array_t->getElementType()), ctx.builder.CreateGEP(var, ctx.builder.getInt32(idx)));
                    }
                }
            }
        }
        else if ((*pt)->type == TYPE_STRUCT || (*pt)->type == TYPE_UNION)
        {
            // struct type
            AggregateType *at = (AggregateType *)*pt;
            StructType *stype = ctx.module->getTypeByName(at->name);
            if(!stype)
                ctx.error("struct or union not defined");

            if (ctx.isglobal)
            {
                GlobalVariable *v = new GlobalVariable(
                    *ctx.module,
                    stype,
                    (*pt)->qual && (*pt)->qual->isconst ? true : false, // const attribute
                    (*pt)->linkage == LINKAGE_EXTERNAL ? GlobalValue::ExternalLinkage : (*pt)->linkage == LINKAGE_INTERNAL ? GlobalValue::InternalLinkage : GlobalValue::PrivateLinkage,
                    0,
                    varname);
                // vector<Constant *> elements;
                // for (Expression *q = (*pi)->init; q; q = q->left)
                //     elements.push_back(ctx.Num2Constant((Number *)q));
                // Constant *constarr = ConstantStruct::get(stype, elements);
                Constant *constarr = ConstantStruct::get(stype);
                v->setInitializer(constarr);
                ctx.blocks.back()[varname] = v;
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
                    (*pt)->linkage == LINKAGE_EXTERNAL ? GlobalValue::ExternalLinkage : (*pt)->linkage == LINKAGE_INTERNAL ? GlobalValue::InternalLinkage : GlobalValue::PrivateLinkage,
                    0,
                    varname);
                if ((*pi)->init)
                    // if initializer exist
                    v->setInitializer((Constant *)(*pi)->init->codeGen(ctx));
                else
                    // else initialize to 0
                    v->setInitializer(ConstantInt::get(t, 0));
                ctx.blocks.back()[varname] = v;
            }
            else
            {
                // allocate space for new local variable
                ctx.blocks.front()[varname] = ctx.builder.CreateAlloca(t, 0, varname.c_str());
                if ((*pi)->init)
                    ctx.builder.CreateStore(ctx.CreateCast((*pi)->init->codeGen(ctx), t), ctx.blocks.front()[varname]);
            }
        }

        // collect struct type variable
        if ((*pt)->getRootType()->type == TYPE_STRUCT || (*pt)->getRootType()->type == TYPE_UNION)
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
    bool isvarargs = false;
    if (params)
    {
        // collect args
        vector<Type *> args;
        for (Parameter *p = params; p; p = (Parameter *)(p->next))
        {
            args.push_back((Type *)(p->codeGen(ctx)));
            if (p->isvariableargs)
                isvarargs = true;
        }
        functype = FunctionType::get(rettype->getType(ctx), args, isvarargs);
    }
    else
        // no param
        // false: is not variable args
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

    // default return statement
    if (stmts->stmt && stmts->stmt->tail && stmts->stmt->tail->getName() != "\"ReturnStatement\"")
    {
        if (rettype->type == TYPE_VOID)
            ctx.builder.CreateRetVoid();
        else
            ctx.builder.CreateRet(ctx.CreateCast(ctx.builder.getInt64(0), rettype->getType(ctx)));
    }

    // leave the current block
    ctx.curFunction = nullptr;
    ctx.blocks.pop_front();

    ctx.dump();

    return func;
}

Value *TypeDeclaration::codeGen(CodeGenerator &ctx)
{
    if (type && (type->type == TYPE_STRUCT || type->type == TYPE_UNION))
    {
        AggregateType *at = (AggregateType *)type;
        // create struct type for assigned name or implement the member declaration
        StructType *stype = ctx.module->getTypeByName(at->name);
        if (!stype)
            stype = StructType::create(ctx.ctx, at->name);
        if (!stype->isOpaque() && at->members)
            ctx.error("redefinition of struct or union '" + at->name + "'");

        if (stype->isOpaque())
        {
            if (type->type == TYPE_STRUCT)
            {
                ctx.structtypes[at->name] = vector<string>();
                if (at->members)
                {
                    // set members
                    vector<Type *> elements;
                    for (auto &p : *at->members)
                    {
                        for (auto &q : *p->first)
                            elements.push_back(q->getType(ctx));
                        // record field name in context
                        for (auto &q : *p->second)
                            ctx.structtypes[at->name].push_back(q->name);
                    }
                    stype->setBody(elements);
                }
                // if no member, just a forward declaration, set as opaque type (default)
            }
            else if (type->type == TYPE_UNION)
            {
                ctx.uniontypes[at->name] = map<string, Type *>();
                if (at->members)
                {
                    vector<Type *> elements;
                    // regard a union as a non-type memory space
                    elements.push_back(ArrayType::get(ctx.builder.getInt8Ty(), at->getSize()));
                    stype->setBody(elements);

                    // set members
                    for (auto &p : *at->members)
                    {
                        auto m = (*p->first).begin();
                        auto n = (*p->second).begin();
                        for (; m != (*p->first).end() && n != (*p->second).end(); m++, n++)
                        {
                            if (ctx.uniontypes[at->name].find((*n)->name) != ctx.uniontypes[at->name].end())
                                ctx.error("redefiniton of member '" + (*n)->name + "'");
                            ctx.uniontypes[at->name][(*n)->name] = (*m)->getType(ctx);
                        }
                    }
                }
            }
        }
    }

    return nullptr;
}