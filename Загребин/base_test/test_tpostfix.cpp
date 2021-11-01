#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_turn_to_postfix)
{
	TPostfix p;
	p.SetInfix("2 + x");
	EXPECT_EQ("2 x + ", p.GetPostfix());
}

TEST(TPostfix, can_calculate_plus_postfix)
{
	TPostfix p;
	p.SetInfix("2 + 2");
	p.GetPostfix();
	EXPECT_EQ(4, p.Calculate());
}

TEST(TPostfix, can_calculate_minus_postfix)
{
	TPostfix p;
	p.SetInfix("2 - 2");
	p.GetPostfix();
	EXPECT_EQ(0, p.Calculate());
}

TEST(TPostfix, can_calculate_multiplication_postfix)
{
	TPostfix p;
	p.SetInfix("2 * 2");
	p.GetPostfix();
	EXPECT_EQ(4, p.Calculate());
}

TEST(TPostfix, can_calculate_division_postfix)
{
	TPostfix p;
	p.SetInfix("2 / 2");
	p.GetPostfix();
	EXPECT_EQ(1, p.Calculate());
}

TEST(TPostfix, can_calculate_power_postfix)
{
	TPostfix p;
	p.SetInfix("2 ^ 2");
	p.GetPostfix();
	EXPECT_EQ(4, p.Calculate());
}

TEST(TPostfix, can_calculate_exp_postfix)
{
	TPostfix p;
	p.SetInfix("exp 0");
	p.GetPostfix();
	EXPECT_EQ(1, p.Calculate());
}

TEST(TPostfix, can_calculate_natural_log_postfix)
{
	TPostfix p;
	p.SetInfix("ln 1");
	p.GetPostfix();
	EXPECT_EQ(0, p.Calculate());
}

TEST(TPostfix, can_calculate_sqrt_postfix)
{
	TPostfix p;
	p.SetInfix("sqrt 4");
	p.GetPostfix();
	EXPECT_EQ(2, p.Calculate());
}

TEST(TPostfix, can_calculate_sin_postfix)
{
	TPostfix p;
	p.SetInfix("sin 0");
	p.GetPostfix();
	EXPECT_EQ(0, p.Calculate());
}