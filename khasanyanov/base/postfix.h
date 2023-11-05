#ifndef __POSTFIX_H__
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
	/*class Lexem
	{
		
		enum class Type
		{
			DIGIT,
			VARIABLE,
			OPERATOR,
			FUNCTION,
			L_BRACKET,
			R_BRACKET,
			DEF
		};
		string data = "";
		Type type = Type::DEF;
	public:
		friend class TPostfix;
		Lexem() {}
		Lexem(string s, Type t) : data(s), type(t) {}
		Lexem (const Lexem&) {}
	};*/

	map<string, function<double(double, double)> > binarOperations = {
	{"+", [](double a, double b) {return a + b; }},
	{"-", [](double a, double b) {return a - b; }},
	{"/", [](double a, double b) {return a / b; }},
	{"*", [](double a, double b) {return a * b; }},
	{"^", [](double a, double b) {return pow(a,b); }},
	};
	map<string, function<double(double)>> unarOperations = {
	{"~", [](double a) {return -1 * a; }},
	{"sin", [](double a) {return sin(a); }},
	{"cos", [](double a) {return cos(a); }},
	{"exp", [](double a) {return exp(a); }},
	{"tg", [](double a) {return sin(a) / cos(a); }},
	};
	string infix = "";                          // входная строка
	string postfix = "";                  // постфиксная форма
	unsigned int operators = 0;
	map<string, unsigned int> priority;
	map<string, double> operands;
	vector<string> lexems;
	inline bool isOperator(const string s); // является ли оператором
	unsigned int countOperators(string s); // количество операторов в строке
	void split();
	
public:
	TPostfix();                            // конструктор по умолчанию 
	TPostfix(string str);                  // конструктор-инициализатор
	string getInfix() const;               // входная строка
	string getPostfix() const;             // постфиксная форма
	void toPostfix();                    // преобразование в постфиксную форму
	double calculate();                    // вычисление по постфиксной форме
};

#endif
