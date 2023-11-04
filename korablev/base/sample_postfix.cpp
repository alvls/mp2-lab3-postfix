#include <iostream>
#include <string>
#include <map>
#include <locale>
#include "postfix.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    string expression;
    int mode;
    map<char, double> values;
    double result;
start:
    cout << "Выберите режим: \n1. Ввод букв\n2. Ввод чисел\n";
    cin >> mode;
    system("cls");
    if (mode == 1) {
        cout << "Введите выражение с переменными (например, a+b*c): ";
        cin >> expression;
        TPostfix calculator(expression);
        cout << "Выражение в постфиксной записи: " << calculator.GetPostfix() << endl;
        vector<char> operands = calculator.GetOperands();
        for (char op : operands) {
            double value;
            cout << "Введите значение для " << op << ": ";
            cin >> value;
            values[op] = value;
        }
        result = calculator.Calculate(values);
        cout << "Результат: " << result << endl;
    }
    else if (mode == 2) {
        cout << "Введите числовое выражение (например, 2+3*4): ";
        cin >> expression;
        TPostfix calculator(expression);
        cout << "Выражение в постфиксной записи: " << calculator.GetPostfix() << endl;
        result = calculator.Calculate({});
        cout << "Результат: " << result << endl;
    }
    else {
        system("cls");
        cout << "Выбран неверный режим." << endl;
        system("pause");
        system("cls");
        goto start;
    }
    return 0;
}