#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_with_expression)
{
	ASSERT_NO_THROW(TPostfix p("2+2"));
}

TEST(TPostfix, can_convert_simple_expression)
{
	TPostfix p("a+b");
	EXPECT_EQ("a b + ", p.ToPostfix());
}

TEST(TPostfix, can_convert_expression_with_priorities)
{
	TPostfix p("a+b*c");
	EXPECT_EQ("a b c * + ", p.ToPostfix());
}

TEST(TPostfix, can_convert_expression_with_brackets)
{
	TPostfix p("(a+b)*c");
	EXPECT_EQ("a b + c * ", p.ToPostfix());
}

TEST(TPostfix, convert_ignores_spaces) {
	TPostfix p("  a  +   b  ");
	EXPECT_EQ("a b + ", p.ToPostfix());
}

TEST(TPostfix, can_calculate_simple_addition)
{
	TPostfix p("12+13");
	EXPECT_DOUBLE_EQ(25.0, p.Calculate());
}

TEST(TPostfix, can_calculate_with_multiple_digits_and_dots)
{
	TPostfix p("10.5 + 2.5 * 4");
	EXPECT_DOUBLE_EQ(20.5, p.Calculate());
}

TEST(TPostfix, can_calculate_complex_expression)
{
	TPostfix p("((2 + 3) * 4 - 2) / 2"); 
	EXPECT_DOUBLE_EQ(9.0, p.Calculate());
}

TEST(TPostfix, throws_when_brackets_are_not_balanced_left)
{
	TPostfix p("((1+2)");
	ASSERT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, throws_when_brackets_are_not_balanced_right)
{
	TPostfix p("(1+2))");
	ASSERT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, throws_when_division_by_zero)
{
	TPostfix p("10 / (5 - 5)");
	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, throws_when_unknown_symbol_used)
{
	TPostfix p("2 $ 3");
	ASSERT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, can_get_unique_operands)
{
	TPostfix p("a + b * a - 5");
	vector<string> ops = p.GetOperands();
	ASSERT_EQ(2, ops.size());
	EXPECT_EQ("a", ops[0]);
	EXPECT_EQ("b", ops[1]);
}

TEST(TPostfix, can_calculate_expression_with_variables)
{
	TPostfix p("a + b * c");
	map<string, double> values = { {"a", 2.0}, {"b", 3.0}, {"c", 4.0} };
	EXPECT_DOUBLE_EQ(14.0, p.Calculate(values));
}

TEST(TPostfix, can_calculate_mixed_variables_and_numbers)
{
	TPostfix p("(x1 + 2.5) * y2");
	map<string, double> values = { {"x1", 1.5}, {"y2", 3.0} };
	EXPECT_DOUBLE_EQ(12.0, p.Calculate(values));
}

TEST(TPostfix, throws_when_variable_value_is_missing)
{
	TPostfix p("a + b");
	map<string, double> values = { {"a", 5.0} }; 
	ASSERT_ANY_THROW(p.Calculate(values));
}

TEST(TPostfix, throws_when_division_by_zero_with_variable)
{
	TPostfix p("10 / x");
	map<string, double> values = { {"x", 0.0} };
	ASSERT_ANY_THROW(p.Calculate(values));
}