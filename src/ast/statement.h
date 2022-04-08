#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include "basic.h"
#include "declaration.h"

using namespace std;

class Statement : public Node
{
public:
    Statement() {}
    virtual string getName() { return "Statement"; }
};

class Declaration;

class CompoundStatement : public Statement
{
public:
    vector<Declaration *> *decs;
    vector<Statement *> *stmts;
    CompoundStatement(vector<Declaration *> *d, vector<Statement *> *s):decs(d), stmts(s) {}
    virtual string getName() { return "CompoundStatement"; }
};

#endif