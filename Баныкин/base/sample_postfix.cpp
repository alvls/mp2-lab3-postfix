#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main() {
	TPostfix postfix;
	postfix.Set("22 + 14.14 * (11 - 4) - 100 + (101 - (25 - 24)) + 1.6");

	cout << "Infix: " << postfix.GetInfix() << endl;
	postfix.GetPostfix();
	cout << "Postfix: " << postfix.GetPostfix() << endl;
	cout << "Result: " << postfix.Calculate() << endl;
	return 0;
}