#include "postfix.h"
#include <gtest.h>
#include <iostream>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, my_test_simple_to_postfix)
{
    TPostfix postfix("a+b");
    EXPECT_EQ(postfix.ToPostfix(), "ab+");
}

TEST(TPostfix, my_test_priority_to_postfix)
{
    TPostfix postfix("a+b*c");
    EXPECT_EQ(postfix.ToPostfix(), "abc*+");
}

TEST(TPostfix, my_test_brackets_to_postfix)
{
    TPostfix postfix("(a+b)*c");
    EXPECT_EQ(postfix.ToPostfix(), "ab+c*");
}

TEST(TPostfix, my_test_digits_to_postfix)
{
    TPostfix postfix("1+2*3");
    EXPECT_EQ(postfix.ToPostfix(), "123*+");
}

TEST(TPostfix, my_test_nested_brackets)
{
    TPostfix postfix("((a+b)*c)-d");
    EXPECT_EQ(postfix.ToPostfix(), "ab+c*d-");
}

