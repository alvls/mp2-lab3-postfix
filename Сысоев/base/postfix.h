#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <iostream>
#define N 6
#define M 4
#define L 100
#define Z 6
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
  TPostfix(string s)
  {
	  infix = s;
  }
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  string ToPostfix();
  double Calculate(); 
  bool Check_op(char c);
  int Priority(char c);
};

#endif
