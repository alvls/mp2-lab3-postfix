#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <cmath>
#include "stack.h"

using namespace std;

class ExpressionError : public exception {
    string message;
    size_t position;
public:
    ExpressionError(const string& msg, size_t pos);

    const char* what() const noexcept override;

    size_t getPosition() const noexcept;
};


class MissingOperandValueError : public exception {
    string message;
public:
    MissingOperandValueError(const string& operand);

    const char* what() const noexcept override;
};


class ExpressionValidator {
    static void CheckValidCharacters(const std::string& expr);
    static void CheckBrackets(const string& expr);

public:
    static bool IsOperator(char c);

    static void Validate(const string& expr);
};


class Parser {
public:
    static vector<string> Parse(const string& str);
};


class InfixToPostfixConverter {
public:
    static map<string, int> priority;

    static string Convert(const string& infix, map<string, double>& operands);
};


class PostfixCalculator {
    static double Factorial(double n);
    static double Function(const string& func, double arg);

public:
    static double Calculate(const string& postfix, const map<string, double>& operands);
};


class TArithmeticExpression {
    string infix;
    string postfix;
    map<string, double> operands;
public:
    TArithmeticExpression(const string& expr = "");
    string GetInfix() const;
    string GetPostfix() const;
    vector<string> GetOperands() const;
    double Calculate(const map<string, double>& values);
};


#endif
