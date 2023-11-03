#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <stdexcept>
#include "stack.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;

class TPostfix
{
	class Lexem
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
	};
	string infix = "";                          // входная строка
	string postfix = "";                   // постфиксная форма
	map<string, unsigned int> priority;
	map<string, double> values;
	vector<Lexem> lexems;
	inline bool isDigit(const char ch);    // является ли числом
	inline bool isVariable(const char ch); // является ли переменной
	inline bool isOperator(const char ch); // является ли оператором
	inline bool isFunction(const string s);
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
