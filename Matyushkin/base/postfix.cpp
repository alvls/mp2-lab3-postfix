#include "postfix.h"
#include "stack.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <cstdlib>

using namespace std;

namespace {

    int Priority(char op)
    {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^')              return 3;
        return 0;
    }

    bool IsOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    vector<string> Tokenize(const string& s)
    {
        vector<string> res;
        size_t i = 0;
        while (i < s.size())
        {
            char c = s[i];
            if (isspace((unsigned char)c)) { ++i; continue; }

            if (isdigit((unsigned char)c) || c == '.')
            {
                size_t j = i;
                while (j < s.size() && (isdigit((unsigned char)s[j]) || s[j] == '.')) ++j;
                res.push_back(s.substr(i, j - i));
                i = j;
            }
            else if (isalpha((unsigned char)c))
            {
                size_t j = i;
                while (j < s.size() && isalpha((unsigned char)s[j])) ++j;
                res.push_back(s.substr(i, j - i));
                i = j;
            }
            else if (IsOperator(c) || c == '(' || c == ')')
            {
                res.push_back(string(1, c));
                ++i;
            }
            else
            {
                throw runtime_error(string("Bad char: ") + c);
            }
        }
        return res;
    }

}

string TPostfix::ToPostfix()
{
    vector<string> tokens = Tokenize(infix);
    postfix.clear();

    TStack<string> st(MaxStackSize);

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        const string& tok = tokens[i];

        if (tok == "(")
        {
            st.Push(tok);
        }
        else if (tok == ")")
        {
            while (!st.IsEmpty() && st.Top() != "(")
            {
                postfix += st.Pop();
                postfix += ' ';
            }
            if (st.IsEmpty())
                throw runtime_error("Mismatched )");
            st.Pop();
        }
        else if (tok.size() == 1 && IsOperator(tok[0]))
        {
            char op = tok[0];
            while (!st.IsEmpty() && st.Top() != "(" &&
                   ( Priority(st.Top()[0]) > Priority(op) ||
                     (Priority(st.Top()[0]) == Priority(op) && op != '^') ))
            {
                postfix += st.Pop();
                postfix += ' ';
            }
            st.Push(tok);
        }
        else
        {
            postfix += tok;
            postfix += ' ';
        }
    }

    while (!st.IsEmpty())
    {
        if (st.Top() == "(")
            throw runtime_error("Mismatched (");
        postfix += st.Pop();
        postfix += ' ';
    }

    if (!postfix.empty() && postfix.back() == ' ')
        postfix.pop_back();

    return postfix;
}

double TPostfix::Calculate()
{
    vector<string> tokens = Tokenize(postfix);

    map<string, double> vars;
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        const string& tok = tokens[i];
        if (!tok.empty() && isalpha((unsigned char)tok[0]) &&
            vars.find(tok) == vars.end())
        {
            double v = 0;
            cout << "Enter " << tok << ": ";
            if (!(cin >> v))
                throw runtime_error("Bad variable value");
            vars[tok] = v;
        }
    }

    TStack<double> st(MaxStackSize);

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        const string& tok = tokens[i];

        if (tok.size() == 1 && IsOperator(tok[0]))
        {
            if (st.IsEmpty()) throw runtime_error("Not enough operands");
            double b = st.Pop();
            if (st.IsEmpty()) throw runtime_error("Not enough operands");
            double a = st.Pop();

            double r = 0.0;
            switch (tok[0])
            {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/':
                    if (b == 0.0) throw runtime_error("Division by zero");
                    r = a / b;
                    break;
                case '^': r = pow(a, b); break;
            }
            st.Push(r);
        }
        else if (!tok.empty() && isalpha((unsigned char)tok[0]))
        {
            st.Push(vars[tok]);
        }
        else
        {
            st.Push(atof(tok.c_str()));
        }
    }

    if (st.IsEmpty()) throw runtime_error("Empty postfix");
    double result = st.Pop();
    if (!st.IsEmpty()) throw runtime_error("Extra operands");
    return result;
}