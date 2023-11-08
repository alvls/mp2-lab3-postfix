#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  map<char, double>date;
  double res=0;
  char name;
  double values;
  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  cin >> expression;
  TPostfix postfix(expression);
  cout << expression << endl;
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  cout << expression << endl;
  for (int i = 0; i < postfix.GetNumberOperands(); i++) {
	  cout << "Введите название переменной и ее значение" << endl;
	  cin >> name;
	  cin >> values;
	  date.insert(std::pair<char, double > (name, values));
  }
  res = postfix.Calculate(date);
  cout << res << endl;
  return 0;
}
