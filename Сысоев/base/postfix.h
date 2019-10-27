#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix;
  string postfix;
  int LenInfix;
public:
	TPostfix();
	TPostfix(string s);
	string GetInfix() { return infix; } 
	string GetPostfix() { return postfix; } 
	string ToPostfix(); 
	double Calculate(double* _values);
	int Priority(char t); 
	int GetLen() { return infix.length(); } 
	int CountVal(); 
};

#endif
