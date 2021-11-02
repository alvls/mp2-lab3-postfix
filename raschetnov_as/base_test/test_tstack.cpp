#include "stack.h"
#include <gtest.h>

TEST (TStack, can_create_stack_with_positive_length) {
  ASSERT_NO_THROW (TStack<int> st(5));
}

TEST (TStack, cant_create_stack_with_negative_length) {
  ASSERT_ANY_THROW (TStack<int> st(-1));
}

TEST (TStack, cant_create_stack_with_too_large_length) {
  ASSERT_ANY_THROW (TStack<int> st(MAX_STACK_SIZE + 1));
}

TEST (TStack, can_create_stack_with_positive_length_and_element_pushed) {
  ASSERT_NO_THROW (TStack<int> st(5, 4));
}

TEST (TStack, can_get_size) {
  TStack<int> st(5);
  EXPECT_EQ (5, st.stack_size());
}

TEST (TStack, current_size_returns_right_value) {
  TStack<int> st(5, 2);
  EXPECT_EQ (1, st.current_size());
}

TEST (TStack, push_adds_element_to_the_top_of_the_stack) {
  TStack<int> st1(5, 2);
  TStack<int> st2(5);
  st2.push(2);
  EXPECT_EQ (st1, st2);
}

TEST (TStack, push_changes_current_size_of_the_stack) {
  TStack<int> st(5, 2);
  st.push(4);
  EXPECT_EQ (2, st.current_size());
}

TEST (TStack, back_returns_top_value) {
  TStack<int> st(5, 2);
  EXPECT_EQ (2, st.back());
}

TEST (TStack, pop_returns_top_value) {
  TStack<int> st(5, 2);
  EXPECT_EQ (2, st.back());
}

TEST (TStack, back_does_not_deletes_top_element) {
  TStack<int> st1(5, 2);
  TStack<int> st2(5, 2);
  st1.back();
  EXPECT_EQ (st1.current_size(), st2.current_size());
}

TEST (TStack, pop_deletes_top_element) {
  TStack<int> st1(5, 2);
  TStack<int> st2(5, 2);
  st1.pop();
  EXPECT_NE (st1.current_size(), st2.current_size());
}

TEST (TStack, stacks_with_different_sizes_are_not_equal) {
  TStack<int> st1(5), st2(6);
  EXPECT_EQ (true, st1 != st2);
}

TEST (TStack, compare_stack_with_itself_returns_true) {
  TStack<int> st(5);
  EXPECT_EQ (true, st == st);
}

TEST (TStack, compare_equal_stacks_returns_true) {
  TStack<int> st1(5, 2), st2(5, 2);
  EXPECT_EQ (true, st1 == st2);
}

TEST (TStack, checks_if_stack_is_full_returns_true) {
  TStack<int> st(1, 1);
  EXPECT_EQ (true, st.is_full());
}

TEST (TStack, checks_if_stack_is_full_returns_false) {
  TStack<int> st(5, 1);
  EXPECT_EQ (false, st.is_full());
}

TEST (TStack, checks_if_stack_is_empty_returns_true) {
  TStack<int> st(5);
  EXPECT_EQ (true, st.is_empty());
}

TEST (TStack, checks_if_stack_is_empty_returns_false) {
  TStack<int> st(5, 1);
  EXPECT_EQ (false, st.is_empty());
}

TEST (TStack, can_assign_stack_to_itself) {
  TStack<int> st(5);
  ASSERT_NO_THROW (st = st);
}

TEST (TStack, can_assign_stacks_of_equal_sizes) {
  TStack<int> st1(5), st2(5);
  EXPECT_EQ (st2, st1 = st2);
}

TEST (TStack, can_asign_stacks_of_different_sizes) {
  TStack<int> st1(5), st2(6);
  EXPECT_EQ (st2, st1 = st2);
}

TEST (TStack, can_create_copied_stack) {
  TStack<int> v1(5);
  ASSERT_NO_THROW (TStack<int> v2(v1));
}

TEST (TStack, copied_stack_is_equal_to_source_one) {
  TStack<int> st1(5), st2(st1);
  EXPECT_EQ (st1, st2);
}
