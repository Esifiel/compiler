%{
#include "ast/program.h"
Program *program;
%}

%code requires {
#include <iostream>
#include <string>
#include <vector>
#include "ast/basic.h"
#include "ast/expression.h"
#include "ast/statement.h"
#include "ast/declaration.h"
#include "ast/type.h"
#include "ast/program.h"

using namespace std;

extern int yylex();
void yyerror(string s);
}

%union {
    char _char;
    short _short;
    int _int;
    long _long;
    float _float;
    double _double;
    string *_string;
    
    Node *node;

    Program *program;
    Declaration *declaration;
    Type *type;
    VariableDeclaration *variableDeclaration;
    Expression *expression;
    Statement *statement;
    TypeDeclaration *typeDeclatation;
    Identifier *identifier;

    vector<Declaration *> *declarations;
    vector<VariableDeclaration *> *variableDeclarations;
    vector<Statement *> *statements;
    vector<Expression *> *expressions;
}

%token  CHAR SHORT INT LONG FLOAT DOUBLE
        STRUCT ENUM UNION VOID
%token  AUTO REGISTER EXTERN CONST UNSIGNED SIGNED VOLATILE STATIC
%token  IF ELSE FOR DO WHILE BREAK CONTINUE SWITCH CASE DEFAULT GOTO
%token  ADD SUB MUL DIV ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN
        AND OR XOR ANDASSIGN ORASSIGN XORASSIGN
        ANDAND OROR
        SL SR SLASSIGN SRASSIGN
        ASSIGN LT GT NOTEQ EQ
%token  TYPEDEF
%token  SIZEOF
%token  RETURN
%token  DELIM

%token<_int> NUMBER
%token<identifier> IDENTIFIER

%type<declarations> declarations
%type<declaration> declaration
%type<type> type
%type<variableDeclaration> var_decl
%type<expression> expression
%type<expressions> expressions
%type<statement> statement
%type<statements> statements
%type<program> program

%left ADD SUB MUL DIV

%start program

%%

program : declarations { $$ = new Program($1); program = $$; }
    ;

declarations : declarations declaration { $1->push_back($2); }
    | declaration { $$ = new vector<Declaration *>; $$->push_back($1); }
    ;

declaration : var_decl
    ;

var_decl : type IDENTIFIER DELIM { $$ = new VariableDeclaration($1, $2); }
    ;

type : CHAR     { $$ = new CharType(); }
    | SHORT     { $$ = new ShortType(); }
    | INT       { $$ = new IntType(); }
    | LONG      { $$ = new LongType(); }
    | FLOAT     { $$ = new FloatType(); }
    | DOUBLE    { $$ = new DoubleType(); }
    | STRUCT
    | ENUM
    | UNION
    | VOID
    ;

%%

void yyerror(string s)
{
    cout << "[!] Error, " << s << endl;
    /* fprintf(stderr, "[!] Error, %s\n", s); */
    exit(1);
}