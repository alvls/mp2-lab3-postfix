#include "postfix.h"
#include "stack.h"
#include <sstream>
#include <cmath>
string TPostfix::ToPostfix()
{
	TStack<string> stack(100);
	for (int ch = 0; ch < infix.length(); ch++) {
		char i;
		i = infix[ch];
		if (i == ' ') continue;
		else if (isalpha(infix[ch])) {
			string word = "";
			while (ch < infix.length() && isalpha(infix[ch])) {
				word += infix[ch];
				ch++;
			}
			ch--;
			if (word == "sin" || word == "cos" || word == "tg" || word == "ln" || word == "sqrt") {
				stack.push(word); 
			}
			else {
				postfix += word;
				postfix += ' ';
			}
		}
		else if (isdigit(i) || i == '.' || i == ',') {
			while (ch + 1 < infix.length() && (isdigit(infix[ch + 1]) || infix[ch + 1] == '.' || infix[ch + 1] == ',')) {
				if (i == '.') i = ',';
				postfix += i;
				ch++;
				
				i = infix[ch];
			}
			postfix += i;
			postfix += ' ';
		}
		else if (i == '(') {
			stack.push({ i });
		}
		else if (i == ')') {
			while (!stack.is_empty() && stack.peek() != "(") {
				postfix += stack.pop();
				postfix += ' ';
			}
			if (!stack.is_empty()) {
				stack.pop();
				if (!stack.is_empty() && (stack.peek() == "sin" || stack.peek() == "cos" 
					|| stack.peek() == "tg" || stack.peek() == "ln" || stack.peek() == "sqrt")) {
					postfix += stack.pop();
					postfix += ' ';
				}
			}
		
		}
		else if (i == '+' || i == '-' || i == '*' || i == '/') {
			while (!stack.is_empty() && GetPriority(stack.peek()) >= GetPriority({ i })) {
				postfix += stack.pop();
				postfix += ' ';
			}
			stack.push({ i });

		}
	}
	while (!stack.is_empty()) {
		postfix += stack.pop();
		postfix += ' ';
	}
	return postfix;
}

double TPostfix::Calculate()
{
	TStack<double> stack(100);
	stringstream ss(postfix);
	string token;

	while (ss >> token) {
		if (token == "sin") {
			double a = stack.pop();
			stack.push(sin(a));
		}
		else if (token == "cos") {
			double a = stack.pop();
			stack.push(cos(a));
		}
		else if (token == "tg") {
			double a = stack.pop();
			stack.push(tan(a));
		}
		else if (token == "ln") {
			double a = stack.pop();
			stack.push(log(a));
		}
		else if (token == "sqrt") {
			double a= stack.pop();
			stack.push(sqrt(a));
		}
		else if (isalpha(token[0])) {
			stack.push(vars.at(token[0]));
		}
		else if (isdigit(token[0])) {
			stack.push(stod(token));
		}
		
		else if (token == "+") {
			double a, b;
			a = stack.pop();
			b = stack.pop();
			stack.push(a + b);

		}
		else if (token == "-") {
			double a, b;
			a = stack.pop();
			b = stack.pop();
			stack.push(b - a);
		}
		else if (token == "*") {
			double a, b;
			a = stack.pop();
			b = stack.pop();
			stack.push(a * b);
		}
		else if (token == "/") {
			double a, b;
			a = stack.pop();
			b = stack.pop();
			stack.push(b / a);
		}
	}
	
	return stack.pop();
}
int GetPriority(string op) {
	if (op == "+" || op == "-") return 1;
	if (op == "*" || op == "/") return 2;
	if (op == "sin" || op == "cos" || op == "tg" || op == "ln" || op == "sqrt") return 3;
	return 0;
}