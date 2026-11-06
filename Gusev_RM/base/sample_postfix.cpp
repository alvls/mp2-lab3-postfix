#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  double res;
  setlocale(LC_ALL, "Russian");
  expression = "a +b+c*(a+b+c)/a+sin(a*b+34,28)+cos(a*b)+tg(a*c)-sqrt(64)+ln(45) + D-1.000001";
  cout << "Введите арифметическое выражение: " << endl;
  getline(cin, expression);
  TPostfix postfix(expression);
  postfix.SetVariable('a', 5);
  postfix.SetVariable('b', 10);
  postfix.SetVariable('c', 15);
  postfix.SetVariable('D', 20);
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  res = postfix.Calculate();
  cout << "Результат: " << res << endl;

  return 0;
}
