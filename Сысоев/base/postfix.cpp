#include "postfix.h"
#include "stack.h"

int TPostfix::Priority(char a)
{
	if ((a == '*') || (a == '/'))
		return 1;
	if ((a == '+') || (a == '-'))
		return 2;
}
/*bool TPostfix::Operat(char a)
{
	for (int i = 0; i < Operation.size(); i++)
	{
		if (a == Operation[i])
			return true;
		else return false;
	}
}*/

/*bool TPostfix::Operat(char a) {
	for (int i = 0; i < op.size(); i++)
	{
		if (a == op[i])
			return true;
		else
			return false;
	}
}*/

bool TPostfix::Operand(char op)
{
	for (char i = '0'; i <= '9'; i++)
		if (op == i)
			return true;
	return false;
}

string TPostfix::ToPostfix()
{
	setlocale;
	TStack<char> stack(infix.length());
	for (int i = 0; i < infix.length(); i++)
	{
		/*if (!Operat(infix[i])) {
			postfix += infix[i];
			while (!Operat(infix[i + 1]))
			{
				postfix += infix[i + 1];
				i++;
			}
			// postfix += " ";
		}*/
		if (Operand(infix[i]))
		{
			postfix += infix[i];
			while (Operand(infix[i + 1]))
			{
				postfix += infix[i + 1];
				i++;
			}
			postfix += " ";
		}
		else  if (infix[i] == '(')
			stack.Push(infix[i]);
		else if (infix[i] == ')')
		{
			while (stack.GetElement() != '(') {
				postfix += stack.Pop();
				postfix += " ";
			}
			stack.Pop();
		}
		else if (stack.IsEmpty())
			stack.Push(infix[i]);
		else if (Priority(infix[i]) < Priority(stack.GetElement())) {
			while (!stack.IsEmpty())
			{
				postfix += stack.Pop();
				postfix += " ";
			}
			stack.Push(infix[i]);
		}
		else
			stack.Push(infix[i]);
	}
	while (!stack.IsEmpty())
	{
		postfix += stack.Pop();
	}
	return postfix;
}

double TPostfix::Calculate()
{
	TStack<double>stack(postfix.length());
	//double sum;
	string tmp;
	double tmp1 = 0.0;
	double tmp2 = 0.0;
	
	for (int i = 0; i < postfix.length(); i++)
	{
		if (postfix[i] == ' ')  continue;
		if (Operand(postfix[i]))
		{
			tmp = "";
			tmp += postfix[i];
			while (Operand(postfix[i + 1]))
			{
				tmp += postfix[i + 1];
				i++;
			}
			stack.Push(stod(tmp));
		}
		else
		{
			switch (NumOperator(postfix[i])) {
			case 0: {
				throw "Unknown operation!!!"; }
			case 1:{
				tmp1 = stack.Pop();
				tmp2 = stack.Pop();
				stack.Push(tmp1 + tmp2);
				break; }
			case 2: {
				tmp1 = stack.Pop();
				tmp2 = stack.Pop() - tmp1;
				stack.Push(tmp2);
				break; }
			case 3: {
				tmp1 = stack.Pop();
				tmp2 = stack.Pop() * tmp1;
				stack.Push(tmp2);
				break; }
			case 4: {
				tmp1 = stack.Pop();
				if (tmp1 != 0)
					{
						tmp2 = stack.Pop() * tmp1;
						stack.Push(tmp2);
					}
				else
					throw "Division by zero!!!";
				break; }
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
