#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    try
    {
        string expression;
        cout << "Введите арифметическое выражение: ";
        cin >> expression;

        TPostfix postfix(expression);
        double res;

        cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
        cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

        cout << "Установка значений переменных:" << endl;
        map<char, double> variables;

        char variable;
        double value;
        while (true)
        {
            cout << "Введите переменную (или 'q' для завершения): ";
            cin >> variable;

            if (variable == 'q')
                break;

            cout << "Введите значение переменной " << variable << ": ";
            cin >> value;

            variables[variable] = value;
        }

        postfix.SetVariables(variables);
        res = postfix.Calculate();
        cout << "Результат: " << res << endl;
    }
    catch (const exception& e)
    {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}