#include "postfix.h"

#include "postfix.h"

// ExpressionError

ExpressionError::ExpressionError(const string& msg, size_t pos)
    : message(msg), position(pos) {}

const char* ExpressionError::what() const noexcept {
    return message.c_str();
}

size_t ExpressionError::getPosition() const noexcept {
    return position;
}


// MissingOperandValueError

MissingOperandValueError::MissingOperandValueError(const string& operand)
    : message("Missing value for operand: " + operand) {}

const char* MissingOperandValueError::what() const noexcept {
    return message.c_str();
}


// ExpressionValidator

void ExpressionValidator::CheckValidCharacters(const std::string& expr) {
    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (!isdigit(c) && !isalpha(c) && !IsOperator(c) && c != '(' && c != ')'
            && c != ' ' && c != '.') {
            throw ExpressionError("Invalid character in expression", i);
        }
    }
}

void ExpressionValidator::CheckBrackets(const string& expr) {
    TStack<int> brStack;
    for (size_t i = 0; i < expr.size(); i++) {
        if (expr[i] == '(') {
            brStack.Push(i);
        }
        else if (expr[i] == ')') {
            if (brStack.IsEmpty()) {
                throw ExpressionError("Closing parenthesis is not matched", i);
            }
            brStack.Pop();
        }
    }
    if (!brStack.IsEmpty()) {
        throw ExpressionError("One or more opening parentheses are not paired", brStack.Size() - 1);
    }
}

bool ExpressionValidator::IsOperator(char c) {
    switch (c) {
    case '+': case '-': case '*': case '/': case '!': case '^': return true;
    default: return false;
    }
}

void ExpressionValidator::Validate(const string& expr) {
    CheckValidCharacters(expr);
    CheckBrackets(expr);
}


// Parser

vector<string> Parser::Parse(const string& str) {
    vector<string> lexems;
    string cur;
    bool LastWasOperator = true;
    for (size_t i = 0; i < str.size(); i++) {
        char c = str[i];
        if (isdigit(c) || (c == '.' && !cur.empty() && isdigit(cur.back()))) {
            cur += c;
            LastWasOperator = false;
        }
        else if (isalpha(c)) {
            cur += c;
            LastWasOperator = false;
        }
        else if (ExpressionValidator::IsOperator(c) || c == '(' || c == ')') {
            if (!cur.empty()) {
                lexems.push_back(cur);
                cur.clear();
            }
            if (c == '-' && (LastWasOperator || lexems.empty()))
                lexems.push_back("_");
            else
                lexems.push_back(string(1, c));
            LastWasOperator = (c != ')');
        }
        else if (c == ' ' && !cur.empty()) {
            lexems.push_back(cur);
            cur.clear();
        }
        else if (c == '!' && !cur.empty()) {
            lexems.push_back(cur);
            lexems.push_back("!");
            cur.clear();
        }
    }
    if (!cur.empty())
        lexems.push_back(cur);
    return lexems;
}


// InfixToPostfixConverter

map<string, int> InfixToPostfixConverter::priority = {
    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"_", 4}, {"!", 5},
    {"sin", 6}, {"cos", 6}, { "log", 6}, {"sqrt", 6}
};

string InfixToPostfixConverter::Convert(const string& infix, map<string, double>& operands) {
    string postfix;
    vector<string> lexems = Parser::Parse(infix);
    TStack<string> st;
    string stItem;
    for (const string& item : lexems) {
        if (item == "(") st.Push(item);
        else if (item == ")") {
            stItem = st.Top(); st.Pop();
            while (stItem != "(") {
                postfix += stItem + " ";
                stItem = st.Top(); st.Pop();
            }
            if (!st.IsEmpty() && isalpha(st.Top()[0])) { // функция перед открывающей скобкой
                postfix += st.Top() + " ";
                st.Pop();
            }
        }
        else if (priority.count(item)) { // проверка что item является оператором
            while (!st.IsEmpty()) {
                stItem = st.Top(); st.Pop();
                if (priority[item] <= priority[stItem])
                    postfix += stItem + " ";
                else {
                    st.Push(stItem);
                    break;
                }
            }
            st.Push(item);
        }
        else {
            operands.insert({ item, 0.0 });
            postfix += item + " ";
        }
    }
    while (!st.IsEmpty()) {
        stItem = st.Top(); st.Pop();
        postfix += stItem + " ";
    }
    return postfix;
}


// PostfixCalculator

double PostfixCalculator::Factorial(double n) {
    if (n < 0) throw runtime_error("factorial of negative number");
    if (n != floor(n)) throw runtime_error("factorial of non-integer number");
    if (n == 0 || n == 1) return 1;
    double res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

double PostfixCalculator::Function(const string& func, double arg) {
    if (func == "sin") return sin(arg);
    if (func == "cos") return cos(arg);
    if (func == "log") return log(arg);
    if (func == "sqrt") {
        if (arg < 0) throw runtime_error("sqrt of negative number");
        return sqrt(arg);
    }
    throw runtime_error("Unknown function: " + func);
}

double PostfixCalculator::Calculate(const string& postfix, const map<string, double>& operands) {
    TStack<double> st;
    stringstream ss(postfix);
    string lexem;
    double leftOp, rightOp;
    while (ss >> lexem) {
        if (lexem == "+") {
            rightOp = st.Top(); st.Pop();
            leftOp = st.Top(); st.Pop();
            st.Push(leftOp + rightOp);
        }
        else if (lexem == "-") {
            rightOp = st.Top(); st.Pop();
            leftOp = st.Top(); st.Pop();
            st.Push(leftOp - rightOp);
        }
        else if (lexem == "*") {
            rightOp = st.Top(); st.Pop();
            leftOp = st.Top(); st.Pop();
            st.Push(leftOp * rightOp);
        }
        else if (lexem == "/") {
            rightOp = st.Top();
            if (rightOp == 0.0) throw runtime_error("division by zero");
            st.Pop();
            leftOp = st.Top(); st.Pop();
            st.Push(leftOp / rightOp);
        }
        else if (lexem == "^") {
            rightOp = st.Top(); st.Pop();
            leftOp = st.Top(); st.Pop();
            st.Push(pow(leftOp, rightOp));
        }
        else if (lexem == "_") {
            rightOp = st.Top();
            st.Pop();
            st.Push(-rightOp);
        }
        else if (lexem == "!") {
            rightOp = st.Top(); st.Pop();
            st.Push(Factorial(rightOp));
        }
        else if (InfixToPostfixConverter::priority.count(lexem) && InfixToPostfixConverter::priority[lexem] == 6) { // функции
            rightOp = st.Top(); st.Pop();
            st.Push(Function(lexem, rightOp));
        }
        else {
            try {
                double value = stod(lexem); // обработка числовых значений
                st.Push(value);
            }
            catch (invalid_argument& e) {
                st.Push(operands.at(lexem)); // обработка переменных
            }
        }
    }
    return st.Top();
}


// TArithmeticExpression

TArithmeticExpression::TArithmeticExpression(const string& expr) : infix(expr) {
    ExpressionValidator::Validate(infix);
    postfix = InfixToPostfixConverter::Convert(infix, operands);
}

string TArithmeticExpression::GetInfix() const { return infix; }
string TArithmeticExpression::GetPostfix() const { return postfix; }

vector<string> TArithmeticExpression::GetOperands() const {
    vector<string> op_list;
    for (const auto& op : operands) {
        try {
            double p = stod(op.first);
        }
        catch (invalid_argument& e) {
            op_list.push_back(op.first);
        }
    }
    return op_list;
}

double TArithmeticExpression::Calculate(const map<string, double>& values) {
    for (const auto& operand : operands) {
        try {
            double op = stod(operand.first);
        }
        catch (invalid_argument& e) {
            if (values.find(operand.first) == values.end()) {
                throw MissingOperandValueError(operand.first);
            }
        }
    }
    for (auto& val : values) {
        try {
            operands.at(val.first) = val.second;
        }
        catch (out_of_range& e) {}
    }
    return PostfixCalculator::Calculate(postfix, operands);
}