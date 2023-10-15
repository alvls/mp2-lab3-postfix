#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <stdexcept>
#include "stack.h"
#include <iostream>
using namespace std;

class TPostfix
{
  string infix = "";                     // входная строка
  string postfix = "";                   // постфиксная форма
  bool isFormula;                        // встречаются ли в выражении переменные
  inline short priority(const char ch);  // приоритет операций
  inline bool isDigit(const char ch);    // является ли числом
  inline bool isVariable(const char ch); // является ли переменной
  inline bool isOperator(const char c);  // является ли оператором
  int countOperators(string s);          // количество операторов в строке
public:
  TPostfix();                            // конструктор по умолчанию 
  TPostfix(string str);                  // конструктор-инициализатор
  string GetInfix() const;               // входная строка
  string GetPostfix() const;             // постфиксная форма
  string ToPostfix(string s);            // преобразование в постфиксную форму
  double Calculate();                    // вычисление по постфиксной форме
};

#endif
