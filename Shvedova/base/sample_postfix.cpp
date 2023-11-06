#include "postfix.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	cout << "Введите выражение: ";
	cin >> expression;
	TPostfix postfix(expression);
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	vector<char> operands = postfix.GetOperands();
	map<char, double> values;
	double val;
	for (const auto& op : operands)
	{
		cout << "Введите значение '" << op << "': ";
		cin >> val;
		values[op] = val;
	}
	cout << "Вычесленное значение выражения: " << postfix.Calculate(values) << endl;
	return 0;
}