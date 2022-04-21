#include "codegen.hpp"

void CodeGenerator::dump()
{
    cout << endl
         << "--------------------IR begin--------------------" << endl;
    module->print(outs(), nullptr);
    cout << "--------------------IR end---------------------" << endl;
}

void CodeGenerator::error(string msg)
{
    cerr << "\033[31m"
         << "error: "
         << "\033[0m" << msg << endl;
    exit(1);
}

Value *CodeGenerator::CreateCast(Value *V, Type *DestTy)
{
    if (V->getType() == DestTy)
        return V;
    else if (V->getType()->isIntegerTy() && DestTy->isIntegerTy())
        return builder.CreateIntCast(V, DestTy, false, "");
    else if (V->getType()->isFloatingPointTy() && DestTy->isFloatingPointTy())
        return builder.CreateFPCast(V, DestTy, "");
    else if (V->getType()->isFloatingPointTy())
        return builder.CreateFPToSI(V, DestTy);
    else if (DestTy->isFloatingPointTy())
        return builder.CreateSIToFP(V, DestTy);
    else
        // error("type casting failed.");
        return builder.CreateIntCast(V, DestTy, false, "");
}

Value *CodeGenerator::GetVar(string name)
{
    if (locals.find(name) != locals.end())
        return locals[name];
    else if (globals.find(name) != globals.end())
        return globals[name];
    else
        error(string("variable '") + name + string("' not found"));
}

Value *CodeGenerator::CreateCmp(Value *a, Value *b)
{

}