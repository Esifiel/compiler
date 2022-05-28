%{
#include "ast/program.hpp"
#include <stdint.h>
#include <map>
Program *program;
map<string, Number *> constvar;
map<string, AggregateType *> aggrdef;
map<string, TypeSpecifier *> typealias;
map<string, uint64_t> enumvalue;
%}

%expect 1 // shift-reduce conflict: optional else-part for if-else statement

%define parse.error verbose

%code requires {
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
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
void yywarning(string s);

static void debug(string s);
static Expression *calculate(Expression *a, enum op_type op);
static Expression *calculate(Expression *a, Expression *b, enum op_type op);
static Expression *calculate(Expression *a, Expression *b, Expression *c, enum op_type op);
static string randstr();
}

%union {
    union union_num num;
    string *stringValue;
    enum op_type op;
    
    Program *program;
    Node *node;

    TypeSpecifier *type;
    Qualifier *qual;
    AggregateType *aggrtype;
    pair<vector<TypeSpecifier *> *, vector<Identifier *> *> *member;
    vector<pair<vector<TypeSpecifier *> *, vector<Identifier *> *> *> *members;

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
    String *str;
}

%token  CHAR SHORT INT LONG FLOAT DOUBLE STRUCT ENUM UNION VOID
%token  AUTO REGISTER EXTERN CONST UNSIGNED SIGNED VOLATILE STATIC
%token  IF ELSE FOR DO WHILE BREAK CONTINUE SWITCH CASE DEFAULT GOTO
%token  ADDORPOSITIVE SUBORNEGATIVE MULORDEREFERENCE DIV MOD
        ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN
        ANDORADDRESSOF OR XOR NOT SL SR
        ANDASSIGN ORASSIGN XORASSIGN SLASSIGN SRASSIGN NOTASSIGN
        ANDAND OROR NOTNOT LT GT GEQ LEQ NEQ EQ
        ASSIGN
        INC DEC
%token  TYPEDEF SIZEOF RETURN DOTDOTDOT
%token  DELIM COMMA COLON QUESTION DOT TO LP RP LB RB LC RC
%token<num> NUMCHAR NUMSHORT NUMINT NUMLONG NUMFLOAT NUMDOUBLE
%token<stringValue> STRING IDENTIFIER TYPENAME

%type<op> assignment-operator unary-operator

%type<program> program

%type<type> type-spec decl-specs spec-qualifier-list type-name storage-class-specifier
%type<qual> pointer type-qualifier type-qualifier-list 
%type<aggrtype> struct-or-union-spec struct-or-union
%type<members> struct-decl-list
%type<member> struct-decl

%type<declaration> external-decl translation-unit decl decl-list
%type<functionDeclaration> function-definition
%type<param> param-list param-type-list param-decl

%type<statement> stat jump-stat labeled-stat stat-list
%type<compoundStatement> compound-stat
%type<expressionStatement> exp-stat
%type<selectionStatement> selection-stat
%type<iterationStatement> iteration-stat

%type<expression> exp assignment-exp postfix-exp conditional-exp primary-exp logical-or-exp logical-and-exp inclusive-or-exp exclusive-or-exp and-exp equality-exp relational-exp shift-expression additive-exp mult-exp cast-exp unary-exp initializer initializer-list
%type<exprs> argument-exp-list
%type<identifier> init-declarator struct-declarator
%type<ids> id-list init-declarator-list struct-declarator-list
%type<number> number const const-exp
%type<str> string-list

%type<node> direct-declarator declarator abstract-declarator

%right ASSIGN ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN ANDASSIGN ORASSIGN XORASSIGN SLASSIGN SRASSIGN
%left OROR
%left ANDAND
%left OR
%left XOR
%left ANDORADDRESSOF
%left EQ NEQ
%left GT GEQ LT LEQ
%left SL SR
%left ADDORPOSITIVE SUBORNEGATIVE
%left MULORDEREFERENCE DIV MOD
%right INC DEC NOTNOT NOT SIZEOF

%start program

%%

program                     : translation-unit { $$ = new Program($1); program = $$; }
                            ;

translation-unit	        : external-decl                     { $$ = $1; $$->tail = $$; }
                            | translation-unit external-decl    { $$ = $1; $$->tail->next = $2; $$->tail = $2; }
                            ;

external-decl               : function-definition   { $$ = $1; }
                            | decl                  { $$ = $1; }
                            ;

function-definition         : decl-specs declarator decl-list compound-stat // TODO: unknown
                            | decl-specs declarator           compound-stat  {
                                $$ = (FunctionDeclaration *)$2;
                                $$->rettype = $1;
                                $$->stmts = $3;
                            }
                            |            declarator decl-list compound-stat // TODO: unknown
                            |            declarator           compound-stat {
                                $$ = (FunctionDeclaration *)$1;
                                $$->rettype = new IntType(); // default return type is int
                                $$->stmts = $2;
                            }
                            ;

decl                        : decl-specs init-declarator-list DELIM {
                                vector<TypeSpecifier *> *ts = new vector<TypeSpecifier *>;

                                for(auto &p : *$2)
                                {
                                    Expression *size = p->right;

                                    // combine qualifier
                                    Qualifier *qual = new Qualifier();
                                    if(p->qual)
                                    {
                                        if(p->qual->isconst)
                                            qual->isconst = true;
                                        if(p->qual->isvolatile)
                                            qual->isvolatile = true;
                                        if(p->qual->pcnt)
                                            qual->pcnt = p->qual->pcnt;
                                    }
                                    if($1->qual)
                                    {
                                        if($1->qual->isconst)
                                            qual->isconst = true;
                                        if($1->qual->isvolatile)
                                            qual->isvolatile = true;
                                        if($1->qual->pcnt)
                                            qual->pcnt += $1->qual->pcnt;
                                    }

                                    // no array size defined and pointer qualifier
                                    if(!size && !qual->pcnt)
                                        ts->push_back($1);
                                    else
                                    {
                                        // basic type
                                        TypeSpecifier *t = $1;
                                        // pointer qualifier
                                        for(int i = 0; i < qual->pcnt; i++)
                                                t = new MyPointerType(t);
                                        // if array size defined
                                        while(size)
                                        {
                                            if(((Number *)size)->valtype != VAL_NONE)
                                                t = new MyArrayType(t, ((Number *)size)->longView());
                                            else
                                                t = new MyPointerType(t);
                                            Expression *tmp = size;
                                            size = size->right;
                                        }
                                        t->qual = qual;
                                        ts->push_back(t);
                                    }

                                    // constant simple value variable
                                    if(qual->isconst)
                                    {
                                        if(!ts->back()->isIterableType() && !ts->back()->isAggregateType() && p->init->getName() == "\"Number\"")
                                            constvar[p->name] = (Number *)(p->init);
                                    }
                                }

                                $$ = new VariableDeclaration(ts, $2);
                            }
                            | decl-specs DELIM {
                                // type definition
                                if($1->isAggregateType())
                                    $$ = new TypeDeclaration($1);
                                else
                                {
                                    yywarning("useless type name in empty declaration");
                                    $$ = new TypeDeclaration();
                                }
                            }
                            | TYPEDEF decl-specs IDENTIFIER DELIM {
                                // type alias
                                if(typealias.find(*$3) == typealias.end())
                                {
                                    if($2->getName() == "\"MyStructType\"")
                                        typealias[*$3] = new MyStructType((MyStructType *)$2);
                                    else if($2->getName() == "\"UnionType\"")
                                        typealias[*$3] = new UnionType((UnionType *)$2);
                                    else
                                        typealias[*$3] = $2;
                                }
                                else
                                    yyerror("redefinition of type alias '" + *$3 + "'");

                                if($2->isAggregateType())
                                    $$ = new TypeDeclaration($2);
                                else
                                    $$ = new TypeDeclaration();
                                
                                delete $3;
                            }
                            ;

decl-list                   : decl { $$ = $1; $$->tail = $$; }
                            | decl-list decl { $$ = $1; $$->tail->next = $2; $$->tail = $2; }
                            ;

decl-specs                  : storage-class-specifier {
                                $$ = new IntType();
                                $$->linkage = $1->linkage;
                                delete $1;
                            }
                            | storage-class-specifier decl-specs {
                                $$ = $2;
                                $$->linkage = $1->linkage;
                                delete $1;
                            }
                            | type-spec { $$ = $1; }
                            | type-spec decl-specs {
                                $$ = $2;
                                $$->isunsigned = $1->isunsigned;
                                delete $1;
                            }
                            | type-qualifier { $$ = new IntType($1); } // no type decl, default is "int"
                            | type-qualifier decl-specs { $$ = $2; $$->qual = $1; }
                            ;

init-declarator-list        : init-declarator { $$ = new vector<Identifier *>; $$->push_back($1); }
                            | init-declarator-list COMMA init-declarator { $1->push_back($3); $$ = $1; }
                            ;

init-declarator             : declarator { $$ = (Identifier *)$1; }
                            | declarator ASSIGN initializer { $$ = (Identifier *)$1; $$->init = $3; }
                            ;

storage-class-specifier     : EXTERN    { $$ = new TypeSpecifier(LINKAGE_EXTERNAL); }
                            | STATIC    { $$ = new TypeSpecifier(LINKAGE_INTERNAL); }
                            | AUTO      { $$ = new TypeSpecifier(LINKAGE_NONE); }
                            | REGISTER  { yyerror("register keywork not supported yet"); } // TODO: register
                            /* | TYPEDEF */
                            ;

type-spec                   : CHAR      { $$ = new CharType();      }
                            | SHORT     { $$ = new ShortType();     }
                            | INT       { $$ = new IntType();       }
                            | LONG      { $$ = new LongType();      }
                            | FLOAT     { $$ = new FloatType();     }
                            | DOUBLE    { $$ = new DoubleType();    }
                            | VOID      { $$ = new VoidType();      }
                            | SIGNED    { $$ = new TypeSpecifier(false); }
                            | UNSIGNED  { $$ = new TypeSpecifier(true); }
                            | struct-or-union-spec { $$ = $1; }
                            | enum-spec // TODO: enum type
                            | TYPENAME  {
                                if(typealias.find(*$1) != typealias.end())
                                    $$ = typealias[*$1];
                                else if(*$1 == "va_list")
                                {
                                    aggrdef["struct.__va_list_tag"] = new MyStructType();
                                    aggrdef["struct.__va_list_tag"]->name = "struct.__va_list_tag";
                                    typealias["struct.__va_list_tag"] = aggrdef["struct.__va_list_tag"];
                                    
                                    $$ = new MyStructType();
                                    ((MyStructType *)$$)->name = "struct.__va_list_tag";
                                    $$ = new MyArrayType($$, 1);
                                }
                                else
                                    yyerror("type name '" + *$1 + "' not found");
                                delete $1;
                            }
                            ;

type-qualifier              : CONST     { $$ = new Qualifier(); $$->isconst    = true; }
                            | VOLATILE  { $$ = new Qualifier(); $$->isvolatile = true; }
                            ;

struct-or-union-spec        : struct-or-union IDENTIFIER LC struct-decl-list RC {
                                if(aggrdef.find(*$2) != aggrdef.end())
                                { 
                                    if(!aggrdef[*$2]->members)
                                        aggrdef[*$2]->members = $4;
                                    // if the struct has been defined, fetch it directly
                                    $$ = aggrdef[*$2];
                                }
                                else
                                {
                                    $$ = $1;
                                    $$->name = *$2;
                                    $$->members = $4;
                                    // add struct definition into map
                                    aggrdef[*$2] = $$;
                                }
                                delete $2;
                            }
                            | struct-or-union LC struct-decl-list RC { $$ = $1; $$->name = randstr(); $$->members = $3; } // annoymous struct
                            | struct-or-union IDENTIFIER { $$ = $1; $$->name = *$2; delete $2; }
                            ;

struct-or-union             : STRUCT    { $$ = new MyStructType(); }
                            | UNION     { $$ = new UnionType(); }
                            ;

struct-decl-list            : struct-decl { $$ = new vector<pair<vector<TypeSpecifier *> *, vector<Identifier *> *> *>(); $$->push_back($1); }
                            | struct-decl-list struct-decl { $$ = $1; $$->push_back($2); }
                            ;

struct-decl                 : spec-qualifier-list struct-declarator-list DELIM {
                                vector<TypeSpecifier *> *ts = new vector<TypeSpecifier *>;

                                for(auto &p : *$2)
                                {
                                    Expression *size = p->right;

                                    // no array size defined and pointer qualifier
                                    if(!size && (p->qual && !p->qual->pcnt))
                                        ts->push_back($1);
                                    else
                                    {
                                        // basic type
                                        TypeSpecifier *t = $1;
                                        // pointer qualifier
                                        if(p->qual)
                                            for(int i = 0; i < p->qual->pcnt; i++)
                                                t = new MyPointerType(t);
                                        // if array size defined
                                        while(size)
                                        {
                                            if(((Number *)size)->valtype != VAL_NONE)
                                                t = new MyArrayType(t, ((Number *)size)->longView());
                                            else
                                                t = new MyPointerType(t);
                                            Expression *tmp = size;
                                            size = size->right;
                                            // delete tmp
                                        }
                                        ts->push_back(t);
                                    }
                                }

                                $$ = new pair<vector<TypeSpecifier *> *, vector<Identifier *> *>(ts, $2);
                            }
                            ;

spec-qualifier-list         : type-spec spec-qualifier-list { $$ = $1; $$->qual = $$->qual; delete $2; }
                            | type-spec { $$ = $1; }
                            | type-qualifier spec-qualifier-list // TODO: unknown
                            | type-qualifier // TODO: unknown
                            ;

struct-declarator-list      : struct-declarator { $$ = new vector<Identifier *>(); $$->push_back($1); }
                            | struct-declarator-list COMMA struct-declarator { $$ = $1; $$->push_back($3); }
                            ;

struct-declarator           : declarator {
                                if($1->getName() != "\"Identifier\"")
                                    yyerror("not supported struct-declarator yet");
                                $$ = (Identifier *)$1;
                            }
                            | declarator COLON const-exp // TODO: bit-fields
                            | COLON const-exp // TODO: bit-fields
                            ;
                    
enum-spec                   : ENUM IDENTIFIER LC enumerator-list RC
                            | ENUM LC enumerator-list RC
                            | ENUM IDENTIFIER
                            ;

enumerator-list             : enumerator
                            | enumerator-list COMMA enumerator
                            ;

enumerator                  : IDENTIFIER
                            | IDENTIFIER ASSIGN const-exp
                            ;

declarator                  : pointer direct-declarator { $$ = $2; ((Identifier *)$$)->qual = $1; }
                            | direct-declarator { $$ = $1; }
                            ;

direct-declarator           : IDENTIFIER { $$ = new Identifier(*$1); delete $1; }
                            | LP declarator RP // TODO: unknown
                            | direct-declarator LB const-exp       RB {
                                $$ = $1;
                                ((Expression *)$3)->right = ((Identifier *)$$)->right;
                                ((Identifier *)$$)->right = $3;
                            }
                            | direct-declarator LB                 RB { $$ = $1; ((Identifier *)$$)->right = new Number(); }
                            | direct-declarator LP id-list         RP // TODO: unknown
                            | direct-declarator LP param-type-list RP { $$ = new FunctionDeclaration(nullptr, (Identifier *)$1, $3, nullptr); }
                            | direct-declarator LP                 RP { $$ = new FunctionDeclaration(nullptr, (Identifier *)$1, nullptr, nullptr); }
                            ;

pointer			            : MULORDEREFERENCE type-qualifier-list { $$ = $2; $$->pcnt++; }
                            | MULORDEREFERENCE { $$ = new Qualifier(1); }
                            | MULORDEREFERENCE type-qualifier-list pointer {
                                $$ = $2;
                                $$->pcnt += $3->pcnt + 1;
                                delete $3;
                            }
                            | MULORDEREFERENCE pointer { $$ = $2; $$->pcnt++; }
                            ;

type-qualifier-list	        : type-qualifier { $$ = $1; }
                            | type-qualifier-list type-qualifier {
                                $$ = $1;
                                $$->isconst = $2->isconst;
                                $$->isvolatile = $2->isvolatile;
                                $$->pcnt += $2->pcnt;
                                delete $2;
                            }
                            ;

param-type-list             : param-list { $$ = $1; }
                            | param-list COMMA DOTDOTDOT { $$ = $1; $$->isvariableargs = true; }
                            ;

param-list                  : param-decl { $$ = $1; $$->tail = $$; }
                            | param-list COMMA param-decl { $$ = $1; $$->tail->next = $3; $$->tail = $3; }
                            ;

param-decl                  : decl-specs declarator {
                                Identifier *id = ((Identifier *)$2);
                                Expression *size = id->right;
                                if(!size && (id->qual && !id->qual->pcnt))
                                    $$ = new Parameter($1, id);
                                else
                                {
                                    TypeSpecifier *t = $1;
                                    if(id->qual)
                                        for(int i = 0; i < id->qual->pcnt; i++)
                                            t = new MyPointerType(t);
                                    while(size)
                                    {
                                        if(((Number *)size)->valtype != VAL_NONE)
                                            t = new MyArrayType(t, ((Number *)size)->longView());
                                        else
                                            t = new MyPointerType(t);
                                        Expression *tmp = size;
                                        size = size->right;
                                    }
                                    id->right = nullptr;
                                    $$ = new Parameter(t, id);
                                }
                            }
                            | decl-specs abstract-declarator // TODO: abstract decl
                            | decl-specs { $$ = new Parameter($1); }
                            ;

id-list			            : IDENTIFIER { $$ = new vector<Identifier *>; $$->push_back(new Identifier(*$1)); delete $1; }
                            | id-list COMMA IDENTIFIER { $1->push_back(new Identifier(*$3)); $$ = $1; delete $3;  }
                            ;

initializer                 : assignment-exp               { $$ = $1; }
                            | LC initializer-list RC       { $$ = $2; }
                            | LC initializer-list COMMA RC { $$ = $2; }
                            ;

initializer-list            : initializer { $$ = $1; }
                            | initializer-list COMMA initializer { 
                                Expression *p = $1;
                                while(p->left)
                                    p = p->left;
                                p->left = $3;
                                $$ = $1;
                            }
                            ;

type-name                   : spec-qualifier-list abstract-declarator {
                                $$ = $1;
                                if($2->getName() == "\"Qualifier\"")
                                    for(int i = 0; i < ((Qualifier *)$2)->pcnt; i++)
                                        $$ = new MyPointerType($$);
                                else
                                    yyerror("abstract-declarator of type '" + $2->getName() + "' is not supported yet");
                            }
                            | spec-qualifier-list { $$ = $1; }
                            ;

abstract-declarator         : pointer { $$ = $1; }
                            | pointer direct-abstract-declarator
                            |         direct-abstract-declarator
                            ;

direct-abstract-declarator  : LP abstract-declarator RP
                            | direct-abstract-declarator LB const-exp RB
                            |                            LB const-exp RB
                            | direct-abstract-declarator LB           RB
                            |                            LB           RB
                            | direct-abstract-declarator LP param-type-list RP
                            |                            LP param-type-list RP
                            | direct-abstract-declarator LP                 RP
                            |                            LP                 RP
                            ;

stat                        : labeled-stat   { $$ = $1; }
                            | exp-stat       { $$ = $1; }
                            | compound-stat  { $$ = $1; }
                            | selection-stat { $$ = $1; }
                            | iteration-stat { $$ = $1; }
                            | jump-stat      { $$ = $1; }
                            ;

labeled-stat		        : IDENTIFIER COLON stat { $$ = new LabelStatement(*$1); delete $1; }
                            /* | CASE const-exp COLON stat { $$ = new CaseStatement($2, $4); } */
                            /* | DEFAULT COLON stat { $$ = new CaseStatement(nullptr, $3); } */
                            | CASE const-exp COLON { $$ = new CaseStatement($2); }
                            | DEFAULT COLON { $$ = new CaseStatement(nullptr); }
                            ;

exp-stat            		: exp DELIM { $$ = new ExpressionStatement($1); }
                            |     DELIM { $$ = new ExpressionStatement(); }
                            ;

compound-stat               : LC decl-list stat-list RC { $$ = new CompoundStatement($2, $3); }
                            | LC           stat-list RC { $$ = new CompoundStatement(nullptr, $2); }
                            | LC decl-list           RC { $$ = new CompoundStatement($2, nullptr); }
                            | LC                     RC { $$ = new CompoundStatement(nullptr, nullptr); }
                            ;

stat-list                   : stat { $$ = $1; $$->tail = $$; }
                            | stat-list stat { $$ = $1; $$->tail->next = $2; $$->tail = $2; }
                            ;

selection-stat		        : IF LP exp RP stat             { $5->next = nullptr; $$ = new IfElseStatement($3, $5); }
                            | IF LP exp RP stat ELSE stat   { $5->next = $7; $$ = new IfElseStatement($3, $5); }
                            | SWITCH LP exp RP stat         {
                                if($5->getName() != "\"CompoundStatement\"")
                                    yyerror("case label not within a switch statement");
                                $$ = new SwitchCaseStatement($3, $5);
                            }
                            ;

iteration-stat      		: WHILE LP exp RP stat                   { $$ = new WhileStatement($3, $5); }
                            | DO stat WHILE LP exp RP DELIM          { $$ = new DoWhileStatement($5, $2); }
                            | FOR LP exp DELIM exp DELIM exp RP stat { $$ = new ForStatement($3, $5, $7, $9); }
                            | FOR LP exp DELIM exp DELIM     RP stat { $$ = new ForStatement($3, $5, nullptr, $8); }
                            | FOR LP exp DELIM     DELIM exp RP stat { $$ = new ForStatement($3, nullptr, $6, $8); }
                            | FOR LP     DELIM exp DELIM exp RP stat { $$ = new ForStatement(nullptr, $4, $6, $8); }
                            | FOR LP exp DELIM     DELIM     RP stat { $$ = new ForStatement($3, nullptr, nullptr, $7); }
                            | FOR LP     DELIM exp DELIM     RP stat { $$ = new ForStatement(nullptr, $4, nullptr, $7); }
                            | FOR LP     DELIM     DELIM exp RP stat { $$ = new ForStatement(nullptr, nullptr, $5, $7); }
                            | FOR LP     DELIM     DELIM     RP stat { $$ = new ForStatement(nullptr, nullptr, nullptr, $6); }
                            ;

jump-stat                   : GOTO IDENTIFIER DELIM { $$ = new GotoStatement(*$2); delete $2; }
                            | CONTINUE DELIM        { $$ = new ContinueStatement(); }
                            | BREAK DELIM           { $$ = new BreakStatement(); }
                            | RETURN exp DELIM      { $$ = new ReturnStatement($2); }
                            | RETURN DELIM          { $$ = new ReturnStatement(); }
                            ;

exp			                : assignment-exp { $$ = $1; }
                            | exp COMMA assignment-exp { $$ = calculate($1, $3, OP_COMMA); }
                            ;

assignment-exp      		: conditional-exp { $$ = $1; }
                            | unary-exp assignment-operator assignment-exp {
                                if( $1->getName() != "\"Identifier\"" && \
                                    $1->op != OP_DEREFERENCE && \
                                    $1->op != OP_INDEX && \
                                    $1->op != OP_DOT && \
                                    $1->op != OP_TO)
                                    yyerror("lvalue required as left operand of assignment");
                                $$ = new Expression($1, $3, $2);
                            }
                            ;

assignment-operator	        : ASSIGN    { $$ = OP_ASSIGN; }
                            | MULASSIGN { $$ = OP_MULASSIGN; }
                            | DIVASSIGN { $$ = OP_DIVASSIGN; }
                            | MODASSIGN { $$ = OP_MODASSIGN; }
                            | ADDASSIGN { $$ = OP_ADDASSIGN; }
                            | SUBASSIGN { $$ = OP_SUBASSIGN; }
                            | SLASSIGN  { $$ = OP_SLASSIGN; }
                            | SRASSIGN  { $$ = OP_SRASSIGN; }
                            | ANDASSIGN { $$ = OP_ANDASSIGN; }
                            | XORASSIGN { $$ = OP_XORASSIGN; }
                            | ORASSIGN  { $$ = OP_ORASSIGN; }
                            | NOTASSIGN { $$ = OP_NOTASSIGN; }
                            ;

conditional-exp             : logical-or-exp { $$ = $1; }
                            | logical-or-exp QUESTION exp COLON conditional-exp { $$ = calculate($3, $5, $1, OP_IFELSE); }
                            ;

const-exp           		: conditional-exp {
                                if($1->getName() == "\"Number\"")
                                    $$ = (Number *)$1;
                                else if($1->getName() == "\"Identifier\"" && constvar[((Identifier *)$1)->name])
                                    $$ = constvar[((Identifier *)$1)->name];
                                else
                                    yyerror("const-exp is not a Number constant");
                            }
                            ;

logical-or-exp		        : logical-and-exp { $$ = $1; }
                            | logical-or-exp OROR logical-and-exp { $$ = calculate($1, $3, OP_OROR); }
                            ;

logical-and-exp		        : inclusive-or-exp { $$ = $1; }
                            | logical-and-exp ANDAND inclusive-or-exp { $$ = calculate($1, $3, OP_ANDAND); }
                            ;

inclusive-or-exp	        : exclusive-or-exp { $$ = $1; }
                            | inclusive-or-exp OR exclusive-or-exp { $$ = calculate($1, $3, OP_OR); }
                            ;

exclusive-or-exp	        : and-exp { $$ = $1; }
                            | exclusive-or-exp XOR and-exp { $$ = calculate($1, $3, OP_XOR); }
                            ;

and-exp			            : equality-exp { $$ = $1; }
                            | and-exp ANDORADDRESSOF equality-exp { $$ = calculate($1, $3, OP_AND); }
                            ;

equality-exp		        : relational-exp { $$ = $1;}
                            | equality-exp EQ relational-exp { $$ = calculate($1, $3, OP_EQ); }
                            | equality-exp NEQ relational-exp { $$ = calculate($1, $3, OP_NEQ); }
                            ;

relational-exp		        : shift-expression { $$ = $1; }
                            | relational-exp LT shift-expression { $$ = calculate($1, $3, OP_LT); }
                            | relational-exp GT shift-expression { $$ = calculate($1, $3, OP_GT); }
                            | relational-exp LEQ shift-expression { $$ = calculate($1, $3, OP_LEQ); }
                            | relational-exp GEQ shift-expression { $$ = calculate($1, $3, OP_GEQ); }
                            ;
                            
shift-expression	        : additive-exp { $$ = $1; }
                            | shift-expression SL additive-exp { $$ = calculate($1, $3, OP_SL); }
                            | shift-expression SR additive-exp { $$ = calculate($1, $3, OP_SR); }
                            ;

additive-exp		        : mult-exp { $$ = $1; }
                            | additive-exp ADDORPOSITIVE mult-exp { $$ = calculate($1, $3, OP_ADD); }
                            | additive-exp SUBORNEGATIVE mult-exp { $$ = calculate($1, $3, OP_SUB); }
                            ;

mult-exp		            : cast-exp { $$ = $1; }
                            | mult-exp MULORDEREFERENCE cast-exp { $$ = calculate($1, $3, OP_MUL); }
                            | mult-exp DIV cast-exp { $$ = calculate($1, $3, OP_DIV); }
                            | mult-exp MOD cast-exp { $$ = calculate($1, $3, OP_MOD); }
                            ;

cast-exp		            : unary-exp { $$ = $1; }
                            | LP type-name RP cast-exp {
                                // coercion type casting
                                $$ = new Expression(new Expression($2), $4, OP_CAST);
                            }
                            ;

unary-exp		            : postfix-exp { $$ = $1; }
                            | INC unary-exp {
                                if( $2->getName() != "\"Identifier\"" && \
                                    $2->op != OP_DEREFERENCE && \
                                    $2->op != OP_INDEX && \
                                    $2->op != OP_DOT && \
                                    $2->op != OP_TO)
                                    yyerror("lvalue required as increment operand");
                                $$ = new Expression($2, OP_INC_FRONT);
                            }
                            | DEC unary-exp {
                                if( $2->getName() != "\"Identifier\"" && \
                                    $2->op != OP_DEREFERENCE && \
                                    $2->op != OP_INDEX && \
                                    $2->op != OP_DOT && \
                                    $2->op != OP_TO)
                                    yyerror("lvalue required as decrement operand");
                                $$ = new Expression($2, OP_DEC_FRONT);
                            }
                            | unary-operator cast-exp { $$ = calculate($2, $1); }
                            | SIZEOF unary-exp {
                                // TODO: size of a expr { yylval.num.longValue = $2->type->getSize(); $$ = new Number(yylval.num, new LongType(), VAL_LONG); }
                                yyerror("sizeof an expression is not supported yet");
                            }
                            | SIZEOF LP type-name RP {
                                if($3->isAggregateType())
                                    yylval.num.longValue = aggrdef[((AggregateType *)$3)->name]->getSize();
                                else
                                    yylval.num.longValue = $3->getSize();
                                $$ = new Number(yylval.num, new LongType(), VAL_LONG);
                            }
                            ;

unary-operator              : ANDORADDRESSOF    { $$ = OP_ADDRESSOF; }
                            | MULORDEREFERENCE  { $$ = OP_DEREFERENCE; }
                            | ADDORPOSITIVE     { $$ = OP_POSITIVE; }
                            | SUBORNEGATIVE     { $$ = OP_NEGATIVE; }
                            | NOT               { $$ = OP_NOT; }
                            | NOTNOT            { $$ = OP_NOTNOT; }
                            ;

postfix-exp		            : primary-exp { $$ = $1; }
                            | postfix-exp LB exp RB {
                                if($1->getName() == "\"Number\"")
                                    yyerror("number is not subscriptable");
                                $$ = new Expression($1, $3, OP_INDEX);
                            }
                            | postfix-exp LP argument-exp-list RP {
                                if($1->getName() == "\"Number\"")
                                    yyerror("number is not callable");
                                $$ = new FunctionCall($1, $3);
                            }
                            | postfix-exp LP RP {
                                if($1->getName() == "\"Number\"")
                                    yyerror("number is not callable");
                                $$ = new FunctionCall($1, nullptr);
                            }
                            | postfix-exp DOT IDENTIFIER { $$ = new Expression($1, new Identifier(*$3), OP_DOT); delete $3; }
                            | postfix-exp TO IDENTIFIER { $$ = new Expression($1, new Identifier(*$3), OP_TO); delete $3; }
                            | postfix-exp INC {
                                if( $1->getName() != "\"Identifier\"" && \
                                    $1->op != OP_DEREFERENCE && \
                                    $1->op != OP_INDEX && \
                                    $1->op != OP_DOT && \
                                    $1->op != OP_TO)
                                    yyerror("lvalue required as increment operand");
                                $$ = new Expression($1, OP_INC_REAR);
                            }
                            | postfix-exp DEC {
                                if( $1->getName() != "\"Identifier\"" && \
                                    $1->op != OP_DEREFERENCE && \
                                    $1->op != OP_INDEX && \
                                    $1->op != OP_DOT && \
                                    $1->op != OP_TO)
                                    yyerror("lvalue required as decrement operand");
                                $$ = new Expression($1, OP_DEC_REAR);
                            }
                            ;

primary-exp		            : IDENTIFIER    { $$ = new Identifier(*$1); delete $1; }
                            /* | CONSTANT */
                            | const         { $$ = $1; }
                            /* | STRING        { $$ = new String(*$1); delete $1; } */
                            | string-list   { $$ = $1; }
                            | LP exp RP     { $$ = $2; }
                            ;

argument-exp-list	        : assignment-exp { $$ = new vector<Expression *>; $$->push_back($1); }
                            | argument-exp-list COMMA assignment-exp { $1->push_back($3); $$ = $1; }
                            ;

const                       : number { $$ = $1; }
                            ;

number                      : NUMCHAR   { $$ = new Number($1, new CharType(),   VAL_CHAR); }
                            | NUMSHORT  { $$ = new Number($1, new ShortType(),  VAL_SHORT); }
                            | NUMINT    { $$ = new Number($1, new IntType(),    VAL_INT); }
                            | NUMLONG   { $$ = new Number($1, new LongType(),   VAL_LONG); }
                            | NUMFLOAT  { $$ = new Number($1, new FloatType(),  VAL_FLOAT); }
                            | NUMDOUBLE { $$ = new Number($1, new DoubleType(), VAL_DOUBLE); }
                            ;

string-list                 : STRING             { $$ = new String(*$1); delete $1; }
                            | string-list STRING {
                                $$ = $1;
                                $$->val = $$->val + *$2;
                                delete $2;
                            }
                            ;

%%

void yyerror(string s)
{
    cerr << "\033[1;31m" << "error: " << "\033[0m" << s << endl;
    cerr << "Line " << yylineno << ": " << "\033[1;31m" << yytext << "\033[0m" << endl;
    exit(1);
}

void yywarning(string s)
{
    cerr << "\033[1;35m" << "warning: " << "\033[0m" << s << endl;
}

static void debug(string s) {
    cout << s << ": " << yytext << endl;
}

// constant folding
static Expression *calculate(Expression *a, enum op_type op)
{
    if(a->getName() == "\"Number\"" || (a->getName() == "\"Identifier\"" && constvar.find(((Identifier *)a)->name) != constvar.end() && (a = constvar[((Identifier *)a)->name])))
    {
        union union_num num;
        bool isfloatpoint = \
            (((Number *)a)->valtype == VAL_FLOAT) || \
            (((Number *)a)->valtype == VAL_DOUBLE);

        switch(op)
        {
        case OP_ADDRESSOF:
            yyerror("lvalue required as unary '&' operand");
        case OP_DEREFERENCE:
            yyerror("invalid type argument of unary '*' operand");
        case OP_POSITIVE:
            if(isfloatpoint)
                num.doubleValue = +((Number *)a)->doubleView();
            else
                num.longValue = +((Number *)a)->longView();
            break;
        case OP_NEGATIVE:
            if(isfloatpoint)
                num.doubleValue = -((Number *)a)->doubleView();
            else
                num.longValue = -((Number *)a)->longView();
            break;
        case OP_NOT:
            if(isfloatpoint)
                yyerror("bitwise not is not supported for double type");
            else
                num.longValue = ~((Number *)a)->longView();
            break;
        case OP_NOTNOT:
            if(isfloatpoint)
                num.doubleValue = !((Number *)a)->doubleView();
            else
                num.longValue = !((Number *)a)->longView();
            break;
        default:
            yyerror("not supported unary operator");
        }
        
        if(isfloatpoint)
            return new Number(num, new DoubleType(), VAL_DOUBLE);
        else
            return new Number(num, new LongType(), VAL_LONG);
    }
    
    return new Expression(a, op);
}

static Expression *calculate(Expression *a, Expression *b, enum op_type op)
{
    if(
        (a->getName() == "\"Number\"" || (a->getName() == "\"Identifier\"" && constvar.find(((Identifier *)a)->name) != constvar.end() && (a = constvar[((Identifier *)a)->name]))) && \
        (b->getName() == "\"Number\"" || (b->getName() == "\"Identifier\"" && constvar.find(((Identifier *)b)->name) != constvar.end() && (b = constvar[((Identifier *)b)->name])))
    )
    {
        union union_num num;
        bool isfloatpoint = \
            (((Number *)a)->valtype == VAL_FLOAT) || \
            (((Number *)b)->valtype == VAL_FLOAT) || \
            (((Number *)a)->valtype == VAL_DOUBLE) || \
            (((Number *)b)->valtype == VAL_DOUBLE);
        if (isfloatpoint)
        {
            double_t v1 = ((Number *)a)->doubleView(), v2 = ((Number *)b)->doubleView();
            switch(op)
            {
            case OP_ADD:
                num.doubleValue = v1 + v2;
                return new Number(num, new DoubleType(), VAL_DOUBLE);
            case OP_SUB:
                num.doubleValue = v1 - v2;
                return new Number(num, new DoubleType(), VAL_DOUBLE);
            case OP_MUL:
                num.doubleValue = v1 * v2;
                return new Number(num, new DoubleType(), VAL_DOUBLE);
            case OP_DIV:
                num.doubleValue = v1 / v2;
                return new Number(num, new DoubleType(), VAL_DOUBLE);
            case OP_COMMA:
                num.doubleValue = v2;
                return new Number(num, new DoubleType(), VAL_DOUBLE);
            case OP_EQ:
                num.longValue = v1 == v2;
                break;
            case OP_NEQ:
                num.longValue = v1 != v2;
                break;
            case OP_LT:
                num.longValue = v1 < v2;
                break;
            case OP_GT:
                num.longValue = v1 > v2;
                break;
            case OP_LEQ:
                num.longValue = v1 <= v2;
                break;
            case OP_GEQ:
                num.longValue = v1 >= v2;
                break;
            case OP_OROR:
                num.longValue = v1 || v2;
                break;
            case OP_ANDAND:
                num.longValue = v1 && v2;
                break;
            default:
                yyerror("not supported binary operator for double type");
            }
            return new Number(num, new LongType(), VAL_LONG);
        }
        else
        {
            uint64_t v1 = ((Number *)a)->longView(), v2 = ((Number *)b)->longView();
            switch(op)
            {
            case OP_ADD:
                num.longValue = v1 + v2;
                break;
            case OP_SUB:
                num.longValue = v1 - v2;
                break;
            case OP_MUL:
                num.longValue = v1 * v2;
                break;
            case OP_DIV:
                num.longValue = v1 / v2;
                break;
            case OP_MOD:
                num.longValue = v1 % v2;
                break;
            case OP_COMMA:
                num.longValue = v2;
                break;
            case OP_SL:
                num.longValue = v1 >> v2;
                break;
            case OP_SR:
                num.longValue = v1 << v2;
                break;
            case OP_AND:
                num.longValue = v1 & v2;
                break;
            case OP_OR:
                num.longValue = v1 | v2;
                break;
            case OP_XOR:
                num.longValue = v1 ^ v2;
                break;
            case OP_EQ:
                num.longValue = v1 == v2;
                break;
            case OP_NEQ:
                num.longValue = v1 != v2;
                break;
            case OP_LT:
                num.longValue = v1 < v2;
                break;
            case OP_GT:
                num.longValue = v1 > v2;
                break;
            case OP_LEQ:
                num.longValue = v1 <= v2;
                break;
            case OP_GEQ:
                num.longValue = v1 >= v2;
                break;
            case OP_OROR:
                num.longValue = v1 || v2;
                break;
            case OP_ANDAND:
                num.longValue = v1 && v2;
                break;
            default:
                yyerror("not supported binary operator for long type");
            }

            return new Number(num, new LongType(), VAL_LONG);
        }
    
    }
    return new Expression(a, b, op);
}

static Expression *calculate(Expression *a, Expression *b, Expression *c, enum op_type op)
{
    if(
        (a->getName() == "\"Number\"" || (a->getName() == "\"Identifier\"" && constvar.find(((Identifier *)a)->name) != constvar.end() && (a = constvar[((Identifier *)a)->name]))) && \
        (b->getName() == "\"Number\"" || (b->getName() == "\"Identifier\"" && constvar.find(((Identifier *)b)->name) != constvar.end() && (b = constvar[((Identifier *)b)->name]))) && \
        (c->getName() == "\"Number\"" || (c->getName() == "\"Identifier\"" && constvar.find(((Identifier *)c)->name) != constvar.end() && (c = constvar[((Identifier *)c)->name])))
    )
    {
        union union_num num;
        bool isfloatpoint = \
            (((Number *)b)->valtype == VAL_FLOAT) || \
            (((Number *)c)->valtype == VAL_FLOAT) || \
            (((Number *)b)->valtype == VAL_DOUBLE) || \
            (((Number *)c)->valtype == VAL_DOUBLE);
        bool choice;
        switch(op)
        {
        case OP_IFELSE:
            switch(((Number *)a)->valtype)
            {
            case VAL_CHAR:
            case VAL_SHORT:
            case VAL_INT:
            case VAL_LONG:
                choice = ((Number *)a)->longView() != 0;
                break;
            case VAL_FLOAT:
            case VAL_DOUBLE:
                choice = ((Number *)a)->doubleView() != 0;
                break;
            default:
                yyerror("not supported value type for condition");
            }
            break;
        default:
            yyerror("not supported trinary operator");
        }

        if(isfloatpoint)
        {
            if(choice)
                num.doubleValue = ((Number *)b)->doubleView();
            else
                num.doubleValue = ((Number *)c)->doubleView();
            return new Number(num, new DoubleType(), VAL_DOUBLE);
        }
        else
        {
            if(choice)
                num.longValue = ((Number *)b)->longView();
            else
                num.longValue = ((Number *)c)->longView();
            return new Number(num, new LongType(), VAL_LONG);
        }
    }
    
    return new Expression(a, b, c, op);
}

static string randstr()
{
    static FILE *fp = fopen("/dev/urandom", "rb");
    static string table = "0123456789abcdef";
    uint8_t buf[16] = {0};
    fread(buf, 1, 16, fp);
    string res = "";
    for(int i = 0; i < 16; i++)
    {
        res += table[buf[i] >> 4];
        res += table[buf[i] & 0xf];
    }
    return res;
}