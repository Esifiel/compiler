%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "ast/type.hpp"
#include "parser.hpp"

extern bool inyyparse;
extern map<string, pair<vector<string>, string>> macrodef;
extern map<string, TypeSpecifier *> typealias;
extern ofstream ofs;
extern bool isedited;
static bool norecursive = false;

extern void yyerror(string s);

// print out token scanned
uint64_t cnt = 0;
static inline void debug() {
    printf("token %lu:\t%s\n", cnt, yytext);
    cnt++;
}

// replace escape char
static void replace(string &src, string sub, string tar)
{
    string::size_type pos = 0;
    int curpos = 0;
    while((pos = src.find(sub, curpos)) != string::npos)
    {
        src.replace(pos, sub.length(), tar);
        curpos = pos + tar.length();
    }
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
%}

%option noyywrap
%option yylineno

%%

":"                             { if(inyyparse) debug(); return COLON; }
";"                             { if(inyyparse) debug(); return DELIM; }
"?"                             { if(inyyparse) debug(); return QUESTION; }
","                             { if(inyyparse) debug(); return COMMA; }
"."                             { if(inyyparse) debug(); return DOT; }
"->"                            { if(inyyparse) debug(); return TO; }
"..."                           { if(inyyparse) debug(); return DOTDOTDOT; }
"!"                             { if(inyyparse) debug(); return NOTNOT; }

"auto"                          { if(inyyparse) debug(); return AUTO; }
"double"                        { if(inyyparse) debug(); return DOUBLE; }
"int"                           { if(inyyparse) debug(); return INT; }
"struct"                        { if(inyyparse) debug(); return STRUCT; }
"break"                         { if(inyyparse) debug(); return BREAK; }
"else"                          { if(inyyparse) debug(); return ELSE; }    
"long"                          { if(inyyparse) debug(); return LONG; }
"switch"                        { if(inyyparse) debug(); return SWITCH; }
"case"                          { if(inyyparse) debug(); return CASE; }
"enum"                          { if(inyyparse) debug(); return ENUM; }
"register"                      { if(inyyparse) debug(); return REGISTER; }
"typedef"                       { if(inyyparse) debug(); return TYPEDEF; }
"char"                          { if(inyyparse) debug(); return CHAR; }
"extern"                        { if(inyyparse) debug(); return EXTERN; }
"return"                        { if(inyyparse) debug(); return RETURN; }
"union"                         { if(inyyparse) debug(); return UNION; }
"const"                         { if(inyyparse) debug(); return CONST; }
"float"                         { if(inyyparse) debug(); return FLOAT; }
"short"                         { if(inyyparse) debug(); return SHORT; }
"unsigned"                      { if(inyyparse) debug(); return UNSIGNED; }
"continue"                      { if(inyyparse) debug(); return CONTINUE; }
"for"                           { if(inyyparse) debug(); return FOR; }
"signed"                        { if(inyyparse) debug(); return SIGNED; }
"void"                          { if(inyyparse) debug(); return VOID; }
"default"                       { if(inyyparse) debug(); return DEFAULT; }
"goto"                          { if(inyyparse) debug(); return GOTO; }
"sizeof"                        { if(inyyparse) debug(); return SIZEOF; }
"volatile"                      { if(inyyparse) debug(); return VOLATILE; }
"do"                            { if(inyyparse) debug(); return DO; }
"if"                            { if(inyyparse) debug(); return IF; }
"static"                        { if(inyyparse) debug(); return STATIC; }
"while"                         { if(inyyparse) debug(); return WHILE; }

"+"                             { if(inyyparse) debug(); return ADDORPOSITIVE; }
"-"                             { if(inyyparse) debug(); return SUBORNEGATIVE; }
"*"                             { if(inyyparse) debug(); return MULORDEREFERENCE; }
"/"                             { if(inyyparse) debug(); return DIV; }
"%"                             { if(inyyparse) debug(); return MOD; }
"&"                             { if(inyyparse) debug(); return ANDORADDRESSOF; }
"|"                             { if(inyyparse) debug(); return OR; }
"~"                             { if(inyyparse) debug(); return NOT; }
"^"                             { if(inyyparse) debug(); return XOR; }
"&&"                            { if(inyyparse) debug(); return ANDAND; }
"||"                            { if(inyyparse) debug(); return OROR; }
"+="                            { if(inyyparse) debug(); return ADDASSIGN; }
"-="                            { if(inyyparse) debug(); return SUBASSIGN; }
"*="                            { if(inyyparse) debug(); return MULASSIGN; }
"/="                            { if(inyyparse) debug(); return DIVASSIGN; }
"%="                            { if(inyyparse) debug(); return MODASSIGN; }
"&="                            { if(inyyparse) debug(); return ANDASSIGN; }
"|="                            { if(inyyparse) debug(); return ORASSIGN; }
"^="                            { if(inyyparse) debug(); return XORASSIGN; }
"~="                            { if(inyyparse) debug(); return NOTASSIGN; }
"="                             { if(inyyparse) debug(); return ASSIGN; }
"<"                             { if(inyyparse) debug(); return LT; }
">"                             { if(inyyparse) debug(); return GT; }
"<="                            { if(inyyparse) debug(); return LEQ; }
">="                            { if(inyyparse) debug(); return GEQ; }
"!="                            { if(inyyparse) debug(); return NEQ; }
"=="                            { if(inyyparse) debug(); return EQ; }
"<<"                            { if(inyyparse) debug(); return SL; }
">>"                            { if(inyyparse) debug(); return SR; }
"<<="                           { if(inyyparse) debug(); return SLASSIGN; }
">>="                           { if(inyyparse) debug(); return SRASSIGN; }
"++"                            { if(inyyparse) debug(); return INC; }
"--"                            { if(inyyparse) debug(); return DEC; }

"("                             { if(inyyparse) debug(); return LP; }
")"                             { if(inyyparse) debug(); return RP; }
"["                             { if(inyyparse) debug(); return LB; }
"]"                             { if(inyyparse) debug(); return RB; }
"{"                             { if(inyyparse) debug(); return LC; }
"}"                             { if(inyyparse) debug(); return RC; }

0|([1-9][0-9]*)                 {
                                    if(inyyparse)
                                    {
                                        debug();
                                        yylval.num.longValue = atoll(yytext);
                                        if((yylval.num.longValue >> 32) == 0)
                                        {
                                            yylval.num.intValue = yylval.num.longValue;
                                            return NUMINT;
                                        }
                                    }
                                    return NUMLONG;
                                }
0[0-7]*                         {
                                    if(inyyparse)
                                    {
                                        debug();
                                        yylval.num.longValue = strtol(yytext, NULL, 8);
                                        if((yylval.num.longValue >> 32) == 0)
                                        {
                                            yylval.num.intValue = yylval.num.longValue;
                                            return NUMINT;
                                        }
                                    }
                                    return NUMLONG;
                                }
0[xX][0-9a-fA-F]+               {
                                    if(inyyparse)
                                    {
                                        debug();
                                        yylval.num.longValue = strtol(yytext, NULL, 16);
                                        if((yylval.num.longValue >> 32) == 0)
                                        {
                                            yylval.num.intValue = yylval.num.longValue;
                                            return NUMINT;
                                        }
                                    }
                                    return NUMLONG;
                                }
(0|([1-9][0-9]*))(\.[0-9]+)?    {
                                    if(inyyparse)
                                    {
                                        debug();
                                        yylval.num.doubleValue = atof(yytext);
                                    }
                                    return NUMDOUBLE;
                                }
[A-Za-z_][A-Za-z0-9_]*          {
                                    if(inyyparse)
                                    {
                                        debug();
                                        yylval.stringValue = new string(yytext);
                                        if(*yylval.stringValue == "va_list" || typealias.find(*yylval.stringValue) != typealias.end())
                                            return TYPENAME;
                                    }
                                    else
                                    {
                                        if(macrodef.find(yytext) != macrodef.end() && !norecursive)
                                        {
                                            norecursive = true;
                                            isedited = true;

                                            if(macrodef[yytext].first.size() == 0)
                                            {
                                                string def = macrodef[yytext].second;
                                                yytext = (char *)malloc(def.length() + 1);
                                                strcpy(yytext, def.c_str());
                                            }
                                            else
                                            {
                                                string curmacro = yytext;
                                                if(!(yylex() && !strcmp(yytext, "(")))
                                                    yyerror("expected '('");

                                                if(yylex() && strcmp(yytext, ")"))
                                                {
                                                    int cnt = 1;
                                                    for(int argindex = 0; ; argindex++)
                                                    {
                                                        ofs << endl << "#define " + macrodef[curmacro].first[argindex] + " ";
                                                        while(1)
                                                        {
                                                            if(yytext[0] == '(')
                                                                cnt++;
                                                            if(yytext[0] == ')')
                                                                cnt--;
                                                            if(!strcmp(yytext, ",") && (cnt == 1))
                                                                break;
                                                            if(!strcmp(yytext, ")") && (cnt == 0))
                                                                break;
                                                            ofs << yytext;
                                                            yylex();
                                                        }
                                                        if(!strcmp(yytext, ")"))
                                                            break;
                                                        yylex();
                                                    }
                                                }
                                                ofs << endl << macrodef[curmacro].second << endl;
                                                // for(auto &p : macrodef[curmacro].first)
                                                //     ofs << "#undef " + p << endl;
                                                yylex();
                                            }

                                            norecursive = false;
                                        }
                                    }
                                    return IDENTIFIER;
                                }
\'.\'                           {
                                    if(inyyparse)
                                    {
                                        // normal single char
                                        debug();
                                        yylval.num.charValue = yytext[1];
                                    }
                                    return NUMCHAR;
                                }
\'\\[abfnrtv\'\"\\]\'           {
                                    if(inyyparse)
                                    {
                                        // escape char
                                        debug();
                                        switch(yytext[2])
                                        {
                                        case 'a':
                                            yylval.num.charValue = '\a';
                                            break;
                                        case 'b':
                                            yylval.num.charValue = '\b';
                                            break;
                                        case 'f':
                                            yylval.num.charValue = '\f';
                                            break;
                                        case 'n':
                                            yylval.num.charValue = '\n';
                                            break;
                                        case 'r':
                                            yylval.num.charValue = '\r';
                                            break;
                                        case 't':
                                            yylval.num.charValue = '\t';
                                            break;
                                        case 'v':
                                            yylval.num.charValue = '\v';
                                            break;
                                        case '\'':
                                            yylval.num.charValue = '\'';
                                            break;
                                        case '\"':
                                            yylval.num.charValue = '\"';
                                            break;
                                        case '\\':
                                            yylval.num.charValue = '\\';
                                            break;
                                        default:
                                            yylval.num.charValue = '\0';
                                            break;
                                        }
                                    }
                                    return NUMCHAR;
                                }
\'\\0[0-7]{1,3}\'               {
                                    if(inyyparse)
                                    {
                                        // octal char
                                        debug();
                                        yytext[strlen(yytext) - 1] = '\0';
                                        yylval.num.charValue = strtol(yytext + 2, NULL, 8);
                                    }
                                    return NUMCHAR;
                                }
\'\\x[0-9a-fA-F]{1,2}\'         {
                                    if(inyyparse)
                                    {
                                        // hexidecimal char
                                        debug();
                                        yytext[strlen(yytext) - 1] = '\0';
                                        yylval.num.charValue = strtol(yytext + 3, NULL, 16);
                                    }
                                    return NUMCHAR;
                                }
\"((\\.)|[^"\\])*\"             {
                                    if(inyyparse)
                                    {
                                        // string const
                                        debug();
                                        // strip "
                                        yylval.stringValue = new string(string(yytext).substr(1, strlen(yytext) - 2));
                                        // multiple strings will be combined
                                        replace(*yylval.stringValue, "\"\"", "");
                                        // translate escape char
                                        replace(*yylval.stringValue, "\\a", "\a");
                                        replace(*yylval.stringValue, "\\b", "\b");
                                        replace(*yylval.stringValue, "\\f", "\f");
                                        replace(*yylval.stringValue, "\\n", "\n");
                                        replace(*yylval.stringValue, "\\r", "\r");
                                        replace(*yylval.stringValue, "\\t", "\t");
                                        replace(*yylval.stringValue, "\\v", "\v");
                                        replace(*yylval.stringValue, "\\\"", "\"");
                                        replace(*yylval.stringValue, "\\'", "'");
                                        replace(*yylval.stringValue, "\\\\", "\\");
                                    }
                                    return STRING;
                                }

"#include"                      { if(!inyyparse) return 1; }
"<".*">"                        { if(!inyyparse) return 1; }
"#define"                       { if(!inyyparse) return 1; }
"#ifdef"                        { if(!inyyparse) return 1; }
"#ifndef"                       { if(!inyyparse) return 1; }
"#else"                         { if(!inyyparse) return 1; }
"#endif"                        { if(!inyyparse) return 1; }
"#undef"                        { if(!inyyparse) return 1; }
"#pragma"                       { if(!inyyparse) return 1; }
"##"                            { if(!inyyparse) return 1; }
"#"                             { if(!inyyparse) return 1; }               

[ \t\n]                         { if(!inyyparse) return 1; }
"//".*                          { if(!inyyparse) return 1; }
"/*"([^*]|"*"+[^/*])*"*"+"/"    { if(!inyyparse) return 1; }
\\$                             { if(!inyyparse) return 1; }

.                               { if(!inyyparse) return 1; }

<<EOF>>                         { yyterminate(); }

%%