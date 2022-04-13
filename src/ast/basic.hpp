#ifndef _BASIC_HPP_
#define _BASIC_HPP_

#include <string>
#include <llvm/IR/Value.h>

using namespace std;

class CodeGenContext;

class Node
{
public:
    Node() {}
    virtual ~Node() {}
    virtual string getName() = 0;
    virtual llvm::Value *codeGen(CodeGenContext &context) { return nullptr; };
};

#endif