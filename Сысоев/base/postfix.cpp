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

bool TPostfix::IsOperand(char op)
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
		if (IsOperand(infix[i]))
		{
			postfix += infix[i];
			while (IsOperand(infix[i + 1]))
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
  return 0;
}
