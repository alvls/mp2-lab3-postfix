#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#define F_Size 10

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <map>
#include "stack.h"

struct operation {
	std::string name;
	int priority;
};

const operation funcs[F_Size] = {			// 4	// 5	 
  {"(", 0}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 4},
  {"exp", 4},  {"sqrt", 4},  {"ln", 4}, {"sin", 4}
}; // 6			// 7			// 8	// 9

class TPostfix
{
	std::string infix;
	std::string postfix;
public:
  TPostfix(){
  }
  std::string GetInfix() { return infix; }
  void SetInfix(std::string s) { infix = s; }
  std::string GetPostfix() { return postfix; }
  std::string ToPostfix();
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
