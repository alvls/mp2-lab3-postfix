#include <string>
#include "postfix.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	getline(cin, expression);
	TPostfix postfix(expression);
	if (!postfix.correct()) return cout << "Некорректное выражение!", 0;
	double res = 0.0;
	res = postfix.execute();
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	cout << "Значение выражения: " << res << endl;
	return 0;
}
