#ifndef POSTFIX_H
#define POSTFIX_H
#include <string>
#include <map>
#include "stack.h"
using namespace std;
class TPostfix
{
    string infix;
    string postfix;
    std::map<char, double> vars;
public:
    TPostfix() { infix = "a+b"; }
    TPostfix(const string& expr) : infix(expr) {}
    void SetInfix(const string& expr) {
        infix = expr;
        postfix = "";
    }

    void SetVariable(char name, double value) { vars[name] = value; }

    string GetInfix() { return infix; }
    string GetPostfix() { return postfix; }

    string ToPostfix();
    double Calculate();
};
int GetPriority(char op);
#endif