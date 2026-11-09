#include <clocale>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include "postfix.h"

using namespace std;

static void PrintHelp()
{
  cout << "В выражении можно использовать:\n"
       << "  числа: 7, 0.25;\n"
       << "  переменные: a, x1, speed (латинские буквы, цифры, '_');\n"
       << "  операции: + - * / ^ (степень), унарные + и -;\n"
       << "  скобки и функции sin, cos, tg, ln, exp, sqrt, abs.\n"
       << "Пример: (a + b * 2) / sqrt(c) - x ^ 2\n";
}

static void ShowSyntaxError(const string& expression, const TSyntaxError& error)
{
  cout << "Ошибка в выражении: " << error.what() << endl;
  cout << "  " << expression << endl;
  cout << "  " << string(error.GetPosition(), ' ') << "^" << endl;
}

static bool ParseNumber(string text, double& result)
{
  const size_t first = text.find_first_not_of(" \t");
  if (first == string::npos)
    return false;
  const size_t last = text.find_last_not_of(" \t\r");
  text = text.substr(first, last - first + 1);

  const char separator = *localeconv()->decimal_point;
  for (size_t i = 0; i < text.size(); i++)
    if (text[i] == '.' || text[i] == ',')
      text[i] = separator;

  char* end = nullptr;
  result = strtod(text.c_str(), &end);
  return end != text.c_str() && *end == '\0' && std::isfinite(result);
}

static bool AskValue(const string& name, double& value)
{
  while (true)
  {
    cout << "  " << name << " = ";
    string line;
    if (!getline(cin, line))
      return false;
    if (ParseNumber(line, value))
      return true;
    cout << "  Это не число, попробуйте ещё раз." << endl;
  }
}

static void EnterExpression(TPostfix& expression)
{
  cout << "Введите выражение: ";
  string line;
  if (!getline(cin, line))
    return;
  try
  {
    expression.SetInfix(line);
    cout << "Выражение принято." << endl;
  }
  catch (const TSyntaxError& error)
  {
    ShowSyntaxError(line, error);
    cout << "Оставлено прежнее выражение." << endl;
  }
}

static void Evaluate(const TPostfix& expression)
{
  const vector<string> names = expression.GetVariables();
  map<string, double> values;
  if (!names.empty())
    cout << "Значения переменных:" << endl;
  for (size_t i = 0; i < names.size(); i++)
  {
    double value;
    if (!AskValue(names[i], value))
      return;
    values[names[i]] = value;
  }
  try
  {
    const double result = expression.Calculate(values);
    cout << expression.GetInfix() << " = " << setprecision(12) << result << endl;
  }
  catch (const exception& error)
  {
    cout << "Ошибка при вычислении: " << error.what() << endl;
  }
}

int main()
{
  setlocale(LC_ALL, "Russian");

  cout << "Вычисление арифметических выражений через постфиксную форму" << endl;
  PrintHelp();

  TPostfix expression;
  while (true)
  {
    cout << endl
         << "Выражение:         " << expression.GetInfix() << endl
         << "Постфиксная форма: " << expression.GetPostfix() << endl
         << "1 - новое выражение, 2 - вычислить, 3 - справка, 0 - выход" << endl
         << "> ";
    string choice;
    if (!getline(cin, choice))
      break;

    if (choice == "1")
      EnterExpression(expression);
    else if (choice == "2")
      Evaluate(expression);
    else if (choice == "3")
      PrintHelp();
    else if (choice == "0")
      break;
    else
      cout << "Нет такого пункта меню." << endl;
  }
  return 0;
}
