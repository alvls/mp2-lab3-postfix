#include "postfix.h"
#include "stack.h"
#include <stdexcept>

int GetPriority(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string TPostfix::ToPostfix()
{
    postfix = "";
    TStack<char> stack(MaxStackSize);

    for (size_t i = 0; i < infix.length(); ++i)
    {
        char c = infix[i];

        if (c == ' ') 
            continue;

        if (c >= '0' && c <= '9')
        {
            postfix += c;
        }
        else if (c == '(')
        {
            stack.Push(c);
        }
        else if (c == ')')
        {
            while (stack.Top() != '(')
            {
                postfix += stack.Pop();
            }
            stack.Pop();
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            while (!stack.IsEmpty() && GetPriority(stack.Top()) >= GetPriority(c))
            {
                postfix += stack.Pop();
            }
            stack.Push(c);
        }
    }

    while (!stack.IsEmpty())
    {
        postfix += stack.Pop();
    }

    return postfix;
}

double TPostfix::Calculate()
{
    TStack<double> stack(MaxStackSize);

    for (size_t i = 0; i < postfix.length(); ++i)
    {
        char c = postfix[i];

        if (c >= '0' && c <= '9')
        {
            stack.Push(c - '0');
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            double b = stack.Pop();
            double a = stack.Pop();
            double res = 0;

            if (c == '+') res = a + b;
            else if (c == '-') res = a - b;
            else if (c == '*') res = a * b;
            else if (c == '/')
            {
                if (b == 0)
                    throw std::domain_error("Division by zero");
                res = a / b;
            }

            stack.Push(res);
        }
    }

    return stack.Pop();
}