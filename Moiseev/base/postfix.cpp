#include "postfix.h"
#include "stack.h"


TPostfix::TPostfix(string infx) :infix(infx) {

	priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
	ToPostfix();
}

string TPostfix::GetInfix() const { return infix; }

string TPostfix::GetPostfix() const { return postfix; }

vector<char> TPostfix::GetOperands() const {

	vector<char> op;
	for (const auto& item : operands) { op.push_back(item.first); }

	return op;
}

void TPostfix::Parse() { for (char c : infix) { lexems.push_back(c); } }

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

		case '+': case '-': case '*': case '/':
			while (!st.IsEmpty())
			{
				stackItem = st.Pop();

				if (priority[item] <= priority[stackItem]) { postfix += stackItem; }

				else { st.Push(stackItem); break; }
			}
			st.Push(item);
			break;

		default:
			operands.insert({ item, 0.0 });
			postfix += item;
		}
	}
	while (!st.IsEmpty()) { stackItem = st.Pop(); postfix += stackItem; }
}

double TPostfix::Calculate(const map<char, double>& values) {

	for (auto& val : values)
	{
		try { operands.at(val.first) = val.second; }
		catch (out_of_range& e) { }
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
		}
	}
	return st.Pop();
}
