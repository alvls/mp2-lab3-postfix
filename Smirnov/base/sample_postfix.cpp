#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

void PrintRulesInput()
{
	cout << "О вводе:" << endl;
	cout << "1) Вводите операнды через пробел, пример: 3 + 5, исключение: унарный минус, в этом случае вводите без пробела: -3" << endl;
	cout << "2) Угловые скобки всегда через пробел" << endl;
	cout << "3) Аргумент функции вводится через пробел, пример: sin ( 30 )" << endl;
	cout << "4) Если ввести операнд без пробела или скобок, то данный операнд будет считаться переменной, пример: sinx - будет считаться переменной" << endl;
	cout << "Пример правильной записи: 2 ^ 2 * sin ( 30 ) / sqrt ( 4 )" << endl;
	cout << endl;
}

void PrintExample()
{
	string expression = "2 ^ 2 * sin ( 30 ) / sqrt ( 4 )";
	cout << "Арифметическое выражение: " + expression << endl;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	cout << "Постфикс: ";
	postfix.PrintPostfix();
	cout << endl;
	double result = postfix.Calculate();
	cout << "Результат: " << result << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	TPostfix postfix;
	double res;
	bool exit = false;
	PrintRulesInput();
	PrintExample();
	while (!exit)
	{
		cout << "Введите арифметическое выражение: ";
		getline(cin, expression);
		cout << expression << endl;
		postfix.SetInfix(expression);
		cin.clear();
		cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
		try
		{
			postfix.ToPostfix();
			cout << "Постфиксная форма: " << endl;
			postfix.PrintPostfix();
			cout << endl;
			cout << "Результат: ";
			res = postfix.Calculate();
		}
		catch (const string& str)
		{
			cout << str << endl;
			continue;
		}
		exit = true;
	}
	cout << res << endl;
	return 0;
}
