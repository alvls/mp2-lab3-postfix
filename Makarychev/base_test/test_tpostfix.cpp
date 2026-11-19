#include "postfix.h"
#include <gtest.h>
#include <sstream>
#include <iostream>
#include <stdexcept>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, default_expression_is_preserved)
{
  TPostfix p;
  EXPECT_EQ("a + b", p.GetInfix());
  EXPECT_EQ("a b +", p.ToPostfix());
}
TEST(TPostfix, respects_operator_precedence)
{
  TPostfix p("2 + 3 * 4");
  EXPECT_EQ("2 3 4 * +", p.ToPostfix());
  EXPECT_DOUBLE_EQ(14.0, p.Calculate());
}
TEST(TPostfix, respects_parentheses)
{
  TPostfix p("(2 + 3) * 4");
  EXPECT_EQ("2 3 + 4 *", p.ToPostfix());
  EXPECT_DOUBLE_EQ(20.0, p.Calculate());
}
TEST(TPostfix, handles_subtraction_and_division)
{
  TPostfix p("10 - 8 / 2");
  EXPECT_DOUBLE_EQ(6.0, p.Calculate());
}
TEST(TPostfix, handles_decimal_numbers)
{
  TPostfix p("1.5 + 2.25");
  EXPECT_DOUBLE_EQ(3.75, p.Calculate());
}
TEST(TPostfix, handles_unary_minus)
{
  TPostfix p("-3 + 5");
  EXPECT_DOUBLE_EQ(2.0, p.Calculate());
}
TEST(TPostfix, handles_unary_minus_after_multiplication)
{
  TPostfix p("2 * -3");
  EXPECT_DOUBLE_EQ(-6.0, p.Calculate());
}
TEST(TPostfix, handles_power)
{
  TPostfix p("2 ^ 3 ^ 2");
  EXPECT_DOUBLE_EQ(512.0, p.Calculate());
}
TEST(TPostfix, can_change_expression)
{
  TPostfix p;
  p.SetInfix("4 + 5");
  EXPECT_EQ("4 5 +", p.ToPostfix());
  EXPECT_DOUBLE_EQ(9.0, p.Calculate());
}
TEST(TPostfix, rejects_empty_expression)
{
  TPostfix p("");
  EXPECT_THROW(p.ToPostfix(), std::invalid_argument);
}
TEST(TPostfix, rejects_unbalanced_parentheses)
{
  TPostfix p("(2 + 3");
  EXPECT_THROW(p.ToPostfix(), std::invalid_argument);
}
TEST(TPostfix, rejects_invalid_characters)
{
  TPostfix p("2 @ 3");
  EXPECT_THROW(p.ToPostfix(), std::invalid_argument);
}
TEST(TPostfix, rejects_missing_operator)
{
  TPostfix p("2 3");
  EXPECT_THROW(p.ToPostfix(), std::invalid_argument);
}
TEST(TPostfix, rejects_division_by_zero)
{
  TPostfix p("2 / (3 - 3)");
  EXPECT_THROW(p.Calculate(), std::domain_error);
}
TEST(TPostfix, evaluates_variables)
{
  TPostfix p("a + b * a");
  std::istringstream values("2 3");
  std::streambuf* old = std::cin.rdbuf(values.rdbuf());
  double result = 0;
  try { result = p.Calculate(); }
  catch (...) { std::cin.rdbuf(old); throw; }
  std::cin.rdbuf(old);
  EXPECT_DOUBLE_EQ(8.0, result);
}
