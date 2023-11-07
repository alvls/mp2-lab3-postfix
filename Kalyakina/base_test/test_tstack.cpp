#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, cant_create_stack_with_too_small_length)
{
	ASSERT_ANY_THROW(TStack<int> st(0));
}

TEST(TStack, cant_create_stack_with_too_big_length)
{
	ASSERT_ANY_THROW(TStack<int> st(130));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-3));
}

TEST(TStack, can_push_element_to_empty_stack)
{
	TStack<int> st(4);
	ASSERT_NO_THROW(st.push(4));
}

TEST(TStack, throws_when_push_element_to_full_stack)
{
	TStack<int> st(2);
	st.push(1);
	st.push(13);
	ASSERT_ANY_THROW(st.push(4));
}

TEST(TStack, can_pop_element_of_stack)
{
	TStack<int> st(2);
	st.push(13);
	st.push(5);
	ASSERT_NO_THROW(st.pop());
	EXPECT_EQ(13, st.pop());
}

TEST(TStack, throws_when_pop_element_of_empty_stack)
{
	TStack<int> st(2);
	ASSERT_ANY_THROW(st.pop());
}

TEST(TStack, check_if_stack_is_empty)
{
	TStack<int> st(2);

	EXPECT_EQ(true, st.empty());
	st.push(13);
	EXPECT_EQ(false, st.empty());
}

TEST(TStack, can_check_top_element_of_stack_without_pop)
{
	TStack<int> st(2);
	st.push(13);
	EXPECT_EQ(13, st.getTop());
}

TEST(TStack, throws_when_check_top_element_of_empty_stack)
{
	TStack<int> st(2);
	ASSERT_ANY_THROW(st.getTop());
}