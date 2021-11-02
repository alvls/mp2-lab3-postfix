#include <iostream>
#include <string>
#include "postfix.h"
#include "stack.h"

using namespace std;


int main()
{
  vector<double> values;
  string expression;
  TPostfix postfix;
  double value;
  double res;
  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  cin >> expression;
  postfix.set_infix(expression);
  cout << "Арифметическое выражение: " << postfix.get_infix() << endl;
  cout << "Постфиксная форма: " << postfix.get_postfix() << endl;
  cout << "Последовательно введите значения операндов. ЗНАЧЕНИЯ УЖЕ ИЗВЕСТНЫХ ОПЕРАНДОВ Т.Е. КОНСТАНТ, ВСЁ РАВНО ВВОДЯТСЯ." << endl;
  for (int i = 0; i < postfix.operands_counter(); i++) {
    cin >> value;
    values.push_back(value);
  }
  res = postfix.calculate(values);
  cout << "Результат: " << res << endl;
  return 0;
}
