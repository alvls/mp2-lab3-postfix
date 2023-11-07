#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p("a+b"));
}

TEST(TPostfix, can_create_postfix_with_compound_operand)
{
	ASSERT_NO_THROW(TPostfix p("a+a1"));
	ASSERT_NO_THROW(TPostfix p("a13+abc"));
}

TEST(TPostfix, cant_create_postfix_with_operand_with_number_before_last_letter)
{
	ASSERT_ANY_THROW(TPostfix p("a+a1t"));
	ASSERT_ANY_THROW(TPostfix p("a+abc1de"));
}

TEST(TPostfix, cant_create_postfix_with_operand_with_forbidden_symbol)
{
	ASSERT_ANY_THROW(TPostfix p("a+a:t"));
	ASSERT_ANY_THROW(TPostfix p("at#-d"));
}

TEST(TPostfix, can_create_postfix_with_brackets)
{
	ASSERT_NO_THROW(TPostfix p("(a+b)/c"));
	ASSERT_NO_THROW(TPostfix p("(s-r)/(s+r)+k"));
}

TEST(TPostfix, throws_when_create_postfix_with_different_count_of_left_and_right_brackets)
{
	ASSERT_ANY_THROW(TPostfix p("(a+b)/(c-d"));
	ASSERT_ANY_THROW(TPostfix p("(a-d)/(b-f)^k)"));
}

TEST(TPostfix, can_create_postfix_with_several_operations_in_a_row)
{
	ASSERT_NO_THROW(TPostfix p("m+sin(a)"));
	ASSERT_NO_THROW(TPostfix p("(-sqrt(x)+t)*a"));
}

TEST(TPostfix, throws_when_create_postfix_with_too_many_operations_in_a_row)
{
	ASSERT_ANY_THROW(TPostfix p("a+*b"));
	ASSERT_ANY_THROW(TPostfix p("a+t-^k"));
}

TEST(TPostfix, can_create_postfix_with_constants)
{
	ASSERT_NO_THROW(TPostfix p("a+2"));
	ASSERT_NO_THROW(TPostfix p("(a+4)/(a*2)"));
}

TEST(TPostfix, can_create_postfix_with_space_between_lexems_in_expression)
{
	ASSERT_NO_THROW(TPostfix p("(a + 2) / 2 * (4 - b)"));
}

TEST(TPostfix, can_return_infix_form)
{
	TPostfix p("(a + b / 2) * 4");
	EXPECT_EQ("(a+b/2)*4", p.GetInfix());
}

TEST(TPostfix, can_convert_infix_form_to_postfix)
{
	TPostfix p("(a+2)/2*(4-b)");
	EXPECT_EQ("a2+2/4b-*", p.GetPostfix());
}

TEST(TPostfix, can_calculate_in_postfix)
{
	TPostfix p("sqrt(abs(a))/2+4^(cos(0))*b-ln(c)");
	EXPECT_EQ((sqrt(abs(-9)) / 2 + pow(4, cos(0)) * 2 - log(1)), p.Calculate(vector<double>{ -9, 2, 1}));
}