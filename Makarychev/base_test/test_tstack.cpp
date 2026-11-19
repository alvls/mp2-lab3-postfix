#include "stack.h"
#include <gtest.h>
#include <stdexcept>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, rejects_zero_size)
{
  ASSERT_ANY_THROW(TStack<int> st(0));
}
TEST(TStack, rejects_negative_size)
{
  ASSERT_ANY_THROW(TStack<int> st(-5));
}
TEST(TStack, rejects_too_large_size)
{
  ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}
TEST(TStack, starts_empty)
{
  TStack<int> st(3);
  EXPECT_TRUE(st.IsEmpty());
  EXPECT_FALSE(st.IsFull());
  EXPECT_EQ(0, st.GetCount());
}
TEST(TStack, push_and_pop_follow_lifo)
{
  TStack<int> st(3);
  st.Push(10);
  st.Push(20);
  EXPECT_EQ(20, st.Top());
  EXPECT_EQ(20, st.Pop());
  EXPECT_EQ(10, st.Pop());
  EXPECT_TRUE(st.IsEmpty());
}
TEST(TStack, detects_full_stack)
{
  TStack<int> st(1);
  st.Push(5);
  EXPECT_TRUE(st.IsFull());
  EXPECT_THROW(st.Push(6), std::overflow_error);
}
TEST(TStack, detects_empty_stack)
{
  TStack<int> st(1);
  EXPECT_THROW(st.Pop(), std::underflow_error);
  EXPECT_THROW(st.Top(), std::underflow_error);
}
TEST(TStack, clear_resets_stack)
{
  TStack<int> st(2);
  st.Push(3);
  st.Clear();
  EXPECT_TRUE(st.IsEmpty());
  st.Push(4);
  EXPECT_EQ(4, st.Pop());
}
TEST(TStack, copy_is_independent)
{
  TStack<int> first(3);
  first.Push(7);
  TStack<int> second(first);
  first.Pop();
  EXPECT_EQ(7, second.Pop());
}
TEST(TStack, assignment_is_independent)
{
  TStack<int> first(2), second(3);
  first.Push(8);
  second = first;
  first.Pop();
  EXPECT_EQ(8, second.Pop());
}
TEST(TStack, self_assignment_keeps_values)
{
  TStack<int> st(2);
  st.Push(9);
  st = st;
  EXPECT_EQ(9, st.Pop());
}
