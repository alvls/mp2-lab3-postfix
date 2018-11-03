#include "postfix.h"
#include "stack.h"

bool TPostfix::CheckAmount()
{
	string var = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string str = " " + infix + " ";
	string arop = "-*//*+";
	for (int i = 0; i < str.length(); i++) {
		if (arop.find(str[i]) >= 0 && arop.find(str[i]) <= str.length())
		{
			if ((var.find(str[i - 1]) >= 0 && var.find(str[i - 1]) <= var.length()) && (var.find(str[i + 1]) >= 0 && var.find(str[i - 1]) <= var.length()))
				continue;
			else
				return false;//throw "ERROR";//"the number of variables does not correspond to the numbers of operations";
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
				return false;//throw "error"; // не хватает (
			else char tmp = skob.Pop();
		}
	}
	if (!skob.IsEmpty())
	{
		return false;//throw "error";
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
		if (temp == 0) return false;//throw "error";
	}
	return true;
}

bool TPostfix::CheckInfix()
{
	CheckChars();
	CheckAmount();
	CheckBrackets();
	if (infix[0] == ')' || infix[0] == '*' || infix[0] == '/' || infix[0] == '-' || infix[0] == '+')
		return false;//throw "First character is operations";
	if (infix[infix.length() - 1] == '(' || infix[infix.length() - 1] == '*' || infix[infix.length() - 1] == '/' || infix[infix.length() - 1] == '-' || infix[infix.length() - 1] == '+')
		return false;//throw "Last character is operations";
	return true;
}

int TPostfix::Priority(char a)
{
	if (!IsOperation(a))
		throw "data is not correct";
	if (a == '(')
		return 0;
	else if (a == ')')
		return 1;
	else if (a == '+' || a == '-')
		return 2;
	return 3;
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

void TPostfix::ToPostfix()
{
	if (!CheckInfix())
		throw "!Correctly Infix";
	TStack<char> stack(infix.length());
	postfix = "";
	for (int i = 0; i < infix.length(); i++)
	{
		if (!IsOperation(infix[i]))
		{
			postfix += infix[i];
			if (i == infix.size() - 1 || IsOperation(infix[i + 1]))
				postfix += ' ';
		}
		
		else
		{
			if (infix[i] != ')')
			{
				if (Priority(infix[i]) == 0 || stack.IsEmpty() || Priority(infix[i]) > Priority(stack.GetElement()))
				{
					stack.Push(infix[i]);
					}

				else
				{
					int a = stack.lenght();
					for (int j = 0; j < a; j++)
					{
						if (Priority(stack.GetElement()) >= Priority(infix[i]))
						{
							postfix += stack.Pop();
							postfix += ' ';
						}
						else
							break;
					}
					stack.Push(infix[i]);
				}
			}
			else {
				int a = stack.lenght();
				for (int j = 0; j < a; j++)
				{
					if (stack.GetElement() != '(')
					{
						postfix += stack.Pop();
						postfix += ' ';
					}
					else
					{
						stack.Erase();
						break;
					}
				}
			}
		}
	}
	while (!stack.IsEmpty())
	{
		postfix += stack.Pop();
		postfix += " ";
	}
}
double TPostfix::Calculate()
{
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
			stack.Push(stod(tmp));//atof(tmp.c_str())
		}
		else
		{
			switch (postfix[i]) {
			case '+': {
				tmp1 = stack.Pop();
				tmp2 = stack.Pop();
				stack.Push(tmp1 + tmp2);
				break; }
			case '-': {
				tmp1 = stack.Pop();
				tmp2 = stack.Pop() - tmp1;
				stack.Push(tmp2);
				break; }
			case '*': {
				tmp1 = stack.Pop();
				tmp2 = stack.Pop() * tmp1;
				stack.Push(tmp2);
				break; }
			case '/': {
				tmp1 = stack.Pop();
				if (tmp1 != 0)
				{
					tmp2 = stack.Pop() / tmp1;
					stack.Push(tmp2);
				}
				else
					throw "Division by zero!!!";
				break; }
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

