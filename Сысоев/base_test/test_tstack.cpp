#include "stack.h"
#include <gtest.h>

TEST(stack, can_create_stack_with_positive_length){
  ASSERT_NO_THROW(stack<int> st(5));
}
