#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main(){
	TPostfix postfix("22 + 14 * (11 - 4) - 100 + (101 - (25 - 24)) + 1");

	setlocale(LC_ALL, "Russian");
	//cout << "Введите арифметическое выражение: ";
	//cin >> expression;
	//cout << expression << endl;
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	postfix.GetPostfix();
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	cout << "Результат: " << postfix.Calculate() << endl;
	return 0;
}