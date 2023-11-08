#include "postfix.h"
#include "stack.h"

TPostfix::TPostfix(string infx)
{
	if (infx.empty())
		throw "Infix is empty";
	infix = infx;
	ToPostfix();
}
vector<char> TPostfix::GetOperands() const {

	vector<char> op;
	for (const auto& item : operands) { op.push_back(item.first); }

	return op;
}
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
				operands.emplace(item, (double)item);
			}
			catch (...) {
				operands.emplace(item, 0);
			}
			postfix += item;
		}
	}
	while (!st.IsEmpty()) { stackItem = st.Pop(); postfix += stackItem; }
}

double TPostfix::Calculate(const map<char, double>& values)
{
        for (const auto& val : values) {
            if (operands.find(val.first) != operands.end())
            {
                operands[val.first] = val.second;
            }
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
		case '^':
			rightOperand = st.Pop();
			leftOperand = st.Pop();
			st.Push(pow(leftOperand, rightOperand));
			break;
		default:
			st.Push(operands[lexem]);
		}
	}
	return st.Pop();
}
map<char, int> TPostfix::priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3} };
string TPostfix::GetInfix() const { return infix; }
string TPostfix::GetPostfix() const { return postfix; }
void TPostfix::Parse() { for (char x : infix) { lexems.push_back(x); } }
