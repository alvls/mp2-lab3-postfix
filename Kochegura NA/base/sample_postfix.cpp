#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
    string expression;
    double res;

    setlocale(LC_ALL, "Russian");

    cout << "Введите арифметическое выражение (например, (2+3)*4 или 10.5-2.5): ";
    getline(cin, expression);

    try {

        TPostfix postfix(expression);

        cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;

        postfix.ToPostfix();
        cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

        res = postfix.Calculate();
        cout << "Результат: " << res << endl;
    }
    catch (const exception& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
    }

    return 0;
}