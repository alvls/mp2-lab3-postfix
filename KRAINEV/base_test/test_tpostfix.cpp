#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	string expression = "2+2";
	ASSERT_NO_THROW(TPostfix p(expression));
}


TEST(TPostfix, simple_multiplication_test_num1)
{
	string expression = "5*5";
	int result = 25;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}
TEST(TPostfix, simple_multiplication_test_num2_with_scobe)
{
	string expression = "(5*5)*6";
	int result = 150;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}

TEST(TPostfix, simple_addition_test_num1)
{
	string expression = "5+5";
	int result = 10;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}

TEST(TPostfix, simple_addition_test_num2_with_scobe)
{
	string expression = "(5+5)+5";
	int result = 15;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}

TEST(TPostfix, simple_divison_test_num1)
{
	string expression = "5/5";
	int result = 1;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}

TEST(TPostfix, simple_divison_test_num1_with_scobe)
{
	string expression = "(20/2)/2";
	int result = 5;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}

TEST(TPostfix, simple_subtraction_test_num1)
{
	string expression = "5-5";
	int result = 0;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}


TEST(TPostfix, simple_subtraction_test_num2_with_scobe)
{
	string expression = "(5-5)-5";
	int result = -5;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}



