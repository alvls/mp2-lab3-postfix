#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, can_create_postfix_with_correct_expression)
{
	ASSERT_NO_THROW(TPostfix p("a/b+ñ*a+2*b-c^3"));
}
TEST(TPostfix, can_create_postfix_with_long_operands)
{
	ASSERT_NO_THROW(TPostfix p("Hello world+My_Program-a2b3+a1,1"));
}
TEST(TPostfix, cant_create_postfix_with_too_many_brackets)
{
	ASSERT_ANY_THROW(TPostfix p("((3+a)"));
}
TEST(TPostfix, cant_create_postfix_with_wrong_operation_placement)
{
	ASSERT_ANY_THROW(TPostfix p("*a+b"));
	ASSERT_ANY_THROW(TPostfix t("k+b-"));
	ASSERT_ANY_THROW(TPostfix r("13*(/b)"));
	ASSERT_ANY_THROW(TPostfix k("a--b"));
}
TEST(TPostfix, can_get_infix)
{
	TPostfix p("a+b-c");
	EXPECT_EQ("a+b-c", p.GetInfix());
}
TEST(TPostfix, can_get_postfix)
{
	TPostfix p("a+b-c");
	p.ToPostfix();
	EXPECT_EQ("ab+c-", p.GetPostfix());
}
TEST(TPostfix, can_calculate)
{
	TPostfix p("3^2-2*84/3+7");
	EXPECT_EQ(3 ^ 2 - 2 * 84 / 3 + 7, int(p.Calculate()));
}