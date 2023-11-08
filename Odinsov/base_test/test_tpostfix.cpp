#include "postfix.h"
#include <gtest.h>


TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p("a+b*c"));
}
TEST(TPostfix, can_get_infix) {
	TPostfix p("a+b*c");
	EXPECT_EQ("a+b*c", p.GetInfix());
}
TEST(TPostfix, can_get_postfix)
{
	TPostfix p("a+b*c");
	EXPECT_EQ("abc*+", p.GetPostfix());
}
TEST(TPostfix, can_get_lexems)
{
	TPostfix p("a+b*c");
	vector<char> ans{'a', '+', 'b', '*', 'c'};
	EXPECT_EQ(ans, p.Getlexems());
}
TEST(TPostfix, can_calculate)
{
	TPostfix p("a+b*c");
	map <char, double> values{{'a', 2}, { 'b',2 }, { 'c',2 }};
	EXPECT_EQ(6, p.Calculate(values));
}
TEST(TPostfix, can_calculate_with_staples)
{
	TPostfix p("(a+b)*c");
	map <char, double> values{{'a', 2}, { 'b',2 }, { 'c',2 }};
	EXPECT_EQ(8, p.Calculate(values));
}
TEST(TPostfix, can_pow)
{
	TPostfix p("a^b");
	map <char, double> values{{'a', 2}, { 'b',3 }};
	EXPECT_EQ(8, p.Calculate(values));
}
TEST(TPostfix, cant_divide_0)
{
	TPostfix p("a/b");
	map<char, double> values{{'a', 2}, { 'b',0 }};
	ASSERT_ANY_THROW(p.Calculate(values));
}
TEST(TPostfix, can_calculate_with_space)
{
	TPostfix p("a + b * c");
	map <char, double> values{{'a', 2}, { 'b',2 }, { 'c',2 }};
	EXPECT_EQ(6, p.Calculate(values));
}