#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <map>
using namespace std;

class TPostfix
{
    string infix;
    string postfix;
    std::map<char, double> vars;
public:
    TPostfix(){
        infix = "a+b";
    }
    TPostfix(const string& expr): infix(expr){}
    void SetInfix(const string& expr) { 
        infix = expr;
    }
    void SetVariable(char name, double value) { vars[name] = value; }
    string GetInfix() { return infix; }
    string GetPostfix() { return postfix; }
    string ToPostfix();
    double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};
int GetPriority(string op);
#endif
