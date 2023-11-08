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
	EXPECT_EQ(p.GetPostfix(), "ab+c-");
}

TEST(TPostfix, can_get_operands)
{
	TPostfix p("a+b-c");
	vector<char> op;
	op.push_back('a');
	op.push_back('b');
	op.push_back('c');
	EXPECT_EQ(p.GetOperands(), op);
}

TEST(TPostfix, can_get_postfix_with_parentheses)
{
	TPostfix p("a+(b-c)");
	EXPECT_EQ(p.GetPostfix(), "abc-+");
}

TEST(TPostfix, can_get_postfix_with_double_parentheses)
{
	TPostfix p("a*((b+c)-d)/e");
	EXPECT_EQ(p.GetPostfix(), "abc+d-*e/");
}

TEST(TPostfix, can_calculate_correct_positive_value)
{
	TPostfix p("a+b-c*d");
	map<char, double> values = { {'a', 5}, {'b', 4}, {'c', 3}, {'d', 2} };
	ASSERT_EQ(3, p.Calculate(values));
}

TEST(TPostfix, can_calculate_correct_negative_value)
{
	TPostfix p("a+b-c*d");
	map<char, double> values = { {'a', 1}, {'b', 3}, {'c', 6}, {'d', 2} };
	ASSERT_EQ(-8, p.Calculate(values));
}