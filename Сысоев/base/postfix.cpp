#include "postfix.h"
#include "stack.h"
#include <string>

using namespace std;

bool TPostfix::IsOperator(char op){
	if (op == '+' || op == '-' || op == '*' || op == '/')
		return true;
	else
		return false;
}

int TPostfix::Priority(char a, char b){
	if ((a == '*' || a == '/') && (b == '*' || b == '/'))
		return 0;
	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
		return 1;
	if ((a == '+' || a == '-') && (b == '*' || b == '/'))
		return -1;
	if ((a == '+' || a == '-') && (b == '+' || b == '-'))
		return 0;
	throw "not operation";
}

double TPostfix::Operation(double left, double right, char c){
	switch (c){
	case '+':{
		return left + right;
	}
	case '-':{
		return left - right;
	}
	case '*':{
		return left * right;
	}
	case '/':{
		if (right == 0)
			throw 0;
		return left / right;
	}
	default:
		throw "invalid operation";
	}
}

bool TPostfix::CheckInfix(){
	if (infix.empty())
		return false;
	else
		if (IsOperator(infix[0]) || IsOperator(infix[infix.size() - 1]))
			return false;
	for (int i = 0; i < infix.size() - 1; i++){
		if (IsOperator(infix[i]) && IsOperator(infix[i + 1]))
			return false;
	}
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	for (int i = 0; i < infix.size(); i++){
		if (infix[i] == ' ')
			return false;
		if (infix[i] == '(')
			count1++;
		if (infix[i] == ')')
			count2++;
		if (IsOperator(infix[i]))
			count3++;
	}
	if ((count1 != count2) || count3 == 0)
		return false;
	return true;
}

string TPostfix::ToPostfix(){
	stack<char> opers(infix.size());
	for (int i = 0; i < infix.size(); i++){
		if (!IsOperator(infix[i]) && infix[i] != '(' && infix[i] != ')'){
			int j = i;
			while (!IsOperator(infix[j]) && j != infix.size() && infix[j] != ')'){
				postfix += infix[j];
				j++;
			}
			i = j - 1;
			postfix += ',';
		}
		else
			if (opers.empty())
				opers.push(infix[i]);
			else
				if (opers.onthetop() == '(')
					opers.push(infix[i]);
				else
					if (infix[i] == '(')
						opers.push(infix[i]);
					else
						if (infix[i] == ')'){
							while (opers.onthetop() != '('){
								postfix += opers.pop();
								postfix += ',';
							}
							opers.pop();
						}
						else
							if (Priority(infix[i], opers.onthetop()) == 1)
								opers.push(infix[i]);
							else{
								while ((opers.onthetop() != '(')){
									if (Priority(infix[i], opers.onthetop()) == 1)
										break;
									postfix += opers.pop();
									postfix += ',';
									if (opers.empty())
										break;
								}
								opers.push(infix[i]);
							}
	}
	while (!opers.empty()){
		postfix += opers.pop();
		postfix += ',';
	}
	return postfix;
}

double TPostfix::Calculate(){
	ToPostfix();
	stack<double> nums(infix.size());
	for (int i = 0; i < postfix.size(); i++){
		if (!IsOperator(postfix[i])){
			string doub;
			doub += postfix[i];
			int j = i + 1;
			while (postfix[j] != ','){
				doub += postfix[j];
				j++;
			}
			nums.push(atof(doub.c_str()));
			i = j;
		}
		else{
			nums.push(Operation(nums.pop(), nums.pop(), postfix[i]));
			i++;
		}
	}
	return nums.onthetop();
}
