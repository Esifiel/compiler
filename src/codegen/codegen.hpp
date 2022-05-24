#ifndef _CODEGEN_HPP_
#define _CODEGEN_HPP_

#pragma once

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
#include <llvm/IR/CFG.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/TypeFinder.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include "llvm/Support/Casting.h"
#include <llvm/Bitcode/BitcodeWriter.h>
#include <iostream>
#include <cstdlib>
#include <map>
#include <stack>
#include <list>
#include "../ast/expression.hpp"
#include "../ast/type.hpp"

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
    Function *curFunction;                          // current defined function
    map<string, Function *> functions;              // functions' def
    list<map<string, Value *>> blocks;              // local environments
    list<pair<BasicBlock *, BasicBlock *>> jumpctx; // for jump statement
    bool isglobal;                                  // global definition
    bool isleft;                                    // left value
    map<string, vector<string>> structtypes;        // record members' name
    map<string, AggregateType *> structvars;        // record struct types' def
    map<string, map<string, Type *>> uniontypes;    // record union type def
    map<string, BasicBlock *> labels;               // record labels' def
    vector<pair<BasicBlock *, string>> dummy;       // record backward goto

    CodeGenerator();
    ~CodeGenerator();

    // for debug
    void dump();
    void error(string msg);
    void warning(string msg);

    // utils
    Value *CreateCast(Value *V, Type *DestTy);
    Value *GetVar(string name);
    Function *GetFunction(string name);
    Value *CreateUnaryExpr(Value *a, enum op_type op);
    Value *CreateBinaryExpr(Value *a, Value *b, enum op_type op);
    Constant *Num2Constant(Number *num);
};

#endif