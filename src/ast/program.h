#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <vector>
#include "basic.h"
#include "declaration.h"

using namespace std;

class Program : public Node
{
public:
    vector<Declaration *> *decs;
    Program(vector<Declaration *> *l) : decs(l) {}
    virtual string getName() { return "\"Program\""; }
};

#endif