#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, converts_simple_expr)
{
  TPostfix p("2+3");
  EXPECT_EQ("2 3 +", p.ToPostfix());
}

TEST(TPostfix, converts_with_priority)
{
  TPostfix p("2+3*4");
  EXPECT_EQ("2 3 4 * +", p.ToPostfix());
}

TEST(TPostfix, converts_with_parentheses)
{
  TPostfix p("(2+3)*4");
  EXPECT_EQ("2 3 + 4 *", p.ToPostfix());
}

TEST(TPostfix, calculates_simple)
{
  TPostfix p("2+3*4");
  p.ToPostfix();
  EXPECT_DOUBLE_EQ(14.0, p.Calculate());
}

TEST(TPostfix, calculates_with_parentheses)
{
  TPostfix p("(2+3)*4");
  p.ToPostfix();
  EXPECT_DOUBLE_EQ(20.0, p.Calculate());
}

TEST(TPostfix, calculates_power)
{
  TPostfix p("2^3^2");
  p.ToPostfix();
  EXPECT_DOUBLE_EQ(512.0, p.Calculate());
}

TEST(TPostfix, subtraction_is_left_associative)
{
  TPostfix p("10-3-2");
  p.ToPostfix();
  EXPECT_DOUBLE_EQ(5.0, p.Calculate());
}

TEST(TPostfix, division_is_left_associative)
{
  TPostfix p("20/2/5");
  p.ToPostfix();
  EXPECT_DOUBLE_EQ(2.0, p.Calculate());
}

TEST(TPostfix, throws_on_division_by_zero)
{
  TPostfix p("5/0");
  p.ToPostfix();
  EXPECT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, throws_on_mismatched_parentheses)
{
  TPostfix p("(2+3");
  EXPECT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, works_with_decimals)
{
  TPostfix p("2.5+1.5");
  p.ToPostfix();
  EXPECT_DOUBLE_EQ(4.0, p.Calculate());
}