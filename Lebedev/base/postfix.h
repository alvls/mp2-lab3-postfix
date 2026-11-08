#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include <map>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix;
  vector<string> lexems;
  vector<string> postfix;
  vector<string> operands;
  map<string, double> values;

  void Parse();
  void ToPostfix();
public:
  TPostfix(const string &expr = "a + b");
  string GetInfix() const { return infix; }
  string GetPostfix() const;
  vector<string> GetOperands() const { return operands; }
  void SetValue(const string &name, double val);
  void SetValues(const map<string, double> &vals);
  double Calculate();
  double Calculate(const map<string, double> &vals);
};

#endif
