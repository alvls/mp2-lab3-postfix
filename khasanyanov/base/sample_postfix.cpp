#include <iostream>
#include <string>
#include "postfix.h"
#include <windows.h>
using namespace std;


int main()
{
  HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN | 0);
  string expression;
  setlocale(LC_ALL, "ru");
  setlocale(LC_NUMERIC, "en");
  system("title Калькулятор Обратной Польской Записи");
  cout << "Введите арифметическое выражение: ";
  getline(cin, expression);
  try {
	  TPostfix {expression};
  }
  catch (invalid_argument) {
	  SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | 0);
	  cout << "Неверное выражение" << endl;
	  exit(0);
  }
  TPostfix postfix(expression);
  auto m = postfix.getOperands();
  for (auto& op : m)
  {
	  if (isalpha(op.first[0]))
	  {
		  string val;
		  cout << "Введите значение для " << op.first << ": ";
		  cin >> val;
		  op.second = stod(val);
	  }
  }
  cout << "Арифметическое выражение: " << postfix.getInfix() << endl;
  cout << "Постфиксная форма: " << postfix.getPostfix() << endl;
  try {
	  cout << "Рассчитанное значение: " << postfix.calculate(m) << endl;
  }
  catch (logic_error) {
	  SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | 0);
	  cout << "Неверное выражение" << endl;
	  exit(0);
  }
  return 0;
}
