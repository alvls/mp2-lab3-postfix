#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix_with_default_argument)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_with_an_argument_input)
{
	ASSERT_NO_THROW(TPostfix p("a+b*c"));
}

TEST(TPostfix, get_infix_return_valid_value)
{
	TPostfix p("a+b*c-d/e");
	EXPECT_EQ("a+b*c-d/e", p.GetInfix());
}

TEST(TPostfix, can_get_postfix)
{
	TPostfix p("a*(b+c)");
	ASSERT_NO_THROW(p.GetPostfix());
}

TEST(TPostfix, get_postfix_return_valid_value)
{
	TPostfix p("(a+b*c)*(c/5-e)+1");
	string s = "";
	for (auto& symbol : p.GetPostfix())
	{
		s += symbol;
	}
	EXPECT_EQ("abc*+c5/e-*1+", s);
}

TEST(TPostfix, supports_any_input_format)
{
	TPostfix p("a +b * c -d/e");
	string s = "";
	for (auto& symbol : p.GetPostfix())
	{
		s += symbol;
	}
	EXPECT_EQ("abc*+de/-", s);
}

TEST(TPostfix, can_calculate_expression_with_only_constants)
{
	TPostfix expr("3+2*6-2");
	EXPECT_EQ(3 + 2 * 6 - 2, expr.Calculate());
}

TEST(TPostfix, can_calculate_mixed_expression)
{
	double c = 3;
	TPostfix expr("1+2*c");
	EXPECT_EQ(1 + 2 * c, expr.Calculate({ {"c", c} }));
}

TEST(TPostfix, can_calculate_expression_with_spaces)
{
	TPostfix expr("1 + 2");
	EXPECT_EQ(1 + 2, expr.Calculate());
}

TEST(TPostfix, can_calculate_expression_with_unary_minus)
{
	TPostfix expr("-1 + 5 - (-8)");
	double res = expr.Calculate();
	EXPECT_EQ(-1 + 5 - (-8), res);
}
