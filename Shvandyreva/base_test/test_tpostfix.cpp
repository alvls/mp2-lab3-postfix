#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	string tmp = "1+2";
	ASSERT_NO_THROW(TPostfix p(tmp));
}
TEST(TPostfix, can_create_postfix_with_two_digit_numbers)
{
	string tmp = "17+28-1";
	ASSERT_NO_THROW(TPostfix p(tmp));
}
TEST(TPostfix, multiplication_test)
{
	string tmp = "1*2";
	TPostfix p(tmp);
	EXPECT_EQ("1 2 *", p.ToPostfix());
}
TEST(TPostfix, addition_test)
{
	string tmp = "1+2";
	TPostfix p(tmp);
	EXPECT_EQ("1 2 +", p.ToPostfix());
}
TEST(TPostfix, division_on_zero_test)
{
	string tmp = "1/0";
	TPostfix p(tmp);
	ASSERT_ANY_THROW(p.Calculate());
}
TEST(TPostfix, division_test)
{
	string tmp = "1/2";
	TPostfix p(tmp);
	EXPECT_EQ("1 2 /", p.ToPostfix());
}
TEST(TPostfix, subtraction_test)
{
	string tmp = "1-2";
	TPostfix p(tmp);
	EXPECT_EQ("1 2 -", p.ToPostfix());
}
TEST(TPostfix, test_first_example)
{
	string tmp = "a+b*c";
	TPostfix p(tmp);
	EXPECT_EQ("a b c * +", p.ToPostfix());
}
TEST(TPostfix, test_second_example)
{
	string tmp = "a+b-c*d";
	TPostfix p(tmp);
	EXPECT_EQ("a b + c d * -", p.ToPostfix());
}
TEST(TPostfix, test_fourth_example)
{
	string tmp = "(a+b)*c";
	TPostfix p(tmp);
	EXPECT_EQ("a b + c *", p.ToPostfix());
}
TEST(TPostfix, mixed_test_number_six)
{
	string tmp = "(a*(b+c)+d)/2";
	TPostfix p(tmp);
	EXPECT_EQ("a b c + * d + 2 /", p.ToPostfix());
}
TEST(TPostfix, calc_multiplication_test)
{
	string tmp = "1*2";
	TPostfix p(tmp);
	p.ToPostfix();
	EXPECT_EQ(2, p.Calculate());
}
TEST(TPostfix, calc_addition_test)
{
	string tmp = "1+2";
	TPostfix p(tmp);
	p.ToPostfix();
	EXPECT_EQ(3, p.Calculate());
}
TEST(TPostfix, calc_division_test)
{
	string tmp = "2/1";
	TPostfix p(tmp);
	p.ToPostfix();
	EXPECT_EQ(2, p.Calculate());
}
TEST(TPostfix, calc_subtraction_test)
{
	string tmp = "2-1";
	TPostfix p(tmp);
	p.ToPostfix();
	EXPECT_EQ(1, p.Calculate());
}
TEST(TPostfix, test_calc_with_two_digit_numbers)
{
	string tmp = "120-((360/6)*2)+3";
	TPostfix p(tmp);
	p.ToPostfix();
	EXPECT_EQ(3, p.Calculate());
}