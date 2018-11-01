#include "postfix.h"
#include <iostream>
#include "stack.h"


TPostfix::TPostfix(string _infix) : infix(_infix), postfix("") {}
bool TPostfix::delim(char c) {
	return c == ' ';
}
bool TPostfix::is_op(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}
int TPostfix::priority(char op) {
	return
		op == '+' || op == '-' ? 1 :
		op == '*' || op == '/' ? 2 :
		-1;
}
void TPostfix::process_op(TStack<double> & st, char op) {
	double right = st.front();
	st.pop();
	double left = st.front();
	st.pop();
	switch (op) {
		case '+': st.push(left + right); break;
		case '-': st.push(left - right); break;
		case '*': st.push(left * right); break;
		case '/': st.push(left / right); break;
	}
}
bool TPostfix::correct(){
	TStack<char> op;
	string s = infix;
	if (is_op(infix[0]) || is_op(infix[infix.size() - 1])) return false;
	for (int i = 1; i < (int)infix.size(); i++) 
		if (is_op(s[i]) && is_op(s[i - 1])) return false;
	for (int i = 0; i < (int)infix.size(); i++) {
		if (infix[i] == ')') {
			if (op.empty()) return false;
			op.pop();
		} else if (infix[i] == '(') {
			op.push('(');
		}
	}
	if (!op.empty()) return false;
	return true;
}
double TPostfix::execute() {
	TStack<double> st;
	TStack<char> op;
	string s = infix;
	for (int i = 0; i < (int)s.size(); i++) 
		if (!delim(s[i])) 
			if (s[i] == '(')
				op.push('(');
			else if (s[i] == ')') {
				while (op.front() != '(') {
					process_op(st, op.front());
					postfix += op.front();
					postfix += " ";
					op.pop();
				}
				op.pop();
			}
			else if (is_op(s[i])) {
				char curOp = s[i];
				while (!op.empty() && priority(op.front()) >= priority(s[i])) {
					process_op(st, op.front());
					postfix += op.front();
					postfix += " ";
					op.pop();
				}
				op.push(curOp);
			}
			else {
				string operand;
				while (i < (int)s.length() && (isalnum(s[i]) || s[i] == '.'))
					operand += s[i++];
				--i;
				if (isdigit(operand[0])) {
					st.push(stod(operand));
					postfix += operand;
					postfix += " ";	
				}
				else
					throw "ERROR";
			}
	while (!op.empty()) {
		process_op(st, op.front());
		postfix += op.front();
		postfix += " ";
		op.pop();
	}
	return st.front();
}
