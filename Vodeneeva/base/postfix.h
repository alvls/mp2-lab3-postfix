#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include "stack.h"

enum class LexemeKind
{
  Number,
  Variable,
  Function,
  BinaryOp,
  UnaryMinus,
  UnaryPlus,
  LeftBracket,
  RightBracket
};

struct Lexeme
{
  LexemeKind kind;
  std::string text;
  double value;
  size_t pos;

  Lexeme()
      : kind(LexemeKind::Number), value(0.0), pos(0) {}
  Lexeme(LexemeKind k, const std::string& t, size_t p, double v = 0.0)
      : kind(k), text(t), value(v), pos(p) {}
};

class TSyntaxError : public std::invalid_argument
{
  size_t position;

public:
  TSyntaxError(const std::string& message, size_t pos)
      : std::invalid_argument(message), position(pos) {}
  size_t GetPosition() const { return position; }
};

class TPostfix
{
  std::string infix;
  std::vector<Lexeme> lexemes;
  std::vector<Lexeme> postfix;
  std::vector<std::string> variables;

  void Tokenize();
  void Validate() const;
  void BuildPostfix();

public:
  TPostfix();
  explicit TPostfix(const std::string& expression);

  void SetInfix(const std::string& expression);

  std::string GetInfix() const { return infix; }
  std::string GetPostfix() const;
  std::vector<std::string> GetVariables() const { return variables; }

  double Calculate(const std::map<std::string, double>& values) const;
};

#endif
