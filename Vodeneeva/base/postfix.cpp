#include "postfix.h"
#include "stack.h"

#include <algorithm>
#include <clocale>
#include <cmath>
#include <cstdlib>
#include <sstream>

namespace
{

// ------------------------------------------------------------------
// Встроенные функции
// ------------------------------------------------------------------

// Функции, которые можно использовать в выражении
bool IsFunction(const std::string& name)
{
  return name == "sin" || name == "cos" || name == "tg" || name == "ln" ||
         name == "exp" || name == "sqrt" || name == "abs";
}

double ApplyFunction(const std::string& name, double x)
{
  if (name == "sin")
    return std::sin(x);
  if (name == "cos")
    return std::cos(x);
  if (name == "tg")
  {
    if (std::fabs(std::cos(x)) < 1e-12)
      throw std::domain_error("tg не определён в этой точке");
    return std::tan(x);
  }
  if (name == "ln")
  {
    if (x <= 0.0)
      throw std::domain_error("ln определён только для положительных чисел");
    return std::log(x);
  }
  if (name == "exp")
    return std::exp(x);
  if (name == "sqrt")
  {
    if (x < 0.0)
      throw std::domain_error("sqrt от отрицательного числа");
    return std::sqrt(x);
  }
  return std::fabs(x); // abs
}

// ------------------------------------------------------------------
// Классы символов
// ------------------------------------------------------------------

bool IsLatinLetter(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
bool IsDecimalDigit(char c)
{
  return c >= '0' && c <= '9';
}
bool IsNameChar(char c)
{
  return IsLatinLetter(c) || IsDecimalDigit(c) || c == '_';
}
bool IsOperationChar(char c)
{
  return std::string("+-*/^").find(c) != std::string::npos;
}

// Перевод записи числа ("12", "3.75") в double.
// strtod берёт разделитель дробной части из текущей локали
// (после setlocale(LC_ALL, "Russian") это запятая), поэтому
// точка заменяется на разделитель локали.
double TextToDouble(const std::string& text)
{
  std::string s = text;
  std::replace(s.begin(), s.end(), '.', *std::localeconv()->decimal_point);
  return std::strtod(s.c_str(), nullptr);
}

// ------------------------------------------------------------------
// Порядок лексем
// ------------------------------------------------------------------

// После таких лексем операнд закончен: дальше может идти
// бинарная операция, ')' или конец выражения
bool FinishesOperand(LexemeKind k)
{
  return k == LexemeKind::Number || k == LexemeKind::Variable ||
         k == LexemeKind::RightBracket;
}

// С таких лексем может начинаться операнд
bool StartsOperand(LexemeKind k)
{
  return k == LexemeKind::Number || k == LexemeKind::Variable ||
         k == LexemeKind::Function || k == LexemeKind::LeftBracket ||
         k == LexemeKind::UnaryMinus || k == LexemeKind::UnaryPlus;
}

// ------------------------------------------------------------------
// Приоритеты операций
// ------------------------------------------------------------------

// Скобки и функции имеют приоритет 0: операции их из стека не выталкивают
int Precedence(const Lexeme& lx)
{
  if (lx.kind == LexemeKind::UnaryMinus)
    return 30;
  if (lx.kind != LexemeKind::BinaryOp)
    return 0;
  switch (lx.text[0])
  {
  case '+':
  case '-':
    return 10;
  case '*':
  case '/':
    return 20;
  default: // '^'
    return 40;
  }
}

// Нужно ли перенести операцию с вершины стека в выходную строку
// перед тем, как положить в стек бинарную операцию incoming.
// Возведение в степень правоассоциативно: a^b^c = a^(b^c).
bool MustPopBefore(const Lexeme& onStack, const Lexeme& incoming)
{
  const int stackPrec = Precedence(onStack);
  const int inPrec = Precedence(incoming);
  if (stackPrec == 0)
    return false;
  if (incoming.text == "^")
    return stackPrec > inPrec;
  return stackPrec >= inPrec;
}

double ApplyBinary(char operation, double left, double right)
{
  switch (operation)
  {
  case '+':
    return left + right;
  case '-':
    return left - right;
  case '*':
    return left * right;
  case '/':
    if (right == 0.0)
      throw std::domain_error("деление на ноль");
    return left / right;
  case '^':
    if (left == 0.0 && right < 0.0)
      throw std::domain_error("ноль в отрицательной степени");
    if (left < 0.0 && right != std::floor(right))
      throw std::domain_error("дробная степень отрицательного числа");
    return std::pow(left, right);
  default:
    throw std::logic_error("неизвестная операция");
  }
}

// Как лексема записывается в постфиксной форме
std::string PostfixText(const Lexeme& lx)
{
  return lx.kind == LexemeKind::UnaryMinus ? "neg" : lx.text;
}

} // namespace

// ------------------------------------------------------------------
// TPostfix
// ------------------------------------------------------------------

TPostfix::TPostfix()
    : TPostfix("a + b")
{
}

TPostfix::TPostfix(const std::string& expression)
    : infix(expression)
{
  Tokenize();
  Validate();
  BuildPostfix();
}

void TPostfix::SetInfix(const std::string& expression)
{
  TPostfix fresh(expression); // если выражение неверное, исключение будет здесь
  *this = fresh;
}

void TPostfix::Tokenize()
{
  lexemes.clear();
  variables.clear();

  const size_t n = infix.size();
  size_t i = 0;
  while (i < n)
  {
    const char c = infix[i];
    const size_t start = i;

    if (c == ' ' || c == '\t')
    {
      i++;
    }
    else if (IsDecimalDigit(c))
    {
      // число: цифры, затем, возможно, точка и ещё цифры
      while (i < n && IsDecimalDigit(infix[i]))
        i++;
      if (i < n && infix[i] == '.')
      {
        i++;
        if (i == n || !IsDecimalDigit(infix[i]))
          throw TSyntaxError("после десятичной точки должна идти цифра", i);
        while (i < n && IsDecimalDigit(infix[i]))
          i++;
      }
      const std::string text = infix.substr(start, i - start);
      lexemes.push_back(Lexeme(LexemeKind::Number, text, start, TextToDouble(text)));
    }
    else if (IsLatinLetter(c))
    {
      // имя: функция или переменная
      while (i < n && IsNameChar(infix[i]))
        i++;
      const std::string name = infix.substr(start, i - start);
      if (IsFunction(name))
      {
        lexemes.push_back(Lexeme(LexemeKind::Function, name, start));
      }
      else
      {
        lexemes.push_back(Lexeme(LexemeKind::Variable, name, start));
        if (std::find(variables.begin(), variables.end(), name) == variables.end())
          variables.push_back(name);
      }
    }
    else if (c == '(')
    {
      lexemes.push_back(Lexeme(LexemeKind::LeftBracket, "(", start));
      i++;
    }
    else if (c == ')')
    {
      lexemes.push_back(Lexeme(LexemeKind::RightBracket, ")", start));
      i++;
    }
    else if (IsOperationChar(c))
    {
      // '+' и '-' унарные, если перед ними нет законченного операнда
      const bool unaryPlace = lexemes.empty() || !FinishesOperand(lexemes.back().kind);
      LexemeKind kind = LexemeKind::BinaryOp;
      if (unaryPlace && c == '-')
        kind = LexemeKind::UnaryMinus;
      else if (unaryPlace && c == '+')
        kind = LexemeKind::UnaryPlus;
      lexemes.push_back(Lexeme(kind, std::string(1, c), start));
      i++;
    }
    else
    {
      throw TSyntaxError(std::string("недопустимый символ '") + c + "'", start);
    }
  }
}

void TPostfix::Validate() const
{
  if (lexemes.empty())
    throw TSyntaxError("выражение пустое", 0);

  int openBrackets = 0;
  for (size_t i = 0; i < lexemes.size(); i++)
  {
    const Lexeme& cur = lexemes[i];

    if (i > 0 && lexemes[i - 1].kind == LexemeKind::Function)
    {
      if (cur.kind != LexemeKind::LeftBracket)
        throw TSyntaxError("после " + lexemes[i - 1].text + " должна идти '('", cur.pos);
    }
    else
    {
      const bool afterOperand = (i > 0) && FinishesOperand(lexemes[i - 1].kind);
      if (afterOperand && StartsOperand(cur.kind))
        throw TSyntaxError("пропущена операция перед '" + cur.text + "'", cur.pos);
      if (!afterOperand && !StartsOperand(cur.kind))
        throw TSyntaxError("пропущен операнд перед '" + cur.text + "'", cur.pos);
    }

    if (cur.kind == LexemeKind::LeftBracket)
    {
      openBrackets++;
    }
    else if (cur.kind == LexemeKind::RightBracket)
    {
      if (openBrackets == 0)
        throw TSyntaxError("лишняя закрывающая скобка", cur.pos);
      openBrackets--;
    }
  }

  const Lexeme& last = lexemes.back();
  const size_t endPos = last.pos + last.text.size();
  if (last.kind == LexemeKind::Function)
    throw TSyntaxError("после " + last.text + " должна идти '('", endPos);
  if (!FinishesOperand(last.kind))
    throw TSyntaxError("выражение не закончено: не хватает операнда", endPos);
  if (openBrackets != 0)
    throw TSyntaxError("не хватает закрывающей скобки", endPos);
}

// Алгоритм Дейкстры: операнды сразу идут в выходную строку,
// операции, функции и '(' проходят через стек
void TPostfix::BuildPostfix()
{
  postfix.clear();
  TStack<Lexeme> pending;

  for (const Lexeme& lx : lexemes)
  {
    switch (lx.kind)
    {
    case LexemeKind::Number:
    case LexemeKind::Variable:
      postfix.push_back(lx);
      break;
    case LexemeKind::UnaryPlus:
      break; // +x == x
    case LexemeKind::Function:
    case LexemeKind::UnaryMinus:
    case LexemeKind::LeftBracket:
      pending.Push(lx);
      break;
    case LexemeKind::RightBracket:
      while (pending.Top().kind != LexemeKind::LeftBracket)
        postfix.push_back(pending.Pop());
      pending.Pop(); // сама '('
      if (!pending.IsEmpty() && pending.Top().kind == LexemeKind::Function)
        postfix.push_back(pending.Pop());
      break;
    case LexemeKind::BinaryOp:
      while (!pending.IsEmpty() && MustPopBefore(pending.Top(), lx))
        postfix.push_back(pending.Pop());
      pending.Push(lx);
      break;
    }
  }
  while (!pending.IsEmpty())
    postfix.push_back(pending.Pop());
}

std::string TPostfix::GetPostfix() const
{
  std::ostringstream result;
  for (size_t i = 0; i < postfix.size(); i++)
  {
    if (i > 0)
      result << ' ';
    result << PostfixText(postfix[i]);
  }
  return result.str();
}

double TPostfix::Calculate(const std::map<std::string, double>& values) const
{
  TStack<double> operands;

  for (const Lexeme& lx : postfix)
  {
    switch (lx.kind)
    {
    case LexemeKind::Number:
      operands.Push(lx.value);
      break;
    case LexemeKind::Variable:
    {
      std::map<std::string, double>::const_iterator it = values.find(lx.text);
      if (it == values.end())
        throw std::out_of_range("не задано значение переменной " + lx.text);
      operands.Push(it->second);
      break;
    }
    case LexemeKind::UnaryMinus:
      operands.Top() = -operands.Top();
      break;
    case LexemeKind::Function:
      operands.Top() = ApplyFunction(lx.text, operands.Top());
      break;
    case LexemeKind::BinaryOp:
    {
      const double right = operands.Pop();
      const double left = operands.Pop();
      operands.Push(ApplyBinary(lx.text[0], left, right));
      break;
    }
    default: // скобок и унарного плюса в постфиксной форме нет
      break;
    }
  }
  return operands.Pop();
}
