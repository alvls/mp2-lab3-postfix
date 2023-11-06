#include <iostream>
#include <string>
#include "postfix.h"
#include <cctype>

using namespace std;

bool parse_double(string in, double& res)
{
	try
	{
		size_t read = 0;
		res = stod(in, &read);
		if (in.size() != read) 
			return false;
	}
	catch (invalid_argument)
	{
		return false;
	}
	return true;
}

int main()
{
	system("title Calculation of arithmetic expressions using Reverse Polish notation");

	string expression;

	cout << "Enter arithmetic expression: ";
	cin >> expression;
	cout << endl;

	TPostfix expr(expression);

	cout << "Arithmetic expression: " << expr.GetInfix() << endl << endl;

	cout << "Postfix form: "; // << expr.GetPostfix() << endl;
	const auto& postfix = expr.GetPostfix();
	for (auto& p : postfix)
	{
		if (p.empty()) 
			continue;
		cout << p << ' ';
	}
	cout << endl << endl;

	vector<string> operands = expr.GetOperands();
	map<string, double> values;

	double num;
	for (const auto& op : operands)
	{
		if (!parse_double(op, num))
		{
			cout << "Enter value of " << op << ": ";
			cin >> num;
			cout << endl;
		}
		values[op] = num;
		//cout << "Enter value of " << op << ": ";
		//cin >> value;
		//values[op] = value;
	}

	cout << "The result of calculation is: " << expr.Calculate(values) << endl;

	return 0;
}
