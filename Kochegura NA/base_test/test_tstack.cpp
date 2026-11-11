#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, throws_when_create_stack_with_zero_length)
{
	ASSERT_ANY_THROW(TStack<int> st(0));
}

TEST(TStack, throws_when_create_stack_with_too_large_length)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, new_stack_is_empty)
{
	TStack<int> st(5);
	EXPECT_TRUE(st.IsEmpty());
	EXPECT_FALSE(st.IsFull());
}

TEST(TStack, stack_becomes_full_after_filling)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(2);
	EXPECT_TRUE(st.IsFull());
	EXPECT_FALSE(st.IsEmpty());
}

TEST(TStack, can_push_and_pop_element)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(st.Push(42));
	EXPECT_EQ(42, st.Pop());
}

TEST(TStack, can_push_and_top_element)
{
	TStack<int> st(5);
	st.Push(42);
	EXPECT_EQ(42, st.Top());
	EXPECT_FALSE(st.IsEmpty()); 
}

TEST(TStack, pop_decrements_stack_size)
{
	TStack<int> st(5);
	st.Push(10);
	st.Push(20);
	st.Pop();
	EXPECT_EQ(10, st.Top()); 
}

TEST(TStack, throws_when_pop_from_empty_stack)
{
	TStack<int> st(5);
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, throws_when_top_from_empty_stack)
{
	TStack<int> st(5);
	ASSERT_ANY_THROW(st.Top());
}

TEST(TStack, throws_when_push_to_full_stack)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(2);
	ASSERT_ANY_THROW(st.Push(3));
}
