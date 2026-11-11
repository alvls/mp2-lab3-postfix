#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "postfix.h"

using namespace std;

int main()
{
    string expression;
    double res;

    setlocale(LC_ALL, "Russian");

    cout << "Введите арифметическое выражение (например, (a + b) * 2.5): ";
    getline(cin, expression);

    try {
        TPostfix postfix(expression);

        cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;

        postfix.ToPostfix();
        cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

        vector<string> operands = postfix.GetOperands();
        map<string, double> values;

        for (const string& op : operands) {
            cout << "Введите значение переменной " << op << ": ";
            cin >> values[op];
        }

        res = postfix.Calculate(values);
        cout << "Результат: " << res << endl;
    }
    catch (const exception& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
    }

    return 0;
}