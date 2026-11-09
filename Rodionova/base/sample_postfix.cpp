#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;

  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  cin >> expression; 
  cout << endl;

  TPostfix postfix(expression);

  cout << "Исходное выражение: " << postfix.GetInfix() << endl;

  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

  double res = postfix.Calculate();
  cout << "Результат: " << res << endl;

  return 0;
}
