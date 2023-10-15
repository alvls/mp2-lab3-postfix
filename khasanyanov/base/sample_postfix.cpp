#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  TPostfix postfix("12+58*123+10-5*10");
  setlocale(LC_ALL, "Russian");
 // cout << "Введите арифметическое выражение: ";
  //cin >> expression;
  //cout << expression << endl;
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  cout << postfix.GetPostfix() << endl;
  //cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  cout << postfix.Calculate();

  return 0;
}
