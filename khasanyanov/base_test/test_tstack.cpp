#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st);
}

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, can_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, can_create_copyed_stack)
{
	ASSERT_NO_THROW(TStack<int> st(TStack<int> s));
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

TEST(TStack, can_use_compare_operator)
{
	TStack<int> st, st2;
	ASSERT_NO_THROW(st2 == st);
}

TEST(TStack, can_use_assign_operator)
{
	TStack<int> st, st2(4);
	ASSERT_NO_THROW(st = st2);
}

TEST(TStack, assign_operator)
{
	TStack<int> st, st2;
	st.push(12);
	st = st2;
	EXPECT_EQ(st2, st);
}

TEST(TStack, assign_operator_change_stack_size)
{
	TStack<int> st, st2;
	st2.push(12); st2.push(22);
	st = st2;
	EXPECT_EQ(st.getSize(), 2);
}

TEST(TStack, copy_create_equal_vector)
{
	TStack<int> st2;
	st2.push(12); st2.push(22);
	TStack<int> st(st2);
	EXPECT_EQ(st, st2);
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