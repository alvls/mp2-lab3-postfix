#include <iostream>
#include <string>
#include "postfix.h"

int main()
{
  setlocale(LC_ALL, "Russian");
  std::string expression;
  TPostfix postfix;
  double res;

  // Запрос выражения у пользователя
  std::cout << "Введите арифметическое выражение: ";
  std::cin >> expression;
  // Создание объекта с введенным выражением
  postfix = TPostfix(expression);

  // Вывод инфиксного выражения
  std::cout << "Инфиксное выражение: " << postfix.GetInfix() << std::endl;
  // Преобразование в постфиксную форму и вывод
  postfix.ToPostfix();
  std::cout << "Постфиксная форма: " << postfix.GetPostfix() << std::endl;

  // Запрос значений переменных
  postfix.ReadVariables();

  // Вычисление выражения и вывод результата
  try {
    res = postfix.Calculate();
    std::cout << "Результат: " << res << std::endl;
  }
  catch (const char* msg) {
    std::cerr << "Ошибка: " << msg << std::endl;
  }

  return 0;
}
