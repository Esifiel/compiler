#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#include "basic.hpp"
#include "declaration.hpp"

using namespace std;

class CodeGenerator;

class Program : public Node
{
public:
    Declaration *decl;

    Program(Declaration *l) : decl(l) {}

    virtual string getName() { return "\"Program\""; }
    virtual llvm::Value *codeGen(CodeGenerator &ctx);
};

#endif