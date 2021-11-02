#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#define _USE_MATH_DEFINES

#include <string>
#include <math.h>
#include "stack.h"
#include <vector>
#include <sstream>
#include <iostream>
#include "Operation.h"

using namespace std;

const int offset = 10;
enum namesOperation
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

enum constsNames
{
    pi,
    e
};

const int countOperation = 11;
const Operation operation[countOperation] = { {"+", 1, plusOp}, {"-", 1,minusOp }, {"*", 2 ,multiplyOp}, {"/", 2, divideOp} ,
    {"(", 0} , {"^", 2, powOp}, {"sin", 3, sinOp}, {"cos", 3, cosOp} , {"ln", 3, lnOp} ,{"lg", 3, lgOp} , {"sqrt", 3, sqrtOp} };

const int countConstants = 2;
const double constants[countConstants] = { M_PI, M_E };

class TPostfix
{
  string infix;
  string postfixStr;
  vector <string> postfix;
public:
  TPostfix()
  {
    infix = "a + b";
  }
  TPostfix(const string& _inf) : infix(_inf)
  {
     
  }
  bool CheckBrackets();
  bool IsOperation(const string& str, Operation& op);
  bool IsConstant(const string& str, int& index);
  string GetInfix() { return infix; } 
  //string GetPostfix() { return postfixStr; }
  void ToPostfix();
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
  vector<string> Split();
  vector<string> GetPostfix() { return postfix; };
  void SetInfix(const string& str) { infix = str; };
};

#endif
