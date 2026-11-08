#include <iostream>
#include <string>
#include <exception>
#include "postfix.h"

using namespace std;

int main()
{
    string expression;
    TPostfix postfix;
    double res;

    setlocale(LC_ALL, "Russian");

    cout << "Введите арифметическое выражение: ";
    getline(cin, expression);

    postfix.SetInfix(expression);

    try
    {
        cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
        postfix.ToPostfix();
        cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

        res = postfix.Calculate();
        cout << "Результат: " << res << endl;
    }
    catch (const exception& e)
    {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;
}