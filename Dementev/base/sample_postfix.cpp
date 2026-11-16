#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cctype>
#include "postfix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    string expression;
    cout << "Введите арифметическое выражение: ";
    getline(cin, expression);

    TPostfix postfix(expression);

    cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;

    postfix.ToPostfix();
    cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

    map<char, double> varValues;
    set<char> variables;

    for (char ch : expression) {
        if (isalpha(ch)) {
            variables.insert(ch);
        }
    }

    for (char var : variables) {
        double val;
        cout << "Введите значение для переменной " << var << ": ";
        cin >> val;
        varValues[var] = val;
    }

    double res = 0.0;
    try {
        res = postfix.Calculate(varValues);
        cout << "Результат: " << res << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка вычисления: " << e.what() << endl;
    }

    return 0;
}