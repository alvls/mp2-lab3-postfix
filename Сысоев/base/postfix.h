#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#include <cstdlib>
#include <string>
#include "stack.h"
#include <vector>
#include <iostream>
using namespace std;
class TPostfix
{
  string infix;
  string postfix;
  vector<string> postf;//не нужен
  vector <string> operand_name;
  vector <char> val;//не нужен
public:
  TPostfix(string inf="")
  {
      infix = inf;
    //infix = "a + b";
      //postf.push_back(infix);
  }
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  vector <string> vstavka(vector<string> postf, string vstavka, int position, int k)//исходный вектор, вставляемый вектор, позиция, на которую ставится строка (нумерация начинается с 0), количество строк, которые надо удалить после номера position
  {
      vector<string> res;
      int size_vect = postf.size();
      for (int i = 0; i < position; i++)
          res.push_back(postf[i]);
      res.push_back(vstavka);
      for (int i = position + k; i < size_vect; i++)
          res.push_back(postf[i]);
      return(res);
  }
  vector <string> make_list_of_operands(vector <string> postf)//для более качественной проверки гугл тестами
  {
      int size = postf.size();
      vector <string> operand_name;
      for (int i = 0; i < size; i++)
      {
          if ((postf[i] != "-") && (postf[i] != "+") && (postf[i] != "*") && (postf[i] != "/"))
          {
              operand_name.push_back(postf[i]);
          }
      }
      return (operand_name);
  }
  vector <string> Get_list_of_operands()//возврат значения для проверки гугл тестами
  {
      return (operand_name);
  }
  bool proverka_na_razlozhenie(vector <string> v)//для проверки гугл тестами
  {
      int size = v.size();
      bool flag = true;
      for (int i = 0; i < size; i++)
      {
          if (v[i].size() > 1)
              flag = false;
      }
      return (flag);
  }
  void ToPostfix()//сделать постфиксную форму
  {
      int size = infix.size();
      //cout <<  size << '\n';
      TStack <char> stack(size+2);
      stack.push('(');
      for (int i = 0; i < size; i++)
      {
          if ((infix[i] != '*') && (infix[i] != '/') && (infix[i] != '-') && (infix[i] != '+') && (infix[i] != '(') && (infix[i] != ')'))//т.е это операнд
          {
              postfix.push_back(infix[i]);
          }
          else
              if (infix[i] == '(')
                  stack.push(infix[i]);
              else
                  if (infix[i] == ')')
                  {
                      char tmp = stack.pop();
                      
                      while (tmp != '(')
                      {
                          postfix.push_back(tmp);
                          tmp = stack.pop();
                      }
                  }
                  else//унарная операция
                      if (( (infix[i] == '-') || (infix[i] == '+'))&&((((i-1)>=0)&&(infix[i-1]=='(' ))||(i==0)))
                          stack.push(infix[i]);
                      else //бинарная операция
                      {
                          if (stack.isfull())
                          {
                              char tmp = stack.pop();
                              TStack <char> temp(size);
                              while (tmp != '(')
                              {
                                  if ((((infix[i] == '/') || (infix[i] == '*')) && ((tmp == '/') || (tmp == '*'))) || ((infix[i] == '+') || (infix[i] == '-')))
                                  {
                                      postfix.push_back(tmp);
                                  }
                                  else
                                  {
                                      temp.push(tmp);
                                  }
                                  tmp = stack.pop();
                              }
                              temp.push('(');
                              while ((temp.isfull() == true))
                              {
                                  stack.push(temp.pop());
                              }
                              stack.push(infix[i]);
                          }
                          else
                          {
                              stack.push('(');
                              stack.push(infix[i]);
                          }
                              
                      }
      }
     
      if (stack.isfull())
      {
          char tmp = stack.pop();
          while ((tmp != '(')&&(stack.isfull()))
          {
              postfix.push_back(tmp);
              tmp = stack.pop();
          }
      }
  }
  vector <string> prisvaivanie(vector <string> postf, vector <double> v)//для возможности проверки гугл тестами, первый ргумент - постфиксная форма, второй - значения переменных
  {
      int size=postf.size();
      int j = 0;
      vector <string> res;
      for (int i = 0; i < size; i++)
      {
          if ((postf[i] != "-") && (postf[i] != "+") && (postf[i] != "*") && (postf[i] != "/"))
          {
              res.push_back(to_string(v[j]));
              j++;
          }
          else
          {
              res.push_back(postf[i]);
          }
      }
      return(res);
  }
  double Calculate()
  {
      vector<double> v;
      int size = postfix.size();
      vector <string> postf;
      for (int i = 0; i < size; i++)
      {
          string tmp;
          tmp.push_back(postfix[i]);
          postf.push_back(tmp);
      }
      vector <string> operand_name = make_list_of_operands(postf);//это для пользователя
      double tmp;
      int sz = operand_name.size();
      for (int i = 0; i < sz; i++)
      {
          double tmp;
          cout<< operand_name[i] <<"=";
          cin >> tmp;
          v.push_back(tmp);
      }
      double op1, op2, res;
      sz = postf.size();
      postf = prisvaivanie(postf, v);
      while (postf.size() > 1)
      {
          for (int i = 0; i < postf.size(); i++)
          {
              if ((postf[i] == "+")&&(i > 1))
              {
                  op1 = stod(postf[i - 2]);
                  op2 = stod(postf[i - 1]);
                  res = op1 + op2;
                  string r = to_string(res);
                  postf = vstavka(postf, r, (i - 2), 3);
                  break;
              }
              if ((postf[i] == "+") && (i == 1))
              {
                  op2 = stod(postf[i - 1]);
                  res = op2;
                  string r = to_string(res);
                  postf = vstavka(postf, r, (i - 1), 2);
                  break;
              }
              if ((postf[i] == "-")&&(i>1))
              {
                  op1 = stod(postf[i - 2]);
                  op2 = stod(postf[i - 1]);
                  res = op1 - op2;
                  string r = to_string(res);
                  postf = vstavka(postf, r, (i - 2), 3);
                  break;
              }
              if ((postf[i] == "-") && (i == 1))
              {
                  op2 = stod(postf[i - 1]);
                  res = - op2;
                  string r = to_string(res);
                  postf = vstavka(postf, r, (i - 1), 2);
                  break;
              }
              if (postf[i] == "*")
              {
                  op1 = stod(postf[i - 2]);
                  op2 = stod(postf[i - 1]);
                  res = op1 * op2;
                  string r = to_string(res);
                  postf = vstavka(postf, r, (i - 2), 3);
                  break;
              }
              if (postf[i] == "/")
              {
                  op1 = stod(postf[i - 2]);
                  op2 = stod(postf[i - 1]);
                  res = op1 / op2;
                  string r = to_string(res);
                  postf = vstavka(postf, r, (i - 2), 3);
                  break;
              }
          }
      }
      res = stod(postf[0]);
      return (res);
  }
};

#endif
