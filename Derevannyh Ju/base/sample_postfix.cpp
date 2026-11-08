#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    try {
        // Выражение, где встречаются разные переменные
        string expression = "a + b * c - D";
        TPostfix postfix(expression);

        // Задаём значения переменных ДО активации программы
        postfix.SetVariable('a', 5);
        postfix.SetVariable('b', 10);
        postfix.SetVariable('c', 15);
        postfix.SetVariable('D', 20);

        cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
        cout << "Постфиксная форма: " << postfix.ToPostfix() << endl;

        double res = postfix.Calculate();
        cout << "Результат: " << res << endl;
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