#ifndef _BASIC_H_
#define _BASIC_H_

#include <string>

using namespace std;

class Node
{
public:
    Node() {}
    virtual ~Node() {}
    virtual string getName() = 0;
};

#endif