#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <map>
#include <vector>

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	static map<char, int> priority;
	vector <char> lexems;
	map<char, double> operands;
	void ToPostfix();
	void Parse();
public:
	TPostfix(string infix);
	string GetInfix();
	string GetPostfix();
	vector <char> GetOperands();
	double Calculate(const map<char, double>& values); // Ввод переменных, вычисление по постфиксной форме
};
#endif
