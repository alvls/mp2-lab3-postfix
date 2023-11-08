#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}
TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(101));
}
TEST(TStack, can_pop)
{
	TStack<int> tmp(1);
	tmp.Push(4);
	EXPECT_EQ(4, tmp.Pop());
}

TEST(TStack, cant_be_more_elements_than_size)
{
	TStack<int> tmp(1);
	tmp.Push(4);
	ASSERT_ANY_THROW(tmp.Push(2));
}
TEST(TStack, cant_pop_if_empty)
{
	TStack<int> tmp(1);
	ASSERT_ANY_THROW(tmp.Pop());
}