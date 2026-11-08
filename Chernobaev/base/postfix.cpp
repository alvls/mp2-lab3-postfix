#include "postfix.h"
#include "stack.h"

#include <iostream>   // std::cin, std::cout
#include <sstream>    // std::istringstream
#include <stdexcept>  // std::runtime_error, std::domain_error

namespace {

    bool IsOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    int GetPriority(char op)
    {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    bool IsDigitChar(char c) { return c >= '0' && c <= '9'; }

    bool IsLetterChar(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    // Добавляет токен в строку через пробел-разделитель
    void AppendToken(std::string& out, const std::string& token)
    {
        if (!out.empty()) out += ' ';
        out += token;
    }

    // Безопасный разбор числа: "12", "3.5", ".5" ...
    double ParseNumber(const std::string& token)
    {
        std::istringstream iss(token);
        double value;
        if (!(iss >> value) || !(iss >> std::ws).eof())
            throw std::runtime_error("TPostfix: invalid number \"" + token + "\"");
        return value;
    }

} // namespace

std::string TPostfix::ToPostfix()
{
    postfix.clear();

    std::string output;
    TStack<char> opstack(MaxStackSize);

    size_t i = 0;
    const size_t n = infix.length();

    while (i < n)
    {
        char c = infix[i];

        if (c == ' ') { ++i; continue; }

        // число (целое или дробное)
        if (IsDigitChar(c) || c == '.')
        {
            size_t start = i;
            while (i < n && (IsDigitChar(infix[i]) || infix[i] == '.')) ++i;
            AppendToken(output, infix.substr(start, i - start));
            continue;
        }

        // переменная — одна буква
        if (IsLetterChar(c))
        {
            AppendToken(output, std::string(1, c));
            ++i;
            continue;
        }

        // открывающая скобка
        if (c == '(')
        {
            opstack.Push(c);
            ++i;
            continue;
        }

        // закрывающая скобка
        if (c == ')')
        {
            while (!opstack.IsEmpty() && opstack.Top() != '(')
                AppendToken(output, std::string(1, opstack.Pop()));
            if (opstack.IsEmpty())
                throw std::runtime_error("TPostfix: mismatched ')'");
            opstack.Pop();
            ++i;
            continue;
        }

        // бинарный оператор
        if (IsOperator(c))
        {
            while (!opstack.IsEmpty() && GetPriority(opstack.Top()) >= GetPriority(c))
                AppendToken(output, std::string(1, opstack.Pop()));
            opstack.Push(c);
            ++i;
            continue;
        }

        throw std::runtime_error(std::string("TPostfix: unexpected char '") + c + "'");
    }

    // выталкиваем остаток стека
    while (!opstack.IsEmpty())
    {
        char op = opstack.Pop();
        if (op == '(')
            throw std::runtime_error("TPostfix: mismatched '('");
        AppendToken(output, std::string(1, op));
    }

    postfix = output;
    return postfix;
}

double TPostfix::Calculate()
{
    if (postfix.empty())
        ToPostfix();

    TStack<double> stack(MaxStackSize);

    // "map" из двух массивов: индекс — код символа
    double varValue[256] = { 0 };
    bool   varKnown[256] = { false };

    std::istringstream iss(postfix);
    std::string token;

    while (iss >> token)
    {
        // переменная
        if (token.size() == 1 && IsLetterChar(token[0]))
        {
            unsigned char idx = static_cast<unsigned char>(token[0]);
            if (!varKnown[idx])
            {
                std::cout << token[0] << " = ";
                if (!(std::cin >> varValue[idx]))
                    throw std::runtime_error("TPostfix: failed to read variable value");
                varKnown[idx] = true;
            }
            stack.Push(varValue[idx]);
            continue;
        }

        // оператор
        if (token.size() == 1 && IsOperator(token[0]))
        {
            if (stack.GetCount() < 2)
                throw std::runtime_error("TPostfix: not enough operands for '" + token + "'");

            const double b = stack.Pop();
            const double a = stack.Pop();
            double r = 0.0;

            switch (token[0])
            {
            case '+': r = a + b; break;
            case '-': r = a - b; break;
            case '*': r = a * b; break;
            case '/':
                if (b == 0.0)
                    throw std::domain_error("TPostfix: division by zero");
                r = a / b;
                break;
            }
            stack.Push(r);
            continue;
        }

        // число
        stack.Push(ParseNumber(token));
    }

    if (stack.GetCount() != 1)
        throw std::runtime_error("TPostfix: expression does not reduce to a single value");

    return stack.Pop();
}