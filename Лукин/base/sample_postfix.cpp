#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	double res;
	cout << "Введите выраженние для вычисления, проверив его правильность." << endl;
	cout << "Позже вам нужно будет ввести значение для операндов." << endl;
	getline(cin, expression);//чтобы пробелы поддерживались
	//string tmp;
	//for (;cin >> tmp;)
	//	expression += tmp;// так почему-то не работает(expression была инициализирована пустой строкой) upd: понял почему не работает, как доработать этот вариант - не понимаю
	TPostfix postfix(expression);
	cout << "Инфиксная форма: " << postfix.GetInfix() << endl;
	cout << "Постфиксная форма: ";
	for (const auto& lex : postfix.GetPostfix())
		cout << lex;
	cout << endl;
	vector<string> operands = postfix.GetOperands();
	map<string, double> values;
	double val;
	for (const auto& op : operands)
	{
		try
		{
			val = stod(op);//если не получилось string -> double - исключение(операнд буквенный), уже в обработке вводим значение
			values[op] = val;
		}
		catch (...)
		{
			cout << "Введите значение для операнда " << op << ": ";
			cin >> val;
			values[op] = val;
		}
	}
	cout << "Вычисленное значение: ";
	cout << postfix.Calculate(values) << endl;
	return 0;
}
