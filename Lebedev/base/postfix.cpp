#include "postfix.h"
#include "stack.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

static bool IsDigit(char c)
{
  return c >= '0' && c <= '9';
}

static bool IsLetter(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static bool IsFunction(const string &s)
{
  return s == "sin" || s == "cos" || s == "sqrt" || s == "abs";
}

static bool IsNumber(const string &s)
{
  return IsDigit(s[0]) || s[0] == '.';
}

static bool IsVariable(const string &s)
{
  return IsLetter(s[0]) && !IsFunction(s);
}

static int Priority(const string &op)
{
  if (op == "+" || op == "-")
    return 1;
  if (op == "*" || op == "/")
    return 2;
  if (op == "~")
    return 3;
  if (op == "^")
    return 4;
  return 0;
}

static bool NeedPop(const string &top, const string &op)
{
  if (op == "^")
    return Priority(top) > Priority(op);
  return Priority(top) >= Priority(op);
}

static double ToNumber(const string &s)
{
  double res = 0;
  double div = 1;
  bool afterDot = false;
  for (size_t i = 0; i < s.size(); i++)
  {
    if (s[i] == '.')
      afterDot = true;
    else
    {
      res = res * 10 + (s[i] - '0');
      if (afterDot)
        div *= 10;
    }
  }
  return res / div;
}

static double CalcFunction(const string &f, double x)
{
  if (f == "sin")
    return sin(x);
  if (f == "cos")
    return cos(x);
  if (f == "abs")
    return fabs(x);
  if (x < 0)
    throw runtime_error("Square root of negative number");
  return sqrt(x);
}

static double CalcOperation(const string &op, double left, double right)
{
  if (op == "+")
    return left + right;
  if (op == "-")
    return left - right;
  if (op == "*")
    return left * right;
  if (op == "/")
  {
    if (right == 0)
      throw runtime_error("Division by zero");
    return left / right;
  }
  return pow(left, right);
}

TPostfix::TPostfix(const string &expr)
{
  infix = expr;
  Parse();
  ToPostfix();
}

void TPostfix::Parse()
{
  lexems.clear();
  size_t i = 0;
  while (i < infix.size())
  {
    char c = infix[i];
    if (c == ' ' || c == '\t')
      i++;
    else if (IsDigit(c) || c == '.')
    {
      string num;
      int dots = 0;
      while (i < infix.size() && (IsDigit(infix[i]) || infix[i] == '.'))
      {
        if (infix[i] == '.')
          dots++;
        num += infix[i];
        i++;
      }
      if (dots > 1 || num == ".")
        throw invalid_argument("Wrong number: " + num);
      lexems.push_back(num);
    }
    else if (IsLetter(c))
    {
      string name;
      while (i < infix.size() && (IsLetter(infix[i]) || IsDigit(infix[i])))
      {
        name += infix[i];
        i++;
      }
      lexems.push_back(name);
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')')
    {
      lexems.push_back(string(1, c));
      i++;
    }
    else
      throw invalid_argument(string("Unknown symbol: ") + c);
  }
  if (lexems.empty())
    throw invalid_argument("Empty expression");
}

void TPostfix::ToPostfix()
{
  postfix.clear();
  operands.clear();
  TStack<string> st;
  bool waitOperand = true;
  int brackets = 0;
  for (size_t i = 0; i < lexems.size(); i++)
  {
    string lex = lexems[i];
    if (IsNumber(lex) || IsVariable(lex))
    {
      if (!waitOperand)
        throw invalid_argument("Missing operation before " + lex);
      postfix.push_back(lex);
      if (IsVariable(lex) && find(operands.begin(), operands.end(), lex) == operands.end())
        operands.push_back(lex);
      waitOperand = false;
    }
    else if (IsFunction(lex))
    {
      if (!waitOperand)
        throw invalid_argument("Missing operation before " + lex);
      if (i + 1 == lexems.size() || lexems[i + 1] != "(")
        throw invalid_argument("Missing ( after " + lex);
      st.Push(lex);
    }
    else if (lex == "(")
    {
      if (!waitOperand)
        throw invalid_argument("Missing operation before (");
      st.Push(lex);
      brackets++;
    }
    else if (lex == ")")
    {
      if (waitOperand)
        throw invalid_argument("Missing operand before )");
      if (brackets == 0)
        throw invalid_argument("Extra )");
      while (st.Top() != "(")
        postfix.push_back(st.Pop());
      st.Pop();
      brackets--;
      if (!st.IsEmpty() && IsFunction(st.Top()))
        postfix.push_back(st.Pop());
    }
    else if (waitOperand)
    {
      if (lex != "-")
        throw invalid_argument("Missing operand before " + lex);
      st.Push("~");
    }
    else
    {
      while (!st.IsEmpty() && NeedPop(st.Top(), lex))
        postfix.push_back(st.Pop());
      st.Push(lex);
      waitOperand = true;
    }
  }
  if (waitOperand)
    throw invalid_argument("Missing operand at the end");
  if (brackets != 0)
    throw invalid_argument("Missing )");
  while (!st.IsEmpty())
    postfix.push_back(st.Pop());
}

string TPostfix::GetPostfix() const
{
  string res;
  for (size_t i = 0; i < postfix.size(); i++)
  {
    if (i > 0)
      res += ' ';
    res += postfix[i];
  }
  return res;
}

void TPostfix::SetValue(const string &name, double val)
{
  if (find(operands.begin(), operands.end(), name) == operands.end())
    throw invalid_argument("Unknown operand: " + name);
  values[name] = val;
}

void TPostfix::SetValues(const map<string, double> &vals)
{
  for (const auto &p : vals)
    SetValue(p.first, p.second);
}

double TPostfix::Calculate()
{
  TStack<double> st;
  for (const string &lex : postfix)
  {
    if (IsNumber(lex))
      st.Push(ToNumber(lex));
    else if (IsVariable(lex))
    {
      if (values.find(lex) == values.end())
        throw invalid_argument("No value for operand: " + lex);
      st.Push(values[lex]);
    }
    else if (lex == "~")
      st.Push(-st.Pop());
    else if (IsFunction(lex))
      st.Push(CalcFunction(lex, st.Pop()));
    else
    {
      double right = st.Pop();
      double left = st.Pop();
      st.Push(CalcOperation(lex, left, right));
    }
  }
  return st.Pop();
}

double TPostfix::Calculate(const map<string, double> &vals)
{
  SetValues(vals);
  return Calculate();
}
