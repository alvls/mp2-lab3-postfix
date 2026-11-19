#include <iostream>
#include <string>
#include <stdexcept>
#include "postfix.h"

int main()
{
  std::cout << "Arithmetic expression calculator (type 'exit' to quit)\n";
  std::cout << "Operators: +, -, *, /, ^; parentheses and variables are supported.\n";

  std::string expression;
  while (true)
  {
    std::cout << "Expression: ";
    if (!std::getline(std::cin, expression) || expression == "exit") break;
    if (expression.empty()) continue;

    try
    {
      TPostfix calculator(expression);
      std::cout << "Postfix: " << calculator.ToPostfix() << '\n';
      std::cout << "Result: " << calculator.Calculate() << '\n';
    }
    catch (const std::exception& error)
    {
      std::cout << "Error: " << error.what() << '\n';
    }

    if (!std::cin.good() && !std::cin.eof()) std::cin.clear();
    // After formatted variable input, consume the rest of the line.
    if (std::cin.peek() == '\n') std::cin.get();
  }
  return 0;
}
