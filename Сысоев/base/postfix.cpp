#include "postfix.h"
#include "stack.h"

/*string TPostfix::ToPostfix()
{
  postfix = string("ab+");
  return postfix;
}

double TPostfix::Calculate()
{
  return 0;
}*/

bool TPostfix::CheckAmount()                      
{
 
	string operand = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string str = " " + infix + " ";
	string arop = "-*//*+";
	for (int i = 0; i < str.length(); i++) {
		if (arop.find(str[i]) >= 0 && arop.find(str[i]) <= str.length())
		{
			if ((operand.find(str[i - 1]) >= 0 && operand.find(str[i - 1]) <= operand.length()) && (operand.find(str[i + 1]) >= 0 && operand.find(str[i - 1]) <= operand.length()))
				continue;
			else
				return false;                       //разное число переменных и операций;
		}
	}
	return true;
}
 bool TPostfix::CheckBrackets()
{
	TStack<char> skob(infix.length());
	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] == '(')
			skob.Push(infix[i]);
		if (infix[i] == ')') {
			if (skob.IsEmpty())
				return false;                                  
			else char tmp = skob.Pop();
		}
	}
	if (!skob.IsEmpty())
	{
		return false;
	}
	return true;
}
 bool TPostfix::CheckChars()
{
	string chars = "()*/-+abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int temp;
	for (int i = 0; i < infix.length(); i++)
	{
		temp = 0;
		for (int j = 0; j < chars.length(); j++)
		{
			if (infix[i] == chars[j])
				temp++;
		}
		if (temp == 0) return false;
	}
	return true;
}
 bool TPostfix::CheckInfix()
{
	CheckChars();
	CheckAmount();
	CheckBrackets();
	if (infix[0] == ')' || infix[0] == '*' || infix[0] == '/' || infix[0] == '-' || infix[0] == '+')
		return false;                               //первый символ в строке - операция;
	if (infix[infix.length() - 1] == '(' || infix[infix.length() - 1] == '*' || infix[infix.length() - 1] == '/' || infix[infix.length() - 1] == '-' || infix[infix.length() - 1] == '+')
		return false;                               //последний символ в строке - операция
	return true;
}
 int TPostfix::Priority(char a, char b)
{
	if ((a == '*' || a == '/') && (b == '*' || b == '/'))
		return 0;
	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
		return 1;
	if ((a == '+' || a == '-') && (b == '*' || b == '/'))
		return -1;
	if ((a == '+' || a == '-') && (b == '+' || b == '-'))
		return 0;
	throw "Error";
}
 bool TPostfix::IsOperation(char elem)
{
	return (elem == '(' || elem == ')' || elem == '+' || elem == '-' || elem == '*' || elem == '/') ? true : false;
}
 bool TPostfix::Operand(char op)
{
	for (char i = '0'; i <= '9'; i++)
		if (op == i)
			return true;
	string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < chars.length(); i++)
	{
		if (op == chars[i])
			return true;
	}
	return false;
}
 


 string TPostfix::ToPostfix()
 {
	// postfix = string("ab+");
	// return postfix;
	 if (!CheckInfix())
		 throw "Error";
	 TStack<char> stack(infix.size());
	 for (int i = 0; i < infix.size(); i++)
	 {
		 if (!IsOperation(infix[i]) && infix[i] != '(' && infix[i] != ')')
		 {
			 int j = i;
			 while (!IsOperation(infix[j]) && j != infix.size() && infix[j] != ')')
			 {
				 postfix += infix[j];
				 j++;
			 }
			 i = j - 1;
			 postfix += ',';
		 }
		 else if (stack.IsEmpty())
			 stack.Push(infix[i]);
		 else if (stack.Back() == '(')
			 stack.Push(infix[i]);
		 else if (infix[i] == '(')
			 stack.Push(infix[i]);
		 else if (infix[i] == ')')
		 {
			 while (stack.Back() != '(')
			 {
				 postfix += stack.Pop();
				 postfix += ',';
			 }
			 stack.Pop();
		 }
		 else if (Priority(infix[i], stack.Back()) == 1)
			 stack.Push(infix[i]);
		 else
		 {
			 while ((stack.Back() != '('))
			 {
				 if (Priority(infix[i], stack.Back()) == 1)
					 break;
				 postfix += stack.Pop();
				 postfix += ',';
				 if (stack.IsEmpty())
					 break;
			 }
			 stack.Push(infix[i]);
		 }
	 }
	 while (!stack.IsEmpty())
	 {
		 postfix += stack.Pop();
		 postfix += ',';
	 }
	 return postfix;
 }

double TPostfix::Calculate()
{
  return 0;
	TStack<double>stack(postfix.length());
	string tmp;
	double tmp1 = 0.0;
	double tmp2 = 0.0;
	for (int i = 0; i < postfix.length(); i++)
	{
		if (postfix[i] == ' ')  continue;
		if (!IsOperation(postfix[i]) && Operand(postfix[i]))
		{
			tmp = "";
			tmp += postfix[i];
			while (Operand(postfix[i + 1]) || (postfix[i + 1] != ' '))
			{
				tmp += postfix[i + 1];
				i++;
			}
			stack.Push(stod(tmp));
	

		}
		else
		{
			tmp1 = stack.Pop();
			tmp2 = stack.Pop();
			switch (postfix[i]) {
			case'+':stack.Push(tmp1 + tmp2); break;
			case'-':stack.Push(tmp2 - tmp1); break;
			case'*':stack.Push(tmp1 * tmp2); break;
			case'/':stack.Push(tmp2 / tmp1); break;
			default: "Error";
			}
		}
		}
		return stack.Pop();
	}

 int TPostfix::NumOperator(char op) {
	if ((op != '+') && (op != '-') && (op != '*') && (op != '/'))
		return 0;
	if (op == '+') return 1;
	if (op == '-') return 2;
	if (op == '*') return 3;
	if (op == '/') return 4;
}
