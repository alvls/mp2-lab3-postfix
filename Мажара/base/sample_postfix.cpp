#include <iostream>
#include "postfix.h"
#include <string>;

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	cout << "Введите выражение(c переменными или константами): ";
	cin >> expression;
	TPostfix postfix(expression);
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	map<char, double> values = postfix.getOperands();
	for (auto& op : values)
	{
		if (isalpha(op.first))
		{
			string val;
			cout << "Введите значение для " << op.first << ": ";
			cin >> val;
			op.second = stod({ val });
		}
	}
	cout << "Реузльтат: " << postfix.Calculate(values) << endl;
	return 0;
}
