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
#line 6 "ecc.y"

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

#line 65 "parser.hpp"

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
    ADDASSIGN = 291,
    SUBASSIGN = 292,
    MULASSIGN = 293,
    DIVASSIGN = 294,
    AND = 295,
    OR = 296,
    XOR = 297,
    ANDASSIGN = 298,
    ORASSIGN = 299,
    XORASSIGN = 300,
    ANDAND = 301,
    OROR = 302,
    SL = 303,
    SR = 304,
    SLASSIGN = 305,
    SRASSIGN = 306,
    ASSIGN = 307,
    LT = 308,
    GT = 309,
    NOTEQ = 310,
    EQ = 311,
    TYPEDEF = 312,
    SIZEOF = 313,
    RETURN = 314,
    DELIM = 315,
    NUMBER = 316,
    IDENTIFIER = 317
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "ecc.y"

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

#line 165 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
