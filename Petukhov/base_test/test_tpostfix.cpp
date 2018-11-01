#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>
#include <iostream>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p("0"));
}
TEST(TPostfix, can_calculate_easy)
{
	TPostfix p("1+2");
	double res = p.execute();
	EXPECT_EQ(3, res);
}
TEST(TPostfix, can_calculate_average)
{
	TPostfix p("1+2*(3-2)-4");
	double res = p.execute();
	EXPECT_EQ(-1, res);
}
TEST(TPostfix, can_calculate_hard)
{
	TPostfix p("(1+2)*3+4");
	double res = p.execute();
	EXPECT_EQ(13, res);
}
TEST(TPostfix, not_correct_infix_form)
{
	TPostfix p("(((1 + 23) * 1 - 22) + 5) * 2 - (7");
	EXPECT_EQ(false, p.correct());
}
TEST(TPostfix, correct_postfix_form)
{
	TPostfix p("(1+2)*3+4");
	p.execute();
	EXPECT_EQ("1 2 + 3 * 4 + ", p.GetPostfix());
}

