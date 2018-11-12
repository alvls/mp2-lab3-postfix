#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_2)
{
	string tmp = "1+2";
	ASSERT_NO_THROW(TPostfix p(tmp));
}

TEST(TPostfix, can_calculate_expression)
{
	TPostfix p("(5+1)*(10-1)");
	p.ToPostfix();
	EXPECT_EQ(54, p.Calculate());
} 

TEST(TPostfix, throw_when_last_character_is_operations)
{
	string inf = "5+7+";
	TPostfix p(inf); 
	EXPECT_EQ(false, p.CheckInfix());
}

TEST(TPostfix, invalid_brackets)
{
	TPostfix p("(a+1))");
	EXPECT_FALSE(p.CheckInfix());
}

TEST(TPostfix, can_not_start_infix_the_operation)
{
	TPostfix p("+a+1");
	EXPECT_EQ(false, p.CheckInfix());
}

TEST(TPostfix, CheckInfix_return_true_when_infix_is_correct)
{
	TPostfix p("a+b");
	EXPECT_TRUE(p.CheckInfix());
}