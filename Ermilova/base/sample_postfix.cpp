#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	cout << "Введите выражение: ";
	cin >> expression;
	TPostfix expr(expression);
	cout << "Арифметическое выражение: " << expr.GetInfix() << endl;
	cout << "Постфиксная форма: " << expr.GetPostfix() << endl;
	vector<char> operands = expr.GetOperands();
	map<char, double> values;
	double val;
	for (const auto& op : operands)
	{
		cout << "Введите значение " << op << ": ";
		cin >> val;
		values[op] = val;
	}
	cout << "Результат: " << expr.Calculate(values) << endl;
	return 0;
}
