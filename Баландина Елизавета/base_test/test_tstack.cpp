#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, can_not_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, can_not_create_stack_with_large_length)
{
	ASSERT_ANY_THROW(TStack<int> s(MaxStackSize + 1));
}
TEST(TStack, can_set_and_get_element)
{
	TStack<int> s(10);

	s.Push(5);

	EXPECT_EQ(s.Pop(), 5);
}
TEST(TStack, check_on_empty_stack)
{
	TStack<int> s(2);

	EXPECT_EQ(true, s.IsEmpty());
}

TEST(TStack, check_on_full_stack)
{
	TStack<int> s(2);

	s.Push(2);
	s.Push(3);

	EXPECT_EQ(true, s.IsFull());
}
TEST(TStack, can_show_elem_of_stack)
{
	TStack<int> s(10);

	s.Push(10);

	EXPECT_EQ(10, s.Top());
}

