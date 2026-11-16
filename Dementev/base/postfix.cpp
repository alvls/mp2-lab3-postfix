#include "postfix.h"
#include <stack>
#include <stdexcept>
#include <cctype>
#include <sstream>

TPostfix::TPostfix(const std::string& expr) : infix(expr) {}

std::string TPostfix::GetInfix() const { return infix; }
std::string TPostfix::GetPostfix() const { return postfix; }

bool TPostfix::IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int TPostfix::GetPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void TPostfix::ToPostfix() {
    std::stack<char> opStack;
    std::string result;
    
    for (size_t i = 0; i < infix.length(); ++i) {
        char ch = infix[i];
        
        if (isspace(ch)) continue;
        
        if (isdigit(ch) || isalpha(ch)) {
            result += ch;
            result += " ";
        }
        else if (ch == '(') {
            opStack.push(ch);
        }
        else if (ch == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                result += opStack.top();
                result += " ";
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop();
        }
        else if (IsOperator(ch)) {
            while (!opStack.empty() && GetPriority(opStack.top()) >= GetPriority(ch)) {
                result += opStack.top();
                result += " ";
                opStack.pop();
            }
            opStack.push(ch);
        }
    }
    
    while (!opStack.empty()) {
        result += opStack.top();
        result += " ";
        opStack.pop();
    }
    
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    postfix = result;
}

double TPostfix::Calculate(const std::map<char, double>& vars) {
    std::stack<double> st;
    std::stringstream ss(postfix);
    std::string token;

    while (ss >> token) {
        char ch = token[0];
        
        if (token.size() == 1 && IsOperator(ch)) {
            if (st.size() < 2) throw std::runtime_error("Ошибка: неверное выражение");
            double right = st.top(); st.pop();
            double left = st.top(); st.pop();
            double res = 0;
            switch (ch) {
                case '+': res = left + right; break;
                case '-': res = left - right; break;
                case '*': res = left * right; break;
                case '/': 
                    if (right == 0) throw std::runtime_error("Деление на ноль");
                    res = left / right; 
                    break;
            }
            st.push(res);
        }
        else if (isalpha(ch)) {
            if (vars.find(ch) == vars.end()) {
                throw std::runtime_error("Нет значения для переменной");
            }
            st.push(vars.at(ch));
        }
        else if (isdigit(ch)) {
            st.push(ch - '0'); 
        }
        else {
            throw std::runtime_error("Неизвестный символ");
        }
    }

    if (st.size() != 1) throw std::runtime_error("Ошибка: неверное выражение");
    return st.top();
}