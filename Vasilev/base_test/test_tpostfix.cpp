#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <gtest.h>
#include "postfix.h"

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_with_expression) {
  ASSERT_NO_THROW(TPostfix p("a+b*c"));
}

TEST(TPostfix, can_convert_to_postfix) {
  TPostfix p("a+b*c");
  ASSERT_NO_THROW(p.ToPostfix());
  EXPECT_EQ(p.GetPostfix(), "abc*+");
}

TEST(TPostfix, can_calculate_postfix) {
  TPostfix p("3+4*2");
  p.ToPostfix();
  double result;
  ASSERT_NO_THROW(result = p.Calculate());
  EXPECT_DOUBLE_EQ(result, 11.0);
}
