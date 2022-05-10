#include "../ast/type.hpp"
#include "../ast/expression.hpp"
#include "codegen.hpp"

Type *CharType::getType(CodeGenerator &ctx)
{
    return ctx.builder.getInt8Ty();
}

Type *ShortType::getType(CodeGenerator &ctx)
{
    return ctx.builder.getInt16Ty();
}

Type *IntType::getType(CodeGenerator &ctx)
{
    return ctx.builder.getInt32Ty();
}

Type *LongType::getType(CodeGenerator &ctx)
{
    return ctx.builder.getInt64Ty();
}

Type *FloatType::getType(CodeGenerator &ctx)
{
    return ctx.builder.getFloatTy();
}

Type *DoubleType::getType(CodeGenerator &ctx)
{
    return ctx.builder.getDoubleTy();
}

Type *VoidType::getType(CodeGenerator &ctx)
{
    return ctx.builder.getVoidTy();
}

Type *MyArrayType::getType(CodeGenerator &ctx)
{
    return ArrayType::get(basictype->getType(ctx), size);
}

Type *MyPointerType::getType(CodeGenerator &ctx)
{
    return PointerType::get(basictype->getType(ctx), 0);
}

Type *MyStructType::getType(CodeGenerator &ctx)
{
    return ctx.module->getTypeByName(name);
}

Type *UnionType::getType(CodeGenerator &ctx)
{
    return nullptr;
}

Type *EnumType::getType(CodeGenerator &ctx)
{
    return nullptr;
}

uint64_t MyStructType::getSize()
{
    uint64_t sum = 0;
    cout << members << endl;
    for (auto &p : *members)
        for (auto &q : *p->first)
            sum += q->getSize();
    return sum;
}

pair<TypeSpecifier *, Identifier *> AggregateType::getMemberDef(Identifier *id)
{
    string name = id->name;
    if (members)
        for (auto &p : *members)
        {
            auto pt = (*p->first).begin();
            auto pi = (*p->second).begin();
            for (; pt != (*p->first).end() && pi != (*p->second).end(); pt++, pi++)
                if ((*pi)->name == name)
                    return pair<TypeSpecifier *, Identifier *>(*pt, *pi);
        }
    return pair<TypeSpecifier *, Identifier *>(nullptr, nullptr);
}