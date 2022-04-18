#ifndef _BASIC_HPP_
#define _BASIC_HPP_

#include <string>
#include <llvm/IR/Value.h>

using namespace std;

class CodeGenerator;

class Node
{
public:
    Node() {}
    virtual string getName() = 0;
    virtual llvm::Value *codeGen(CodeGenerator &context) { return nullptr; };
};

#endif