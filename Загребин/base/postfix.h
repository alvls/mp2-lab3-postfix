#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#define F_Size 10

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <map>
#include "stack.h"

using namespace std;

struct operation {
	string name;
	int priority;
};

struct variable{
  string name;
  double value;
};

const operation funcs[F_Size] = {			// 4	// 5	 
  {"(", 0}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 4},
  {"exp", 4},  {"sqrt", 3},  {"ln", 4}, {"sin", 3}
}; // 6			// 7			// 8	// 9

class TPostfix
{
	string infix;
	string postfix;
public:
  TPostfix(){
  }
  string GetInfix() { return infix; }
  void SetInfix(string s) { infix = s; }
  string GetPostfix() { return postfix; }
  string ToPostfix();
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
