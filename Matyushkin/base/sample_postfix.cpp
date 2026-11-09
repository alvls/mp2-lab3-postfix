#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    string expression;
    cout << "Enter expression: ";
    getline(cin, expression);

    TPostfix postfix(expression);

    cout << "Infix:   " << postfix.GetInfix() << endl;
    postfix.ToPostfix();
    cout << "Postfix: " << postfix.GetPostfix() << endl;

    double res = postfix.Calculate();
    cout << "Result:  " << res << endl;

    return 0;
}