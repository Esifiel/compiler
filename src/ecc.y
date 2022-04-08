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
    FunctionDeclaration *functionDeclaration;
    Expression *expression;
    Statement *statement;
    TypeDeclaration *typeDeclatation;
    Identifier *identifier;
    Parameter *param;
    CompoundStatement *compoundStatement;

    vector<Declaration *> *declarations;
    vector<VariableDeclaration *> *variableDeclarations;
    vector<FunctionDeclaration *> *functionDeclarations;
    vector<Statement *> *statements;
    vector<Parameter *> *params;
}

%token  CHAR SHORT INT LONG FLOAT DOUBLE STRUCT ENUM UNION VOID
%token  AUTO REGISTER EXTERN CONST UNSIGNED SIGNED VOLATILE STATIC
%token  IF ELSE FOR DO WHILE BREAK CONTINUE SWITCH CASE DEFAULT GOTO
%token  ADD SUB MUL DIV MOD ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN
        AND OR XOR NOT ANDASSIGN ORASSIGN XORASSIGN SL SR SLASSIGN SRASSIGN
        ANDAND OROR ASSIGN LT GT GEQ LEQ NEQ EQ
%token  TYPEDEF SIZEOF RETURN
%token  DELIM COMMA LP RP LB RB LC RC

%token<_int> NUMBER
%token<_string> IDENTIFIER

%type<program> program
%type<declarations> declaration-list local-declarations
%type<declaration> declaration
%type<type> type-specifier
%type<variableDeclaration> var-declaration
%type<functionDeclaration> fun-declaration
%type<param> param
%type<params> param-list params
%type<expression> expression expression-stmt
%type<statement> statement
%type<statements> statement-list
%type<compoundStatement> compound-stmt
%type<identifier> id


%left ADD SUB MUL DIV

%start program

%%

program : declaration-list { $$ = new Program($1); program = $$; }
    ;

declaration-list : declaration-list declaration { $1->push_back($2); $$ = $1; }
    | declaration { $$ = new vector<Declaration *>; $$->push_back($1); }
    ;

declaration : var-declaration { $$ = $1; }
    | fun-declaration { $$ = $1; }
    ;

var-declaration : type-specifier id DELIM { $$ = new VariableDeclaration($1, $2); }
    | type-specifier id LB NUMBER RB DELIM { $$ = new VariableDeclaration(new ArrayType($1, $4), $2); }
    ;

id : IDENTIFIER { $$ = new Identifier(*$1); }
    ;

type-specifier : CHAR   { $$ = new CharType(); }
    | SHORT             { $$ = new ShortType(); }
    | INT               { $$ = new IntType(); }
    | LONG              { $$ = new LongType(); }
    | FLOAT             { $$ = new FloatType(); }
    | DOUBLE            { $$ = new DoubleType(); }
    | STRUCT
    | ENUM
    | UNION
    | VOID              { $$ = new VoidType(); }
    ;

fun-declaration : type-specifier id LP params RP compound-stmt { $$ = new FunctionDeclaration($1, $2, $4, $6); }
    ;

params : param-list { $$ = $1; }
    | VOID { $$ = new vector<Parameter *>; $$->push_back(new Parameter(new VoidType())); }
    | { $$ = new vector<Parameter *>; }
    ;

param-list : param-list COMMA param { $1->push_back($3); $$ = $1; }
    | param { $$ = new vector<Parameter *>; }
    ;

param : type-specifier id { $$ = new Parameter($1, $2); }
    | type-specifier id LB RB { $$ = new Parameter(new ArrayType($1, 0), $2); }
    ;

compound-stmt : LC local-declarations statement-list RC { $$ = new CompoundStatement($2, $3); }
    ;

local-declarations : local-declarations var-declaration { $1->push_back($2); $$ = $1; }
    | { $$ = new vector<Declaration *>; }
    ;

statement-list : statement-list statement
    |
    ;

statement : expression-stmt
    | compound-stmt
    | selection-stmt
    | iteration-stmt
    | return-stmt
    ;

expression-stmt : expression DELIM
    | DELIM
    ;

selection-stmt : IF LP expression RP statement
    | IF LP expression RP ELSE statement
    ;

iteration-stmt : WHILE LP expression RP statement
    ;

return-stmt : RETURN DELIM
    | RETURN expression DELIM
    ;

expression : var ASSIGN expression
    | simple-expression
    ;

var : id
    | id LB expression RB
    ;

simple-expression : additive-expression relop additive-expression
    | additive-expression
    ;

relop : LEQ
    | LT
    | GT
    | GEQ
    | EQ
    | NEQ
    | ANDAND
    | OROR
    ;

additive-expression : additive-expression addop term
    | term
    ;

addop : ADD
    | SUB
    ;

term : term mulop factor
    | factor
    ;

mulop : MUL
    | DIV
    ;

factor : LP expression RP
    | var
    | call
    | NUMBER
    ;

call : id LP args RP
    ;

args : arg-list
    |
    ;

arg-list : arg-list COMMA expression
    | expression
    ;

%%

void yyerror(string s)
{
    cout << "[!] Error, " << s << endl;
    /* fprintf(stderr, "[!] Error, %s\n", s); */
    exit(1);
}