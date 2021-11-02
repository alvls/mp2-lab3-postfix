#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include "stack.h"


class TPostfix
{
  std::string infix;
  std::vector<std::string> postfix;
private:
  std::vector<std::string> infix_divide();
  std::vector<std::string> to_postfix();
  std::string postfix_to_string();
  bool correct_input_check();
public:
  TPostfix(std::string _infix = "") : infix(_infix)
  {
    if (!correct_input_check())
      throw "incorrect input.";
    postfix = to_postfix();
  }
  void set_infix(std::string _infix);
  std::string get_infix() { return infix; }
  std::string get_postfix();
  int operands_counter();
  double calculate(std::vector<double> values); // Ввод переменных, вычисление по постфиксной форме
};

#endif
