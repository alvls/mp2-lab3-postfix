#include "postfix.h"
#include "stack.h"

TPostfix::TPostfix(string infx) : infix(infx)
{
	priority = { {'+',1}, {'-',1}, {'*',2}, {'/',2} };
	ToPostfix();
}
void TPostfix::Parse()
{
	for (char c : infix)
		lexems.push_back(c);
}
void TPostfix::ToPostfix()
{
	Parse();
	TStack<char> st;
	char StackItem;
	for (char item : lexems)
	{
		switch (item)
		{
		case '(':
			st.Push(item);
			break;
		case ')':
			StackItem = st.Pop();
			while (StackItem != '(')
			{
				postfix += StackItem;
				StackItem = st.Pop();
			}
			break;
		case '+': case '-': case '*': case '/':
			while (!st.IsEmpty())
			{
				StackItem = st.Pop();
				if (priority[item] <= priority[StackItem])
					postfix += StackItem;
				else
				{
					st.Push(StackItem);
					break;
				}
			}
			st.Push(item);
			break;
		default:
			operands.insert({ item, 0.0 });
			postfix += item;
			break;
		}
	}
	while (!st.IsEmpty())
	{
		StackItem = st.Pop();
		postfix += StackItem;
	}
}
vector<char> TPostfix::GetOperands() const
{
	vector<char> op;
	for (const auto& item : operands)
		op.push_back(item.first);
	return op;
}
double TPostfix::Calculate(const map<char, double>& values) {
	for (auto& val : values)
	{
		try
		{
			operands.at(val.first) = val.second;
		}
		catch (out_of_range& e) {}
	}
	TStack<double> st;
	double leftOperand, rightOperand;
	for (char lexem : postfix)
	{
		switch (lexem)
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
		default:
			st.Push(operands[lexem]);
			break;
		}
	}
	return st.Pop();
}