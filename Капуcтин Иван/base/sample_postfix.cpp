#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	map<char, double> values;
	double val;
	cout << "Введите выражение(c переменными или константами): ";
	cin >> expression;
	TPostfix postfix(expression);
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	vector<char> operands = postfix.GetOperands();
	for (const auto& op : operands)
	{
		cout << "Введите значение переменных или подтвердите значение констант '" << op << "': ";
		cin >> val;
		values[op] = val;
	}
	cout << "Реузльтат: " << postfix.Calculate(values) << endl;
	return 0;
}
