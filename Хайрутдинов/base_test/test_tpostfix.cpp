#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, can_get_postfix_of_two_arguments_with_brackets)
{
	TPostfix p("(a+b)*c");
	p.ToPostfix();
	EXPECT_EQ("ab+c*", p.GetPostfix());
}
TEST(TPostfix, can_get_postfix_of_two_arguments)
{
	TPostfix p("a+b");
	p.ToPostfix();
	EXPECT_EQ("ab+", p.GetPostfix());
}
TEST(TPostfix, can_set_infix)
{
	ASSERT_NO_THROW(TPostfix p("a+b"));
}
TEST(TPostfix, can_get_infix)
{
	TPostfix p("a+b");
	EXPECT_EQ("a+b", p.GetInfix());
}
TEST(TPostfix, can_get_postfix_with_different_operations)
{
	TPostfix p("a+b*c");
	p.ToPostfix();
	EXPECT_EQ("abc*+", p.GetPostfix());
}
TEST(TPostfix, can_get_postfix_with_closed_bracket)
{
	TPostfix p(")a+b");
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, can_get_postfix_with_operation_in_begin)
{
	TPostfix p("*a+b)");
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, cant_create_postfix_with_incorrectinfix)
{
	TPostfix p("5+5-");
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, can_calculate_postfix)
{
	TPostfix p("a+b");
	p.ToPostfix();
	double tmp[2] = { 2,2 };
	EXPECT_EQ(4, p.Calculate(2, tmp));
}
TEST(TPostfix, cant_calculate_postfix_without_right_count)
{
	TPostfix p("a+b");
	p.ToPostfix();
	double tmp[2] = { 2,2 };
	ASSERT_ANY_THROW(p.Calculate(3, tmp));
}