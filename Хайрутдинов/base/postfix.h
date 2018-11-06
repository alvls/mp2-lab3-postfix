#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	int count = 0;
	int Compare(char _t1);
	bool CorrectRecord();
	bool IsOperations(char s);
	bool IsOperand(char s);
public:
	TPostfix()
	{
		infix = "a * b";
	}
	TPostfix(string str)
	{
		infix = str;
	}
	void SetInfix(string _infix, int _count);
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	void ToPostfix();
	double Calculate(int _count, double *_arg); // Ввод переменных, вычисление по постфиксной форме

};

#endif
