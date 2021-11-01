#include <iostream>
#include "postfix.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "Russian");
    TPostfix postfix; string expression; int choice = 0;
    try {
    post:
        cout << "Введите арифметическое выражение (ввод: 1,4 ): "; // expression
        getline(cin, expression);
        postfix.SetInfix(expression);
        try {
            cout << "Постфиксная форма: " << postfix.ToPostfix() << endl;;
        }
        catch (...) {
            cout << "Ошибка! " << endl;
            goto post;
        }

        cout << "Вычислить? Нет-0, Да-1: ";
        cin >> choice;
        if (choice) {
        calc:
            cout << "Ответ: " << postfix.Calculate() << endl;
            cout << "Снова посчитать? Нет-0, Да-1: ";
            cin >> choice;
            if (choice) {
                getline(cin, expression);
                goto calc;
            }
        }

        cout << "Сначала? Нет-0, Да-1: ";
        cin >> choice;
        if (choice) {
            getline(cin, expression);
            goto post;
        }
    }
    catch (...) {
        cout << endl <<  "!!Fatal ERROR!!";
    }

  return 0;
}
