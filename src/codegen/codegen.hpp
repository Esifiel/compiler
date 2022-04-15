#ifndef _CODEGEN_HPP_
#define _CODEGEN_HPP_

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <iostream>
#include <map>

using namespace llvm;
using namespace std;

// helper for the generation procedure of IR
class CodeGenerator
{
public:
    LLVMContext ctx;
    Module *module;
    IRBuilder<> builder;
    map<string, Value *> symtable;

    // initialize the context
    CodeGenerator() : builder(ctx)
    {
        module = new Module("main", ctx);
    }
    // GenericValue runCode()
    // {
    //     Constant *c = TheModule.getOrInsertFunction("foo", llvm::Type::getVoidTy(context), llvm::Type::getVoidTy(TheContext), NULL);
    //     Function* foo = cast<Function>(c);
    //     foo->setCallingConv(CallingConv::C);

    //     cout << "Running code..." << endl;
    //     ExecutionEngine *engine = EngineBuilder(TheModule).create();
    //     engine->finalizeObject();
    //     vector<GenericValue> noargs;
    //     GenericValue v = engine->runFunction(mainFunction, noargs);
    //     std::cout << "Code was run.\n";
    //     return v;
    // }
};

#endif