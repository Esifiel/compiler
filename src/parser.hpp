/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 8 "ecc.y"

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

#line 68 "parser.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR = 258,
    SHORT = 259,
    INT = 260,
    LONG = 261,
    FLOAT = 262,
    DOUBLE = 263,
    STRUCT = 264,
    ENUM = 265,
    UNION = 266,
    VOID = 267,
    AUTO = 268,
    REGISTER = 269,
    EXTERN = 270,
    CONST = 271,
    UNSIGNED = 272,
    SIGNED = 273,
    VOLATILE = 274,
    STATIC = 275,
    IF = 276,
    ELSE = 277,
    FOR = 278,
    DO = 279,
    WHILE = 280,
    BREAK = 281,
    CONTINUE = 282,
    SWITCH = 283,
    CASE = 284,
    DEFAULT = 285,
    GOTO = 286,
    ADD = 287,
    SUB = 288,
    MUL = 289,
    DIV = 290,
    MOD = 291,
    ADDASSIGN = 292,
    SUBASSIGN = 293,
    MULASSIGN = 294,
    DIVASSIGN = 295,
    MODASSIGN = 296,
    AND = 297,
    OR = 298,
    XOR = 299,
    NOT = 300,
    ANDASSIGN = 301,
    ORASSIGN = 302,
    XORASSIGN = 303,
    SL = 304,
    SR = 305,
    SLASSIGN = 306,
    SRASSIGN = 307,
    ANDAND = 308,
    OROR = 309,
    ASSIGN = 310,
    LT = 311,
    GT = 312,
    GEQ = 313,
    LEQ = 314,
    NEQ = 315,
    EQ = 316,
    TYPEDEF = 317,
    SIZEOF = 318,
    RETURN = 319,
    DELIM = 320,
    COMMA = 321,
    LP = 322,
    RP = 323,
    LB = 324,
    RB = 325,
    LC = 326,
    RC = 327,
    NUMCHAR = 328,
    NUMSHORT = 329,
    NUMINT = 330,
    NUMLONG = 331,
    NUMFLOAT = 332,
    NUMDOUBLE = 333,
    STRING = 334,
    IDENTIFIER = 335
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "ecc.y"

    union union_num num;
    string *stringValue;
    enum op_type op;
    
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
    Number *number;

    vector<Declaration *> *decls;
    vector<VariableDeclaration *> *vars;
    vector<FunctionDeclaration *> *funcs;
    vector<Statement *> *stmts;
    vector<Parameter *> *params;
    vector<Expression *> *exprs;

#line 198 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
