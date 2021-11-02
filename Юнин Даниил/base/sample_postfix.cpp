#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	//TPostfix test_class("asd+abs+234-3,124+(242-3)*(-2+5)");
	//test_class.ChangeInfixToPostfix();
	//double res = test_class.Calculate();
	//cout << res << endl;
	//try
	//{
	   // double value = stod(a1);
	   // cout << "Converted string to a value of " << value << endl;
	//}
	//catch (std::exception& e)
	//{
	   // cout << "Could not convert string to double" << endl;
	//}
	//(12-4-4-3)*(15-3-3-3-3)
	string expression;
	vector<string> v;
	double res;

	setlocale(LC_ALL, "Russian");
	cout << "Введите арифметическое выражение (вводите подряд и без пробелов, если вводите дробные числа, вводите через , ) : ";
	cin >> expression;
	TPostfix postfix(expression);
	cout << "Строка : " <<  expression << endl;
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	try
	{
		postfix.ChangeInfixToPostfix();
		v = postfix.GetPostfix();
		cout << "Постфиксная форма: " << endl;
		for (int i = 0; i < v.size(); i++) {
			cout << i + 1 << ")" << v[i] << endl;
		}
		res = postfix.Calculate();
		cout << res << endl;
	}
	catch (const char* exception)
	{
		cout << exception << endl;
	}
	

	return 0;
}
