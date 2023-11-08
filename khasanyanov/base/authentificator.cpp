#include "stack.h"
#include <stdexcept>
#include <string>

enum class SymbolType {
    Digit,
    Dot,
    Letter,
    LeftBracket,
    RightBracket,
    Operator,
    Unknown
};

string eraseSpaces(const string& s)
{
    string res = "";
    for (auto& c : s)
        if (c != ' ')
            res += c;
    return res;
}

inline bool isOperator(const char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '!' || c == '%');
}

SymbolType getType(const char c)
{
    if (c == '(')
    {
        return SymbolType::LeftBracket;
    }
    else if (c == ')')
    {
        return SymbolType::RightBracket;
    }
    else if (isOperator(c))
    {
        return SymbolType::Operator;
    }
    else if (c == '.')
    {
        return SymbolType::Dot;
    }
    else if (isdigit(c))
    {
        return SymbolType::Digit;
    }
    else if (isalpha(c))
    {
        return SymbolType::Letter;
    }
    return SymbolType::Unknown;
}

void autentificateInfix(const string& infix)
{
    SymbolType prev = SymbolType::Unknown;
    TStack<size_t> brackets;
    size_t i = 0;
    for (const char c : infix)
    {
        ++i;
        const SymbolType current = getType(c);
        if (current == SymbolType::Unknown)
            throw invalid_argument("syntax error");
        else if (current == SymbolType::LeftBracket)
            brackets.push(i);
        else if (current == SymbolType::RightBracket)
        {
            if (brackets.empty())
                throw invalid_argument("missing left bracket");
            brackets.pop();
        }
        if (i - 1 == 0 && (isOperator(c) && c != '-' || current == SymbolType::Dot))
            throw invalid_argument("syntax error");
        switch (prev)
        {
        case SymbolType::Digit:
        {
            if (current != SymbolType::Digit && current != SymbolType::Dot && current != SymbolType::Operator && c != ')')
                throw invalid_argument("malformed number");
            break;
        }
        case SymbolType::Dot:
        {
            if (current != SymbolType::Digit)
                throw invalid_argument("malformed number, fractional part expected");
            break;
        }
        case SymbolType::Operator:
        {
            if ((current == SymbolType::RightBracket || current == SymbolType::Operator) && infix[i-2] != '!')
                throw invalid_argument("malformed operator");
            break;
        case SymbolType::LeftBracket:
            if(current == SymbolType::Operator && c != '-')
                throw invalid_argument("malformed operator");
            break;
        }
        }
        prev = current;
    }
    if(prev == SymbolType::Operator && infix[i - 1] != '!')
        throw invalid_argument("useless operator");
    if (!brackets.empty())
        throw invalid_argument("missing right bracket");
}