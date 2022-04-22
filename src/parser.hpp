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
void yywarning(string s, string addition = "");

#line 69 "parser.hpp"

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
    SL = 301,
    SR = 302,
    ANDASSIGN = 303,
    ORASSIGN = 304,
    XORASSIGN = 305,
    SLASSIGN = 306,
    SRASSIGN = 307,
    ANDAND = 308,
    OROR = 309,
    NOTNOT = 310,
    LT = 311,
    GT = 312,
    GEQ = 313,
    LEQ = 314,
    NEQ = 315,
    EQ = 316,
    ASSIGN = 317,
    INC = 318,
    DEC = 319,
    TYPEDEF = 320,
    SIZEOF = 321,
    RETURN = 322,
    DOTDOTDOT = 323,
    DELIM = 324,
    COMMA = 325,
    COLON = 326,
    QUESTION = 327,
    DOT = 328,
    TO = 329,
    LP = 330,
    RP = 331,
    LB = 332,
    RB = 333,
    LC = 334,
    RC = 335,
    NUMCHAR = 336,
    NUMSHORT = 337,
    NUMINT = 338,
    NUMLONG = 339,
    NUMFLOAT = 340,
    NUMDOUBLE = 341,
    STRING = 342,
    IDENTIFIER = 343
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "ecc.y"

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

#line 198 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
