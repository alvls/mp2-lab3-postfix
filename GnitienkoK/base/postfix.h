#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix;
  string postfix;
public:
  TPostfix()
  {
    infix = "a + b";
  }
  TPostfix(string str) {
      infix = str;
  }
  bool isDigit(const char num) const;
  bool isLetter(const char a) const;
  bool TPostfix::isOperator(const char op) const;
  int precedence(const char op) const;
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  string ToPostfix();
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
