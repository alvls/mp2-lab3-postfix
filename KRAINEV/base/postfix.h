#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
    string infix; //инфиксная запись
    string postfix; //постфиксная запись
public:
    TPostfix(string Value) { infix = Value; }
    TPostfix() { infix = "a + b"; }
    int Priority(char val);
    size_t checkStringIsANumber(string inString);
    char getEndOfString(); // return '\0'
    string GetInfix() { return infix; }
    string GetPostfix() { return postfix; }
    string ToPostfix();
    double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
