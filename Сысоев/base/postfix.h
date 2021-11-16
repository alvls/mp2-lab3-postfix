#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include <locale>
#include "stack.h"

using namespace std;

enum class wrong
{
    brackets_quantity,
    operation_placement,
};
enum class priority
{
    leftbracket,
    addition_and_substraction,
    multiplication_and_division,
    exponentation,
};
class TPostfix
{
    string infix;
    string postfix;//постфиксная форма
    vector <string> expression;//переделать в вектор строк
public:
    TPostfix(const string& _infix = "a+b"): expression(0),postfix("")
    {
        const int size_of_op = 5;
        const char operations[size_of_op] = { '+','-','*','/','^' };
        int left_bracket = 0;
        int right_bracket = 0;
        string copy;
        for (int i = 0; i < _infix.size(); i++)
            if (_infix[i] != ' ')
                copy.push_back(_infix[i]);
        for (int i = 0; i < size_of_op; i++)
            if (copy[0] == operations[i])
                throw wrong::operation_placement;
        for (int i = 0; i < size_of_op; i++)
            if (copy[copy.size() - 1] == operations[i])
                throw wrong::operation_placement;
        for (int i = 0; i < copy.size(); i++)
            if (copy[i] == '(')
            {
                left_bracket++;
                i++;
                if (i == copy.size())
                    throw wrong::brackets_quantity;
                for (int j = 0; j < size_of_op; j++)
                    if (copy[i] == operations[j])
                        throw wrong::operation_placement;
            }
            else
                if (copy[i] == ')')
                    right_bracket++;
                else
                {
                    int j = 0;
                    for (; j < size_of_op; j++)
                        if (copy[i] == operations[j])
                            break;
                    if (j<size_of_op)
                    {
                        i++;
                        for (int j = 0; j < size_of_op; j++)
                            if (copy[i] == operations[j])
                                throw wrong::operation_placement;
                    }
                }
        if (left_bracket != right_bracket)
        {
            throw wrong::brackets_quantity;
        }
        infix = copy;
    }
    void ToPostfix();
    string GetInfix() const { return infix; }
    string GetPostfix() const { return postfix; }
    double Calculate(); // Ввод переменных, вычисление по постфиксной форме
    vector<double> GetValues();// Получение значений операндов
    bool is_current_bigger_or_eq(string current, string next) const;
    bool is_next_more_important(string current, string next) const;
};
double getdb(string s);
double addition(double one, double two);
double subtraction(double one, double two);
double multiplication(double one, double two);
double division(double one, double two);
double exponentation(double one, double two);
#endif
