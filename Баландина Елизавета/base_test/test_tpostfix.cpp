#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	string ex = "a+b";
  ASSERT_NO_THROW(TPostfix p(ex));
}

TEST(TPostfix, number_one_test)
{
	string ex = "a+b";
	TPostfix p(ex);
	string res = "ab+";
	EXPECT_EQ(res,p.ToPostfix());
}
TEST(TPostfix, number_two_test)
{
	string ex = "a+b/d-c";
	TPostfix p(ex);
	string res = "abd/+c-";
	EXPECT_EQ(res, p.ToPostfix());
}
TEST(TPostfix, number_three_test)
{
	string ex = "(a+b)/k-c";
	TPostfix p(ex);
	string res = "ab+k/c-";
	EXPECT_EQ(res, p.ToPostfix());
}
TEST(TPostfix, number_four_test)
{
	string ex = "(a+b)/(d*c)";
	TPostfix p(ex);
	string res = "ab+dc*/";
	EXPECT_EQ(res, p.ToPostfix());
}