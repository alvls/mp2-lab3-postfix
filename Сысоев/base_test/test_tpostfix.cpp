#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_with_inicialization_of_string)
{
	ASSERT_NO_THROW(TPostfix p("a+b"));
}

TEST(TPostfix, can_get_infix)
{
	TPostfix p("a+b");
	EXPECT_EQ("a+b", p.GetInfix());
}

TEST(TPostfix, can_create_right_postfix)
{
	TPostfix p("a+b*c/d-e");
	p.ToPostfix();
	EXPECT_EQ(" abc*d/+e-", p.GetPostfix());
}

TEST(TPostfix, can_calculate_postfix)
{
	TPostfix p("(1+2)+(3*4+1+1)");
	p.ToPostfix();
	EXPECT_EQ(17, p.Calculate());
}

/*TEST(TPostfix, can_get_right_priority_of_the_operations)
{
	TPostfix p("a+b");
	EXPECT_TRUE(p.Priority('*') > p.Priority('+'));
}
TEST(TPostfix, can_get_right_priority_of_operations)
{
	TPostfix p("a*b");
	string res;
	res = p.GetInfix();
	EXPECT_EQ(true, res.Check_op(p[1]));
}

TEST(TPostfix, can_get_check_operations)
{
	TPostfix p("a*b");
	string res;
	res = p.GetInfix();
	EXPECT_EQ(2, res.Priority(p[1]));
}*/

