#include "postfix.h"
#include "stack.h"
#include <iostream>


int GetPriority(char ch) 
{
  switch (ch) 
  {
  case '*':
  case '/':
    return 2;
  case '+':
  case '-':
    return 1;
  default:
    return -1;
  }
}

bool IsOperator(char ch) 
{
  return std::string("+-*/").find(ch) != std::string::npos;
}

bool IsOperand(char ch) 
{
  return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

std::string TPostfix::ToPostfix() 
{
  TStack<char> stack(MaxStackSize);
  postfix = "";

  for (size_t i = 0; i < infix.size(); i++) 
  {
    char ch = infix[i];

    if (IsOperand(ch))
      postfix += ch;
    else if (ch == '(')
      stack.Push(ch);
    else if (ch == ')')
    {
      while (!stack.IsEmpty() && stack.Peek() != '(')
        postfix += stack.Pop();
      stack.Pop(); // Удаляем открывающую скобку
    }
    else if (IsOperator(ch))
    {
      while (!stack.IsEmpty() && GetPriority(stack.Peek()) >= GetPriority(ch))
        postfix += stack.Pop();
      stack.Push(ch);
    }
  }

  while (!stack.IsEmpty())
    postfix += stack.Pop();

  return postfix;
}

double TPostfix::Calculate() 
{
  TStack<double> stack(MaxStackSize);

  for (char token : postfix) 
  {
    if (IsOperand(token)) 
    {
      // Если токен - переменная, используем её значение, иначе преобразуем число из строки
      if (isalpha(token))
        stack.Push(variables[token]);
      else // Если это цифра, то просто кладём её в стек
        stack.Push(token - '0');
    }
    else 
    {
      double right = stack.Pop();
      double left = stack.Pop();
      switch (token) 
      {
      case '+':
        stack.Push(left + right);
        break;
      case '-':
        stack.Push(left - right);
        break;
      case '*':
        stack.Push(left * right);
        break;
      case '/':
        if (right == 0) throw "Division by zero!";
        stack.Push(left / right);
        break;
      default:
        throw "Unsupported operation!";
      }
    }
  }
  if (stack.IsEmpty())
    throw "Error in expression!";
  double result = stack.Pop();
  if (!stack.IsEmpty())
    throw "Error in expression!";

  return result;
}

void TPostfix::ReadVariables() 
{
  std::cout << "Введите значения переменных для выражения: " << infix << std::endl;
  for (char token : infix) 
  {
    if (std::isalpha(token) && variables.find(token) == variables.end()) 
    {
      std::cout << token << " = ";
      double value;
      std::cin >> value;
      variables[token] = value;
    }
  }
}
