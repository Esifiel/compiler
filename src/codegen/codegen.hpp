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
#include <stack>

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
    stack<map<string, Value *>> env;

    // initialize the context
    CodeGenerator() : builder(ctx) { module = new Module("main", ctx); }
};

#endif