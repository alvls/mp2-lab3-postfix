#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <cctype>
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
  TPostfix(string _infix)
  {
	  infix = _infix;
  }
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  int Priority(char sym);
  string ToPostfix();
  double Calculate(double *values);
};

#endif
