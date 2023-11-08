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
	vector<string> postfix;
	static map<char, int> priority;
	vector <string> lexems;
	map<string, double> operands;
	void ToPostfix();
	void Parse();
public:
	TPostfix(string infix);
	string GetInfix();
	vector<string> GetPostfix();
	vector <string> GetOperands();
	double Calculate(const map<string, double>& values); // Ввод переменных, вычисление по постфиксной форме
};
#endif
