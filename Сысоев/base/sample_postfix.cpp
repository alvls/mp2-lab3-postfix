#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  cout << "Введите выражение\n";
  cin >> expression;
  TPostfix postfix(expression);
  double res;
  setlocale(LC_ALL, "Russian");
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  res = postfix.Calculate();
  cout << res << endl;
  return 0;
}
