#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{

	string expression;
	cout << "Enter expression: ";
	cin >> expression;
	TPostfix postfix(expression);
	cout << expression << endl;
	cout << "Expression: " << postfix.GetInfix() << endl;
	postfix.ToPostfix();
	cout << "Posfix form: " << postfix.GetPostfix() << endl;
	cout << postfix.Calculate() << endl;

	return 0;
	
}
