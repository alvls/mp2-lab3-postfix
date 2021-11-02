#include <gtest.h>
#include "postfix.h"
#include "postfix.cpp"

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_turn_to_postfix)
{
	TPostfix p; std::string s("2 x 3 + / ");
	p.SetInfix("2 / ( x + 3 ) ");
	EXPECT_EQ(s, p.ToPostfix());
}

TEST(TPostfix, can_calculate_plus_postfix)
{
	TPostfix p;
	p.SetInfix("2 + 2.5");
	p.ToPostfix();
	EXPECT_EQ(2 + 2.5, p.Calculate());
}

TEST(TPostfix, can_calculate_minus_postfix)
{
	TPostfix p;
	p.SetInfix("2 - 0.5");
	p.ToPostfix();
	EXPECT_EQ(1.5, p.Calculate());
}

TEST(TPostfix, can_calculate_multiplication_postfix)
{
	TPostfix p;
	p.SetInfix("0.1 * 0.2");
	p.ToPostfix();
	EXPECT_EQ(0.1 * 0.2, p.Calculate());
}

TEST(TPostfix, can_calculate_division_postfix)
{
	TPostfix p;
	p.SetInfix("2 / 3");
	p.ToPostfix();
	EXPECT_EQ(double(2) / 3, p.Calculate());
}

TEST(TPostfix, can_calculate_power_postfix)
{
	TPostfix p;
	p.SetInfix("2 ^ 0.8");
	p.ToPostfix();
	EXPECT_EQ(pow(2, 0.8), p.Calculate());
}

TEST(TPostfix, can_calculate_exp_postfix)
{
	TPostfix p;
	p.SetInfix("exp 2");
	p.ToPostfix();
	EXPECT_EQ(exp(2), p.Calculate());
}

TEST(TPostfix, can_calculate_natural_log_postfix)
{
	TPostfix p;
	p.SetInfix("ln 2");
	p.ToPostfix();
	EXPECT_EQ(log(2), p.Calculate());
}

TEST(TPostfix, can_calculate_sqrt_postfix)
{
	TPostfix p;
	p.SetInfix("sqrt 2");
	p.ToPostfix();
	EXPECT_EQ(sqrt(2), p.Calculate());
}

TEST(TPostfix, can_calculate_sin_postfix)
{
	TPostfix p;
	p.SetInfix("sin 1");
	p.ToPostfix();
	EXPECT_EQ(sin(1), p.Calculate());
}