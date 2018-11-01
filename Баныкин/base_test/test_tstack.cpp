#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, can_not_create_stack_with_negative_length) {
	ASSERT_ANY_THROW(TStack<int> st(-1));
}

TEST(TStack, can_not_create_stack_with_too_large_length) {
	ASSERT_ANY_THROW(TStack<int> st(1000));
}

TEST(TStack, can_assign_stack_with_equal_size) {
	TStack<int> st(4);
	TStack<int> st1(4);
	st.push_back(4);
	st1 = st;
	EXPECT_EQ(4, st1.pop_back());
}

TEST(TStack, can_assign_stack_with_not_equal_size) {
	TStack<int> st(4);
	TStack<int> st1(1);
	st.push_back(4);
	st1 = st;
	EXPECT_EQ(4, st1.pop_back());
}

TEST(TStack, assign_change_stack_size) {
	TStack<int> st(4);
	TStack<int> st1(1);
	st1 = st;
	EXPECT_EQ(4, st1.Size());
}

TEST(TStack, can_add_item) {
	TStack<int> a(5);
	a.push_back(4);
	EXPECT_EQ(4, a.pop_back());
}

TEST(TStack, can_not_add_item_if_stack_is_full) {
	TStack<int> st1(1);
	st1.push_back(1);
	ASSERT_ANY_THROW(st1.push_back(1));
}

TEST(TStack, can_get_item) {
	TStack<int> a(1);
	a.push_back(4);
	EXPECT_EQ(4, a.look_top());
	EXPECT_EQ(4, a.pop_back());
}

TEST(TStack, can_not_get_item_if_stack_is_empty) {
	TStack<int> a(1);
	a.push_back(4);
	a.pop_back();
	ASSERT_ANY_THROW(a.pop_back());
}