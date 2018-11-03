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
	void ToPostfix();
	double Calculate();// Ввод переменных, вычисление по постфиксной форме
	int Priority(char a);
	bool Operand(char op);
	int NumOperator(char op);
	bool CheckAmount(); // Проверка соответствия кол-ва переменных кол-ву операций
	bool CheckBrackets(); // Проверка количества скобок
	bool CheckChars();
	bool CheckInfix(); // Общая проверка

	bool IsOperation(char elem);
};

#endif