#include "stack.h"
#include <gtest.h>


TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}


TEST(TStack, cant_create_stack_with_unpositive_size)
{
	ASSERT_ANY_THROW(TStack <int> st(-1));
}

TEST(TStack, cant_create_stack_with_big_size)
{
	ASSERT_ANY_THROW(TStack <int> st(MaxStackSize + 1));
}

TEST(TStack, can_check_stack_is_empty)
{
	TStack <int> st(3);
	EXPECT_EQ(true, st.Empty());
}

TEST(TStack, can_check_stack_is_full)
{
	TStack <int> st(3);
	for (int i = 0; i < 3; i++)
		st.Push(1);
	EXPECT_EQ(true, st.Full());
}

TEST(TStack, cant_get_value_from_empty_stack)
{
	TStack <int> st(3);
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, can_get_value_from_stack)
{
	TStack <int> st1(3), st2(3);
	st1.Push(1);
	st2.Push(st1.Pop());
	EXPECT_EQ(1, st2.Pop());
}

TEST(TStack, cant_push_element_in_full_stack)
{
	TStack <int> st(3);
	for (int i = 0; i < 3; i++)
		st.Push(1);
	ASSERT_ANY_THROW(st.Push(1));
}

TEST(TStack, can_push_element)
{
	TStack <int> st(1);
	st.Push(1);
	EXPECT_EQ(1, st.Pop());
}

TEST(TStack, can_cope_stack)
{
	TStack<int> st1(3);
	for (int i = 0; i < 3; i++)
		st1.Push(1);
	TStack <int> st2(st1);
	EXPECT_EQ(1, st2.GetTopElem());
}

TEST(TStack, stacks_have_different_memory)
{
	TStack<int> st1(3), st2(4);
	EXPECT_NE(&st1, &st2);
}


