#include "postfix.h"
#include "stack.h"
#include <iostream>

inline bool TPostfix::isDigit(const char num) const
{
	return(num >= '0' && num <= '9');
}
inline bool TPostfix::isLetter(const char a) const
{
	return((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z'));
}

inline bool TPostfix::isOperator(const char op) const
{
	return (op == '+' || op == '-' || op == '*' || op == '/');
}

int TPostfix::precedence(const char op) const
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else
		return 0;
}

string TPostfix::ToPostfix()
{
	TStack<char> stk;
	postfix = "";

	for (char c : infix)
	{
		if (c == ' ') {
			continue;
			//postfix += ' ';
		}

		if (isDigit(c) || isLetter(c))
		{
			postfix += c;
		}
		else if (isOperator(c))
		{
			if (postfix == "" || postfix == " ") throw "Отсутствие операндов";
			while (!stk.IsEmpty() && stk.Top() != '(' && precedence(c) <= precedence(stk.Top()))
			{
				postfix += stk.pop();
			}
			stk.push(c);
			postfix += " ";
		}
		else if (c == '(')
		{   
			stk.push(c);
		}
		else if (c == ')')
		{
			while (!stk.IsEmpty() && stk.Top() != '(')
			{
				postfix += stk.pop();
			}
			stk.pop(); 
		}
	}

	while (!stk.IsEmpty())
	{
		postfix += " ";
		postfix += stk.pop();
	}
	return postfix;
}

double TPostfix::Calculate()
{
	TStack<double> operands;
	bool flag = false;

	for (int i = 0; i < postfix.length(); i++) {

		if (postfix[i] == ' ') {
			continue;
		}

		if (isLetter(postfix[i])) {
			switch (postfix[i]) {
			case 'a': {
				operands.push(tabl::a); flag = 1; break;;
			}
			case 'b': {
				operands.push(tabl::b); flag = 1; break;
			}
			case 'c': {
				operands.push(tabl::c); flag = 1; break;
			}
			}
		}

		if (isLetter(postfix[i]) && flag == false)
			throw exception("");

		if (isDigit(postfix[i])) {
			operands.push(stod(postfix.substr(i)));
			while (isDigit(postfix[i + 1])) {
				i++;
			}
		}
		if (isOperator(postfix[i])) {
			double operand2 = operands.pop();
			double operand1 = operands.pop();

			switch (postfix[i]) {
			case '+':
				operands.push(operand1 + operand2);
				break;
			case '-':
				operands.push(operand1 - operand2);
				break;
			case '*':
				operands.push(operand1 * operand2);
				break;
			case '/':
				operands.push(operand1 / operand2);
				break;
			}
		}
		flag = false;
	}

	return operands.Top();
}

