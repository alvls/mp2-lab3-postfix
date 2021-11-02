#include <vector>
#include <string>
#include <map>
#include "postfix.h"
#include "stack.h"


double calculate_function (double a, double b, std::string _operator) {
  double result;
  int value = 0;
  std::map<std::string, int> mp = {{"*", 1}, {"/", 2}, {"+", 3}, {"-", 4}};
  for (const auto& kv : mp)
    if (_operator == kv.first) {
      value = kv.second;
      break;
    }
  switch (value) {
    case 3: 
      result = a + b;
      break;
    case 1:
      result = a * b;
      break;
    case 4:
      result = a - b;
      break;
    case 2:
      result = a / b;
      break;
  }
  return result;
}

int TPostfix::operands_counter() {
  int counter = 0;
  int postfix_size = postfix.size();
  std::string operations[4] = {"+", "-", "/", "*"};
  for (int i = 0; i < postfix_size; i++) {
    for (std::string symbol : operations)
      if (postfix[i] == symbol) {
        counter++;
        break;
      }
  }
  return postfix_size - counter;
}

void TPostfix::set_infix (std::string _infix) {
  infix = _infix;
  postfix = to_postfix();
}

bool TPostfix::correct_input_check() {
  int counter = 0;
  std::vector<std::string> tmp(infix_divide());
  for (int i = 0; i < tmp.size(); i++)
    if (tmp[i] == "(" || tmp[i] == ")")
      counter++;
  if (!(counter % 2))
    return true;
  else
    return false;
}

std::string TPostfix::postfix_to_string() {
  std::string tmp;
  for (int i = 0; i < postfix.size(); i++)
    tmp += postfix[i];
  return tmp;
}

std::string TPostfix::get_postfix() {
  return postfix_to_string();
}

std::vector<std::string> TPostfix::infix_divide() {
  bool flag = false;
  std::string temp;
  std::vector<std::string> divided_infix;
  char operations[6] = {'+', '-', '/', '(', ')', '*'};
  for (int i = 0; i < infix.size(); i++) {
    while (infix[i] == ' ')
     i++;
    flag = false;
    temp.clear();
    for (char symbol : operations)
      if (infix[i] == symbol) {
        flag = true;
        break;
      }
    if (flag) 
      temp.push_back(infix[i]);
    else {
      while (!flag && i < infix.size()) {
        if (infix[i] != ' ')
          temp.push_back(infix[i]);    
        i++;
        for (char symbol : operations) 
          if (infix[i] == symbol) {
            flag = true;
            break;
          }  
          if (flag)
            i--;
      }
    } 
    divided_infix.push_back(temp);
  }
  return divided_infix;
}

std::vector<std::string> TPostfix::to_postfix() {
  bool flag = true;
  bool flag_1 = true;;
  int status_infix;
  int status_operations;
  std::map<std::string, int> mp = {{"*", 1}, {"/", 1}, {"+", 0}, {"-", 0}, {"(", -1}, {")", -1}};
  TStack<std::string> operations(MAX_STACK_SIZE);
  std::vector<std::string> postfix_form;
  std::vector<std::string> divided_infix_form = infix_divide();
  for (int i = 0; i < divided_infix_form.size(); i++) {
    flag = true;
    flag_1 = true;
    for (const auto& kv : mp) {
      if (divided_infix_form[i] == kv.first) {
        flag = false;
        break;
      }
    }
    if (flag) {
      postfix_form.push_back(divided_infix_form[i]);
    }
    else if (divided_infix_form[i] == ")") {
      while (operations.back() != "(") {
        postfix_form.push_back(operations.pop());
      }
      operations.pop();
    }
    else {
      for (const auto& kv : mp)
        if (divided_infix_form[i] == kv.first)
          status_infix = kv.second;
      while (!operations.is_empty() && operations.back() != "(" && flag_1) {
        flag_1 = true;
        for (const auto& kv : mp)
          if (operations.back() == kv.first)
            status_operations = kv.second;
        if (status_operations >= status_infix && divided_infix_form[i] != "(")
          postfix_form.push_back(operations.pop());
        else
          flag_1 = false;
      }
      operations.push(divided_infix_form[i]);
    }
  }
  while(!operations.is_empty())
    postfix_form.push_back(operations.pop());
  return postfix_form;
}

double TPostfix::calculate(std::vector<double> values) {
  bool flag = false;
  std::string operations[4] = {"+", "-", "/", "*"};
  int j = 0;
  TStack<double> operands(MAX_STACK_SIZE);
  for (int i = 0; i < postfix.size(); i++) {
    flag = false;
    for (std::string symbol : operations)
      if (postfix[i] == symbol) {
        flag = true;
        break;
      }
    if (!flag) {
      operands.push(values[j]);
      j++;
    }
    else {
      operands.push(calculate_function (operands.pop(), operands.pop(), postfix[i]));
    }
  }
  return operands.pop();
}
