#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	cout << "Введите арифметическое выражение: ";
	cin >> expression;

	TPostfix postfix(expression);
	double res;

	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

	map<char, double> variables;
	variables['a'] = 5.0;
	variables['b'] = 10.0;

	postfix.SetVariables(variables); 
	res = postfix.Calculate();
	cout << "Результат: " << res << endl;

	return 0;
}
