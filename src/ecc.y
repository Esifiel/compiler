%{
#include "ast/program.hpp"
Program *program;
%}

%code requires {
#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include "ast/basic.hpp"
#include "ast/expression.hpp"
#include "ast/statement.hpp"
#include "ast/declaration.hpp"
#include "ast/type.hpp"
#include "ast/program.hpp"

using namespace std;

extern int yylineno;
extern char *yytext;
extern int yylex();
void yyerror(string s);
}

%union {
    union union_num num;
    string *stringValue;
    
    Node *node;
    Program *program;

    TypeSpecifier *type;

    Declaration *declaration;
    VariableDeclaration *variableDeclaration;
    FunctionDeclaration *functionDeclaration;
    TypeDeclaration *typeDeclatation;

    Statement *statement;
    CompoundStatement *compoundStatement;
    ExpressionStatement *expressionStatement;
    SelectionStatement *selectionStatement;
    IterationStatement *iterationStatement;
    WhileStatement *whileStatement;
    ForStatement *forStatement;
    ReturnStatement *returnStatement;

    Expression *expression;
    Identifier *identifier;
    Parameter *param;
    FunctionCall *functionCall;

    vector<Declaration *> *decls;
    vector<VariableDeclaration *> *vars;
    vector<FunctionDeclaration *> *funcs;
    vector<Statement *> *stmts;
    vector<Parameter *> *params;
    vector<Expression *> *exprs;
}

%token  CHAR SHORT INT LONG FLOAT DOUBLE STRUCT ENUM UNION VOID
%token  AUTO REGISTER EXTERN CONST UNSIGNED SIGNED VOLATILE STATIC
%token  IF ELSE FOR DO WHILE BREAK CONTINUE SWITCH CASE DEFAULT GOTO
%token  ADD SUB MUL DIV MOD ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN
        AND OR XOR NOT ANDASSIGN ORASSIGN XORASSIGN SL SR SLASSIGN SRASSIGN
        ANDAND OROR ASSIGN LT GT GEQ LEQ NEQ EQ
%token  TYPEDEF SIZEOF RETURN
%token  DELIM COMMA LP RP LB RB LC RC
%token<num> NUMBER
%token<stringValue> STRING IDENTIFIER 

%type<program> program

%type<type> type-specifier

%type<decls> declaration-list
%type<declaration> declaration
%type<variableDeclaration> var-declaration
%type<functionDeclaration> fun-declaration
%type<vars> local-declarations

%type<expression> expression
%type<identifier> id var
%type<param> param
%type<params> param-list params
%type<exprs> expression-list args arg-list
%type<functionCall> call
%type<expression> simple-expression additive-expression term factor

%type<statement> statement
%type<stmts> statement-list
%type<compoundStatement> compound-stmt
%type<expressionStatement> expression-stmt
%type<selectionStatement> selection-stmt
%type<iterationStatement> iteration-stmt
%type<whileStatement> while-stmt
%type<forStatement> for-stmt
%type<returnStatement> return-stmt

%type<stringValue> addop mulop relop

%left ADD SUB MUL DIV MOD

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
    | type-specifier id LB NUMBER RB DELIM { $$ = new VariableDeclaration(new ArrayType($1, $4.longValue), $2); }
    ;

id : IDENTIFIER { $$ = new Identifier($1); }
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
    | { $$ = new vector<VariableDeclaration *>; }
    ;

statement-list : statement-list statement { $1->push_back($2); $$ = $1; }
    | { $$ = new vector<Statement *>; }
    ;

statement : expression-stmt { $$ = $1; }
    | compound-stmt { $$ = $1; }
    | selection-stmt { $$ = $1; }
    | iteration-stmt { $$ = $1; }
    | return-stmt { $$ = $1; }
    ;

expression-stmt : expression DELIM { $$ = new ExpressionStatement($1); }
    | DELIM { $$ = new ExpressionStatement(); }
    ;

selection-stmt : IF LP expression RP statement
    | IF LP expression RP ELSE statement
    ;

iteration-stmt : while-stmt { $$ = $1; }
    | for-stmt { $$ = $1; }
    ;

while-stmt : WHILE LP expression RP compound-stmt { $$ = new WhileStatement($3, $5); }
    ;

for-stmt : FOR LP expression-list DELIM expression DELIM expression-list RP compound-stmt { $$ = new ForStatement($3, $5, $7, $9); }
    ;

expression-list : expression-list COMMA expression { $1->push_back($3); $$ = $1; }
    | expression { $$ = new vector<Expression *>; $$->push_back($1); }
    ;

return-stmt : RETURN expression-stmt { $$ = new ReturnStatement($2); }
    ;

expression : var ASSIGN expression { $$ = new Assignment($1, $3); }
    | simple-expression { $$ = $1; }
    ;

var : id { $$ = $1; }
    | id LB NUMBER RB { $$ = new Identifier($1->name, $3.longValue); }
    ;

simple-expression : additive-expression relop additive-expression { $$ = new SimpleExpression($1, $2, $3); }
    | additive-expression { $$ = $1; }
    ;

relop : LEQ { $$ = new string("<="); }
    | LT { $$ = new string("<"); }
    | GT { $$ = new string(">"); }
    | GEQ { $$ = new string(">="); }
    | EQ { $$ = new string("=="); }
    | NEQ { $$ = new string("!="); }
    | ANDAND { $$ = new string("&&"); }
    | OROR { $$ = new string("||"); }
    ;

additive-expression : additive-expression addop term { $$ = new AdditiveExpression($1, $2, $3); }
    | term { $$ = $1; }
    ;

addop : ADD { $$ = new string("+"); }
    | SUB { $$ = new string("-"); }
    ;

// what type is it
term : term mulop factor { $$ = new SimpleExpression($1, $2, $3); }
    | factor { $$ = $1; }
    ;

mulop : MUL { $$ = new string("*"); }
    | DIV { $$ = new string("/"); }
    | MOD { $$ = new string("%"); }
    ;

factor : LP expression RP { $$ = $2; }
    | var { $$ = $1; }
    | call { $$ = $1; }
    | NUMBER { $$ = new Number($1); }
    ;

call : var LP args RP { $$ = new FunctionalCall($1, $3); }
    ;

args : arg-list { $$ = $1; }
    | { $$ = new vector<Expression *>; }
    ;

arg-list : arg-list COMMA expression { $1->push_back($3); $$ = $1; }
    | expression { $$ = new vector<Expression *>; $$->push_back($1); }
    ;

%%

void yyerror(string s)
{
    fprintf(stderr, "[!] %s in Line %d: %s\n", s.c_str(), yylineno, yytext);
    exit(1);
}