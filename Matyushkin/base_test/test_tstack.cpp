#include "stack.h"
#include <gtest.h>
#include <string>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throws_on_negative_length)
{
  ASSERT_ANY_THROW(TStack<int> st(-1));
}

TEST(TStack, new_stack_is_empty)
{
  TStack<int> st(3);
  EXPECT_TRUE(st.IsEmpty());
  EXPECT_FALSE(st.IsFull());
}

TEST(TStack, push_top_pop)
{
  TStack<int> st(3);
  st.Push(1);
  st.Push(2);
  EXPECT_EQ(2, st.Top());
  EXPECT_EQ(2, st.Pop());
  EXPECT_EQ(1, st.Pop());
  EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, throws_on_push_to_full)
{
  TStack<int> st(1);
  st.Push(1);
  EXPECT_TRUE(st.IsFull());
  EXPECT_ANY_THROW(st.Push(2));
}

TEST(TStack, throws_on_pop_from_empty)
{
  TStack<int> st(2);
  EXPECT_ANY_THROW(st.Pop());
}

TEST(TStack, throws_on_top_from_empty)
{
  TStack<int> st(2);
  EXPECT_ANY_THROW(st.Top());
}

TEST(TStack, works_with_string)
{
  TStack<std::string> st(5);
  st.Push("a");
  st.Push("b");
  EXPECT_EQ("b", st.Pop());
  EXPECT_EQ("a", st.Pop());
}