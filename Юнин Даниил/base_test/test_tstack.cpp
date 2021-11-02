#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> st(10);
	ASSERT_NO_THROW(TStack<int> st1(st));
}

TEST(TStack, can_create_stack_with_operator_equal)
{
	TStack<int> st(10);
	TStack<int> temp(4);
	ASSERT_NO_THROW(st = temp);
}

TEST(TStack, true_if_stack_is_empty)
{
	TStack<int> st(2);
	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TStack, true_if_stack_is_full)
{
	TStack<int> st(3);
	for (int i = 0; i < 3; i++) {
		st.Put(3);
	}
	EXPECT_EQ(true, st.IsFull());
}

TEST(TStack, can_get_data_count_of_stack)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(st.GetDataCount());
}

TEST(TStack, can_get_top_of_stack)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(st.GetTop());
}

TEST(TStack, can_push_elem_in_stack)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(st.Put(5));
}

TEST(TStack, can_get_top_elem_in_stack)
{
	TStack<int> st(5);
	st.Put(5);
	EXPECT_EQ(5, st.Get());
}

TEST(TStack, can_put_elem_in_stack)
{
	TStack<int> st(5);
	st.Put(5);
	st.Put(5);
	st.Get();
	EXPECT_EQ(1, st.GetDataCount());
}

TEST(TStack, throws_when_stack_is_empty_and_do_get)
{
	TStack<int> st(2);
	ASSERT_ANY_THROW(st.Get());
}

TEST(TStack, throws_when_stack_is_full_and_do_put)
{
	TStack<int> st(3);
	for (int i = 0; i < 3; i++) {
		st.Put(3);
	}
	ASSERT_ANY_THROW(st.Put(2));
}
