#include "postfix.h"
#include "stack.h"
#include <stdexcept>

string TPostfix::ToPostfix()
{
	Parse();
	TStack<char> st(5);
	char stackItem;
	for (char item : lexems) {
		switch (item)
		{
		case '(':
			st.Push(item);
			break;
		case ')':
			stackItem = st.Pop();
			while (stackItem != '(')
			{
				postfix += stackItem;
				stackItem = st.Pop();
			}
			break;
		case '+':case'-':case'*':case'/':case'^':
			while (!st.isempty()) {
				stackItem = st.Pop();
				if (priority[item] <= priority[stackItem])
					postfix += stackItem;
				else {
					st.Push(stackItem);
					break;
				}
			}
			st.Push(item);
			break;
		default:
			operands.insert({ item,0.0 });
			postfix += item;
			break;
		}
	}
	while (!st.isempty()) {
		stackItem = st.Pop();
		postfix += stackItem;
	}

	return postfix;
}

double TPostfix::Calculate(const map<char, double>& values)
{
	for (auto& val : values) {

		operands.at(val.first) = val.second;

	}
	TStack<double> st;
	double leftOperand, rightOperand;
	for (char lexem : postfix) {
		switch (lexem)
		{
		case'+':
			rightOperand = st.Pop();
			leftOperand = st.Pop();
			st.Push(leftOperand + rightOperand);
			break;
		case'-':
			rightOperand = st.Pop();
			leftOperand = st.Pop();
			st.Push(leftOperand - rightOperand);
			break;
		case'*':
			rightOperand = st.Pop();
			leftOperand = st.Pop();
			st.Push(leftOperand * rightOperand);
			break;
		case'/':
			rightOperand = st.Pop();
			leftOperand = st.Pop();
			if (rightOperand == 0)
				throw "Cant delete";
			st.Push(leftOperand / rightOperand);
			break;
		default:
			st.Push(operands[lexem]);
		}
	}
	return st.Pop();
}

