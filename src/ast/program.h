#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <vector>
#include "basic.h"
#include "declaration.h"

using namespace std;

class Program : public Node
{
public:
    vector<Declaration *> *dec_list;
    Program(vector<Declaration *> *l) : dec_list(l) {}
    void print() {
        
    }
};

#endif