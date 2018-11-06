#include "postfix.h"
#include "stack.h"

void TPostfix::ToPostfix()
{
	if (CorrectRecord() == false)
		throw "error";
	TStack<char> op(infix.size());
	postfix = "";
	for (int i = 0; i < infix.size(); i++)
	{
		if (IsOperations(infix[i]) == false)
		{
			postfix += infix[i];
		}
		else
			if (infix[i] == '(')
				op.Push(infix[i]);
			else
				if (infix[i] == ')')
				{
					while (op.Back() != '(')
						postfix += op.Pop();
					op.Pop();
				}
				else
					if (op.IsEmpty() == true)
					{
						op.Push(infix[i]);
					}
					else
						if (Compare(infix[i]) <= Compare(op.Back()))
						{
							postfix += op.Pop();
							op.Push(infix[i]);
						}
						else
							op.Push(infix[i]);
	}
	while (op.IsEmpty() == false)
		postfix += op.Pop();
}

void TPostfix::SetInfix(string _infix, int _count)
{
	infix = _infix;
	count = _count;
}

double TPostfix::Calculate(int _count, double *arg)
{
	if (count != _count)
		throw "error";
	TStack<double> oper(postfix.size());
	double tmp1;
	double tmp2;
	int j = 0;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (IsOperations(postfix[i])==false && j < count)
		{
			oper.Push(arg[j]);
			j++;
		}
		else if (IsOperations(postfix[i]))
		{

			tmp1 = oper.Pop();
			oper.Pop();
			tmp2 = oper.Pop();
			oper.Pop();
			switch (postfix[i])
			{
			case '+':oper.Push(tmp1 + tmp2);
			case '-':oper.Push(tmp2 - tmp1);
			case '/':oper.Push(tmp2 / tmp1);
			case '*':oper.Push(tmp2 * tmp1);
			}
		}
	}
	return oper.Pop();
}

int TPostfix::Compare(char tmp1)
{
	if (tmp1 == '*' || tmp1 == '/')
		return 2;
	if (tmp1 == '-' || tmp1 == '+')
		return 1;
}

bool TPostfix::CorrectRecord()
{
	int lb = 0, rb = 0;
	int operations = 0, operands = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			lb++;
		else if (infix[i] == ')')
			rb++;
		if (rb > lb)
			return false;
		if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
			operations++;
		else if (infix[i] != '+' || infix[i] != '-' || infix[i] != '*' || infix[i] != '/' || infix[i] != '(' || infix[i] != ')')
			operands++;
	}
	if (infix[0] == '(' || infix[infix.length() - 1] == ')')
		return true;
	else if ((IsOperations(infix[0]) == true || IsOperations(infix[infix.size() - 1]) == true))
		return false;
	if (operands == operations + 1)
		return true;
	else return false;
	if (lb == rb)
		return true;
	else return false;
}

bool TPostfix::IsOperations(char s)
{
	if (s == '+' || s == '-' || s == '*' || s == '/' || s == '(' || s == ')')
		return true;
	return false;
}
bool TPostfix::IsOperand(char s)
{
	if ((int(s) >= 65 && int(s) <= 90) || (int(s) >= 97 && int(s) <= 122))
		return true;
	return false;
}

