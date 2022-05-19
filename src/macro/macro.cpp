#include "macro.hpp"
#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <fstream>

using namespace std;

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

// tuple (name, args, definition)
vector<tuple<string, vector<string>, string>> macrodef;

void macro_expansion(string src)
{
    ifstream ifs(src, ios::in);
    static ofstream ofs("./tmp.i", ios::out);
    if (!ifs.is_open())
        err("open " + src + " failed");
    if (!ofs.is_open())
        err("open output tmp file failed");

    string buf, tmp, path = src;
    if (path.find('/') != string::npos)
        path = path.substr(0, path.find_last_of('/') + 1);
    else
        path = "./";
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
                    cout << path + buf.substr(q + 1, buf.length() - 2 - q) << endl;
                    macro_expansion(path + buf.substr(q + 1, buf.length() - 1 - (q + 1)));
                }
                else
                    err("missing <> or \"\" around filename: " + buf.substr(q, buf.length() - 1 - q));
            }
            else if (tmp == "#define")
            {
                // skip blank
                while (q < buf.length() && isspace(buf[q]))
                    p = ++q;

                if(buf[q] != '_' && !isalpha(buf[q]))
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
                    err("not enough definition: " + buf.substr(p, buf.length() - 1 - p));

                if (!hasparameter)
                {
                    // constant macro
                    string name = buf.substr(p, q - p);

                    while (q < buf.length() && isspace(buf[q]))
                        q++;
                    string definition = buf.substr(q, buf.length() - q);

                    macrodef.push_back(
                        tuple<string, vector<string>, string>(
                            name,
                            vector<string>(),
                            definition));
                    // replacement will be done in yylex()
                    
                    // check
                    for(auto &p : macrodef)
                        cout << "macro: " << get<0>(p) << " " << get<2>(p) << endl;
                }
                else
                {
                    // macro with parameter
                }
            }
            else if (tmp == "#ifdef")
            {
            }
            else if (tmp == "#ifndef")
            {
            }
            else if (tmp == "#else")
            {
            }
            else if (tmp == "#endif")
            {
            }
            else if (tmp == "#pragma")
            {
            }
        }
        else
            ofs << buf << endl;
    }
}