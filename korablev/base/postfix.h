﻿#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <cmath>
#include "stack.h"

using namespace std;

class TPostfix {
	string infix;
	string postfix;
	vector<char> lexems;
	map<char, double> operands;
	static map<char, int> priority;
	void ParseInfix();
	void ToPostfix();
public:
	TPostfix(string infx);
	string GetInfix() const;
	string GetPostfix() const;
	vector<char> GetOperands() const;
	double Calculate(const map<char, double>& values);
};

#endif