#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p("a+b"));
}
TEST(TPostfix, can_get_infix)
{
  TPostfix str("((45 + 34)+ a+c/(g) +7))");
  EXPECT_EQ("((45 + 34)+ a+c/(g) +7))", str.GetInfix());
}

TEST(TPostfix, can_get_postfix_1)
{
  TPostfix str("(a-b)*c");
  EXPECT_EQ("ab-c*", str.ToPostfix());
}

TEST(TPostfix, can_get_postfix_2)
{
  TPostfix pos("1/b+(2+3)/(tg(9-2)^2-6/7)");
  EXPECT_EQ("1b/23+92-tg2^67/-/+", pos.ToPostfix());
}
TEST(TPostfix, can_get_postfix_3)
{
  TPostfix pos("(1+2)*sin(4)+3");
  EXPECT_EQ("12+4sin*3+", pos.ToPostfix());
}

TEST(TPostfix, can_get_postfix_4)
{
  TPostfix pos("-(c*d+a)/(b*e)");
  EXPECT_EQ("cd*a+be*/-", pos.ToPostfix());
}

TEST(TPostfix, can_get_postfix_5)
{
  TPostfix pos("-(b*(d+a!))/(c*e)");
  EXPECT_EQ("bda!+*ce*/-", pos.ToPostfix());
}
TEST(TPostfix, cant_start_with_clossed_bracket)
{
  TPostfix str(")a+b(");
  ASSERT_ANY_THROW(str.ToPostfix());
}
TEST(TPostfix, cant_set_different_value_of_RLbrackets)
{
  TPostfix str("((a+b)");
  ASSERT_ANY_THROW(str.ToPostfix());
}
TEST(TPostfix, cant_translate_an_incorrect_expression_into_a_postfix_form)
{
  TPostfix str("a++b");
  ASSERT_ANY_THROW(str.ToPostfix());
}
TEST(TPostfix, cant_calculate_without_postfix_form)
{
  TPostfix str("(((1+23)*1-22)+5)*2-7");
  ASSERT_ANY_THROW(str.Calculate());
}
TEST(TPostfix, cant_be_divided_by_zero)
{
  TPostfix str("1+2/(3-3)");
  str.ToPostfix();
  ASSERT_ANY_THROW(str.Calculate());
}
TEST(TPostfix, can_calculate_the_expression)
{
  TPostfix str("8 + 7 /  ( 2 + 5 )");
  str.ToPostfix();
  EXPECT_EQ(9, str.Calculate());
}
TEST(TPostfix, can_calculate_double) 
{
  TPostfix str("0.48 + 1.12");
  str.ToPostfix();
  EXPECT_EQ(1.6, str.Calculate());
}
TEST(TPostfix, is_equal_expression_in_postfix_form)
{
  TPostfix p1("(a+b)+(c)"), p2("a+b+c");
  p1.ToPostfix();
  p2.ToPostfix();
  EXPECT_EQ(p1.GetPostfix(), p2.GetPostfix());
}
