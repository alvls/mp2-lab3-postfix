#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <stdexcept>
#include "stack.h"
#include <vector>
#include <map>
#include <cmath>

using namespace std;

class TPostfix
{
   string infix;
   string postfix;
   static map<char, int> priority;
   map<char, double> variables;
   bool isOperator(char ch);
   bool isOperand(char ch);

public:
   TPostfix(string _infix);
   string GetInfix() const;
   string GetPostfix() const;
   void ToPostfix();
   double Calculate();
   void PromptAndStoreVariables();
};

#endif
