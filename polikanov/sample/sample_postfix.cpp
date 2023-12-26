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
	setlocale(LC_ALL, "Russian");
	int exit = 1;


	while (exit != 0) {

		cout << "  Поддерживаемые операции:\n" << "sqrt(), sin(), cos(), *, /, +, -, скобки" << "\n\n  ";

		try {
			string expression;
			cout << "Введите арифметическое выражение: ";
			getline(cin, expression);
			TPostfix postfix(expression);
			cout << "\nарифметическое выражение::\n" << postfix.GetStringInfix() << endl;
			cout << "\nпостфиксная форма:\n" << postfix.GetStringPostfix() << endl;

			double res = postfix.Calculate();
			cout << "\nРезультат:\n" << res << endl;

			cout << "\nПродолжить?\n1 - Да\n0 - Нет\n";
			cin >> exit;
			clean();
			system("cls");

		}
		catch (string exc) {
			cout << '\n' << exc << '\n';
		}
	}
	system("PAUSE");
	return 0; 
}