#include <iostream>
#include <string>
#include <map>
#include <locale>
#include "postfix.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    string expression;
    map<char, double> values;
    double result;
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
    return 0;
}