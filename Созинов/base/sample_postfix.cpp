#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	double res;

	setlocale(LC_ALL, "Russian");
	cout << "Введите арифметическое выражение: ";
	getline(cin, expression);
	cout << expression << endl;
	TPostfix postfix(expression);		
	string s = postfix.CheckOnCorrect();
	cout << s << endl;
	if (s == "All good")
	{
		postfix.ToPostfix();
		cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
		cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
		res = postfix.Calculate();
		cout << res << endl;
	}
	return 0;
}
