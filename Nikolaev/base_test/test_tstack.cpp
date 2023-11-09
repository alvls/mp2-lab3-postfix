#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length) {
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, cant_create_too_large_stack) {
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, throws_when_create_stack_with_negative_length) {
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, can_set_and_get_last_element) {
	TStack<int> st(5);
	st.push(7);
	EXPECT_EQ(7, st.pop());
}

TEST(TStack, can_set_and_check_last_element) {
	TStack<int> st(5);
	st.push(21);
	EXPECT_EQ(21, st.peek());
}

TEST(TStack, can_get_information_that_full_stack_is_full) {
	TStack<int> st(1);
	st.push(21);
	EXPECT_EQ(true, st.full());
}