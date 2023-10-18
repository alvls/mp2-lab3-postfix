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
  setlocale(LC_ALL, "Russian");
  system("title Калькулятор Обратной Польской Записи");
  cout << "Введите арифметическое выражение: ";
  cin >> expression;
  TPostfix postfix(expression);
  cout << "Арифметическое выражение: " << postfix.getInfix() << endl;
  cout << "Постфиксная форма: " << postfix.getPostfix() << endl;
  cout << "Рассчитанное значение: " << postfix.calculate() << endl;
  return 0;
}
