#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <vector>
#include <map>
#include <math.h>
using namespace std;

class TPostfix
{
  string infix;
  string postfix;
  vector <char> lexems;
  

  map<char, double> operands;
  map<char, int> priority = { {'^',1}, {'+',2},{'-',2},{'*',3},{'/',3} };
  void Parse() {
      for (char c : infix) {
		  if (c != ' ') 
			lexems.push_back(c);
      }
  }
public:
  TPostfix(string tmp)
  {
      infix = tmp;
	  ToPostfix();
  
  }
  vector<char>Getlexems() { return lexems; }
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  int GetNumberOperands() { return operands.size(); }
  string ToPostfix();
  double Calculate(const map<char, double>& values);
};

#endif
