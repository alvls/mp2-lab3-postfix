#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include <map>
#include <cstddef>
#include "stack.h"

using namespace std;

struct Token {
    string value;
    char type;
    size_t pos;
};

class TPostfix
{
  string infix;
  string postfix;

  vector<Token> tokens;
  vector<Token> postfixTokens;

  int priority(char op);

public:
  TPostfix(const string& expr = "a + b") : infix(expr) {}

  string GetInfix() const { return infix; }
  string GetPostfix() const { return postfix; }

  void tokenize();
  bool check(string& error_msg, size_t& error_pos);
  string ToPostfix();
  vector<string> GetVariables() const;
  double Calculate(const map<string, double>& values);
  double Calculate();
};

#endif