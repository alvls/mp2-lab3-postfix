#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include "postfix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    try {
        cout << "Введите арифметическое выражение (например, a + b * c - D): ";
        string expression;
        getline(cin, expression);

        if (expression.empty()) {
            cerr << "Выражение не может быть пустым!" << endl;
            return 1;
        }

        TPostfix postfix(expression);

        set<char> variables;
        for (char c : expression) {
            if (isalpha(c)) {
                variables.insert(c);
            }
        }

        if (!variables.empty()) {
            cout << "\nВ выражении найдены переменные. Задайте их значения:\n";
            for (char var : variables) {
                double value;
                cout << "  " << var << " = ";
                cin >> value;
                postfix.SetVariable(var, value);
            }
        }
        else {
            cout << "\nПеременных не найдено, выражение состоит только из чисел.\n";
        }

        cout << "\nАрифметическое выражение: " << postfix.GetInfix() << endl;
        cout << "Постфиксная форма:        " << postfix.ToPostfix() << endl;

        double res = postfix.Calculate();
        cout << "Результат:                " << res << endl;
    }
    catch (const std::exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    catch (int code) {
        cerr << "Ошибка стека, код " << code << endl;
        return 1;
    }
    catch (const char* msg) {
        cerr << "Ошибка: " << msg << endl;
        return 1;
    }

    return 0;
}