#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#define _USE_MATH_DEFINES
#include <string>
#include <math.h>
#include "stack.h"
#include <vector>
#include <sstream>
#include <iostream>
#include "operation.h"
using namespace std;

const int reserve = 15;
enum OperationNames
{
    plusOp = 0,
    minusOp,
    multiplyOp,
    divideOp,
    bracketOp,
    powOp,
    sinOp,
    cosOp,
    lnOp,
    lgOp,
    sqrtOp
};

enum ConstsNames
{
    pi,
    e
};

const int countOperation = 11;
const Operation operation[countOperation] = { {"+", 1, 2}, {"-", 1, 2}, {"*", 2, 2}, {"/", 2, 2} ,
    {"(", 0, 1} , {"^", 2, 2}, {"sin", 3, 1}, {"cos", 3, 1} , {"ln", 3, 1} ,{"lg", 3, 1} , {"sqrt", 3, 1} };

const int countConstants = 2;
const double constants[countConstants] = { M_PI, M_E };

class TPostfix
{
private:
  string infix;
  vector<string> lexemes;
  vector <string> postfix;
  bool CheckBrackets();
  bool IsOperation(const string& str, Operation& op, int& indexOperation);
  bool IsConstant(const string& str, int& constIndex);
  vector<string> Split();
public:
  TPostfix()
  {
    infix = "a + b";
  }
  TPostfix(const string& _inf) : infix(_inf)
  {
     
  }
  void ToPostfix();
  void SetInfix(const string& str) { infix = str; };
  string GetInfix() { return infix; }
  vector<string> GetPostfix() { return postfix; };
  double Calculate(); 
  void PrintPostfix();
};

#endif
