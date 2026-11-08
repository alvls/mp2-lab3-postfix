#include "stack.h"
#include <gtest.h>
#include <string>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, can_create_stack_with_default_length)
{
  ASSERT_NO_THROW(TStack<int> st);
}

TEST(TStack, can_create_stack_with_max_length)
{
  ASSERT_NO_THROW(TStack<int> st(MaxStackSize));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
  ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, throws_when_create_stack_with_zero_length)
{
  ASSERT_ANY_THROW(TStack<int> st(0));
}

TEST(TStack, throws_when_create_too_large_stack)
{
  ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, new_stack_is_empty)
{
  TStack<int> st(5);

  EXPECT_TRUE(st.IsEmpty());
  EXPECT_EQ(0, st.GetCount());
}

TEST(TStack, new_stack_is_not_full)
{
  TStack<int> st(5);

  EXPECT_FALSE(st.IsFull());
}

TEST(TStack, stack_is_not_empty_after_push)
{
  TStack<int> st(5);
  st.Push(1);

  EXPECT_FALSE(st.IsEmpty());
}

TEST(TStack, can_push_and_pop_element)
{
  TStack<int> st(5);
  st.Push(7);

  EXPECT_EQ(7, st.Pop());
}

TEST(TStack, stack_is_empty_after_pop_of_last_element)
{
  TStack<int> st(5);
  st.Push(7);
  st.Pop();

  EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, pop_returns_elements_in_reverse_order)
{
  TStack<int> st(5);
  st.Push(1);
  st.Push(2);
  st.Push(3);

  EXPECT_EQ(3, st.Pop());
  EXPECT_EQ(2, st.Pop());
  EXPECT_EQ(1, st.Pop());
}

TEST(TStack, top_returns_last_element)
{
  TStack<int> st(5);
  st.Push(1);
  st.Push(2);

  EXPECT_EQ(2, st.Top());
}

TEST(TStack, top_does_not_remove_element)
{
  TStack<int> st(5);
  st.Push(1);
  st.Push(2);
  st.Top();

  EXPECT_EQ(2, st.GetCount());
  EXPECT_EQ(2, st.Pop());
}

TEST(TStack, throws_when_pop_from_empty_stack)
{
  TStack<int> st(5);

  ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, throws_when_top_from_empty_stack)
{
  TStack<int> st(5);

  ASSERT_ANY_THROW(st.Top());
}

TEST(TStack, throws_when_pop_more_elements_than_pushed)
{
  TStack<int> st(5);
  st.Push(1);
  st.Pop();

  ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, stack_is_full_after_pushing_max_elements)
{
  TStack<int> st(3);
  st.Push(1);
  st.Push(2);
  st.Push(3);

  EXPECT_TRUE(st.IsFull());
}

TEST(TStack, throws_when_push_to_full_stack)
{
  TStack<int> st(2);
  st.Push(1);
  st.Push(2);

  ASSERT_ANY_THROW(st.Push(3));
}

TEST(TStack, can_push_after_pop_from_full_stack)
{
  TStack<int> st(2);
  st.Push(1);
  st.Push(2);
  st.Pop();

  ASSERT_NO_THROW(st.Push(3));
  EXPECT_EQ(3, st.Top());
}

TEST(TStack, get_count_returns_number_of_elements)
{
  TStack<int> st(5);
  st.Push(1);
  st.Push(2);
  st.Push(3);
  st.Pop();

  EXPECT_EQ(2, st.GetCount());
}

TEST(TStack, clear_makes_stack_empty)
{
  TStack<int> st(5);
  st.Push(1);
  st.Push(2);
  st.Clear();

  EXPECT_TRUE(st.IsEmpty());
  EXPECT_EQ(0, st.GetCount());
}

TEST(TStack, can_push_after_clear)
{
  TStack<int> st(2);
  st.Push(1);
  st.Push(2);
  st.Clear();
  st.Push(5);

  EXPECT_EQ(5, st.Top());
}

TEST(TStack, can_create_copied_stack)
{
  TStack<int> st(5);
  st.Push(1);

  ASSERT_NO_THROW(TStack<int> st1(st));
}

TEST(TStack, copied_stack_has_same_elements)
{
  TStack<int> st(5);
  st.Push(1);
  st.Push(2);
  TStack<int> st1(st);

  EXPECT_EQ(2, st1.GetCount());
  EXPECT_EQ(2, st1.Pop());
  EXPECT_EQ(1, st1.Pop());
}

TEST(TStack, copied_stack_has_its_own_memory)
{
  TStack<int> st(5);
  st.Push(1);
  TStack<int> st1(st);

  st1.Pop();
  st1.Push(100);

  EXPECT_EQ(1, st.Top());
}

TEST(TStack, can_assign_stacks)
{
  TStack<int> st1(5), st2(5);
  st1.Push(4);
  st1.Push(8);

  st2 = st1;

  EXPECT_EQ(2, st2.GetCount());
  EXPECT_EQ(8, st2.Pop());
  EXPECT_EQ(4, st2.Pop());
}

TEST(TStack, assign_changes_stack_size)
{
  TStack<int> st1(5), st2(2);
  st1.Push(1);

  st2 = st1;
  st2.Push(2);
  st2.Push(3);

  EXPECT_EQ(3, st2.GetCount());
}

TEST(TStack, can_assign_stack_to_itself)
{
  TStack<int> st(5);
  st.Push(3);

  ASSERT_NO_THROW(st = st);
  EXPECT_EQ(3, st.Top());
}

TEST(TStack, can_use_stack_of_strings)
{
  TStack<std::string> st(3);
  st.Push("abc");
  st.Push("de");

  EXPECT_EQ("de", st.Pop());
  EXPECT_EQ("abc", st.Pop());
}

TEST(TStack, can_use_stack_of_doubles)
{
  TStack<double> st(3);
  st.Push(1.5);

  EXPECT_DOUBLE_EQ(1.5, st.Pop());
}
