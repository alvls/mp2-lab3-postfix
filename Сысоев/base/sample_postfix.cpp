#include <iostream>
#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	double res;

	//setlocale(LC_ALL, "Russian");
	cout << "Enter arithmetic expression: ";
	cin >> expression;
	TPostfix postfix(expression);
	//cout << expression << endl;
	cout << "Arithmetic expression: " << postfix.GetInfix() << endl;
	postfix.ToPostfix();
	cout << "Postfix form: " << postfix.GetPostfix() << endl;
	res = postfix.Calculate();
	cout << "Calculation result: " << res << endl;
	system("pause");
	// cout << res << endl;


	return 0;
}