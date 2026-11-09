#include "postfix.h"
#include "stack.h"
#include <iostream>
#include <stdexcept>
#include <cctype>

using namespace std;

int GetPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


string TPostfix::ToPostfix()
{
    string result = "";
    TStack<char> stack(100);
    string expr = infix;
    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (c == ' ') continue; 
        if (isalpha(c) || isdigit(c)) {
            result += c;
        }
        else if (c == '(') {
            stack.Push(c);
        }
        else if (c == ')') {
            while (!stack.IsEmpty() && stack.Top() != '(') {
                result += stack.Pop();
            }
            if (!stack.IsEmpty()) stack.Pop(); 
        }
        else {
            while (!stack.IsEmpty() && GetPriority(stack.Top()) >= GetPriority(c)) {
                result += stack.Pop();
            }
            stack.Push(c); 
        }
    }
    while (!stack.IsEmpty()) {
        result += stack.Pop();
    }
    postfix = result;
    return postfix;
}


double TPostfix::Calculate()
{
    if (postfix.empty()){
        ToPostfix();
}
    TStack<double> stack(100);
    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];

        if (isdigit(c)) {
            stack.Push(c - '0');
        }
        else if (isalpha(c)) {
            cout << "Введите значение для " << c << ": ";
            double val;
            cin >> val;
            stack.Push(val);
        }
        else {
            if (stack.IsEmpty()) throw std::invalid_argument("Invalid expression");
            double b = stack.Pop();

            if (stack.IsEmpty()) throw std::invalid_argument("Invalid expression");
            double a = stack.Pop();

            double res = 0;
            if (c == '+') res = a + b;
            else if (c == '-') res = a - b;
            else if (c == '*') res = a * b;
            else if (c == '/') res = a / b;
            
            stack.Push(res);
        }

    }
    return stack.Pop();
}

