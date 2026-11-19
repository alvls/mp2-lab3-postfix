#include "postfix.h"

#include <cctype>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace
{
  bool is_operator(const string& s)
  {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "~";
  }

  int priority(const string& op)
  {
    if (op == "~") return 4;
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
  }

  bool right_associative(const string& op) { return op == "^" || op == "~"; }

  bool is_number(const string& s)
  {
    if (s.empty()) return false;
    std::istringstream input(s);
    double number;
    char extra;
    return (input >> number) && !(input >> extra);
  }

  bool is_identifier(const string& s)
  {
    if (s.empty() || !(std::isalpha(static_cast<unsigned char>(s[0])) || s[0] == '_'))
      return false;
    for (size_t i = 1; i < s.size(); ++i)
      if (!(std::isalnum(static_cast<unsigned char>(s[i])) || s[i] == '_')) return false;
    return true;
  }

  std::vector<string> tokenize(const string& expression)
  {
    std::vector<string> result;
    for (size_t i = 0; i < expression.size();)
    {
      unsigned char ch = static_cast<unsigned char>(expression[i]);
      if (std::isspace(ch)) { ++i; continue; }
      if (std::isdigit(ch) || expression[i] == '.')
      {
        size_t start = i;
        bool dot = false;
        while (i < expression.size() &&
               (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.'))
        {
          if (expression[i] == '.')
          {
            if (dot) throw std::invalid_argument("Invalid number");
            dot = true;
          }
          ++i;
        }
        string token = expression.substr(start, i - start);
        if (!is_number(token)) throw std::invalid_argument("Invalid number");
        result.push_back(token);
      }
      else if (std::isalpha(ch) || expression[i] == '_')
      {
        size_t start = i++;
        while (i < expression.size() &&
               (std::isalnum(static_cast<unsigned char>(expression[i])) || expression[i] == '_')) ++i;
        result.push_back(expression.substr(start, i - start));
      }
      else if (string("+-*/^()").find(expression[i]) != string::npos)
      {
        result.push_back(string(1, expression[i++]));
      }
      else throw std::invalid_argument("Invalid character in expression");
    }
    return result;
  }
}

string TPostfix::ToPostfix()
{
  std::vector<string> tokens = tokenize(infix);
  if (tokens.empty()) throw std::invalid_argument("Empty expression");

  TStack<string> operators(MaxStackSize);
  std::vector<string> output;
  bool need_operand = true;

  for (size_t i = 0; i < tokens.size(); ++i)
  {
    string token = tokens[i];
    if (is_number(token) || is_identifier(token))
    {
      if (!need_operand) throw std::invalid_argument("Missing operator");
      output.push_back(token);
      need_operand = false;
    }
    else if (token == "(")
    {
      if (!need_operand) throw std::invalid_argument("Missing operator before parenthesis");
      operators.Push(token);
    }
    else if (token == ")")
    {
      if (need_operand) throw std::invalid_argument("Missing operand");
      bool matched = false;
      while (!operators.IsEmpty())
      {
        string op = operators.Pop();
        if (op == "(") { matched = true; break; }
        output.push_back(op);
      }
      if (!matched) throw std::invalid_argument("Mismatched parentheses");
      need_operand = false;
    }
    else
    {
      if (need_operand)
      {
        if (token == "+") continue;
        if (token == "-") token = "~";
        else throw std::invalid_argument("Missing operand");
      }
      else need_operand = true;

      // Unary negation is a prefix operator: keep it above any pending binary operator.
      if (token != "~")
      {
        while (!operators.IsEmpty() && is_operator(operators.Top()) &&
               (priority(operators.Top()) > priority(token) ||
                (priority(operators.Top()) == priority(token) && !right_associative(token))))
          output.push_back(operators.Pop());
      }
      operators.Push(token);
    }
  }

  if (need_operand) throw std::invalid_argument("Incomplete expression");
  while (!operators.IsEmpty())
  {
    string op = operators.Pop();
    if (op == "(") throw std::invalid_argument("Mismatched parentheses");
    output.push_back(op);
  }

  std::ostringstream result;
  for (size_t i = 0; i < output.size(); ++i)
  {
    if (i) result << ' ';
    result << output[i];
  }
  postfix = result.str();
  return postfix;
}

double TPostfix::Calculate()
{
  // Rebuild after any expression change; malformed input must not reuse old output.
  ToPostfix();
  std::istringstream input(postfix);
  std::map<string, double> variables;
  TStack<double> values(MaxStackSize);
  string token;

  while (input >> token)
  {
    if (is_number(token))
    {
      values.Push(std::stod(token));
    }
    else if (is_identifier(token))
    {
      if (variables.find(token) == variables.end())
      {
        double value;
        std::cout << "Enter " << token << ": ";
        if (!(std::cin >> value)) throw std::runtime_error("Failed to read variable");
        variables[token] = value;
      }
      values.Push(variables[token]);
    }
    else if (token == "~")
    {
      values.Push(-values.Pop());
    }
    else if (is_operator(token))
    {
      double right = values.Pop();
      double left = values.Pop();
      if (token == "+") values.Push(left + right);
      else if (token == "-") values.Push(left - right);
      else if (token == "*") values.Push(left * right);
      else if (token == "/")
      {
        if (right == 0.0) throw std::domain_error("Division by zero");
        values.Push(left / right);
      }
      else values.Push(std::pow(left, right));
    }
    else throw std::invalid_argument("Invalid postfix token");
  }

  if (values.GetCount() != 1) throw std::invalid_argument("Invalid expression");
  return values.Pop();
}
