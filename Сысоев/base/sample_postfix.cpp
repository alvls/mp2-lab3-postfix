#include <iostream>
#include <string>
#include "postfix.h"
#include <conio.h>
#include <locale>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	bool repeat;
	char c;
	do 
	{
		try
		{
			string expression;
			cout << "Введите выражение без пробелов и знака равенства. В конце введите Enter\n";
			c = getchar();
			while (c != '\n')
			{
				expression.push_back(c);
				c = getchar();
			}
			TPostfix postfix(expression);
			double res;
			setlocale(LC_ALL, "Russian");
			cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
			postfix.ToPostfix();
			cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
			res = postfix.Calculate();
			cout << res << endl;
			repeat = false;
		}
		catch (wrong a)
		{
			switch (a)
			{
			case wrong::brackets_quantity:
				cout << "Неправильное количество скобок\n";
				break;
			case wrong::operation_placement:
				cout << "Расположение одной или нескольких операций неверно\n";
				break;
			}
			cout << "Если хотите ввести заново, нажмите Enter, иначе введите любой другой символ\n";
			c = _getch();
			switch (c)
			{
			case '\r':
				repeat = true;
				break;
			default:
				repeat = false;
				break;
			}
		}
	} while (repeat);
  return 0;
}
