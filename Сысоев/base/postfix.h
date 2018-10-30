#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <cctype>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix;
  string postfix;
public:
  TPostfix(string _infix)
  {
   // infix = "a + b";
	  infix = _infix;
  }
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  string ToPostfix()
  {
	  TStack<char> operations(infix.size);
	  TStack<char> symbols(infix.size);
	  for (int i = 0; i < infix.size; i++)
	  {
		  if (!isalpha(infix[i]))
			  operations.Put(infix[i]);
		  else
			  symbols.Put(infix[i]);
		//  if( infix[i]=='(' || infix[i]==')')
	  }
  }
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
