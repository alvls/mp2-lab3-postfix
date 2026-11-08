#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "=== Калькулятор арифметических выражений (ОПЗ) ===" << endl;
    cout << "Поддерживаются: +, -, *, /, скобки (), унарный минус и переменные." << endl;
    cout << "Введите выражение (или 'exit' для выхода):" << endl;

    string input;
    while (true) {
        cout << "\n> ";
        if (!getline(cin, input) || input == "exit") {
            break;
        }

        if (input.empty()) {
            continue;
        }

        TPostfix expr(input);
        expr.tokenize();

        string error_msg;
        size_t error_pos;
        if (!expr.check(error_msg, error_pos)) {
            cout << "Ошибка: " << error_msg << endl;
            cout << "  " << input << endl;
            cout << "  " << string(error_pos, ' ') << "^" << endl;
            continue;
        }

        try {
            string postfix = expr.ToPostfix();
            cout << "Постфиксная форма (ОПЗ): " << postfix << endl;
            double res = expr.Calculate();
            cout << "Результат: " << res << endl;
        } catch (const exception& e) {
            cout << "Ошибка при обработке: " << e.what() << endl;
        }
    }

    cout << "Завершение работы." << endl;
    return 0;
}