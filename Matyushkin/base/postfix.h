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
  TPostfix() : infix("a + b") {}
  TPostfix(const string& expr) : infix(expr) {}

  string GetInfix()   { return infix; }
  string GetPostfix() { return postfix; }
  void SetInfix(const string& expr) { infix = expr; postfix.clear(); }

  string ToPostfix();
  double Calculate();
};

#endif