#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#define PI 3.14159265358979323846

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
	void toPostfix();                                                       // преобразование в постфиксную форму
	inline void updatePostfix(const string s) noexcept;                     // формирование выходной строки
	
public:
	TPostfix();                                                             // конструктор по умолчанию 
	TPostfix(string str);                                                   // конструктор-инициализатор
	string getInfix() const noexcept;                                       // входная строка
	string getPostfix() const noexcept;                                     // постфиксная форма
	map<string, double> getOperands() const noexcept;                       // значения операндов
	double calculate(map<string, double> values);                           // вычисление по постфиксной форме
};

#endif
