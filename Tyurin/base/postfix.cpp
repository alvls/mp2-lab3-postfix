#include "postfix.h"
#include "stack.h"
#include <iostream>

using namespace std;

map<char, int> TPostfix::priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3} };

TPostfix::TPostfix(string _infix) :infix(_infix) { ToPostfix(); }

string TPostfix::GetInfix() const { return infix; }

string TPostfix::GetPostfix() const { return postfix; }

bool TPostfix::isOperand(char ch)
{
   return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9');
}

bool TPostfix::isOperator(char ch)
{
   return string("+-*/^").find(ch) != string::npos;
}

void TPostfix::ToPostfix()
{
   TStack<char> st;
   postfix = "";

   for (size_t i = 0; i < infix.size(); i++) {
      char ch = infix[i];

      if (isOperand(ch))
         postfix += ch;
      else if (ch == '(')
         st.Push(ch);
      else if (ch == ')') {
         while (!st.isEmpty() && st.getTopElem() != '(')
            postfix += st.Pop();
         st.Pop();
      }
      else if (isOperator(ch)) {
         while (!st.isEmpty() && (priority[ch] <= priority[st.getTopElem()]))
            postfix += st.Pop();
         st.Push(ch);
      }
   }

   while (!st.isEmpty())
      postfix += st.Pop();
}


double TPostfix::Calculate() {

   TStack<double> st;

   for (char item : postfix) {
      if (isOperand(item)) {
         if (isalpha(item))
            st.Push(variables[item]);
         else
            st.Push(item - '0');
      }
      else {
         double rightOperand = st.Pop();
         double leftOperand = st.Pop();

         switch (item) {

         case '+':
            st.Push(leftOperand + rightOperand);
            break;

         case '-':
            st.Push(leftOperand - rightOperand);
            break;

         case '*':
            st.Push(leftOperand * rightOperand);
            break;

         case '/':
            if (right == 0)
               throw "Деление на ноль";
            st.Push(leftOperand / rightOperand);
            break;

         case '^':
            st.Push(pow(leftOperand, rightOperand));
            break;

         default:
            throw "Неподдерживаемая операция";
         }
      }
   }
   if (st.isEmpty())
      throw "Ошибка в выражении";

   double res = st.Pop();
   if (!st.isEmpty())
      throw "Ошибка в выражении";

   return res;
}

void TPostfix::PromptAndStoreVariables()
{
   cout << "Введите значения переменных: " << endl;
   for (char item : infix)
   {
      if (isalpha(item) && variables.find(item) == variables.end())
      {
         cout << item << " = ";
         double val;
         cin >> val;
         variables[item] = val;
      }
   }
}