#include "postfix.h"
#include <cctype>
#include <stdexcept>
#include <algorithm>

string TPostfix::ToPostfix()
{
    postfix = "";
    TStack<char> opStack(infix.length());

    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (c == ' ') continue;

        if (isdigit(c) || c == '.') {
            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
                postfix += infix[i];
                i++;
            }
            postfix += ' ';
            i--;
        }
        else if (isalpha(c)) {
            while (i < infix.length() && isalnum(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += ' ';
            i--;
        }
        else if (c == '(') {
            opStack.Push(c);
        }
        else if (c == ')') {
            while (!opStack.IsEmpty() && opStack.Top() != '(') {
                postfix += opStack.Pop();
                postfix += ' ';
            }
            if (opStack.IsEmpty()) throw invalid_argument("Ошибка: несогласованные скобки");
            opStack.Pop();
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!opStack.IsEmpty() && GetPriority(opStack.Top()) >= GetPriority(c)) {
                postfix += opStack.Pop();
                postfix += ' ';
            }
            opStack.Push(c);
        }
        else {
            throw invalid_argument("Ошибка: встречен недопустимый символ");
        }
    }

    while (!opStack.IsEmpty()) {
        if (opStack.Top() == '(') throw invalid_argument("Ошибка: несогласованные скобки");
        postfix += opStack.Pop();
        postfix += ' ';
    }

    return postfix;
}

vector<string> TPostfix::GetOperands()
{
    if (postfix.empty()) {
        ToPostfix();
    }

    vector<string> operands;

    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];

        if (isalpha(c)) {
            string varName = "";
            while (i < postfix.length() && isalnum(postfix[i])) {
                varName += postfix[i];
                i++;
            }
            i--;

            if (find(operands.begin(), operands.end(), varName) == operands.end()) {
                operands.push_back(varName);
            }
        }
    }

    return operands;
}

double TPostfix::Calculate(const map<string, double>& values)
{
    if (postfix.empty()) {
        ToPostfix();
    }

    TStack<double> resStack(postfix.length());

    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];

        if (c == ' ') continue;

        if (isdigit(c) || c == '.') {
            string numStr = "";
            while (i < postfix.length() && (isdigit(postfix[i]) || postfix[i] == '.')) {
                numStr += postfix[i];
                i++;
            }
            resStack.Push(stod(numStr));
            i--;
        }
        else if (isalpha(c)) {
            string varName = "";
            while (i < postfix.length() && isalnum(postfix[i])) {
                varName += postfix[i];
                i++;
            }
            i--;

            auto it = values.find(varName);
            if (it == values.end()) {
                throw invalid_argument("Ошибка: не задано значение переменной " + varName);
            }
            resStack.Push(it->second);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (resStack.IsEmpty()) throw invalid_argument("Ошибка в выражении");
            double op2 = resStack.Pop();

            if (resStack.IsEmpty()) throw invalid_argument("Ошибка в выражении");
            double op1 = resStack.Pop();

            double res = 0;
            switch (c) {
            case '+': res = op1 + op2; break;
            case '-': res = op1 - op2; break;
            case '*': res = op1 * op2; break;
            case '/':
                if (op2 == 0.0) throw runtime_error("Ошибка: деление на ноль!");
                res = op1 / op2; break;
            }
            resStack.Push(res);
        }
    }

    if (resStack.IsEmpty()) throw invalid_argument("Ошибка: пустое выражение");
    double finalResult = resStack.Pop();

    if (!resStack.IsEmpty()) throw invalid_argument("Ошибка: неверный формат выражения");

    return finalResult;
}