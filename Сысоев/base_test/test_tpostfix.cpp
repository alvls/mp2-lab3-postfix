#include <gtest.h>
#include "postfix.h"
#include "postfix.cpp"

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, get_infix)
{
	TPostfix p("a+b*c");
	EXPECT_EQ("a+b*c", p.GetInfix());
}

TEST(TPostfix, get_postfix_form)
{
	TPostfix p("(a+b)*c+d");
	p.ToPostfix();
	EXPECT_EQ("ab+c*d+", p.GetPostfix());
}

TEST(TPostfix, check_CountValue)
{
	TPostfix p("a+b-c+d");
	EXPECT_EQ(4, p.CountVal());
}

TEST(TPostfix, check_postfix1)
{
	TPostfix p("a + b * c");
	p.ToPostfix();
	EXPECT_EQ("abc*+", p.GetPostfix());
}

TEST(TPostfix, check_postfix2)
{
	TPostfix p("a+b*(c-d)-e");
	p.ToPostfix();
	EXPECT_EQ("abcd-*+e-", p.GetPostfix());
}

TEST(TPostfix, check_postfix3)
{
	TPostfix p("(a+b)*(c-d)");
	p.ToPostfix();
	EXPECT_EQ("ab+cd-*", p.GetPostfix());
}

TEST(TPostfix, check_postfix4)
{
	TPostfix p("( ( ( a + b ) * c - d ) + h ) * m - k");
	p.ToPostfix();
	EXPECT_EQ("ab+c*d-h+m*k-", p.GetPostfix());
}

TEST(TPostfix, check_calculate1)
{
	TPostfix p("( ( ( a + b ) * c - d ) + h ) * s - n");
	p.ToPostfix();
	double* values;
	int CountVal = p.CountVal();
	values = new double[CountVal];
	int j = 1;
	for (int i = 0; i < CountVal; i++)
	{
		values[i] = j++;
	}
	int res;
	res = p.Calculate(values);
	EXPECT_EQ(res, 53);
}

TEST(TPostfix, check_calculate2)
{
	TPostfix p("(a + b) * (c - d)");
	p.ToPostfix();
	double* values;
	int CountVal = p.CountVal();
	values = new double[CountVal];
	for (int i = 0; i < CountVal; i++)
	{
		values[i] = i + 1;
	}
	int res;
	res = p.Calculate(values);
	EXPECT_EQ(res, -3);
}

TEST(TPostfix, check_calculate3)
{
	TPostfix p("a+b+(c*i)+(d-y)+g");
	p.ToPostfix();
	double* values;
	int CountVal = p.CountVal();
	values = new double[CountVal];
	for (int i = 0; i < CountVal; i++)
	{
		values[i] = i + 1;
	}
	int res;
	res = p.Calculate(values);
	EXPECT_EQ(res, 21);
}

TEST(TPostfix, check_calculate4)
{
	TPostfix p("a+b+c+d-g");
	p.ToPostfix();
	double* values;
	int CountVal = p.CountVal();
	values = new double[CountVal];
	for (int i = 0; i < CountVal; i++)
	{
		values[i] = i + 1;
	}
	int res;
	res = p.Calculate(values);
	EXPECT_EQ(res, 5);
}

