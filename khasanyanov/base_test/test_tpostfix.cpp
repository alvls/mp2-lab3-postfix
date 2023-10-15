#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

//TEST(TPostfix, can_create_postfix_from_expression)
//{
//	ASSERT_NO_THROW(TPostfix p("1+3*(5-7)"));
//}

//TEST(TPostfix, can_create_postfix_from_formula)
//{
//	ASSERT_NO_THROW(TPostfix p("b-4ac"));
//}