#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <vector>
#include <map>

using namespace std;

class TPostfix
{
private:
	string infix;
	vector<string> postfix;
	vector<string> lexems;
	static map<char, int> priority;
	map<string, double> operands;

	void Parse();
	void ToPostfix();

public:
	TPostfix(string infx);

	string GetInfix() const;
	vector<string> GetPostfix() const;

	vector<string> GetOperands() const;
	double Calculate(const map<string, double>& values);
};

#endif
