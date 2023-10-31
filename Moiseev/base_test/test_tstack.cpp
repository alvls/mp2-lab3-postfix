#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st);
}

TEST(TStack, can_get_size)
{
	TStack<int> st;
	st.Push(1);
	ASSERT_NO_THROW(st.getSize());
}

TEST(TStack, can_get_size_from_empty_stack)
{
	TStack<int> st;
	ASSERT_NO_THROW(st.getSize());
}

TEST(TStack, can_check_empty)
{
	TStack<int> st;
	ASSERT_NO_THROW(st.IsEmpty());
}

TEST(TStack, can_push_element)
{
	TStack<int> st;
	ASSERT_NO_THROW(st.Push(1));
}

TEST(TStack, can_pop_element)
{
	TStack<int> st;
	st.Push(1);
	ASSERT_NO_THROW(st.Pop());
}

TEST(TStack, cant_pop_element_from_empty_stack)
{
	TStack<int> st;
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, double_pop_element)
{
	TStack<int> st;
	st.Push(1);
	st.Push(2);
	EXPECT_EQ(st.Pop(), 2);
}

TEST(TStack, dinamic_length_stack)
{
	TStack<int> st;
	st.Push(1);
	st.Push(2);
	st.Push(3);
	st.Pop();
	st.Push(4);
	st.Push(5);

	ASSERT_NO_THROW(st.Pop());
}
