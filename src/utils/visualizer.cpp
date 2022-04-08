// traverse AST and write to json
#include "visualizer.hpp"
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

string head = "{";
string tail = "}";
string sub = ": ";
string sep = ", ";

void Visualizer::traverse()
{
    out << head;
    if (program)
        visitProgram(program);
    out << tail;
}

void Visualizer::visitProgram(Program *p)
{
    if (p->decs)
    {
        out << head << p->getName() << sub;
        out << head;
        visitDeclarationList(p->decs);
        out << tail;
    }
}

void Visualizer::visitDeclarationList(vector<Declaration *> *l)
{
    for (auto p = l->begin(); p != l->end(); p++)
    {
        out << (*p)->getName() << sub;
        out << head;
        visitDeclaration(*p);
        out << tail;
        out << sep;
    }
}

void Visualizer::visitDeclaration(Declaration *d)
{

}

void Visualizer::visitVarDeclaration(VariableDeclaration *d)
{

}

void Visualizer::visitFunDeclaration(FunctionDeclaration *d)
{

}

// var-declaration : type-specifier IDENTIFIER DELIM { $$ = new VariableDeclaration($1, $2); }
//     | type-specifier IDENTIFIER LB NUMBER RB DELIM { $$ = new ArrayDeclaration($1, $2, $4); }
//     ;

// type-specifier : CHAR   { $$ = new CharType(); }
//     | SHORT             { $$ = new ShortType(); }
//     | INT               { $$ = new IntType(); }
//     | LONG              { $$ = new LongType(); }
//     | FLOAT             { $$ = new FloatType(); }
//     | DOUBLE            { $$ = new DoubleType(); }
//     | STRUCT
//     | ENUM
//     | UNION
//     | VOID              { $$ = new VoidType(); }
//     ;

// fun-declaration : type-specifier IDENTIFIER LP params RP compound-stmt
//     ;

// params : param-list
//     | VOID { $$ = new vector<Parameter *>; $$->push_back(new Parameter(new VoidType())); }
//     |
//     ;

// param-list : param-list COMMA param
//     | param
//     ;

// param : type-specifier IDENTIFIER
//     | type-specifier IDENTIFIER LB RB
//     ;

// compound-stmt : LC local-declarations statement-list RC
//     ;

// local-declarations : local-declarations var-declaration
//     |
//     ;

// statement-list : statement-list statement
//     |
//     ;

// statement : expression-stmt
//     | compound-stmt
//     | selection-stmt
//     | iteration-stmt
//     | return-stmt
//     ;

// expression-stmt : expression DELIM
//     | DELIM
//     ;

// selection-stmt : IF LP expression RP statement
//     | IF LP expression RP ELSE statement
//     ;

// iteration-stmt : WHILE LP expression RP statement
//     ;

// return-stmt : RETURN DELIM
//     | RETURN expression DELIM
//     ;

// expression : var ASSIGN expression
//     | simple-expression
//     ;

// var : IDENTIFIER
//     | IDENTIFIER LB expression RB
//     ;

// simple-expression : additive-expression relop additive-expression
//     | additive-expression
//     ;

// relop : LEQ
//     | LT
//     | GT
//     | GEQ
//     | EQ
//     | NEQ
//     | ANDAND
//     | OROR
//     ;

// additive-expression : additive-expression addop term
//     | term
//     ;

// addop : ADD
//     | SUB
//     ;

// term : term mulop factor
//     | factor
//     ;

// mulop : MUL
//     | DIV
//     ;

// factor : LP expression RP
//     | var
//     | call
//     | NUMBER
//     ;

// call : IDENTIFIER LP args RP
//     ;

// args : arg-list
//     |
//     ;

// arg-list : arg-list COMMA expression
//     | expression
//     ;