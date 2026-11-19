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
  explicit TPostfix(const string& expression) : infix(expression) {}

  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  void SetInfix(const string& expression) { infix = expression; postfix.clear(); }
  string ToPostfix();
  double Calculate();
};

#endif
