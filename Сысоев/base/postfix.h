#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	string Operation = "+,-,*,/,%";
	// string Operation = {"+", "-", "*", "/", "sin", "cos", "ex"};
public:
	TPostfix(string i = " ") { infix = i; }
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	string ToPostfix();
	double Calculate();// Ввод переменных, вычисление по постфиксной форме
	int Priority(char a);
	bool Operat(char a);
	bool IsOperand(char op);
};

#endif
