#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p());
}

TEST(TPostfix, can_get_infix)
{
	TPostfix p("a+b-c");
	EXPECT_EQ(p.GetInfix(), "a+b-c");
}

TEST(TPostfix, can_get_postfix)
{
	TPostfix p("a+b-c");

	std::vector<string> expected = { "a", "b", "+", "c", "-" };
	EXPECT_EQ(p.GetPostfix(), expected);
}

TEST(TPostfix, can_get_operands)
{
	TPostfix p("a+b-c");
	vector<string> op;
	op.push_back("a");
	op.push_back("b");
	op.push_back("c");
	EXPECT_EQ(p.GetOperands(), op);
}

TEST(TPostfix, can_get_postfix_with_parentheses)
{
	TPostfix p("a+(b-c)");
	std::vector<string> expected = { "a", "b", "c", "-", "+"};
	EXPECT_EQ(expected,p.GetPostfix());
}

TEST(TPostfix, can_get_postfix_with_double_parentheses)
{
	TPostfix p("a*((b+c)-d)/e");
	std::vector<string> expected = { "a", "b", "c", "+", "d", "-", "*", "e", "/" };
	EXPECT_EQ(expected, p.GetPostfix());
}

TEST(TPostfix, can_calculate_correct_positive_value_literal_expression)
{
	TPostfix p("a+b-c*d");
	map<string, double> values = { {"a", 5}, {"b", 4}, {"c", 3}, {"d", 2} };
	ASSERT_EQ(3, p.Calculate(values));
}

TEST(TPostfix, can_calculate_correct_negative_value_literal_expression)
{
	TPostfix p("a+b-c*d");
	map<string, double> values = { {"a", 1}, {"b", 3}, {"c", 6}, {"d", 2} };
	ASSERT_EQ(-8, p.Calculate(values));
}

TEST(TPostfix, can_calculate_correct_positive_value_numeric_expression)
{
	TPostfix p("5+4-3*2");
	map<string, double> values = { {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2} };
	ASSERT_EQ(3, p.Calculate(values));
}

TEST(TPostfix, can_calculate_correct_negative_value_numeric_expression)
{
	TPostfix p("1+3-6*2");
	map<string, double> values = { {"1", 1}, {"3", 3}, {"6", 6}, {"2", 2} };
	ASSERT_EQ(-8, p.Calculate(values));
}

TEST(TPostfix, can_calculate_correct_positive_value_literal_and_numeric_expression)
{
	TPostfix p("a+b-3*d");
	map<string, double> values = { {"a", 5}, {"b", 4}, {"3", 3}, {"d", 2} };
	ASSERT_EQ(3, p.Calculate(values));
}

TEST(TPostfix, can_calculate_correct_negative_value_literal_and_numeric_expression)
{
	TPostfix p("1+b-6*d");
	map<string, double> values = { {"1", 1}, {"b", 3}, {"6", 6}, {"d", 2} };
	ASSERT_EQ(-8, p.Calculate(values));
}