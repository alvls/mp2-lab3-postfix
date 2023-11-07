#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	double res;

	setlocale(LC_ALL, "Russian");
	do
	{
		cout << endl << "Введите выражение (для выхода end): ";
		cin >> expression;
		if (expression == "end")
			break;
		try
		{
			TPostfix p(expression);
			cout << "Инфиксная форма: " << p.GetInfix() << endl;
			cout << "Постфиксная форма:" << p.GetPostfix() << endl;
			res = p.Calculate();	//Можно передать вектор значений всех операндов или считать их в методе (для консоли)
			cout << "Значение выражения: " << res << endl;
		}
		catch (const char* message)
		{
			cout << message;
		}
	} while (1);

	return 0;
}
