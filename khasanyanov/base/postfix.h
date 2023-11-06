﻿#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <stdexcept>
#include "stack.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <functional>
using namespace std;

class TPostfix
{
	static map<string, function<double(double, double)> > binaryOperations; // функции бинарных операций
	static map<string, function<double(double)>> unaryOperations;           // функции унарных операций
	static map<string, unsigned int> priority;                              // приоритет операций
	string infix = "";                                                      // входная строка
	string postfix = "";                                                    // постфиксная форма
	unsigned int operators = 0;                                             // кол-во операторов
	map<string, double> operands;                                           // операнды и значения
	vector<string> lexems;                                                  // вектор лексем
	inline bool isOperator(const string s);                                 // является ли оператором
	unsigned int countOperators(string s);                                  // количество операторов в строке
	void split();                                                           // парсер строки
	
public:
	TPostfix();                                                             // конструктор по умолчанию 
	TPostfix(string str);                                                   // конструктор-инициализатор
	string getInfix() const;                                                // входная строка
	string getPostfix() const;                                              // постфиксная форма
	map<string, double> getOperands() const;                                // значения операндов
	void toPostfix();                                                       // преобразование в постфиксную форму
	double calculate(map<string, double> values);                           // вычисление по постфиксной форме
};

#endif
