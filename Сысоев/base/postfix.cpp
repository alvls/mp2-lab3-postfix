#include "postfix.h"
#include "stack.h"

TPostfix::TPostfix() {
	infix = "))a+b+c+d-g((";
}
bool TPostfix::Operation(char op) {
	if ((op == '+') || (op == '-') || (op == '*') || (op == '/'))
		return true;
	return false;
}

bool TPostfix::Check() {
	int num = 0, operat = 0;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == '+' || infix[i] == '-' || infix[i] == '/' || infix[i] == '*')
			operat++;
		else if (!Operation(infix[i]) && infix[i] != ')' && infix[i] != '(')
		{
			while (infix[i]!='+'&& infix[i] != '-'&& infix[i] != '/'&& infix[i] != '*'){
				i++;
				if (i == infix.size())
					break;
			}
			i--;
			num++;
		}
	}
	CountNumber = num;
	if (num != operat + 1)
		return false;
	int LBracket = 0, RBracket = 0;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == '(')
			LBracket++;
		else if (infix[i] == ')')
			RBracket++;
	}
	if (LBracket != RBracket)
		return false;
	if (infix[0] == ')' || infix[0] == '/' || infix[0] == '*' || infix[0] == '-' || infix[0] == '+')
		return false;
	if (infix[infix.size()-1] == '(' || infix[infix.size() - 1] == '/' || infix[infix.size() - 1] == '*' || infix[infix.size() - 1] == '-' || infix[infix.size() - 1] == '+')
		return false;
	return true;
}

int TPostfix::CountNum() {
	return CountNumber;
}

int TPostfix::Priority(char a, char b) {
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

string TPostfix::ToPostfix()
{
	if (Check()==false)
		throw "Error";
	TStack<char> ops(infix.size());
	postfix = "";
	for (int i = 0; i < infix.size(); i++)
	{
		if (isalpha(infix[i])) postfix += infix[i];
		else if (Operation(infix[i]) || (infix[i] == '(') || (infix[i] == ')')) {
		if (ops.IsEmpty())
			ops.Push(infix[i]);
		else if (ops.GetTop() == '(')
			ops.Push(infix[i]);
		else if (infix[i] == '(')
			ops.Push(infix[i]);
		else if (infix[i] == ')')
		{
			while (ops.GetTop() != '(')
			{
				postfix += ops.pop();

			}
			ops.pop();
		}
		else if (Priority(infix[i], ops.GetTop()) == 1)
			ops.Push(infix[i]);
		else
		{
			while ((ops.GetTop() != '('))
			{
				if (Priority(infix[i], ops.GetTop()) == 1)
					break;

				postfix += ops.pop();

				if (ops.IsEmpty())
					break;
			}
			ops.Push(infix[i]);
		}
		}
	}
	while (!ops.IsEmpty())
	{
		postfix += ops.pop();
		
	}
	return postfix;
}


TPostfix::TPostfix(string str) {
	infix = str;
}
double TPostfix::Calculate(double* _val )
{
	TStack<double>stack(postfix.size());
	double num1, num2;
	int j = 0;
	for (int i = 0; i < postfix.size(); i++) {
		
		if (isalpha(postfix[i]))
		{
			stack.Push(_val[j]);
			j++;
		}
		else {
			num2 = stack.pop();
			num1 = stack.pop();		
			switch (postfix[i]) {
			case'+':
				stack.Push(num1 + num2);
				break;
			case'-':
				stack.Push(num1 - num2);
				break;
			case'*':
				stack.Push(num1 * num2);
				break;
			case'/':
				stack.Push(num1 / num2);
				break;
			default:
				break;
			}
		}
	}
	return stack.pop();
}
