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
  cout << "Enter arithmetic expression";
  cin >> expression;
  TPostfix postfix(expression);
  cout << "Postfix form: " << postfix.GetPostfix() << endl;
  for (int i = 0; i < postfix.GetNumberOperands(); i++) {
	  cout << "Enter name and value" << endl;
	  cin >> name;
	  cin >> values;
	  date.insert(std::pair<char, double > (name, values));
  }
  res = postfix.Calculate(date);
  cout << res << endl;
  return 0;
}
