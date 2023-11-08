#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	vector<char> lexems;
	static map<char, int> priority;
	map<char, double> operands;
	void Parse();
	void ToPostfix();
public:
	TPostfix(string infx);
	string GetInfix() const;
	string GetPostfix() const;
	map<char, double> getOperands();
	double Calculate( map<char, double> values);
};

#endif
