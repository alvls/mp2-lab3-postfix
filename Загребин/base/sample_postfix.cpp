#include "postfix.h"

int main(){
    setlocale(LC_ALL, "Russian");
    TPostfix postfix; std::string expression; int choice = 0;
    try {
    post:
        std::cout << "Введите арифметическое выражение (ввод: 1,4 ): "; // expression
        std::getline(std::cin, expression);
        postfix.SetInfix(expression);
        try {
            std::cout << "Постфиксная форма: " << postfix.ToPostfix() << '.' << std::endl;;
        }
        catch (...) {
            std::cout << "Ошибка! " << std::endl;
            goto post;
        }

        std::cout << "Вычислить? Нет-0, Да-1: ";
        std::cin >> choice;
        if (choice) {
        calc:
            std::cout << "Ответ: " << postfix.Calculate() << std::endl;
            std::cout << "Снова посчитать? Нет-0, Да-1: ";
            std::cin >> choice;
            if (choice) {
                std::getline(std::cin, expression);
                goto calc;
            }
        }

        std::cout << "Сначала? Нет-0, Да-1: ";
        std::cin >> choice;
        if (choice) {
            std::getline(std::cin, expression);
            goto post;
        }
    }
    catch (...) {
        std::cout << std::endl <<  "!!Fatal ERROR!!";
    }

  return 0;
}
