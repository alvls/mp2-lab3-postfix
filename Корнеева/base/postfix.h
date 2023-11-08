#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <vector>
#include <map>
#include <stdexcept>

using namespace std;

class TPostfix
{
private:
	string infix;                   // Инфиксное выражение
	string postfix;                 // Постфиксное выражение
	static map<char, int> priority; // Приоритет операторов
	map<char, double> values;       // Значения переменных

	void ToPostfix();                               // Преобразует инфиксное выражение в постфиксное
	bool BracketsCorrect(const string& str) const;  // Проверяет корректность расстановки скобок в строке
	bool isOperator(char ch);                       // Проверяет, является ли символ оператором
	bool isOperand(char ch);                        // Проверяет, является ли символ операндом

public:
	TPostfix(string infx);                                  // Конструктор (принимает инфиксное выражение)

	string GetInfix() const;                                // Получить инфиксное выражение
	string GetPostfix() const;                              // Получить постфиксное выражение

	void SetVariable(char variable, double value);          // Установить значение переменной
	void SetVariables(const map<char, double>& values);     // Установить значения нескольких переменных одновременно
	double Calculate();                                     // Вычислить значение выражения
};

#endif