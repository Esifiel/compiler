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
#include <cstdlib>
#include <map>
#include <stack>

using namespace llvm;
using namespace std;

// helper for the generation procedure of IR
class CodeGenerator
{
public:
    // necessary data structure
    LLVMContext ctx;
    Module *module;
    IRBuilder<> builder;
    // auxiliary
    Function *curFunction;
    map<string, Function *> functions;
    map<string, Value *> locals;
    map<string, Value *> globals;
    bool isglobal;

    // initialize the context
    CodeGenerator() : builder(ctx)
    {
        module = new Module("main", ctx);
        curFunction = nullptr;
        isglobal = false;
    }
    ~CodeGenerator() {}

    // utils
    void dump()
    {
        cout << "--------------------IR begin--------------------" << endl;
        module->print(outs(), nullptr);
        cout << "--------------------IR end---------------------" << endl;
    }
    void error(string msg)
    {
        cerr << "\033[31m" << "error: " << "\033[0m" << msg << endl;
        exit(1);
    }
    void warning()
    {
    }
};

#endif