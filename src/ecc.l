%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.hpp"

void debug() { printf("%s ", yytext); }
%}

%option noyywrap

%%

[ \t\n]                         {}
"//".*\n                        {}
"/*"([^*]|"*"+[^/*])*"*"+"/"    {}
\\$                             {}
";"                             { debug(); return DELIM; }

"auto"                          { debug(); return AUTO; }
"double"                        { debug(); return DOUBLE; }
"int"                           { debug(); return INT; }
"struct"                        { debug(); return STRUCT; }
"break"                         { debug(); return BREAK; }
"else"                          { debug(); return ELSE; }    
"long"                          { debug(); return LONG; }
"switch"                        { debug(); return SWITCH; }
"case"                          { debug(); return CASE; }
"enum"                          { debug(); return ENUM; }
"register"                      { debug(); return REGISTER; }
"typedef"                       { debug(); return TYPEDEF; }
"char"                          { debug(); return CHAR; }
"extern"                        { debug(); return EXTERN; }
"return"                        { debug(); return RETURN; }
"union"                         { debug(); return UNION; }
"const"                         { debug(); return CONST; }
"float"                         { debug(); return FLOAT; }
"short"                         { debug(); return SHORT; }
"unsigned"                      { debug(); return UNSIGNED; }
"continue"                      { debug(); return CONTINUE; }
"for"                           { debug(); return FOR; }
"signed"                        { debug(); return SIGNED; }
"void"                          { debug(); return VOID; }
"default"                       { debug(); return DEFAULT; }
"goto"                          { debug(); return GOTO; }
"sizeof"                        { debug(); return SIZEOF; }
"volatile"                      { debug(); return VOLATILE; }
"do"                            { debug(); return DO; }
"if"                            { debug(); return IF; }
"static"                        { debug(); return STATIC; }
"while"                         { debug(); return WHILE; }

"+"                             { debug(); return ADD; }
"-"                             { debug(); return SUB; }
"*"                             { debug(); return MUL; }
"/"                             { debug(); return DIV; }
"&"                             { debug(); return AND; }
"|"                             { debug(); return OR; }
"^"                             { debug(); return XOR; }
"&&"                            { debug(); return ANDAND; }
"||"                            { debug(); return OROR; }
"+="                            { debug(); return ADDASSIGN; }
"-="                            { debug(); return SUBASSIGN; }
"*="                            { debug(); return MULASSIGN; }
"/="                            { debug(); return DIVASSIGN; }
"&="                            { debug(); return ANDASSIGN; }
"|="                            { debug(); return ORASSIGN; }
"^="                            { debug(); return XORASSIGN; }
"="                             { debug(); return ASSIGN; }
"<"                             { debug(); return LT; }
">"                             { debug(); return GT; }
"!="                            { debug(); return NOTEQ; }
"=="                            { debug(); return EQ; }
"<<"                            { debug(); return SL; }
">>"                            { debug(); return SR; }
"<<="                           { debug(); return SLASSIGN; }
">>="                           { debug(); return SRASSIGN; }

-?(0|([1-9][0-9]*))             { debug(); return NUMBER; }
-?0[0-7]*                       { debug(); return NUMBER; }
-?0[xX][0-9a-fA-F]+             { debug(); return NUMBER; }
-?(0|([1-9][0-9]*))(\.[0-9]+)?  { debug(); return NUMBER; }
[A-Za-z_][A-Za-z0-9_]*          { debug(); return IDENTIFIER; }
\'.\'                           { debug(); return NUMBER; }
\".*\"                          {}
                            
"#if"                           {}
"#else"                         {}
"#endif"                        {}
"#define"                       {}

.                               {}

%%