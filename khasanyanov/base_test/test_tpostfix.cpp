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
	EXPECT_EQ(p.getPostfix(), " 1 2+ 3 5*-");
}

TEST(TPostfix, get_postfix_from_expression_with_spaces_return_true_value)
{
	TPostfix p("1   +2- 3 * 5");
	EXPECT_EQ(p.getPostfix(), " 1 2+ 3 5*-");
}

TEST(TPostfix, convert_formula_to_postfix_form_return_true_value)
{
	TPostfix p("2*a+b-3*5");
	EXPECT_EQ(p.getPostfix(), " 2 a* b+ 3 5*-");
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
	TPostfix p("56*23-6/12");
	EXPECT_EQ(p.calculate(p.getOperands()), 1287.5);
}

TEST(TPostfix, calculate_test2)
{
	TPostfix p("12^3-(12*12*12)");
	EXPECT_EQ(p.calculate(p.getOperands()), 0);
}

TEST(TPostfix, calculate_test3)
{
	TPostfix p("(((54/65)-543)+900)/3");
	cout << p.calculate(p.getOperands());
	EXPECT_EQ((((54 / 65) - 543) + 900) / 3, p.calculate(p.getOperands()));
}