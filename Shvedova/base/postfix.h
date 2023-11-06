#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	vector<char> lexems;
	map<char, int> priority;
	map<char, double> operands;
	void Parse();
	void ToPostfix();
public:
	TPostfix(string infx);
	vector<char> GetOperands() const;
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	double Calculate(const map<char, double>& val); // Ввод переменных, вычисление по постфиксной форме
};
#endif
