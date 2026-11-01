#include "postfix.h"
#include <gtest.h>
#include <stdexcept>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_with_string)
{
  ASSERT_NO_THROW(TPostfix p("2+2"));
}

TEST(TPostfix, converts_to_postfix_correctly)
{
  TPostfix p("2+3*4");
  EXPECT_EQ(p.ToPostfix(), "234*+");
}

TEST(TPostfix, converts_with_brackets)
{
  TPostfix p("(2+3)*4");
  EXPECT_EQ(p.ToPostfix(), "23+4*");
}

TEST(TPostfix, calculates_simple_expression)
{
  TPostfix p("2+3*4");
  p.ToPostfix();
  EXPECT_DOUBLE_EQ(p.Calculate(), 14.0);
}

TEST(TPostfix, calculates_with_brackets)
{
  TPostfix p("(2+3)*4");
  p.ToPostfix();
  EXPECT_DOUBLE_EQ(p.Calculate(), 20.0);
}

TEST(TPostfix, calculates_subtraction_and_division)
{
  TPostfix p("8-4/2");
  p.ToPostfix();
  EXPECT_DOUBLE_EQ(p.Calculate(), 6.0);
}

TEST(TPostfix, calculates_float_result)
{
  TPostfix p("7/2");
  p.ToPostfix();
  EXPECT_DOUBLE_EQ(p.Calculate(), 3.5);
}

TEST(TPostfix, throws_on_division_by_zero)
{
  TPostfix p("5/0");
  p.ToPostfix();
  ASSERT_ANY_THROW(p.Calculate());
} 