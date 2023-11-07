#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <map>

class TPostfix
{
  std::string infix;
  std::string postfix;
  std::map<char, double> variables;
public:
  TPostfix(const std::string& expression = "")
  {
    infix = expression.empty() ? "a + b" : expression;
  }
  std::string GetInfix() { return infix; }
  std::string GetPostfix() { return postfix; }
  std::string ToPostfix();
  double Calculate();
  void ReadVariables();
};

#endif __POSTFIX_H__