%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "parser.hpp"

// print out token scanned
uint64_t cnt = 0;
void debug() {
    printf("token %lu:\t%s\n", cnt, yytext);
    cnt++;
}

// replace escape char
void replace(string &src, string sub, string tar)
{
    string::size_type pos = 0;
    while((pos = src.find(sub)) != string::npos)
        src.replace(pos, sub.length(), tar);
}
%}

%option noyywrap
%option yylineno

%%

[ \t\n]                         {}
"//".*\n                        {}
"/*"([^*]|"*"+[^/*])*"*"+"/"    {}
\\$                             {}
";"                             { debug(); return DELIM; }
","                             { debug(); return COMMA; }

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
"%"                             { debug(); return MOD; }
"&"                             { debug(); return AND; }
"|"                             { debug(); return OR; }
"~"                             { debug(); return NOT; }
"^"                             { debug(); return XOR; }
"&&"                            { debug(); return ANDAND; }
"||"                            { debug(); return OROR; }
"+="                            { debug(); return ADDASSIGN; }
"-="                            { debug(); return SUBASSIGN; }
"*="                            { debug(); return MULASSIGN; }
"/="                            { debug(); return DIVASSIGN; }
"%="                            { debug(); return MODASSIGN; }
"&="                            { debug(); return ANDASSIGN; }
"|="                            { debug(); return ORASSIGN; }
"^="                            { debug(); return XORASSIGN; }
"="                             { debug(); return ASSIGN; }
"<"                             { debug(); return LT; }
">"                             { debug(); return GT; }
"<="                            { debug(); return LEQ; }
">="                            { debug(); return GEQ; }
"!="                            { debug(); return NEQ; }
"=="                            { debug(); return EQ; }
"<<"                            { debug(); return SL; }
">>"                            { debug(); return SR; }
"<<="                           { debug(); return SLASSIGN; }
">>="                           { debug(); return SRASSIGN; }

"("                             { debug(); return LP; }
")"                             { debug(); return RP; }
"["                             { debug(); return LB; }
"]"                             { debug(); return RB; }
"{"                             { debug(); return LC; }
"}"                             { debug(); return RC; }

-?(0|([1-9][0-9]*))             {
                                    debug();
                                    yylval.num.longValue = atoll(yytext);
                                    return NUMLONG;
                                }
-?0[0-7]*                       {
                                    debug();
                                    yylval.num.longValue = strtol(yytext, NULL, 8);
                                    return NUMLONG;
                                }
-?0[xX][0-9a-fA-F]+             {
                                    debug();
                                    yylval.num.longValue = strtol(yytext, NULL, 16);
                                    return NUMLONG;
                                }
-?(0|([1-9][0-9]*))(\.[0-9]+)?  {
                                    debug();
                                    yylval.num.doubleValue = atof(yytext);
                                    return NUMDOUBLE;
                                }
[A-Za-z_][A-Za-z0-9_]*          {
                                    debug();
                                    yylval.stringValue = new string(yytext);
                                    return IDENTIFIER;
                                }
\'.\'                           {
                                    debug();
                                    yylval.num.charValue = *yytext;
                                    return NUMCHAR;
                                }
\".*\"                          {
                                    debug();
                                    yytext[strlen(yytext) - 1] = 0;
                                    yylval.stringValue = new string(yytext + 1);
                                    replace(*yylval.stringValue, string("\\n"), string("\n"));
                                    return STRING;
                                }
                            
"#if"                           {}
"#else"                         {}
"#endif"                        {}
"#define"                       {}

.                               {}

%%