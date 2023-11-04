#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix_with_valid_infix)
{
	ASSERT_NO_THROW(TPostfix p("a+b*(c^d-e)"));
}
TEST(TPostfix, can_convert_infix_to_postfix)
{
	TPostfix p("a+b*(c^d-e)^(f+g*h)-i");
	ASSERT_EQ("abcd^e-fgh*+^*+i-", p.GetPostfix());
}

TEST(TPostfix, can_retrieve_infix_expression)
{
	TPostfix p("a+b*(c^d-e)^(f+g*h)-i");
	ASSERT_EQ("a+b*(c^d-e)^(f+g*h)-i", p.GetInfix());
}

TEST(TPostfix, can_calculate_correct_value)
{
	TPostfix p("a+b*c");
	map<char, double> values = { {'a', 1}, {'b', 2}, {'c', 3} };
	ASSERT_EQ(7, p.Calculate(values));
}

TEST(TPostfix, can_handle_parentheses)
{
	TPostfix p("(a+b)*c");
	ASSERT_EQ("ab+c*", p.GetPostfix());
}

TEST(TPostfix, can_handle_multiple_operators)
{
	TPostfix p("a+b*c-d/e");
	ASSERT_EQ("abc*+de/-", p.GetPostfix());
}

TEST(TPostfix, can_handle_power_operator)
{
	TPostfix p("a^b");
	ASSERT_EQ("ab^", p.GetPostfix());
}

TEST(TPostfix, can_handle_empty_expression)
{
	ASSERT_ANY_THROW(TPostfix p(""));
}
