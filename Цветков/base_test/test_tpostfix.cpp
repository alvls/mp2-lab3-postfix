#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_get_infix)
{
	TPostfix p;
	std::string form = "5+3*4/(2-1)";
	p.SetInfix(form);
	std::string in = "A+B*C/(D-E)";
	EXPECT_EQ(in, p.GetInfix());
}
TEST(TPostfix, can_get_postfix)
{
	TPostfix p;
	std::string form = "5+3*4/(2-1)";
	p.SetInfix(form);
	p.ToPostfix();
	std::string post = "ABC*DE-/+";
	EXPECT_EQ(post, p.GetPostfix());
}
TEST(TPostfix, can_calculate_plus)
{
	TPostfix p;
	std::string form = "5+3.5";
	p.SetInfix(form);
	p.ToPostfix();
	EXPECT_EQ(8.5, p.Calculate());
}

TEST(TPostfix, can_calculate_minus)
{
	TPostfix p;
	std::string form = "5-3.5";
	p.SetInfix(form);
	p.ToPostfix();
	EXPECT_EQ(1.5, p.Calculate());
}

TEST(TPostfix, can_calculate_multiplication)
{
	TPostfix p;
	std::string form = "5*3";
	p.SetInfix(form);
	p.ToPostfix();
	EXPECT_EQ(5 * 3, p.Calculate());
}

TEST(TPostfix, can_calculate_division)
{
	TPostfix p;
	std::string form = "6/3";
	p.SetInfix(form);
	p.ToPostfix();
	EXPECT_EQ(6 / 3, p.Calculate());
}

