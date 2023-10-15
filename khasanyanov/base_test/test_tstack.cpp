#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, canå_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(1000));
}

TEST(TStack, can_get_size)
{
	TStack<int> st(4);
	ASSERT_NO_THROW(st.getSize());
}

TEST(TStack, can_get_top_element)
{
	TStack<int> st(4);
	st.push(1);
	ASSERT_NO_THROW(st.getTop());
}

TEST(TStack, can_push_element)
{
	TStack<int> st(4);
	ASSERT_NO_THROW(st.push(34));
}

TEST(TStack, cant_push_element_to_full_stack)
{
	TStack<int> st(1);
	st.push(33);
	ASSERT_ANY_THROW(st.push(34));
}

TEST(TStack, can_pop_element)
{
	TStack<int> st(4);
	st.push(33);
	ASSERT_NO_THROW(st.pop());
}

TEST(TStack, cant_pop_element_from_empty_stack)
{
	TStack<int> st(1);
	ASSERT_ANY_THROW(st.pop());
}

TEST(TStack, cant_get_top_element_from_empty_stack)
{
	TStack<int> st(1);
	ASSERT_ANY_THROW(st.getTop());
}

TEST(TStack, operator_push_element)
{
	TStack<int> st(1);
	st.push(33);
	EXPECT_EQ(st.getTop(), 33);
}

TEST(TStack, operator_pop_element)
{
	TStack<int> st(1);
	st.push(33);
	EXPECT_EQ(st.pop(), 33);
}

TEST(TStack, double_operator_pop_and_push)
{
	TStack<int> st(3);
	st.push(33);
	st.push(32);
	st.pop();
	EXPECT_EQ(st.pop(), 33);
}

TEST(TStack, double_operator_pop_create_stack_empry)
{
	TStack<int> st(3);
	st.push(33);
	st.push(32);
	st.pop();
	st.pop();
	ASSERT_ANY_THROW(st.getTop());
}