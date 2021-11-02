#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <iostream>
#include <vector>

using namespace std;

class TPostfix
{
private:
    string infix;
    vector<string> postfix;
    int DetermineOperation(const vector<string>& operations, const vector<int>& v_priority, const string& symbol);
    void ChangeStringToVectorForInfix(vector<string>& v);
    void FindAndChangeUnaryMinusOnBinaryMinus();
    void CheckerBrackets();
    //Моя единственная проверка выражения, для этого нужно будет исключения бахнуть
public:
    TPostfix(string _infix) {
        //string temp(_infix);
        //FindAndChangeUnaryMinusOnBinaryMinus(temp);
        infix = _infix;
    }
    void SetInfix(string _infix) {
        //string temp(_infix);
        //FindAndChangeUnaryMinusOnBinaryMinus(temp);
        infix = _infix;
    }
    string GetInfix() { return infix; }
    vector<string> GetPostfix() { return postfix; }
    void ChangeInfixToPostfix();
    double Calculate(); // Ввод переменных, вычисление по постфиксной форме
    
};

#endif
