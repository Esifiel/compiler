%{
#include "ast/program.hpp"
Program *program;
%}

/* %expect 1 // shift-reduce conflict: optional else-part for if-else statement */

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
void yywarning(string s, string addition = "");
}

%union {
    union union_num num;
    string *stringValue;
    enum op_type op;
    bool flag;
    
    Program *program;

    TypeSpecifier *type;

    Declaration *declaration;
    VariableDeclaration *variableDeclaration;
    vector<VariableDeclaration *> *vars;
    Parameter *param;
    FunctionDeclaration *functionDeclaration;

    Statement *statement;
    CompoundStatement *compoundStatement;
    ExpressionStatement *expressionStatement;
    SelectionStatement *selectionStatement;
    IterationStatement *iterationStatement;

    Expression *expression;
    Identifier *identifier;
    vector<Identifier *> *ids;
    vector<Expression *> *exprs;
    Number *number;
}

%token  CHAR SHORT INT LONG FLOAT DOUBLE STRUCT ENUM UNION VOID
%token  AUTO REGISTER EXTERN CONST UNSIGNED SIGNED VOLATILE STATIC
%token  IF ELSE FOR DO WHILE BREAK CONTINUE SWITCH CASE DEFAULT GOTO
%token  ADD SUB MUL DIV MOD
        ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN
        AND OR XOR NOT SL SR
        ANDASSIGN ORASSIGN XORASSIGN SLASSIGN SRASSIGN
        ANDAND OROR NOTNOT LT GT GEQ LEQ NEQ EQ
        ASSIGN
        INC DEC
%token  TYPEDEF SIZEOF RETURN DOTDOTDOT
%token  DELIM COMMA COLON QUESTION DOT TO LP RP LB RB LC RC
%token<num> NUMCHAR NUMSHORT NUMINT NUMLONG NUMFLOAT NUMDOUBLE
%token<stringValue> STRING IDENTIFIER
%type<op> unary-operator assignment-operator
%type<flag> signed-spec

%type<program> program

%type<type> type-spec decl-specs

%type<declaration> external-decl translation-unit
%type<variableDeclaration> decl
%type<functionDeclaration> function-definition
%type<param> param-list param-type-list param-decl
%type<vars> decl-list

%type<statement> stat jump-stat labeled-stat stat-list
%type<compoundStatement> compound-stat
%type<expressionStatement> exp-stat
%type<selectionStatement> selection-stat
%type<iterationStatement> iteration-stat

%type<expression> exp assignment-exp postfix-exp conditional-exp primary-exp const-exp logical-or-exp logical-and-exp inclusive-or-exp exclusive-or-exp and-exp equality-exp relational-exp shift-expression additive-exp mult-exp cast-exp unary-exp initializer declarator
%type<exprs> argument-exp-list
%type<identifier> id typedef-name direct-declarator init-declarator
%type<ids> id-list init-declarator-list
%type<number> number const

%right ASSIGN ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN ANDASSIGN ORASSIGN XORASSIGN SLASSIGN SRASSIGN
%left OROR
%left ANDAND
%left OR
%left XOR
%left AND
%left EQ NEQ
%left GT GEQ LT LEQ
%left SL SR
%left ADD SUB
%left MUL DIV MOD
%right INC DEC NOTNOT NOT SIZEOF

%start program

%%

program                     : translation-unit { $$ = new Program($1); program = $$; }
                            ;

translation-unit	        : external-decl { $$ = $1; }
                            | translation-unit external-decl { $1->next = $2; $$ = $1; }
                            ;

external-decl               : function-definition { $$ = $1; }
                            | decl { $$ = $1; }
                            ;

function-definition         : decl-specs declarator param-type-list compound-stat { $$ = new FunctionDeclaration($1, $2, $3, $4); }
                            |            declarator param-type-list compound-stat { $$ = new FunctionDeclaration(nullptr, $1, $2, $3); }
                            | decl-specs declarator                 compound-stat { $$ = new FunctionDeclaration($1, $2, nullptr, $3); }
                            |            declarator                 compound-stat { $$ = new FunctionDeclaration(nullptr, $1, nullptr, $2); }
                            ;

decl                        : decl-specs init-declarator-list DELIM { $$ = new VariableDeclaration($1, $2); }
                            | decl-specs DELIM
                            ;

decl-list                   : decl { $$ = new vector<VariableDeclaration *>; $$->push_back($1); }
                            | decl-list decl { $1->push_back($2); $$ = $1; }
                            ;

decl-specs                  : signed-spec type-spec { $2->isunsigned = $1; $$ = $2; }
                            | type-spec { $$ = $1; }
                            ;

storage-class-spec          : AUTO
                            | REGISTER
                            | STATIC
                            | EXTERN
                            | TYPEDEF
                            ;

signed-spec                 : SIGNED { $$ = false; }
                            | UNSIGNED { $$ = true; }
                            ;

type-spec                   : CHAR { $$ = new CharType(); }
                            | SHORT { $$ = new ShortType(); }
                            | INT { $$ = new IntType(); }
                            | LONG { $$ = new LongType(); }
                            | FLOAT { $$ = new FloatType(); }
                            | DOUBLE { $$ = new DoubleType(); }
                            | VOID { $$ = new VoidType(); }
                            | struct-or-union-spec
                            | enum-spec
                            | typedef-name
                            ;

type-qualifier              : CONST
                            | VOLATILE
                            ;

struct-or-union-spec        : struct-or-union id LC struct-decl-list RC
                            | struct-or-union LC struct-decl-list RC
                            | struct-or-union id
                            ;

struct-or-union             : STRUCT
                            | UNION
                            ;

struct-decl-list            : struct-decl
                            | struct-decl-list struct-decl
                            ;

init-declarator-list        : init-declarator { $$ = new vector<Identifier *>; $$->push_back($1); }
                            | init-declarator-list COMMA init-declarator { $1->push_back($3); $$ = $1; }
                            ;

init-declarator             : declarator { $$ = new Identifier($1); }
                            | declarator ASSIGN initializer { $$ = new Identifier($1, $3); }
                            ;

struct-decl                 : spec-qualifier-list struct-declarator-list DELIM
                            ;

spec-qualifier-list         : type-spec spec-qualifier-list
                            | type-spec
                            | type-qualifier spec-qualifier-list
                            | type-qualifier
                            ;

struct-declarator-list      : struct-declarator
                            | struct-declarator-list COMMA struct-declarator
                            ;

struct-declarator           : declarator
                            | declarator COLON const-exp
                            | COLON const-exp
                            ;
                    
enum-spec                   : ENUM id LC enumerator-list RC
                            | ENUM LC enumerator-list RC
                            | ENUM id
                            ;

enumerator-list             : enumerator
                            | enumerator-list COMMA enumerator
                            ;

enumerator                  : id
                            | id ASSIGN const-exp
                            ;

declarator                  : pointer direct-declarator
                            | direct-declarator { $$ = $1; }
                            ;

direct-declarator           : id { $$ = $1; }
                            | LP declarator RP
                            | direct-declarator LB const-exp RB
                            | direct-declarator LB RB
                            | direct-declarator LP param-type-list RP
                            | direct-declarator LP id-list RP
                            | direct-declarator LP RP
                            ;

pointer			            : MUL type-qualifier-list
                            | MUL
                            | MUL type-qualifier-list pointer
                            | MUL pointer
                            ;

type-qualifier-list	        : type-qualifier
                            | type-qualifier-list type-qualifier
                            ;

param-type-list             : param-list { $$ = $1; }
                            | param-list COMMA DOTDOTDOT
                            ;

param-list                  : param-decl { $$ = $1; }
                            | param-list COMMA param-decl { $1->next = $3; $$ = $1; }
                            ;

param-decl                  : decl-specs declarator { $$ = new Parameter($1, $2); }
                            | decl-specs abstract-declarator
                            | decl-specs { $$ = new Parameter($1); }
                            ;

id-list			            : id { $$ = new vector<Identifier *>; $$->push_back($1); }
                            | id-list COMMA id { $1->push_back($3); $$ = $1; }
                            ;

initializer                 : assignment-exp { $$ = $1; }
                            | LC initializer-list RC
                            | LC initializer-list COMMA RC
                            ;

initializer-list            : initializer
                            | initializer-list COMMA initializer
                            ;

type-name                   : spec-qualifier-list abstract-declarator
                            | spec-qualifier-list
                            ;

abstract-declarator         : direct-abstract-declarator
                            ;

direct-abstract-declarator  : LP abstract-declarator RP
                            | direct-abstract-declarator LB const-exp RB
                            | LB const-exp RB
                            | direct-abstract-declarator LB RB
                            | LB RB
                            | direct-abstract-declarator LB param-type-list RP
                            | LB param-type-list RP
                            | direct-abstract-declarator LP RP
                            | LP RP
                            ;

typedef-name                : id { $$ = $1; }
                            ;

id                          : IDENTIFIER { $$ = new Identifier(new String(*yylval.stringValue)); }
                            ;

stat                        : labeled-stat { $$ = $1; }
                            | exp-stat { $$ = $1; }
                            | compound-stat { $$ = $1; }
                            | selection-stat { $$ = $1; }
                            | iteration-stat { $$ = $1; }
                            | jump-stat { $$ = $1; }
                            ;

labeled-stat		        : id COLON stat
                            | CASE const-exp COLON stat
                            | DEFAULT COLON stat
                            ;

exp-stat            		: exp DELIM { $$ = new ExpressionStatement($1); }
                            | DELIM { $$ = new ExpressionStatement(); }
                            ;

compound-stat               : LC decl-list stat-list RC { $$ = new CompoundStatement($2, $3); }
                            | LC stat-list RC { $$ = new CompoundStatement(nullptr, $2); }
                            | LC decl-list RC { $$ = new CompoundStatement($2, nullptr); }
                            | LC RC { $$ = new CompoundStatement(nullptr, nullptr); }
                            ;

stat-list                   : stat { $$ = $1; }
                            | stat-list stat { $1->next = $2; $$ = $1; }
                            ;

selection-stat		        : IF LP exp RP stat { $$ = new IfElseStatement($3, $5); }
                            | IF LP exp RP stat ELSE stat { $5->next = $7; $$ = new IfElseStatement($3, $5); }
                            | SWITCH LP exp RP stat
                            ;

iteration-stat      		: WHILE LP exp RP stat { $$ = new WhileStatement($3, $5); }
                            | DO stat WHILE LP exp RP DELIM { $$ = new DoWhileStatement($5, $2); }
                            | FOR LP exp DELIM exp DELIM exp RP stat { $$ = new ForStatement($3, $5, $7, $9); }
                            | FOR LP exp DELIM exp DELIM     RP stat { $$ = new ForStatement($3, $5, nullptr, $8); }
                            | FOR LP exp DELIM     DELIM exp RP stat { $$ = new ForStatement($3, nullptr, $6, $8); }
                            | FOR LP     DELIM exp DELIM exp RP stat { $$ = new ForStatement(nullptr, $4, $6, $8); }
                            | FOR LP exp DELIM     DELIM     RP stat { $$ = new ForStatement($3, nullptr, nullptr, $7); }
                            | FOR LP     DELIM exp DELIM     RP stat { $$ = new ForStatement(nullptr, $4, nullptr, $7); }
                            | FOR LP     DELIM     DELIM exp RP stat { $$ = new ForStatement(nullptr, nullptr, $5, $7); }
                            | FOR LP     DELIM     DELIM     RP stat { $$ = new ForStatement(nullptr, nullptr, nullptr, $6); }
                            ;

jump-stat                   : GOTO id DELIM
                            | CONTINUE DELIM
                            | BREAK DELIM
                            | RETURN exp DELIM { $$ = new ReturnStatement($2); }
                            | RETURN DELIM { $$ = new ReturnStatement(); }
                            ;

exp			                : assignment-exp { $$ = $1; }
                            | exp COMMA assignment-exp { $$ = new Expression($1, $3, OP_COMMA); }
                            ;

assignment-exp      		: conditional-exp { $$ = $1; }
                            | unary-exp assignment-operator assignment-exp { $$ = new Expression($1, $3, $2); }
                            ;

assignment-operator	        : ASSIGN { $$ = OP_ASSIGN; }
                            | MULASSIGN { $$ = OP_MULASSIGN; }
                            | DIVASSIGN { $$ = OP_DIVASSIGN; }
                            | MODASSIGN { $$ = OP_MODASSIGN; }
                            | ADDASSIGN { $$ = OP_ADDASSIGN; }
                            | SUBASSIGN { $$ = OP_SUBASSIGN; }
                            | SLASSIGN { $$ = OP_SLASSIGN; }
                            | SRASSIGN { $$ = OP_SRASSIGN; }
                            | ANDASSIGN { $$ = OP_ANDASSIGN; }
                            | XORASSIGN { $$ = OP_XORASSIGN; }
                            | ORASSIGN { $$ = OP_ORASSIGN; }
                            ;

conditional-exp             : logical-or-exp { $$ = $1; }
                            | logical-or-exp QUESTION exp COLON conditional-exp { $$ = new Expression($3, $5, $1, OP_IFELSE); }
                            ;

const-exp           		: conditional-exp { $$ = $1; }
                            ;

logical-or-exp		        : logical-and-exp { $$ = $1; }
                            | logical-or-exp OROR logical-and-exp { $$ = new Expression($1, $3, OP_OROR); }
                            ;

logical-and-exp		        : inclusive-or-exp { $$ = $1; }
                            | logical-and-exp ANDAND inclusive-or-exp { $$ = new Expression($1, $3, OP_ANDAND); }
                            ;

inclusive-or-exp	        : exclusive-or-exp { $$ = $1; }
                            | inclusive-or-exp OR exclusive-or-exp { $$ = new Expression($1, $3, OP_OR); }
                            ;

exclusive-or-exp	        : and-exp { $$ = $1; }
                            | exclusive-or-exp XOR and-exp { $$ = new Expression($1, $3, OP_XOR); }
                            ;

and-exp			            : equality-exp { $$ = $1; }
                            | and-exp AND equality-exp { $$ = new Expression($1, $3, OP_AND); }
                            ;

equality-exp		        : relational-exp { $$ = $1;}
                            | equality-exp EQ relational-exp { $$ = new Expression($1, $3, OP_EQ); }
                            | equality-exp NEQ relational-exp { $$ = new Expression($1, $3, OP_NEQ); }
                            ;

relational-exp		        : shift-expression { $$ = $1; }
                            | relational-exp LT shift-expression { $$ = new Expression($1, $3, OP_LT); }
                            | relational-exp GT shift-expression { $$ = new Expression($1, $3, OP_GT); }
                            | relational-exp LEQ shift-expression { $$ = new Expression($1, $3, OP_LEQ); }
                            | relational-exp GEQ shift-expression { $$ = new Expression($1, $3, OP_GEQ); }
                            ;
                            
shift-expression	        : additive-exp { $$ = $1; }
                            | shift-expression SL additive-exp { $$ = new Expression($1, $3, OP_SL); }
                            | shift-expression SR additive-exp { $$ = new Expression($1, $3, OP_SR); }
                            ;

additive-exp		        : mult-exp { $$ = $1; }
                            | additive-exp ADD mult-exp { $$ = new Expression($1, $3, OP_ADD); }
                            | additive-exp SUB mult-exp { $$ = new Expression($1, $3, OP_SUB); }
                            ;

mult-exp		            : cast-exp { $$ = $1; }
                            | mult-exp MUL cast-exp { $$ = new Expression($1, $3, OP_MUL); }
                            | mult-exp DIV cast-exp { $$ = new Expression($1, $3, OP_DIV); }
                            | mult-exp MOD cast-exp { $$ = new Expression($1, $3, OP_MOD); }
                            ;

cast-exp		            : unary-exp { $$ = $1; }
                            | LP type-name RP cast-exp
                            ;

unary-exp		            : postfix-exp  { $$ = $1; }
                            | INC unary-exp { $$ = new Expression($2, OP_INC_FRONT); }
                            | DEC unary-exp { $$ = new Expression($2, OP_DEC_FRONT); }
                            | unary-operator cast-exp { $$ = new Expression($2, $1); }
                            | SIZEOF unary-exp
                            | SIZEOF LP type-name RP
                            ;

unary-operator              : AND { $$ = OP_AND; }
                            | MUL { $$ = OP_POINTER; }
                            | ADD { $$ = OP_POSITIVE; }
                            | SUB { $$ = OP_NEGTIVE; }
                            | NOT { $$ = OP_NOT; }
                            | NOTNOT { $$ = OP_NOTNOT; }
                            ;

postfix-exp		            : primary-exp { $$ = $1; }
                            | postfix-exp LB exp RB { $$ = new Identifier($1, $3); }
                            | postfix-exp LP argument-exp-list RP { $$ = new FunctionCall($1, $3); }
                            | postfix-exp LP RP { $$ = new FunctionCall($1, nullptr); }
                            | postfix-exp DOT id
                            | postfix-exp TO id
                            | postfix-exp INC { $$ = new Expression($1, OP_INC_REAR); }
                            | postfix-exp DEC { $$ = new Expression($1, OP_DEC_REAR); }
                            ;

primary-exp		            : id { $$ = $1; }
                            | const { $$ = $1; }
                            | STRING { $$ = new String(*yylval.stringValue); }
                            | LP exp RP { $$ = $2; }
                            ;

argument-exp-list	        : assignment-exp { $$ = new vector<Expression *>; $$->push_back($1); }
                            | argument-exp-list COMMA assignment-exp { $1->push_back($3); $$ = $1; }
                            ;
                            
/* const			            : int-const
                            | char-const
                            | float-const
                            | enumeration-const
                            ; */

const                       : number { $$ = $1; }
                            ;

number                      : NUMCHAR { $$ = new Number($1, new CharType(), VAL_CHAR); }
                            | NUMSHORT { $$ = new Number($1, new ShortType(), VAL_SHORT); }
                            | NUMINT { $$ = new Number($1, new IntType(), VAL_INT); }
                            | NUMLONG { $$ = new Number($1, new LongType(), VAL_LONG); }
                            | NUMFLOAT { $$ = new Number($1, new FloatType(), VAL_FLOAT); }
                            | NUMDOUBLE { $$ = new Number($1, new DoubleType(), VAL_DOUBLE); }
                            ;

%%

void yyerror(string s)
{
    cerr << "\033[1;31m"
         << "error: "
         << "\033[0m" << s << " in Line " << yylineno << ": " << yytext << endl;
    exit(1);
}

void yywarning(string s, string addition)
{
    cerr << "\033[1;35m"
         << "warning: "
         << "\033[0m" << s << " in Line " << yylineno << ": " << yytext << ". " << addition << endl;
}