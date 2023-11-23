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
  vector<string> postfix;
  vector <string> lexems;
  map<string, double> operands;
  map<string, int> priority = { {"^",1}, {"+",2},{"-",2},{"*",3},{"/",3}};
  void Parse() {
	  string tmp = "";
      for (char c : infix) {
		  if (c != ' ') {
			  if ((c != '+') && (c != '-') && (c != '*') && (c != '/') && (c != '^')&&(c!='(')&&(c!=')')) {
				  tmp += c;
			  }
			  else {
				  if (tmp != "")
					lexems.push_back(tmp);
				  tmp = c;
				  lexems.push_back(tmp);
				  tmp = "";
			  }
		  }  
      }
	  lexems.push_back(tmp);
  }
public:
  TPostfix(string tmp)
  {
      infix = tmp;
	  ToPostfix();
  
  }
  vector<string>GetOperands() {
	  vector<string> tmp;
	  for (int i = 0; i < lexems.size(); i++) {
		  string c = lexems[i];
		  if ((c != "+") && (c != "-") && (c != "*") && (c != "/") && (c != "^") && (c != "(") && (c != ")"))
			  tmp.push_back(c);
	  }
	  return tmp;
  }
  vector<string>Getlexems() { return lexems; }
  string GetInfix() { return infix; }
  string GetPostfix() {
	  string tmp = "";
	  for (int i = 0; i < postfix.size(); i++) {
		  tmp += postfix[i];
	  }
	  return tmp; 
  }
  int GetNumberOperands() { return operands.size(); }
  vector<string> ToPostfix();
  double Calculate( map<string, double>& values);

};

#endif
