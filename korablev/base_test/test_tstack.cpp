#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st);
}

TEST(TStack, can_push_and_pop_element)
{
	TStack<int> st;
	st.Push(1);
	ASSERT_EQ(1, st.Pop());
}

TEST(TStack, pop_from_empty_stack_throws_exception)
{
	TStack<int> st;
	ASSERT_THROW(st.Pop(), const char*);
}

TEST(TStack, can_peek_top_element)
{
	TStack<int> st;
	st.Push(2);
	ASSERT_EQ(2, st.Peek());
}

TEST(TStack, peek_does_not_remove_top_element)
{
	TStack<int> st;
	st.Push(3);
	st.Peek();
	ASSERT_FALSE(st.IsEmpty());
}

TEST(TStack, can_check_if_stack_is_empty)
{
	TStack<int> st;
	ASSERT_TRUE(st.IsEmpty());
}

TEST(TStack, can_check_if_stack_is_not_empty_after_push)
{
	TStack<int> st;
	st.Push(4);
	ASSERT_FALSE(st.IsEmpty());
}

TEST(TStack, stack_size_is_correct_after_multiple_pushes)
{
	TStack<int> st;
	st.Push(5);
	st.Push(6);
	ASSERT_EQ(2, st.getSize());
}

TEST(TStack, stack_size_is_correct_after_pushes_and_pops)
{
	TStack<int> st;
	st.Push(7);
	st.Push(8);
	st.Pop();
	ASSERT_EQ(1, st.getSize());
}

TEST(TStack, stack_grows_correctly)
{
	TStack<int> st;
	for (int i = 0; i < 100; ++i) {
		st.Push(i);
	}
	ASSERT_EQ(100, st.getSize());
}

TEST(TStack, peek_throws_exception_when_stack_is_empty)
{
	TStack<int> st;
	ASSERT_THROW(st.Peek(), const char*);
}

TEST(TStack, pop_throws_exception_when_stack_is_empty)
{
	TStack<int> st;
	ASSERT_THROW(st.Pop(), const char*);
}

TEST(TStack, can_handle_large_number_of_elements)
{
	TStack<int> st;
	for (int i = 0; i < 10000; ++i) {
		ASSERT_NO_THROW(st.Push(i));
	}
	ASSERT_EQ(10000, st.getSize());
}