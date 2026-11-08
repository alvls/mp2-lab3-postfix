#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  setlocale(LC_ALL, "Russian");
  cout << "Вычисление арифметических выражений" << endl;
  cout << "Можно использовать числа, переменные, операции + - * / ^, скобки" << endl;
  cout << "и функции sin, cos, sqrt, abs" << endl;
  cout << "Для выхода введите пустую строку" << endl;

  while (true)
  {
    string expression;
    cout << endl << "Введите арифметическое выражение: ";
    if (!getline(cin, expression) || expression.empty())
      break;
    try
    {
      TPostfix postfix(expression);
      cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
      vector<string> operands = postfix.GetOperands();
      for (size_t i = 0; i < operands.size(); i++)
      {
        double val;
        cout << operands[i] << " = ";
        while (!(cin >> val))
        {
          if (cin.eof())
            return 0;
          cin.clear();
          cin.ignore(10000, '\n');
          cout << "Нужно ввести число. " << operands[i] << " = ";
        }
        postfix.SetValue(operands[i], val);
      }
      if (!operands.empty())
        cin.ignore(10000, '\n');
      double res = postfix.Calculate();
      cout << "Результат: " << res << endl;
    }
    catch (exception &e)
    {
      cout << "Ошибка: " << e.what() << endl;
    }
  }
  return 0;
}
