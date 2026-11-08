#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include "stack.h"

// Виды лексем арифметического выражения
enum class LexemeKind
{
  Number,      // числовая константа: 7, 12.5
  Variable,    // переменная: a, x1, speed
  Function,    // функция: sin, cos, tg, ln, exp, sqrt, abs
  BinaryOp,    // бинарная операция: + - * / ^
  UnaryMinus,  // унарный минус, в постфиксной форме записывается как "neg"
  UnaryPlus,   // унарный плюс, на результат не влияет
  LeftBracket, // (
  RightBracket // )
};

// Одна лексема выражения
struct Lexeme
{
  LexemeKind kind;
  std::string text; // запись лексемы в исходной строке
  double value;     // значение числовой константы
  size_t pos;       // позиция первого символа лексемы в исходной строке

  Lexeme()
      : kind(LexemeKind::Number), value(0.0), pos(0) {}
  Lexeme(LexemeKind k, const std::string& t, size_t p, double v = 0.0)
      : kind(k), text(t), value(v), pos(p) {}
};

// Синтаксическая ошибка в выражении.
// Кроме сообщения хранит позицию символа, на котором найдена ошибка.
class TSyntaxError : public std::invalid_argument
{
  size_t position;

public:
  TSyntaxError(const std::string& message, size_t pos)
      : std::invalid_argument(message), position(pos) {}
  size_t GetPosition() const { return position; }
};

// Арифметическое выражение в инфиксной и постфиксной (обратной польской) форме.
// Выражение разбирается и переводится в постфиксную форму сразу при создании
// объекта; при ошибке в записи выбрасывается TSyntaxError.
//
// Поддерживается: числа (целые и с точкой), переменные (латинская буква,
// затем буквы, цифры, '_'), операции + - * / ^, унарные + и -, скобки,
// функции sin, cos, tg, ln, exp, sqrt, abs. Операция ^ правоассоциативна
// и выполняется раньше унарного минуса: -2^2 = -4.
//
// Ошибки при вычислении:
//   std::out_of_range  - не задано значение переменной;
//   std::domain_error  - деление на ноль, ln или sqrt вне области определения и т.п.
class TPostfix
{
  std::string infix;
  std::vector<Lexeme> lexemes;        // лексемы в порядке записи
  std::vector<Lexeme> postfix;        // лексемы в постфиксном порядке
  std::vector<std::string> variables; // имена переменных без повторов

  void Tokenize();       // строка -> лексемы
  void Validate() const; // проверка порядка лексем и скобок
  void BuildPostfix();   // лексемы -> постфиксная форма
public:
  TPostfix(); // выражение "a + b"
  explicit TPostfix(const std::string& expression);

  // Заменяет выражение. Если новое выражение записано с ошибкой,
  // объект остаётся прежним.
  void SetInfix(const std::string& expression);

  std::string GetInfix() const { return infix; }
  std::string GetPostfix() const; // лексемы через пробел
  std::vector<std::string> GetVariables() const { return variables; }

  // Вычисление при заданных значениях переменных.
  // Лишние значения в словаре игнорируются.
  double Calculate(const std::map<std::string, double>& values) const;
};

#endif
