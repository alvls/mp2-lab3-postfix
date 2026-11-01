#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  setlocale(LC_ALL, "Russian");
  
  string expression = "2+3*4"; 

  TPostfix postfix(expression);
  
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  
  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  
  double res = postfix.Calculate();
  cout << "Результат: " << res << endl;

  return 0;
}