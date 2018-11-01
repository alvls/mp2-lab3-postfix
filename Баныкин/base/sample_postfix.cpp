#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main() {
	TPostfix postfix;
	postfix.Set("1 + 2 * 3 / 4 - 5");

	cout << "Infix: " << postfix.GetInfix() << endl;
	postfix.GetPostfix();
	cout << "Postfix: " << postfix.GetPostfix() << endl;
	cout << "Result: " << postfix.Calculate() << endl;
	return 0;
}