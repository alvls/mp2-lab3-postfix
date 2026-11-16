#pragma once
#include <string>
#include <vector>
#include <map>

class TPostfix {
private:
    std::string infix;
    std::string postfix;
    std::vector<std::string> tokens;

    bool IsOperator(char c);
    bool IsOperand(const std::string& token);
    int GetPriority(char op);

public:
    TPostfix(const std::string& expr);
    std::string GetInfix() const;
    std::string GetPostfix() const;
    void ToPostfix();
    double Calculate(const std::map<char, double>& vars);
};