#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(3));
}

TEST(TStack, cannot_create_stack_with_negetive_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-3));
}

TEST(TStack, cannot_create_stack_with_length_larger_MaxStackSize)
{
	ASSERT_ANY_THROW(TStack<int> st(101));
}

TEST(TStack, can_push_element)
{
	TStack<int> st(2);
	st.Push(1);
	EXPECT_EQ(st.GetTop(), 1);
}


TEST(TStack, can_delete_element)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(2);
	st.pop();

	EXPECT_EQ(st.GetTop(), 1);
}

TEST(TStack, check_IsEmpty_if_Stack_IsEmpty)
{
	TStack<int> st(2);

	EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, check_IsEmpty_if_Stack_not_IsEmpty)
{
	TStack<int> st(2);
	st.Push(1);

	EXPECT_FALSE(st.IsEmpty());
}

TEST(TStack, check_IsFull_if_Stack_IsFull)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(2);

	EXPECT_TRUE(st.IsFull());
}

TEST(TStack, check_IsFull_if_not_Stack_IsFull)
{
	TStack<int> st(2);

	EXPECT_FALSE(st.IsFull());
}


