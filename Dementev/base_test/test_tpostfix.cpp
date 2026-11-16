#include "postfix.h"
#include <gtest.h>
#include <stdexcept>
#include <map>

TEST(TPostfix, can_create_postfix_with_string)
{
  ASSERT_NO_THROW(TPostfix p("2+2"));
}

TEST(TPostfix, converts_to_postfix_correctly)
{
  TPostfix p("2+3*4");
  p.ToPostfix();
  EXPECT_EQ(p.GetPostfix(), "2 3 4 * +");
}

TEST(TPostfix, converts_with_brackets)
{
  TPostfix p("(2+3)*4");
  p.ToPostfix();
  EXPECT_EQ(p.GetPostfix(), "2 3 + 4 *");
}

TEST(TPostfix, calculates_simple_expression)
{
  TPostfix p("2+3*4");
  p.ToPostfix();
  std::map<char, double> emptyVars;
  EXPECT_DOUBLE_EQ(p.Calculate(emptyVars), 14.0);
}

TEST(TPostfix, calculates_with_brackets)
{
  TPostfix p("(2+3)*4");
  p.ToPostfix();
  std::map<char, double> emptyVars;
  EXPECT_DOUBLE_EQ(p.Calculate(emptyVars), 20.0);
}

TEST(TPostfix, calculates_subtraction_and_division)
{
  TPostfix p("8-4/2");
  p.ToPostfix();
  std::map<char, double> emptyVars;
  EXPECT_DOUBLE_EQ(p.Calculate(emptyVars), 6.0);
}

TEST(TPostfix, calculates_float_result)
{
  // Внимание: так как цифры односимвольные, 7/2 даст 3.5, 
  // но мы не можем ввести "15", только "1" и "5"
  TPostfix p("7/2");
  p.ToPostfix();
  std::map<char, double> emptyVars;
  EXPECT_DOUBLE_EQ(p.Calculate(emptyVars), 3.5);
}

TEST(TPostfix, throws_on_division_by_zero)
{
  TPostfix p("5/0");
  p.ToPostfix();
  std::map<char, double> emptyVars;
  ASSERT_ANY_THROW(p.Calculate(emptyVars));
}

TEST(TPostfix, calculates_with_variables)
{
  TPostfix p("a+b*c");
  p.ToPostfix();
  std::map<char, double> vars = {{'a', 2.0}, {'b', 3.0}, {'c', 4.0}};
  EXPECT_DOUBLE_EQ(p.Calculate(vars), 14.0);
}