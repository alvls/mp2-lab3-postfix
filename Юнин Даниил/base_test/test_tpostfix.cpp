#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix_with_expression)
{
	ASSERT_NO_THROW(TPostfix postf("4+d"));
}

TEST(TPostfix, can_change_expression_use_setinfix)
{
	TPostfix postf("4+d");
	ASSERT_NO_THROW(postf.SetInfix("5+8"));
}

TEST(TPostfix, can_get_infix_expression)
{
	TPostfix postf("4+d");
	EXPECT_EQ("4+d", postf.GetInfix());
}

TEST(TPostfix, can_get_postfix_expression)
{
	TPostfix postf("4+d");
	postf.ChangeInfixToPostfix();
	vector<string> v;
	v.push_back("4");
	v.push_back("d");
	v.push_back("+");
	EXPECT_EQ(v, postf.GetPostfix());
}

TEST(TPostfix, throws_if_find_error_with_brackets_they_are_together_without_sign)
{
	TPostfix postf("(4+d)(4+5)");
	ASSERT_ANY_THROW(postf.ChangeInfixToPostfix());
}

TEST(TPostfix, throws_if_find_error_with_brackets_open_more_then_close)
{
	TPostfix postf("((4+d)(4+5)");
	ASSERT_ANY_THROW(postf.ChangeInfixToPostfix());
}

TEST(TPostfix, throws_if_find_error_with_brackets_close_more_then_open)
{
	TPostfix postf("(4+d)(4+5))");
	ASSERT_ANY_THROW(postf.ChangeInfixToPostfix());
}

TEST(TPostfix, find_unary_minus_and_change_it_on_binary)
{
	TPostfix postf("-4+2");
	postf.ChangeInfixToPostfix();
	EXPECT_EQ("0-4+2", postf.GetInfix());
}

TEST(TPostfix, can_calculate_sum_expression)
{
	TPostfix postf("4+5");
	postf.ChangeInfixToPostfix();
	EXPECT_EQ(9, postf.Calculate());
}

TEST(TPostfix, can_calculate_expression_with_unary_minus)
{
	TPostfix postf("-4+5+3");
	postf.ChangeInfixToPostfix();
	EXPECT_EQ(4, postf.Calculate());
}
