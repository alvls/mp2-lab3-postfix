#include <iostream>
#include <string>
#include "postfix.h"
#include <cctype>

using namespace std;

int main()
{
	system("title Calculation of arithmetic expressions using Reverse Polish notation");

	string expression;

	cout << "Enter arithmetic expression: ";
	getline(cin, expression);
	cout << endl;

	TPostfix expr(expression);

	cout << "Arithmetic expression: " << expr.GetInfix() << endl << endl;

	cout << "Postfix form: "; // << expr.GetPostfix() << endl;
	const auto& postfix = expr.GetPostfix();
	for (auto& symbol : postfix)
	{
		if (symbol.empty())
			continue;
		cout << symbol << ' ';
	}
	cout << endl << endl;

	vector<string> operands = expr.GetOperands();
	map<string, double> values;

	double num;
	for (const auto& op : operands)
	{
		cout << "Enter value of " << op << ": ";
		cin >> num;
		cout << endl;

		values[op] = num;
	}

	cout << "The result of calculation is: " << expr.Calculate(values) << endl;

	return 0;
}
