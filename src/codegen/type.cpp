#include "../ast/type.hpp"
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