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
	ASSERT_NO_THROW(TPostfix p("b^2-4*a*c"));
}

TEST(TPostfix, can_create_postfix_from_expression_without_operators)
{
	ASSERT_NO_THROW(TPostfix p("123"));
}

TEST(TPostfix, cant_create_postfix_from_wrong_expression_test1)
{
	ASSERT_ANY_THROW(TPostfix p("((1+2)-3)*5)"));
}

TEST(TPostfix, cant_create_postfix_from_wrong_expression_test2)
{
	ASSERT_ANY_THROW(TPostfix p("324+-*6"));
}

TEST(TPostfix, cant_create_postfix_from_wrong_expression_test3)
{
	ASSERT_ANY_THROW(TPostfix p("23.67-5.+4"));
}

TEST(TPostfix, cant_create_postfix_from_empty_expression)
{
	ASSERT_ANY_THROW(TPostfix p(""));
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

TEST(TPostfix, get_postfix_return_true_value)
{
	TPostfix p("1+2-3*5");
	EXPECT_EQ(p.getPostfix(), "1 2+ 3 5*-");
}

TEST(TPostfix, get_postfix_from_expression_with_spaces_return_true_value)
{
	TPostfix p("1   +2- 3 * 5");
	EXPECT_EQ(p.getPostfix(), "1 2+ 3 5*-");
}

TEST(TPostfix, convert_formula_to_postfix_form_return_true_value)
{
	TPostfix p("2*a+b-3*5");
	EXPECT_EQ(p.getPostfix(), "2 a* b+ 3 5*-");
}

TEST(TPostfix, can_calculate_expression)
{
	TPostfix p("1+2-3*5");
	ASSERT_NO_THROW(p.calculate(p.getOperands()));
}

TEST(TPostfix, calculate_expression_return_true_value)
{
	TPostfix p("1+2-3*5");
	EXPECT_EQ(p.calculate(p.getOperands()), -12);
}

TEST(TPostfix, calculate_test1)
{
	TPostfix p("((sin(1))^2 + (cos(1))^2)");
	EXPECT_EQ(p.calculate(p.getOperands()), 1);
}

TEST(TPostfix, calculate_test2)
{
	TPostfix p("-27+lg(10)*ceil(2.43)^3");
	EXPECT_EQ(p.calculate(p.getOperands()), 0);
}

TEST(TPostfix, calculate_test3)
{
	TPostfix p("(((54.65/65)-543)+900.23)*3");
	EXPECT_EQ(p.calculate(p.getOperands()), (((54.65 / 65) - 543) + 900.23) * 3);
}