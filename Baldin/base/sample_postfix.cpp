#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main() {
    try {
        string expression = "-(-ab +babcd* (-(cd - dc)))/ e + (3.5^2 - gh^3) + sin(7) /sqrt(-f) * 3!"; // = 17,09596...
        TArithmeticExpression arithExpr(expression);

        cout << "Infix: " << arithExpr.GetInfix() << endl;
        cout << "Postfix: " << arithExpr.GetPostfix() << endl;
        cout << "Operands of arithmetic expression: ";
        for (string op : arithExpr.GetOperands()) cout << op << ' ';
        cout << '\n';

        map<string, double> operandValues = {
            {"ab", 5.0},
            {"babcd", 2.0},
            {"cd", 8.0},
            {"dc", 3.0},
            {"e", 5.0},
            {"f", -4.0},
            {"gh", 0.5}
        };

        double result = arithExpr.Calculate(operandValues);
        cout << "Result: " << result << endl;
    }
    catch (const ExpressionError& e) {
        cerr << "Error in position " << e.getPosition() << ": " << e.what() << '\n';
    }
    catch (const std::exception& e) {
        cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}