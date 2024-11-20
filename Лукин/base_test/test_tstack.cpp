#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st{});
}

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throws_an_error_if_the_stack_size_is_too_large)
{
	ASSERT_ANY_THROW(TStack<int> st(1000));
}

TEST(TStack, throws_an_error_if_the_stack_size_is_less_than_one)
{
	ASSERT_ANY_THROW(TStack<int> st(0));
	ASSERT_ANY_THROW(TStack<int> st(-1));
}

TEST(TStack, pop_and_top_work_correctly)
{
	TStack<int> tmp(5);

	tmp.push(10);

	EXPECT_EQ(10, tmp.pop());
}

TEST(TStack, impossible_to_push_to_full_stack)
{
	TStack<int> tmp(MaxStackSize);

	for (int i = 1; i <= MaxStackSize; i++)
		tmp.push(i);

	ASSERT_ANY_THROW(tmp.push(101));
}

TEST(TStack, isEmpty_working)
{
	TStack<int> tmp(1);

	EXPECT_TRUE(tmp.isEmpty());
}

TEST(TStack, throws_an_error_when_pop_from_an_empty_stack)
{
	TStack<int> tmp(1);

	ASSERT_ANY_THROW(tmp.pop());
}

TEST(TStack, can_get_size)
{
	TStack<int> tmp(19);

	EXPECT_EQ(19, tmp.stack_size());
}

TEST(TStack, can_change_size_if_it_need)
{
	TStack<int> tmp;

	tmp.push(1);

	EXPECT_EQ(1, tmp.stack_size());
	EXPECT_NO_THROW(tmp.push(2));
	EXPECT_GE(tmp.stack_size(), 1);
}
