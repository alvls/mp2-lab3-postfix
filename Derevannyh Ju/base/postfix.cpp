#include "postfix.h"
#include <iostream>
#include <cctype>
#include <cmath>
#include <stdexcept>
using namespace std;
int GetPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}
string TPostfix::ToPostfix() {
    postfix = "";
    TStack<char> stack(100);
    for (size_t i = 0; i < infix.size(); i++) {
        char c = infix[i];

        if (c == ' ') continue;

        if (isdigit(c)) {
            while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) {
                postfix += infix[i];
                i++;
            }
            postfix += ' ';
            i--;
        }
        else if (isalpha(c)) {
            postfix += c;
            postfix += ' ';
        }
        else if (c == '(') {
            stack.Push(c);
        }
        else if (c == ')') {
            while (!stack.IsEmpty() && stack.Peek() != '(') {
                postfix += stack.Pop();
                postfix += ' ';
            }
            stack.Pop(); // удаляем '('
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            // Учитываем правую ассоциативность для '^'
            while (!stack.IsEmpty() && stack.Peek() != '(' &&
                (GetPriority(stack.Peek()) > GetPriority(c) ||
                    (GetPriority(stack.Peek()) == GetPriority(c) && c != '^'))) {
                postfix += stack.Pop();
                postfix += ' ';
            }
            stack.Push(c);
        }
    }

    while (!stack.IsEmpty()) {
        postfix += stack.Pop();
        postfix += ' ';
    }

    return postfix;
}
double TPostfix::Calculate() {
    TStack<double> stack(100);
    string numStr = "";
    for (size_t i = 0; i < postfix.size(); i++) {
        char c = postfix[i];

        if (c == ' ') {
            if (!numStr.empty()) {
                if (isdigit(numStr[0])) {
                    stack.Push(stod(numStr));
                }
                else {
                    char varName = numStr[0];
                    if (vars.find(varName) != vars.end()) {
                        stack.Push(vars[varName]);
                    }
                    else {
                        throw runtime_error("Переменная не задана: " + string(1, varName));
                    }
                }
                numStr = "";
            }
        }
        else if (isdigit(c) || c == '.' || isalpha(c)) {
            numStr += c;
        }
        else {
            if (!numStr.empty()) {
                if (isdigit(numStr[0])) {
                    stack.Push(stod(numStr));
                }
                else {
                    char varName = numStr[0];
                    if (vars.find(varName) != vars.end()) stack.Push(vars[varName]);
                    else throw runtime_error("Переменная не задана: " + string(1, varName));
                }
                numStr = "";
            }

            if (stack.IsEmpty()) throw runtime_error("Не хватает операндов");
            double b = stack.Pop();
            if (stack.IsEmpty()) throw runtime_error("Не хватает операндов");
            double a = stack.Pop();

            double result = 0;
            if (c == '+') result = a + b;
            if (c == '-') result = a - b;
            if (c == '*') result = a * b;
            if (c == '/') {
                if (b == 0) throw runtime_error("Деление на ноль!");
                result = a / b;
            }
            if (c == '^') result = pow(a, b);

            stack.Push(result);
        }
    }

    if (!numStr.empty()) {
        if (isdigit(numStr[0])) stack.Push(stod(numStr));
        else {
            char varName = numStr[0];
            if (vars.find(varName) != vars.end()) stack.Push(vars[varName]);
            else throw runtime_error("Переменная не задана: " + string(1, varName));
        }
    }

    if (stack.IsEmpty()) throw runtime_error("Пустое выражение");
    return stack.Pop();
}