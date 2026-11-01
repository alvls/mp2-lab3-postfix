#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throws_when_creating_stack_with_negative_length)
{
  ASSERT_ANY_THROW(TStack<int> st(-1));
}

TEST(TStack, throws_when_creating_stack_with_too_large_length)
{
  ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, can_push_and_pop)
{
  TStack<int> st(5);
  st.Push(10);
  st.Push(20);
  EXPECT_EQ(st.Pop(), 20);
  EXPECT_EQ(st.Pop(), 10);
}

TEST(TStack, throws_when_pop_from_empty)
{
  TStack<int> st(5);
  ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, throws_when_top_from_empty)
{
  TStack<int> st(5);
  ASSERT_ANY_THROW(st.Top());
}

TEST(TStack, can_check_is_empty)
{
  TStack<int> st(5);
  EXPECT_TRUE(st.IsEmpty());
  st.Push(1);
  EXPECT_FALSE(st.IsEmpty());
  st.Pop();
  EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, can_copy_stack)
{
  TStack<int> st1(5);
  st1.Push(1);
  st1.Push(2);
  
  TStack<int> st2(st1);
  EXPECT_EQ(st2.Pop(), 2);
  EXPECT_EQ(st2.Pop(), 1);
}

TEST(TStack, can_assign_stack)
{
  TStack<int> st1(5);
  st1.Push(1);
  st1.Push(2);
  
  TStack<int> st2(5);
  st2 = st1;
  EXPECT_EQ(st2.Pop(), 2);
  EXPECT_EQ(st2.Pop(), 1);
}