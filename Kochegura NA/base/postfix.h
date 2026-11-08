#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
    string infix;
    string postfix;

    int GetPriority(char op)
    {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0; 
    }
public:
    TPostfix(string expr = "")
    {
        infix = expr;
        postfix = "";
    }

    string GetInfix() { return infix; }
    string GetPostfix() { return postfix; }

    string ToPostfix();
    double Calculate(); 
};

#endif
