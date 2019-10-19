#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  TPostfix postfix;
  double res;

  setlocale(LC_ALL, "Russian");

  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

  double* val;
  int Count = postfix.CountNum();
  val = new double[Count];

  for (int i = 0; i < Count; i++) {
	  cin >> val[i];
  }

  res = postfix.Calculate(val);
  cout << res << endl;

  return 0;
}
