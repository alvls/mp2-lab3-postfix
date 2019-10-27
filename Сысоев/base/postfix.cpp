#include "postfix.h"
#include "stack.h"


TPostfix::TPostfix()

{
	{
		infix = "(((a+b)*c-d)+e)*f-g";
	}
}
TPostfix::TPostfix(string s)
{
		infix = s;
		LenInfix = GetLen();
}

string TPostfix::ToPostfix()
{
	TStack<char> operation(LenInfix);
	postfix = "";
	for (int i = 0; i < LenInfix; i++)
	{
		if (isalpha(infix[i]))
			postfix += infix[i];
		else
			if ((infix[i] == '*') || (infix[i] == '/') || (infix[i] == '+') || (infix[i] == '-') || (infix[i] == '(') || (infix[i] == ')'))
			{
				if (operation.IsEmpty())
					operation.Push(infix[i]);
				else
				{
					if (Priority(infix[i]) <= Priority(operation.GetTop()))
					{
						if (infix[i] == '(') operation.Push(infix[i]);
						else if (infix[i] == ')')
						{
							while (operation.GetTop() != '(')
							{
								postfix += operation.Pop();
							}
							operation.Pop();
						}
						else
						{
							while ((!operation.IsEmpty()) && (operation.GetTop() != '('))
							{
								postfix += operation.Pop();
							}
							operation.Push(infix[i]);
						}
					}
					else if (Priority(infix[i]) > Priority(operation.GetTop()))
					{
						operation.Push(infix[i]);
					}
				}
			}
	}

		while (!operation.IsEmpty())
		{
			postfix += operation.Pop();
		}
		return postfix;
}

int TPostfix::CountVal()
{
	int count = 0;
	for (int i = 0; i < LenInfix; i++)
	{
		if (isalpha(infix[i]))
			count++;
	}
	return count;
}

int TPostfix::Priority(char t)
{
	if (t == '(')
		return 0;
	else
		if (t == ')')
			return 1;
		else
			if (t == '+' || t == '-')
				return 2;
			else if (t == '*' || t == '/')
				return 3;
			else throw ("Erorr");
}

double TPostfix::Calculate(double *_values)
{
	TStack<double> Value(CountVal());
	double val1, val2;
	int j = 0;
	for (int i = 0; i < postfix.length(); i++)
	{
		if (isalpha(postfix[i]))
		{
			Value.Push(_values[j++]);
		}
		else
		{
			val1 = Value.Pop();
			val2 = Value.Pop();

			switch (postfix[i])
			{
			case '+':
				Value.Push(val1 + val2);
				break;
			case '-':
				Value.Push(val2 - val1);
				break;
			case '/':
				Value.Push(val2 / val1);
				break;
			case '*':
				Value.Push(val1 * val2);
				break;
			}
		}
	}
	return Value.GetTop();
}