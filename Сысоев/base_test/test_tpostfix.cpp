#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix1)
{
	string tmp = "3+5";
	ASSERT_NO_THROW(TPostfix p(tmp));
}

TEST(TPostfix, can_create_postfix2)
{
	string tmp = "(((1+23)*1-22)+5)*2*7";
	ASSERT_NO_THROW(TPostfix p(tmp));
}
/*
TEST(TPostfix, can_calculate)
{
	string tmp = "(((1+23)*-22)+5)*2*7";
	TPostfix p(tmp);
	EXPECT_EQ(7, p.Calculate());
}
*/
TEST(TPostfix, throw_when_last_character_is_operations)
{
	string inf = "5+7+";
	TPostfix p(inf);
	ASSERT_NO_THROW(p);
}

TEST(TPostfix, ToPostfix)
{
	string tmp = "(1+2)*(1-3/3*6-4)";
	TPostfix p(tmp);
	p.ToPostfix();
	tmp = "1 2 + 1 3 3 / 6 * 4 - - * ";
	EXPECT_EQ(tmp, p.GetPostfix());
}

TEST(TPostfix, throw_when_incorrect_number_of_brackets)
{
	string inf = "(((7+6))";
	ASSERT_ANY_THROW(TPostfix p(inf));
}


TEST(TPostfix, can_use_Calculate)
{
	string inf = "a+b+c";
	TPostfix p(inf);
	p.ToPostfix();
	ASSERT_NO_THROW(p.Calculate());
}


