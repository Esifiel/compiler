#include "macro.hpp"
#include <iostream>
#include <stdlib.h>
#include <ctype.h>
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

// split macro line with blank characters
static vector<string> parse_macro(const string &s)
{
    vector<string> tokens;

    size_t begin = 0, end = s.length() - 1;
    while (begin < end && isspace(s[begin]))
        begin++;
    while (end > begin && isspace(s[end]))
        end--;
    size_t p = begin;
    while (p < end)
    {
        while (p <= end && !isspace(s[p]))
            p++;
        tokens.push_back(s.substr(begin, p - begin));
        begin = p + 1;
        p = begin + 1;
    }

    return tokens;
}

// the same with 'startwith' in python
static bool startswith(const string &s, const string &head)
{
    size_t begin = 0, end = s.length() - 1;
    while (begin < end && isspace(s[begin]))
        begin++;
    if (s.substr(begin, head.length()) == head)
        return true;
    else
        return false;
}

// map { name: (args, definition) }
map<string, pair<vector<string>, string>> macrodef;

void macro_expansion(string src)
{
    ifstream ifs(src, ios::in);
    static ofstream ofs("./tmp.i", ios::out);
    if (!ifs.is_open())
        err("open " + src + " failed");
    if (!ofs.is_open())
        err("open output tmp file failed");

    string buf, tmp;
    bool ifdefined = true;
    while (getline(ifs, buf))
    {
        // continue reading if '\' in the end of line
        while (buf[buf.length() - 1] == '\\')
        {
            getline(ifs, tmp);
            buf = buf.substr(0, buf.length() - 2) + tmp;
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
                    macro_expansion(string(path).substr(0, string(path).find_last_of("/") + 1) + buf.substr(q + 1, buf.length() - 1 - (q + 1)));
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

                if (!hasparameter)
                {
                    // constant macro
                    string name = buf.substr(p, q - p);

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
                }
            }
            else if (tmp == "#ifdef" || tmp == "#ifndef")
            {
                // skip blank
                while (q < buf.length() && isspace(buf[q]))
                    p = ++q;

                if (buf[q] != '_' && !isalpha(buf[q]))
                    err("macro names must be identifiers: " + buf);

                while (q < buf.length() && (buf[q] == '_' || isalpha(buf[q]) || isdigit(buf[q])))
                    q++;

                string name = buf.substr(p, q - p);
                if ((tmp == "#ifdef") ^ (macrodef.find(name) != macrodef.end()))
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