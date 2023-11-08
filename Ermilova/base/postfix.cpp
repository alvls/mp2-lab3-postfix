#include "postfix.h"
#include "stack.h"
#include <stdexcept>

TPostfix::TPostfix(string infx) {
	if (infx.empty())
		throw "Stack is empty";
	infix = infx;
	ToPostfix(); 
}

string TPostfix::GetInfix(){
	return infix; 
}

vector<string> TPostfix::GetPostfix(){
	return postfix; 
}

vector<string> TPostfix::GetOperands(){

	vector<string> op(operands.size());
	size_t i = 0;

	for (const auto& item : operands){
		op[i++] = item.first; 
	}
	return op;
}

void TPostfix::Parse() { 
	string tmp = "";
	for (char c : infix) {
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
			if (!tmp.empty()) {
				lexems.push_back(tmp);
			}
			lexems.push_back(string{ c });
			tmp = "";
			continue;
		}
		tmp += c;
	}
	if (!tmp.empty()) {
		lexems.push_back(tmp);
	}
}

map<char, int>TPostfix::priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

void TPostfix::ToPostfix() {
	Parse();
	TStack<string> st;
	string stackItem;
	for (auto& item : lexems){
		switch (item[0]) {
		case '(':
			st.Push(item);
			break;
		case ')':
			stackItem = st.Pop();
			while (stackItem != "(") {
				postfix.push_back(stackItem);
				stackItem = st.Pop();
			}
			break;
		case '+': case '-': case '*': case '/':
			while (!st.IsEmpty()){
				stackItem = st.Pop();
				if (priority[item[0]] <= priority[stackItem[0]]){
					postfix.push_back(stackItem);
				}
				else {
					st.Push(stackItem);
					break;
				}
			}
			st.Push(item);
			break;
		default:
			operands.insert({ item, 0.0 });
			postfix.push_back(item);
			break;
		}
	}
	while (!st.IsEmpty()) {
		stackItem = st.Pop();
		postfix.push_back(stackItem);
	}
}

double TPostfix::Calculate(const map<string, double>& values) {
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
	for (const string& lexem : postfix)
	{
		const char c = lexem[0];
		switch (c)
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
