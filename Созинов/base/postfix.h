#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#pragma once

#include <string>
#include "stack.h"

using namespace std;

const string Alphabet_string = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string Alphabet_number = "1234567890.";
const string Alphabet_operator = "+-*/";

class TPostfix
{
	string infix;
	string postfix;
public:
	TPostfix(string s = "");

	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	bool CheckOnSymbol(char s);
	bool CheckOnNumber(char s);
	bool CheckOnOperator(char s);
	bool BalanceParentheses();
	void DelSpace();
	string CheckOnCorrect();
	string ToPostfix();
	double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};


#endif
