#include "postfix.h"
#include "stack.h"
#include <iostream>
#include <string>
TPostfix::TPostfix(string infx)
{
	if (infx.empty())
		throw "Infix is empty";
	infix = infx;
	ToPostfix();
}
map<char, double> TPostfix::getOperands()
{ return operands; }
void TPostfix::ToPostfix() {

	Parse();

	TStack<char> st;
	char stackItem;
	for (char item : lexems)
	{
		switch (item)
		{
		case '(':
			st.Push(item);
			break;

		case ')':
			stackItem = st.Pop();

			while (stackItem != '(') { postfix += stackItem; stackItem = st.Pop(); }
			break;

		case '+': case '-': case '*': case '/': case '^':
			while (!st.IsEmpty())
			{
				stackItem = st.Pop();

				if (priority[item] <= priority[stackItem]) { postfix += stackItem; }

				else { st.Push(stackItem); break; }
			}
			st.Push(item);
			break;

		default:
			try
			{
				operands.emplace(item, stod(string{ item }));
			}
			catch (...) {
				operands.emplace(item, 0.0);
			}
			postfix += item;
		}
	}
	while (!st.IsEmpty()) { stackItem = st.Pop(); postfix += stackItem; }
}

double TPostfix::Calculate(map<char, double> values)
{
	double rightOperand, leftOperand;
	TStack<double> st;
	for (auto& l : postfix)
	{
			switch (l)
			{
			case '+':
				rightOperand = st.Pop();
				leftOperand = st.Pop();
				st.Push(leftOperand + rightOperand);
				break;

			case '-':
				rightOperand = st.Pop();
				leftOperand = st.Pop();
				st.Push(leftOperand - rightOperand);
				break;

			case '*':
				rightOperand = st.Pop();
				leftOperand = st.Pop();
				st.Push(leftOperand * rightOperand);
				break;

			case '/':
				rightOperand = st.Pop();
				leftOperand = st.Pop();
				st.Push(leftOperand / rightOperand);
				break;
			case '^':
				rightOperand = st.Pop();
				leftOperand = st.Pop();
				st.Push(pow(leftOperand, rightOperand));
				break;
			default:
				st.Push(values[l]);
			}
		}
	return st.Peek();
}
map<char, int> TPostfix::priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3} };
string TPostfix::GetInfix() const { return infix; }
string TPostfix::GetPostfix() const { return postfix; }
void TPostfix::Parse() { for (char x : infix) { lexems.push_back(x); } }
