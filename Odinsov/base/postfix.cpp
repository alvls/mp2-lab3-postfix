#include "postfix.h"
#include "stack.h"
#include <stdexcept>
vector<string> TPostfix::ToPostfix()
{
	Parse();
	TStack<string> st(5);
	string stackItem;
	bool flag;
	for (int i=0;i<lexems.size();i++){
		flag = true;
		if (lexems[i] == "(") {
			flag = false;
			st.Push(lexems[i]);
		}
		if (lexems[i] == ")") {
			flag = false;
			stackItem = st.Pop();
			while (stackItem != "(")
			{
				postfix.push_back(stackItem);
				stackItem = st.Pop();
			}
		}
		if ((lexems[i] == "+") || (lexems[i] == "-") || (lexems[i] == "*") || (lexems[i] == "/") || (lexems[i] == "^")) {
			flag = false;
			while (!st.isempty()) {
				stackItem = st.Pop();
				if (priority[lexems[i]] <= priority[stackItem])
						postfix.push_back(stackItem);
				else {
					st.Push(stackItem);
					break;
					}
				}
				st.Push(lexems[i]);
		}
		if (flag){
			operands.insert({lexems[i],0.0});
			postfix.push_back(lexems[i]);
		}
	}
	while (!st.isempty()) {
		stackItem = st.Pop();
		postfix.push_back(stackItem);
	}
	return postfix;
}

double TPostfix::Calculate( map<string, double>& values)
{
	for (auto& val : values) {

		operands.at(val.first) = val.second;

	}
	TStack<double> st;
	double leftOperand, rightOperand;
	for (int i=0;i<postfix.size();i++){
		bool flag = true;
		string lexem = postfix[i];
		if (lexem == "+") {
			flag = false;
			rightOperand = st.Pop();
			leftOperand = st.Pop();
			st.Push(leftOperand + rightOperand);
		}
		if (lexem == "-") {
			flag = false;
			rightOperand = st.Pop();
			leftOperand = st.Pop();
			st.Push(leftOperand - rightOperand);
		}
		if (lexem == "*") {
			flag = false;
			rightOperand = st.Pop();
			leftOperand = st.Pop();
			st.Push(leftOperand * rightOperand);
		}
		if (lexem == "/") {
			flag = false;
			rightOperand = st.Pop();
			leftOperand = st.Pop();
			if (rightOperand == 0)
				throw "Cant delete";
			st.Push(leftOperand / rightOperand);
		}
		if (lexem == "^") {
			flag = false;
			rightOperand = st.Pop();
			leftOperand = st.Pop();
			st.Push(pow(leftOperand, rightOperand));
		}
		if (flag){
			string tmp = "";
			tmp += lexem;
			st.Push(operands[tmp]);
		}
	}
	return st.Pop();
}



