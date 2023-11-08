#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p("a*b"));
}
TEST(TStack, can_calculate_expressions_with_spaces)
{
    TStack expr("1 + 2");
    EXPECT_EQ(1 + 2, expr.calculate());
}
