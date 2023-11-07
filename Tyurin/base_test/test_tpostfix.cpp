#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
   ASSERT_NO_THROW(TPostfix p("a+b"));
}

TEST(TPostfix, can_create_postfix_whith_parenthesis)
{
   ASSERT_NO_THROW(TPostfix expr("(a+b)*c"));
}

TEST(TPostfix, can_convert_to_postfix) {
   TPostfix p("(a+b)*c");
   ASSERT_NO_THROW(p.ToPostfix());
}

TEST(TPostfix, can_get_postfix)
{
   TPostfix expr("a+c");

   EXPECT_EQ(expr.GetPostfix(), "ac+");
}

TEST(TPostfix, can_get_infix)
{
   TPostfix expr("a+c");

   EXPECT_EQ(expr.GetInfix(), "a+c");
}

TEST(TPostfix, can_handle_multiple_operators)
{
   TPostfix p("a+b-c*d/e");
   EXPECT_EQ("ab+cd*e/-", p.GetPostfix());
}

TEST(TPostfix, calculate_test)
{
   TPostfix p("5+2-3*4/6");
   EXPECT_EQ(p.Calculate(), 5);
}

TEST(TPostfix, can_handle_power_operator)
{
   TPostfix p("(a+c)^b");
   EXPECT_EQ("ac+b^", p.GetPostfix());
}

TEST(TPostfix, calculate_test_1)
{
   TPostfix p("(1+1)^3");
   EXPECT_EQ(p.Calculate(), 8);
}