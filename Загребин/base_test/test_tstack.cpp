#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, cant_create_stack_with_wrong_length)
{
	ASSERT_ANY_THROW(TStack<int> st(0), st1(-1));
}

TEST(TStack, cant_create_stack_with_too_big_length)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize+1));
}

TEST(TStack, true_if_stack_is_empty)
{
	TStack<int> st(1);
	EXPECT_EQ(true, st.Empty());
}

TEST(TStack, can_get_size_of_stack)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(st.GetSize());
}

TEST(TStack, can_push_elem_in_stack)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(st.push(5));
}

TEST(TStack, cant_push_101th_elem_in_stack)
{
	TStack<int> st(30);
	for(int i = 0; i < 100; i++)
		st.push(i);
	ASSERT_ANY_THROW(st.push(101));
}

TEST(TStack, can_get_top_elem_in_stack)
{
	TStack<int> st(5);
	st.push(5);
	EXPECT_EQ(5, st.Top());
}

TEST(TStack, can_pop_elem_in_stack)
{
	TStack<int> st(5);
	st.push(5);
	st.pop();
	EXPECT_EQ(0, st.GetSize());
}