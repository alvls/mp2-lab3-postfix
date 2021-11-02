#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  TPostfix postfix;
  double res;
  vector<string> postFix;

  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  getline(cin,expression);
  //cout << expression << endl;
  postfix.SetInfix(expression);
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  postFix = postfix.GetPostfix();
  //cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  cout << "Постфиксная форма: " << endl;
  for (size_t i = 0; i < postFix.size(); i++)
  {
	  cout <<postFix[i] + " ";
  }
  cout << endl;
  cout << "Результат: ";
  try
  {
	  res = postfix.Calculate();
  }
  catch (int i)
  {
	  cout << i << endl;
  }
  cout << res << endl;

  return 0;
}
