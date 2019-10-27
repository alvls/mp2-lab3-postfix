#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  double res;

  setlocale(LC_ALL, "Russian");

  cout << "Введите арифметическое выражение: ";
  cin >> expression;
  TPostfix postfix(expression);

  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  double* value;
  int Count = postfix.CountVal();
  value = new double[Count];
  for (int i = 0; i < Count; i++) 
  {
	  cin >> value[i];
  }
  res = postfix.Calculate(value);
  cout << res << endl;
  return 0;
}
