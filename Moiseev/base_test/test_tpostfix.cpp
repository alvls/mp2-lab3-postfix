#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix expr("a+b"));
}

TEST(TPostfix, can_create_postfix_whith_parenthesis)
{
	ASSERT_NO_THROW(TPostfix expr("a*(b+c)"));
}

TEST(TPostfix, can_get_infix)
{
	TPostfix expr("a+b");

	EXPECT_EQ(expr.GetInfix(), "a+b");
}

TEST(TPostfix, can_get_postfix)
{
	TPostfix expr("a+b");

	EXPECT_EQ(expr.GetPostfix(), "ab+");
}

TEST(TPostfix, can_get_postfix_with_parenthesis)
{
	TPostfix expr("a+b*c/(d-e)");

	EXPECT_EQ(expr.GetPostfix(), "abc*de-/+");
}

TEST(TPostfix, can_get_postfix_with_multiparenthesis)
{
	TPostfix expr("(a*(b+c))");

	EXPECT_EQ(expr.GetPostfix(), "abc+*");
}

TEST(TPostfix, can_get_get_operands)
{
	TPostfix expr("a+b");

	char a = 'a', b = 'b';

	vector<char> op;
	op.push_back(a);
	op.push_back(b);

	EXPECT_EQ(expr.GetOperands(), op);
}

TEST(TPostfix, can_get_get_operands_with_parenthesis)
{
	TPostfix expr("(a+(b-c))");

	char a = 'a', b = 'b', c = 'c';

	vector<char> op;
	op.push_back(a);
	op.push_back(b);
	op.push_back(c);

	EXPECT_EQ(expr.GetOperands(), op);
}

TEST(TPostfix, can_get_calculate_positive)
{
	TPostfix expr("a+b*c/(d-e)");
	
	map<char, double> values;
	values['a'] = 1;
	values['b'] = 2;
	values['c'] = 6;
	values['d'] = 3;
	values['e'] = 1;

	EXPECT_EQ(expr.Calculate(values), 7);
}

TEST(TPostfix, can_get_calculate_negative)
{
	TPostfix expr("a+b*c/(d-e)");

	map<char, double> values;
	values['a'] = -1;
	values['b'] = 2;
	values['c'] = 6;
	values['d'] = 3;
	values['e'] = 6;

	EXPECT_EQ(expr.Calculate(values), -5);
}

TEST(TPostfix, not_eq_with_parenthesis)
{
	TPostfix expr("a*b+c");
	TPostfix expr2("a*(b+c)");

	map<char, double> values;
	values['a'] = 2;
	values['b'] = 3;
	values['c'] = 1;

	EXPECT_NE(expr.Calculate(values), expr2.Calculate(values));
}
