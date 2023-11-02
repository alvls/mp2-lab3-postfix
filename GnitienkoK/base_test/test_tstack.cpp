#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throw_when_create_stack_with_negative_length) {
	ASSERT_ANY_THROW(TStack<int> stck(-5));
}

TEST(TStack, can_push_elem_to_stack) {
	TStack<int> stck(5);
	ASSERT_NO_THROW(stck.push(4));
}

TEST(TStack, can_pop_element_of_stack) {
	TStack<int> stck(5);
	stck.push(10);
	EXPECT_EQ(10, stck.pop());
}

TEST(TStack, throw_when_create_stack_with_too_much_length) {
	ASSERT_ANY_THROW(TStack<int> stck(MaxStackSize+1));
}

TEST(TStack, can_check_the_state_of_the_stack_isFull) {
	TStack<int> stck(1);
	stck.push(10);
	EXPECT_EQ(true, stck.IsFull());
}

TEST(TStack, can_check_the_state_of_the_stack_isEmpty) {
	TStack<int> stck(1);
	EXPECT_EQ(true, stck.IsEmpty());
}

TEST(TStack, can_get_size_of_stack) {
	TStack<int> stck(10);
	int i;
	for (i = 0; i < 5; i++) {
		stck.push(1);
	}
	EXPECT_EQ(i, stck.ssize());
}
