#include <iostream>
#include <string>
#include "postfix.h"
#include "operations.h"

using namespace std;

void clean() {
	while (getchar() != '\n');
	cin.clear();
}

int main() {
	int exit = 1;
	while (exit != 2) {
		cout << "Supported operations:\n" << "sqrt(), sin(), cos(), *, /, +, -, (, )" << "\n\n";
		try {
			string expression;
			cout << "Enter an arithmetic expression: ";
			getline(cin, expression);
			TPostfix postfix(expression);
			cout << "\nArithmetic expression:\n" << postfix.GetStringInfix() << endl;
			cout << "\nPostfix form:\n" << postfix.GetStringPostfix() << endl;

			double res = postfix.Calculate();
			cout << "\nResult:\n" << res << endl;

			cout << "\nContinue?\n1 - Yes\n2 - No\n";
			cin >> exit;
			clean();
			system("cls");
		} catch (string exc) {
			cout << '\n' << exc << '\n';
		}
	}
	system("pause");
	return 0;
}
