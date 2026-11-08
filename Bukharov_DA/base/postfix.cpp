#include "postfix.h"
#include <iostream>
#include <cctype>
#include <sstream>
#include <stdexcept>

using namespace std;

int TPostfix::priority(char op) {
    switch (op) {
        case '(': return 0;
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '~': return 3;
        default:  return -1;
    }
}

void TPostfix::tokenize() {
    tokens.clear();
    size_t i = 0;

    while (i < infix.length()) {
        char c = infix[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        if (isdigit(c) || c == '.') {
            size_t start = i;
            string num = "";
            int dotCount = 0;

            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
                if (infix[i] == '.') dotCount++;
                num += infix[i];
                i++;
            }

            if (dotCount > 1 || num == ".") {
                tokens.push_back({num, '?', start});
            } else {
                tokens.push_back({num, 'n', start});
            }
            continue;
        }

        if (isalpha(c) || c == '_') {
            size_t start = i;
            string var = "";
            while (i < infix.length() && (isalnum(infix[i]) || infix[i] == '_')) {
                var += infix[i];
                i++;
            }
            tokens.push_back({var, 'v', start});
            continue;
        }

        if (c == '(' || c == ')') {
            tokens.push_back({string(1, c), c, i});
            i++;
            continue;
        }

        if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (c == '-') {
                bool isUnary = false;
                if (tokens.empty()) {
                    isUnary = true;
                } else {
                    char prevType = tokens.back().type;
                    if (prevType == 'o' || prevType == '(') {
                        isUnary = true;
                    }
                }

                if (isUnary) {
                    tokens.push_back({"~", 'o', i});
                    i++;
                    continue;
                }
            }

            tokens.push_back({string(1, c), 'o', i});
            i++;
            continue;
        }


        tokens.push_back({string(1, c), '?', i});
        i++;
    }
}

bool TPostfix::check(string& error_msg, size_t& error_pos) {
    if (tokens.empty()) {
        error_msg = "Выражение пустое";
        error_pos = 0;
        return false;
    }

    TStack<size_t> brackets;

    for (size_t i = 0; i < tokens.size(); i++) {
        const Token& t = tokens[i];

  
        if (t.type == '?') {
            error_msg = "Некорректный символ или число";
            error_pos = t.pos;
            return false;
        }

  
        if (t.type == '(') {
            brackets.push(t.pos);
            if (i + 1 < tokens.size() && tokens[i + 1].type == ')') {
                error_msg = "Пустые скобки";
                error_pos = t.pos;
                return false;
            }
        } else if (t.type == ')') {
            if (brackets.empty()) {
                error_msg = "Лишняя закрывающая скобка";
                error_pos = t.pos;
                return false;
            }
            brackets.pop();
        }

        if (t.type == 'o' && t.value != "~") {
            if (i == 0 || i == tokens.size() - 1) {
                error_msg = "Оператор на границе выражения";
                error_pos = t.pos;
                return false;
            }

            Token prev = tokens[i - 1];
            Token next = tokens[i + 1];

       
            if (prev.type == '(' || prev.type == 'o') {
                error_msg = "Некорректное расположение оператора";
                error_pos = t.pos;
                return false;
            }

            // После бинарного оператора не может стоять ')'
            if (next.type == ')') {
                error_msg = "Оператор перед закрывающей скобкой";
                error_pos = t.pos;
                return false;
            }
        }


        if (t.type == 'o' && t.value == "~") {
            if (i == tokens.size() - 1 || tokens[i + 1].type == ')') {
                error_msg = "Унарный минус без операнда";
                error_pos = t.pos;
                return false;
            }
        }
    }

    if (!brackets.empty()) {
        error_msg = "Не закрыта открывающая скобка";
        error_pos = brackets.pop();
        return false;
    }

    return true;
}

string TPostfix::ToPostfix() {
    tokenize();

    string err_msg;
    size_t err_pos;
    if (!check(err_msg, err_pos)) {
        throw runtime_error(err_msg + " (символ " + to_string(err_pos) + ")");
    }

    postfixTokens.clear();
    TStack<Token> opStack;
    stringstream ss;

    for (const auto& t : tokens) {
        if (t.type == 'n' || t.type == 'v') {
            postfixTokens.push_back(t);
            ss << t.value << " ";
        } else if (t.type == '(') {
            opStack.push(t);
        } else if (t.type == ')') {
            while (!opStack.empty() && opStack.top().type != '(') {
                postfixTokens.push_back(opStack.top());
                ss << opStack.pop().value << " ";
            }
            if (!opStack.empty()) opStack.pop(); 
        } else if (t.type == 'o') {
            if (t.value == "~") {
                while (!opStack.empty() && priority(opStack.top().value[0]) > priority(t.value[0])) {
                    postfixTokens.push_back(opStack.top());
                    ss << opStack.pop().value << " ";
                }
            } else {
                while (!opStack.empty() && priority(opStack.top().value[0]) >= priority(t.value[0])) {
                    postfixTokens.push_back(opStack.top());
                    ss << opStack.pop().value << " ";
                }
            }
            opStack.push(t);
        }
    }

    while (!opStack.empty()) {
        postfixTokens.push_back(opStack.top());
        ss << opStack.pop().value << " ";
    }

    postfix = ss.str();
    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }
    return postfix;
}

vector<string> TPostfix::GetVariables() const {
    vector<string> vars;
    for (const auto& t : tokens) {
        if (t.type == 'v') {
            bool found = false;
            for (const auto& v : vars) {
                if (v == t.value) {
                    found = true;
                    break;
                }
            }
            if (!found) vars.push_back(t.value);
        }
    }
    return vars;
}

double TPostfix::Calculate(const map<string, double>& values) {
    if (postfixTokens.empty()) {
        ToPostfix();
    }

    TStack<double> valStack;

    for (const auto& t : postfixTokens) {
        if (t.type == 'n') {
            valStack.push(stod(t.value));
        } else if (t.type == 'v') {
            auto it = values.find(t.value);
            if (it == values.end()) {
                throw runtime_error("Значение для переменной " + t.value + " не задано");
            }
            valStack.push(it->second);
        } else if (t.type == 'o') {
            if (t.value == "~") {
                if (valStack.empty()) throw runtime_error("Ошибка вычисления унарного минуса");
                double val = valStack.pop();
                valStack.push(-val);
            } else {
                if (valStack.empty()) throw runtime_error("Недостаточно операндов для операции");
                double right = valStack.pop();
                if (valStack.empty()) throw runtime_error("Недостаточно операндов для операции");
                double left = valStack.pop();

                switch (t.value[0]) {
                    case '+': valStack.push(left + right); break;
                    case '-': valStack.push(left - right); break;
                    case '*': valStack.push(left * right); break;
                    case '/':
                        if (right == 0.0) throw runtime_error("Деление на ноль");
                        valStack.push(left / right);
                        break;
                }
            }
        }
    }

    if (valStack.empty()) throw runtime_error("Стек пуст по окончании вычислений");
    return valStack.pop();
}

double TPostfix::Calculate() {
    if (postfixTokens.empty()) {
        ToPostfix();
    }

    vector<string> vars = GetVariables();
    map<string, double> values;

    for (const auto& var : vars) {
        double val;
        cout << "Введите значение для " << var << ": ";
        while (!(cin >> val)) {
            cout << "Ошибка ввода! Введите число для " << var << ": ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        values[var] = val;
    }

    return Calculate(values);
}