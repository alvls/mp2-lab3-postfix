#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> stack);
}

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> stack(5));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> stack(MAX_STACK_SIZE + 1));
}

TEST(TStack, is_new_stack_empty)
{
	TStack<int> stack;
	EXPECT_EQ(1, stack.is_empty());
}

TEST(TStack, is_stack_empty_after_pop_of_alone_elem)
{
	TStack<int> stack;
	stack.push(7);
	stack.pop();
	EXPECT_EQ(1, stack.is_empty());
}

TEST(TStack, can_get_size)
{
	TStack<int> stack(2);
	stack.push(3);
	ASSERT_NO_THROW(stack.size());
}

TEST(TStack, can_get_size_empty_stack)
{
	TStack<int> stack;
	ASSERT_NO_THROW(stack.size());
}

TEST(TStack, can_push_element)
{
	TStack<int> stack;
	ASSERT_NO_THROW(stack.push(3));
}

TEST(TStack, can_pop_element)
{
	TStack<int> stack;
	stack.push(3);
	ASSERT_NO_THROW(stack.pop());
}

TEST(TStack, throws_when_pop_from_empty_stack)
{
	TStack<int> stack(3);
	ASSERT_ANY_THROW(stack.pop());
}

TEST(TStack, can_get_top_element)
{
	TStack<int> stack;
	stack.push(3);
	ASSERT_NO_THROW(stack.top());
}

TEST(TStack, throws_when_get_top_from_empty_stack)
{
	TStack<int> stack(1);
	ASSERT_ANY_THROW(stack.top());
}

TEST(TStack, is_last_added_element_the_top_one)
{
	TStack<int> stack;
	stack.push(1);
	stack.push(5);
	stack.push(9);
	stack.push(4);
	stack.push(8);
	EXPECT_EQ(8, stack.top());
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> stack(-5));
}