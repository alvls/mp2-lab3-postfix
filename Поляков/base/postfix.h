#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include <map>
#include "stack.h"

using namespace std;

class TPostfix
{
private:
    vector<string> infix;
    vector<string> postfix;
    TPostfix(const TPostfix&) = delete; // Запрет на копирование
    void operator=(const TPostfix&) = delete; // Запрет на присваивание
    bool BracketsCorrect(string& str) const; // Проверка на корректность раставления скобок в полученной на вход строке
    void ToInfix(string& str); // Преобразование полученной строки в vector<string> infix
    void ToPostfix(); // Преобразование infix в vector<string> postfix
    vector<string> GetVecOfVariables() const; // Получить вектор переменных из постфиксной формы

public:
    TPostfix(string str) // Конструктор
    {
        if (!BracketsCorrect(str))
            throw string("The brackets in expression are incorrect");
        ToInfix(str);
        ToPostfix();
    }

    vector<string> GetInfix() const { return infix; }

    vector<string> GetPostfix() const { return postfix; }

    string GetStringInfix() const
    {
        string tmp;
        for (const string& elem : infix)
            tmp += elem + ' ';
        return tmp;
    }

    string GetStringPostfix() const
    {
        string tmp;
        for (const string& elem : postfix)
            tmp += elem + ' ';
        return tmp;
    }

    double Calculate(bool interface = true, vector<double> vecofvalues = {}) const; // Ввод переменных, вычисление по постфиксной форме
};

#endif
