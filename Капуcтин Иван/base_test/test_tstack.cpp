#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st);
}
TEST(TStack, cant_pop_from_empty_stack)
{
	TStack<int> st;
	ASSERT_ANY_THROW(st.Pop());
}
