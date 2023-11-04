#include "postfix.h"
#include "stack.h"

TPostfix::TPostfix(string infx)
{
    if (infx.empty())
        throw "Infix is empty";
    infix = infx;
    ToPostfix();
}

vector<char> TPostfix::GetOperands() const {

    size_t i = 0;
    vector<char> op(operands.size());
    for (const auto& item : operands) { op[i++] = item.first; }
    return op;
}

void TPostfix::ParseInfix()
{
    for (char c : infix)
        lexems.push_back(c);
}

void TPostfix::ToPostfix() {
    ParseInfix();
    TStack<char> st;
    for (char item : lexems) {
        if (isalnum(item)) {
            postfix += item;
            operands.insert({ item, 0.0 });
        }
        else if (item == '(') {
            st.Push(item);
        }
        else if (item == ')') {
            while (!st.IsEmpty() && st.Peek() != '(') {
                postfix += st.Pop();
            }
            st.Pop();
        }
        else {
            while (!st.IsEmpty() && st.Peek() != '(' && priority[item] <= priority[st.Peek()]) {
                postfix += st.Pop();
            }
            st.Push(item);
        }
    }
    while (!st.IsEmpty()) {
        postfix += st.Pop();
    }
}


double TPostfix::Calculate(const map<char, double>& values) {
    for (const auto& val : values) {
        if (operands.find(val.first) != operands.end()) {
            operands[val.first] = val.second;
        }
    }
    TStack<double> temp;
    double leftOperand, rightOperand;
    for (char lexem : postfix) {
        switch (lexem) {
        case '+':
            rightOperand = temp.Pop();
            leftOperand = temp.Pop();
            temp.Push(leftOperand + rightOperand);
            break;
        case '-':
            rightOperand = temp.Pop();
            leftOperand = temp.Pop();
            temp.Push(leftOperand - rightOperand);
            break;
        case '*':
            rightOperand = temp.Pop();
            leftOperand = temp.Pop();
            temp.Push(leftOperand * rightOperand);
            break;
        case '/':
            rightOperand = temp.Pop();
            leftOperand = temp.Pop();
            temp.Push(leftOperand / rightOperand);
            break;
        case '^':
            rightOperand = temp.Pop();
            leftOperand = temp.Pop();
            temp.Push(pow(leftOperand, rightOperand));
            break;
        default:
            temp.Push(operands[lexem]);
            break;
        }
    }
    return temp.Pop();
}

map<char, int> TPostfix::priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3} };

string TPostfix::GetInfix() const { return infix; }

string TPostfix::GetPostfix() const { return postfix; }