%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%option noyywrap

%%

"//".*\n                        {}
"/*"([^*]|"*"+[^/*])*"*"+"/"    {}
"auto"                          { return AUTO; }
"double"                        { return DOUBLE; }
"int"                           { return INT; }
"struct"                        { return STRUCT; }
"break"                         { return BREAK; }
"else"                          { return ELSE; }    
"long"                          { return LONG; }
"switch"                        { return SWITCH; }
"case"                          { return CASE; }
"enum"                          { return ENUM; }
"register"                      { return REGISTER; }
"typedef"                       { return TYPEDEF; }
"char"                          { return CHAR; }
"extern"                        { return EXTERN; }
"return"                        { return RETURN; }
"union"                         { return UNION; }
"const"                         { return CONST; }
"float"                         { return FLOAT; }
"short"                         { return SHORT; }
"unsigned"                      { return UNSIGNED; }
"continue"                      { return CONTINUE; }
"for"                           { return FOR; }
"signed"                        { return SIGNED; }
"void"                          { return VOID; }
"default"                       { return DEFAULT; }
"goto"                          { return GOTO; }
"sizeof"                        { return SIZEOF; }
"volatile"                      { return VOLATILE; }
"do"                            { return DO; }
"if"                            { return IF; }
"static"                        { return STATIC; }
"while"                         { return WHILE; }
"+"                             { return ADD; }
"-"                             { return SUB; }
"*"                             { return MUL; }
"/"                             { return DIV; }
"&"                             { return AND; }
"|"                             { return OR; }
"^"                             { return XOR; }
"&&"                            { return ANDAND; }
"||"                            { return OROR; }
"+="                            { return ADDASSIGN; }
"-="                            { return SUBASSIGN; }
"*="                            { return MULASSIGN; }
"/="                            { return DIVASSIGN; }
"&="                            { return ANDASSIGN; }
"|="                            { return ORASSIGN; }
"^="                            { return XORASSIGN; }
"="                             { return ASSIGN; }
"<"                             { return LT; }
">"                             { return GT; }
"!="                            { return NOTEQ; }
"=="                            { return EQ; }
"<<"                            { return SL; }
">>"                            { return SR; }
"<<="                           { return SLASSIGN; }
">>="                           { return SRASSIGN; }
-?(0|([1-9][0-9]*))             {
                                    yylval.type = INTEGER;
                                    yylval.val.intval = atoll(yytext);
                                    return NUMBER;
                                }
-?0[0-7]*                       {

                                }
-?0[xX][0-9a-fA-F]+             {

                                }
-?(0|([1-9][0-9]*))(\.[0-9]+)?  {
                                    yylval.type = FLOAT;
                                    yylval.val.floatval = atof(yytext);
                                    return NUMBER;
                                }
[A-Za-z_][A-Za-z0-9_]*          { return IDENTIFIER; }
\\$                             {}
[ \t\n]                         {}
"#if"                           {}
"#else"                         {}
"#endif"                        {}
"#define"                       {}
.                               {}

%%