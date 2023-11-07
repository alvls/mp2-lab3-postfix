#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "stack.h"
#include "Operations.h"

using namespace std;

class TPostfix
{
	vector<string> infix;
	string infix_str;
	vector<string> postfix;
	string postfix_str;
	map<string, double> operands;
	map<string, double> constants;
public:
	TPostfix(string str);
	string GetInfix() { return infix_str; }
	string GetPostfix() { return postfix_str; }
private:
	void ToInfix();
	void CheckOfExpression();
	void ToPostfix();

public:
	double Calculate(vector<double> values_or_operands = {}); // Ввод переменных, вычисление по постфиксной форме
};

#endif