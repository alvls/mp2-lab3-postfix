#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	cout << "Введите выражение без пробелов: ";
	cin >> expression;
	TPostfix expr(expression);
	cout << "Арифметическое выражение: " << expr.GetInfix() << endl;
	const auto postfix = expr.GetPostfix();
	for (const auto& lexem : postfix)
	{
		cout << lexem << ' ';
	}
	cout << endl;
	//cout << "Постфиксная форма: " << expr.GetPostfix() << endl;
	vector<string> operands = expr.GetOperands();
	map<string, double> values;
	double val;
	for (const auto& op : operands)
	{
		try {
			double val = stod(op);
			values[op] = val;
		}
		catch(...){
			cout << "Введите значение " << op << ": ";
			cin >> val;
			values[op] = val;
		}
	}
	cout << "Результат: " << expr.Calculate(values) << endl;
	return 0;
}
