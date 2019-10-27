#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	double res;

	setlocale(LC_ALL, "Russian");
	bool F = false;
	do
	{
		cout << "Введите арифметическое выражение: ";
		getline(cin, expression);
		cout << expression << endl;
		TPostfix postfix(expression);
		
		/*switch (postfix.CheckOnCorrect())
		{
		case 1:
			cout << "first symbol is operator!";
			break;
		case 2:
			cout << "last symbol is operator!";
			break;
		case 3:
			cout << "Uncorrect input parentheses!";
			break;
		case 4:
			cout << "Operand after close parentheses!";
			break;
		case 5:
			cout << "Operand before open parenthess!";
			break;
		case 6:
			cout << "Operator after open parentheses!";
			break;
		case 7:
			cout << "Operator before close parenthess!";
			break;
		case 8:
			cout << "Two or more operators in a row!";
			break;
		case 0:
			cout << "All good";
			break;
		default:
			break;
		}*/
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
		if (postfix.GetInfix() == "00")
			F = true;
	} while (F == false);
	return 0;
}
