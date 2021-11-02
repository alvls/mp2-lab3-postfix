#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include "eq_exception.h"
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <sstream>

#include "stack.h"

using namespace std;

struct OpData
{
    int operands;
    int priority;
};

class TPostfix
{
  string infix;
  string postfix_str;
  vector<string> postfix;
  int stacklen;

  map<string, OpData> op_data = {
    {"(",{0,0}},
    {")",{0,-1}},
    {"+",{2,1}},
    {"-",{2,1}},
    {"*",{2,2}},
    {"/",{2,2}},
    {"^",{2,2}},
    {"cos",{1,3}},
    {"sin",{1,3}},
    {"exp",{1,4}},
    {"sqrt",{1,3}},
    {"tg",{1,3}},
    {"ctg",{1,3}},
    {"ln",{1,4}},
    {"log",{1,4}},
    {"mdl",{1,5}}
  };

  template<class T>
  bool IsInclude(const map<string, T>& map, const string& key) const; 
  vector<string> Split(const string& str) const;
  int Priority(const string& key);
  int Operands(const string& key);
  double ToDoubleNum(const string& str);
  bool IfDoubleNum(const string& str);


  template<class T>
  void Operation(const string& str, TStack<T>& stack, T first, T second, bool isdouble) const;
public:
  TPostfix(const string& _infix) : infix(_infix), postfix(), postfix_str(""), stacklen(0) {}
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix_str; }
  void InfixAnalyzer(const string& infix) const;
  string ToPostfix();
  void ChangeExpression(const string& _infix);
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
