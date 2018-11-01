﻿#include "postfix.h"
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
		return ((a == '*' || a == '/') && (b == '+' || b == '-'));
	};

	auto eqCmp = [](char a, char b) {
		if ((a == '*' || a == '/') && (b == '*' || b == '/'))
			return true;
		if ((a == '-' || a == '+') && (b == '-' || b == '+'))
			return true;
		return false;
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

			split();
			if (orderCmp(part, stack.look_top())) {
				stack.push_back(part);
				break;
			}
			else if (eqCmp(part, stack.look_top())) {
				postfix += stack.pop_back();
				stack.push_back(part);
				++count;
				split();
				break;
			}
			while (!stack.empty()) {
				if (stack.look_top() == '(') break;
				postfix += stack.pop_back();
				split();
				--count;
			}
			stack.push_back(part);
			++count;
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
	if (postfix == "")
		GetPostfix();

	TStack<double> stack(infix.size());
	string temp;

	//проверка на оператор
	auto isOperator = [](char p) {
		return (p == '+' || p == '-' || p == '*' || p == '/' || p == '(' || p == ')');
	};

	//функция пушит число в стак
	auto push = [&stack](string &temp) {
		if (!temp.empty()) {
			//проверка на число
			for (auto i : temp)
				if (!isdigit(i) && i != '.')
					throw "Incorrect expression";

			stack.push_back(atof(temp.c_str()));
			temp.clear();
		}
	};

	for (char part : postfix) {
		if (part == '_') {
			push(temp);
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
			if (a == 0)
				throw "Divide by zero";
			stack.push_back(b / a);
			break;
		}
	}
	return stack.pop_back();
}