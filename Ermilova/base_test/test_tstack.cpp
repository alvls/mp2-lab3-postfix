#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
  ASSERT_NO_THROW(TStack<int> st);
}

TEST(TStack, can_get_size)
{
	TStack<int> st;
	st.Push(4);
	ASSERT_NO_THROW(st.GetSize());
}

TEST(TStack, can_get_size_empty_stack)
{
	TStack<int> st;
	ASSERT_NO_THROW(st.GetSize());
}

TEST(TStack, can_cheñk_empty)
{
	TStack<int> st;
	ASSERT_NO_THROW(st.IsEmpty());
}

TEST(TStack, can_push_element)
{
	TStack<int> st;
	ASSERT_NO_THROW(st.Push(6));
}

TEST(TStack, can_pop_element)
{
	TStack<int> st;
	st.Push(6);
	ASSERT_NO_THROW(st.Pop());
}

TEST(TStack, cant_pop_element_empty_stack)
{
	TStack<int> st;
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, cant_push_element_in_full_stack)
{
	TStack<int> st;
	for (int i = 0; i < 100; i++) {
		st.Push(i);
	}
	ASSERT_ANY_THROW(st.Push(1));
}

TEST(TStack, double_push_operation)
{
	TStack<int> st;
	st.Push(6);
	st.Push(8);
	EXPECT_EQ(st.Pop(), 8);
}

TEST(TStack, double_pop_operation)
{
	TStack<int> st;
	st.Push(6);
	st.Push(8);
	st.Push(2);
	st.Pop();
	st.Pop();
	EXPECT_EQ(st.Pop(), 6);
}