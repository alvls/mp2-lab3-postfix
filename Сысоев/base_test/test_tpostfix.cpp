#include "postfix.h"
#include "postfix.cpp"
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

TEST(TPostfix, can_calculate2)
{
	double res;
	string tmp = "3+5";
	TPostfix p(tmp);
	p.ToPostfix();
	res = p.Calculate();
	EXPECT_EQ(8, res);
}


TEST(TPostfix, can_create_postfix2)
{
	string tmp = "(((1+23)*1-22)+5)*2*7";
	ASSERT_NO_THROW(TPostfix p(tmp));
}

TEST(TPostfix, throw_when_last_character_is_operations)
{
	string inf = "5+7+";
	TPostfix p(inf); 
	EXPECT_EQ(false, p.CheckInfix());
}

TEST(TPostfix, can_not_start_infix_the_operation)
{
	TPostfix p("+a+1");
	EXPECT_EQ(false, p.CheckInfix());
}

TEST(TPostfix, parentheses_is_not_correct)
{
	TPostfix p("(a+1))");
	EXPECT_EQ(false, p.CheckBrackets());
}

TEST(TPostfix, another_haracter)
{
	TPostfix p("5+6&");
	EXPECT_EQ(false, p.CheckChars());
}


TEST(TPostfix, ToPostfix)
{
	string tmp = "(1+2)*5";
	TPostfix p(tmp);
	p.ToPostfix();
	tmp = "1 2 + 5 * ";
	EXPECT_EQ(tmp, p.GetPostfix());
}

TEST(TPostfix, can_use_Calculate)
{
	string inf = "4+5+6";
	TPostfix p(inf);
	p.ToPostfix();
	ASSERT_NO_THROW(p.Calculate());
}

TEST(TPostfix, can_calculate_expression)
{
	TPostfix p("(5+1)*(10+1)");
	p.ToPostfix();
	EXPECT_EQ(66, p.Calculate());
}

