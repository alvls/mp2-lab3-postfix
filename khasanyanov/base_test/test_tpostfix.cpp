#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_from_expression)
{
	ASSERT_NO_THROW(TPostfix p("1+3*(5-7)"));
}

TEST(TPostfix, can_create_postfix_from_formula)
{
	ASSERT_NO_THROW(TPostfix p("b*b-4ac"));
}

TEST(TPostfix, cant_create_postfix_from_expression_without_operators)
{
	ASSERT_ANY_THROW(TPostfix p("123"));
}

TEST(TPostfix, cant_convert_wrong_expression)
{
	ASSERT_ANY_THROW(TPostfix p("((1+2)-3)*5)"));
}

TEST(TPostfix, can_get_infix)
{
	TPostfix p;
	ASSERT_NO_THROW(p.getInfix());
}

TEST(TPostfix, get_infix_return_true_value)
{
	TPostfix p;
	EXPECT_EQ(p.getInfix(), "1+2-3*5");
}

TEST(TPostfix, can_get_postfix)
{
	TPostfix p("1+2-3*5");
	ASSERT_NO_THROW(p.getPostfix());
}

TEST(TPostfix, can_get_postfix_from_expression_with_spaces)
{
	TPostfix p("1   +2- 3 * 5");
	ASSERT_NO_THROW(p.getPostfix());
}

TEST(TPostfix, get_postfix_return_true_value)
{
	TPostfix p("1+2-3*5");
	EXPECT_EQ(p.getPostfix(), "1 2 + 3 5 * -");
}

TEST(TPostfix, get_postfix_from_expression_with_spaces_return_true_value)
{
	TPostfix p("1   +2- 3 * 5");
	EXPECT_EQ(p.getPostfix(), "1 2 + 3 5 * -");
}

TEST(TPostfix, can_convert_expression_to_postfix_form)
{
	TPostfix p;
	ASSERT_NO_THROW(p.toPostfix());
}

TEST(TPostfix, convert_expression_to_postfix_form_return_true_value)
{
	TPostfix p;
	EXPECT_EQ(p.toPostfix(), "1 2 + 3 5 * -");
}

TEST(TPostfix, convert_formula_to_postfix_form_return_true_value)
{
	TPostfix p("2*a+b-3*5");
	EXPECT_EQ(p.toPostfix(), "2 a * b + 3 5 * -");
}

TEST(TPostfix, can_calculate_expression)
{
	TPostfix p("1+2-3*5");
	ASSERT_NO_THROW(p.calculate());
}

TEST(TPostfix, cant_calculate_formula)
{
	TPostfix p("a+b-3*5");
	ASSERT_ANY_THROW(p.calculate());
}

TEST(TPostfix, calculate_expression_return_true_value)
{
	TPostfix p("1+2-3*5");
	EXPECT_EQ(p.calculate(), -12);
}

TEST(TPostfix, calculate_test1)
{
	TPostfix p("56*23-6/12");
	EXPECT_EQ(p.calculate(), 1287.5);
}

TEST(TPostfix, calculate_test2)
{
	TPostfix p("12^3-(12*12*12)");
	EXPECT_EQ(p.calculate(), 0);
}

TEST(TPostfix, calculate_test3)
{
	TPostfix p("(((54/65)-543)+900)/3");
	EXPECT_EQ(p.calculate(), 119.2769230);
}