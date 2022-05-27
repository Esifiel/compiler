#include "macro.hpp"
#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

#define MAXLEN 4096

static void err(string s)
{
    cerr << "\033[1;31m"
         << "error: "
         << "\033[0m" << s << endl;
    exit(1);
}

// map { name: (args, definition) }
map<string, pair<vector<string>, string>> macrodef;
extern int yylex();
extern char *yytext;
extern FILE *yyin;
void macro_expansion(string src, ofstream &ofs)
{
    ifstream ifs(src, ios::in);
    if (!ifs.is_open())
        err("open " + src + " failed");

    string buf, tmp;
    bool ifdefined = true;
    while (getline(ifs, buf))
    {
        // continue reading if '\' in the end of line
        while (buf[buf.length() - 1] == '\\')
        {
            getline(ifs, tmp);
            buf = buf.substr(0, buf.length() - 2) + "\n" + tmp;
        }

        int p = 0, q = 0;

        // skip blank
        while (q < buf.length() && isspace(buf[q]))
            p = ++q;

        // if macro start symbol
        if (buf[p] == '#')
        {
            // skip blank
            while (q < buf.length() && !isspace(buf[q]))
                q++;
            // parse macro instruction
            tmp = buf.substr(p, q - p);

            if (tmp == "#endif")
            {
                ifdefined = true;
                continue;
            }
            else if (tmp == "#else")
            {
                ifdefined = !ifdefined;
                continue;
            }

            // if #ifdef is false, ignore the line
            if (!ifdefined)
                continue;

            if (tmp == "#include")
            {
                // skip blank
                while (q < buf.length() && isspace(buf[q]))
                    q++;

                // check the remaining content
                if (buf[q] == '<' && buf[buf.length() - 1] == '>')
                {
                    // TODO: system header files
                }
                else if (buf[q] == '"' && buf[buf.length() - 1] == '"')
                {
                    // recursively expansion
                    char path[MAXLEN] = {0};
                    realpath(src.c_str(), path);
                    macro_expansion(string(path).substr(0, string(path).find_last_of("/") + 1) + buf.substr(q + 1, buf.length() - 1 - (q + 1)), ofs);
                }
                else
                    err("missing <> or \"\" around filename: " + buf.substr(q, buf.length() - 1 - q));
            }
            else if (tmp == "#define")
            {
                // skip blank
                while (q < buf.length() && isspace(buf[q]))
                    p = ++q;

                if (buf[q] != '_' && !isalpha(buf[q]))
                    err("macro names must be identifiers: " + buf);

                bool hasparameter = false;
                while (q < buf.length())
                {
                    if (buf[q] == '(')
                    {
                        hasparameter = true;
                        break;
                    }
                    else if (isspace(buf[q]))
                        break;
                    q++;
                }

                if (q >= buf.length())
                {
                    // no definition macro
                    macrodef[buf.substr(p, buf.length() - p)] = pair<vector<string>, string>();
                    continue;
                }

                string name = buf.substr(p, q - p);

                if (!hasparameter)
                {
                    // constant macro
                    while (q < buf.length() && isspace(buf[q]))
                        q++;
                    string definition = buf.substr(q, buf.length() - q);

                    // cover directly (in gcc's behavior)
                    macrodef[name] = pair<vector<string>, string>(vector<string>(), definition);
                    // replacement will be done in yylex()
                }
                else
                {
                    // macro with parameter
                    vector<string> args;
                    p = ++q;
                    while (q < buf.length())
                    {
                        q++;
                        if (buf[q] == ',' || buf[q] == ')')
                        {
                            // record args
                            args.push_back(buf.substr(p, q - p));
                            if (buf[q] == ')')
                                break;
                            p = ++q;
                            while (q < buf.length() && isspace(buf[q]))
                                p = ++q;
                        }
                    }
                    if (q >= buf.length())
                        err("expected ',' or ')': " + buf);

                    while (q < buf.length() && isspace(buf[++q]))
                        ;
                    string definition = buf.substr(q, buf.length() - q);
                    macrodef[name] = pair<vector<string>, string>(args, definition);
                }
            }
            else if (tmp == "#ifdef" || tmp == "#ifndef" || tmp == "#undef")
            {
                // skip blank
                while (q < buf.length() && isspace(buf[q]))
                    p = ++q;

                if (buf[q] != '_' && !isalpha(buf[q]))
                    err("macro names must be identifiers: " + buf);

                while (q < buf.length() && (buf[q] == '_' || isalpha(buf[q]) || isdigit(buf[q])))
                    q++;

                string name = buf.substr(p, q - p);

                if (tmp == "#undef")
                    macrodef.erase(name);
                else if ((tmp == "#ifdef") ^ (macrodef.find(name) != macrodef.end()))
                    ifdefined = false;
            }
            else if (tmp == "#pragma")
            {
            }
            else if (tmp == "#")
            {
            }
            else if (tmp == "##")
            {
            }
        }
        else
        {
            if (ifdefined)
                ofs << buf << endl;
        }
    }
}