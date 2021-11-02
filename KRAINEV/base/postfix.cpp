#include "postfix.h"
#include "stack.h"
#include <iostream>
#include <cstdlib> 
using namespace std;

int TPostfix::Priority(char val){
	if ((val == '*') || (val == '/')) { return 2; } //highest priority for + or - operator
	else if ((val == '+') || (val == '-')) { return 1; } //lowest priority among operators
	return 0;//works for operands
}

size_t TPostfix::checkStringIsANumber(string inString) {
	unsigned int flag = inString.find_first_not_of("0123456789");
	return flag;
}

char TPostfix::getEndOfString() { return '\0'; } //return '\0'

string TPostfix::ToPostfix(){
	char result[MaxStackSize]; // MaxStackSize const from stack.h
	unsigned int resultPosition = 0;
	TStack<char> stack_(MaxStackSize);// MaxStackSize const from stack.h

	for (unsigned int i = 0; i < infix.length(); i++) {
		if ((infix[i] != '(') && (infix[i] != ')') && (infix[i] != '+') &&
								 (infix[i] != '-') && (infix[i] != '*') && (infix[i] != '/')){
			result[resultPosition] = infix[i];
			resultPosition++;
			result[resultPosition] = getEndOfString();
		}
		
		if (infix[i] == '(') { stack_.Put(infix[i]); }	
		
		if (infix[i] == ')'){
			while (stack_.Get() != '('){
				result[resultPosition] = ' ';
				resultPosition++;
				result[resultPosition] = stack_.Pop();
				resultPosition++;
				result[resultPosition] = getEndOfString();
			}
			stack_.Pop();
		}

		if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/')) {

			result[resultPosition] = ' ';
			resultPosition++;
			

			if (stack_.IsEmpty() || stack_.Get() == '(') { stack_.Put(infix[i]); }
				
			else if (Priority(infix[i]) > Priority(stack_.Get())) { stack_.Put(infix[i]); }

			else{
				while (!stack_.IsEmpty() && Priority(infix[i]) <= Priority(stack_.Get())){
					result[resultPosition] = stack_.Pop();
					resultPosition++;
					result[resultPosition] = getEndOfString();
				}

				result[resultPosition] = ' ';
				resultPosition++;
				stack_.Put(infix[i]); //new operation on the stack
			}
		}

	}
	while (stack_.IsEmpty() == 0){
		result[resultPosition] = ' ';
		resultPosition++;
		result[resultPosition] = stack_.Pop();
		resultPosition++;
		result[resultPosition] = getEndOfString();
	}
	postfix = result;
	return postfix;
};

double TPostfix::Calculate(){
	double storageOfOperands[MaxStackSize];// MaxStackSize const from stack.h
	string intermediateResult;//промежуточный результат
	double variableValues;
	int j = 0;

	TStack<double> stack(MaxStackSize);

	for (int i = 0; i < postfix.length(); i++){
		if ((postfix[i] != '+') && (postfix[i] != '-') && (postfix[i] != '*') && (postfix[i] != '/')){
			if (postfix[i] != ' ') { intermediateResult = intermediateResult + postfix[i]; }
			if ((postfix[i] == ' ') && (postfix[i-1] != '+') && 
									   (postfix[i-1] != '-') && (postfix[i-1] != '*') && (postfix[i-1] != '/')){

				size_t flag = checkStringIsANumber(intermediateResult);
				if ((flag == std::string::npos) && (postfix[i] == ' ')) {
					storageOfOperands[j] = stoi(intermediateResult); // string to int 
				}
				else {
					cout << postfix[i - 1] << "=";
					cin >> variableValues;
					storageOfOperands[j] = variableValues;
				}
				stack.Put((double)storageOfOperands[j]);
				intermediateResult = "";
				j++;
			}
		}
		else { 
			double tmp1 = stack.Pop();
			double tmp2 = stack.Pop();
			if (postfix[i] == '+') { stack.Put(tmp2 + tmp1); } //addition
			if (postfix[i] == '-') { stack.Put(tmp2 - tmp1); } //subtraction
			if (postfix[i] == '/') { stack.Put(tmp2 / tmp1); } //division
			if (postfix[i] == '*') { stack.Put(tmp2 * tmp1); } //multiplication
		}
	}
	return stack.Pop();
};



