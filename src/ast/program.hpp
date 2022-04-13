#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#include <vector>
#include "basic.hpp"
#include "declaration.hpp"

using namespace std;

class Program : public Node
{
public:
    vector<Declaration *> *decs;
    Program(vector<Declaration *> *l) : decs(l) {}
    virtual string getName() { return "\"Program\""; }
};

#endif