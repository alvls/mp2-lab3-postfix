#include <iostream>
#include <string>
#include "postfix.h"
#include<vector>
using namespace std;

int main()
{
  string expression;
  map<string, double>date;
  double res=0;
  char name;
  double values;
  string tmp ="";
  setlocale(LC_ALL, "Russian");
  cout << "Enter arithmetic expression";
  cin >> expression;
  TPostfix postfix(expression);
  vector<string> operands = postfix.GetOperands();
  cout << "Postfix form: " << postfix.GetPostfix() << endl;
  for (const auto& op : operands) {
      try {
          int values = std::stoi(op);
          date[op] = values;
      }
      catch (std::invalid_argument const& e) {
          cout << "Enter value of " << op << ": ";
          cin >> values;
          date[op] = values;
      }
   } 
  
  res = postfix.Calculate(date);
  cout << res << endl;
  return 0;
}
