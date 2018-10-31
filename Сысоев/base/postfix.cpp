#include "postfix.h"
#include "stack.h"

string TPostfix::GetPostfix() {
	//если постфикс уже посчитан, то это не будет сделано еще раз
	if (postfix != "")
		return postfix;

	int count = -1;//счетчик операндов
	TStack<char> stack(infix.size());

	//проверка на оператор
	auto isOperator = [](char p) {
		return (p == '+' || p == '-' || p == '*' || p == '/' || p == '(' || p == ')');
	};

	//разделение переменных черточкой
	auto split = [&]() {
		postfix += '_';
	};

	//сравнение порядка
	auto orderCmp = [](char a, char b) {
		return (((a == '*' || a == '/') && (b == '+' || b == '-')) || b == '(');
	};

	for (char part : infix) {
		if (part == ' ')
			continue;

		if (!isOperator(part)) {
			postfix += part;
			continue;
		}

		switch (part) {
		case '(':

			stack.push_back(part);
			++count;
			break;

		case ')':

			split();
			while (stack.look_top() != '(') {
				postfix += stack.pop_back();
				--count;
			}
			stack.pop_back();
			--count;
			break;

		default:

			if (orderCmp(part, stack.look_top())) {
				stack.push_back(part);
				split();
				++count;
			}
			else {
				split();
				while (!stack.empty()) {
					if (stack.look_top() == '(') break;
					postfix += stack.pop_back();
					split();
					--count;
				}
				stack.push_back(part);
				++count;
			}
			break;

		}
	}
	while (count >= 0) {
		split();
		postfix += stack.pop_back();
		--count;
	}
	return postfix;
}

double TPostfix::Calculate() {
	TStack<double> stack(infix.size());
	string temp;

	//проверка на оператор
	auto isOperator = [](char p) {
		return (p == '+' || p == '-' || p == '*' || p == '/' || p == '(' || p == ')');
	};

	//функция пушит число в стак
	auto push = [&]() {
		if (!temp.empty()) {
			stack.push_back(stof(temp));
			temp.clear();
		}
	};

	for (char part : postfix) {
		if (part == '_') {
			push();
			continue;
		}
		if (!isOperator(part)) {
			temp += part;
			continue;
		}

		double a = stack.pop_back();
		double b = stack.pop_back();

		switch (part) {
		case '+':
			stack.push_back(b + a);
			break;
		case '-':
			stack.push_back(b - a);
			break;
		case '*':
			stack.push_back(b * a);
			break;
		case '/':
			if (b == 0)
				throw "Divide by zero";
			stack.push_back(a / b);
			break;
		}
	}
	return stack.pop_back();
}