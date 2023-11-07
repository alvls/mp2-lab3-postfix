#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main() {

   string expression;
   double res;

   setlocale(LC_ALL, "Russian");

   cout << "Введите выражение( например: (a*b)+c ): ";
   cin >> expression;

   TPostfix calculator(expression);

   cout << "Выражение в постфиксной форме: " << calculator.GetPostfix() << endl;

   calculator.PromptAndStoreVariables();

   res = calculator.Calculate();
   cout << "Результат: " << res << endl;

   return 0;
}
