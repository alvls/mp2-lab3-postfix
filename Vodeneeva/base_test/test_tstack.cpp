#include "stack.h"
#include <gtest.h>
#include <stdexcept>
#include <string>
#include <utility>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, default_stack_is_empty_and_has_default_capacity)
{
  TStack<int> st;

  EXPECT_TRUE(st.IsEmpty());
  EXPECT_EQ(0u, st.Size());
  EXPECT_EQ(DefaultStackSize, st.Capacity());
}

TEST(TStack, constructor_sets_requested_capacity)
{
  TStack<int> st(7);

  EXPECT_EQ(7u, st.Capacity());
  EXPECT_EQ(0u, st.Size());
}

TEST(TStack, can_create_stack_with_limit_capacity)
{
  ASSERT_NO_THROW(TStack<char> st(MaxStackSize));
}

TEST(TStack, throws_out_of_range_for_zero_capacity)
{
  ASSERT_THROW(TStack<int> st(0), std::out_of_range);
}

TEST(TStack, throws_out_of_range_for_capacity_above_limit)
{
  ASSERT_THROW(TStack<int> st(MaxStackSize + 1), std::out_of_range);
}

TEST(TStack, throws_for_negative_capacity)
{
  ASSERT_ANY_THROW(TStack<int> st(-3));
}

TEST(TStack, freshly_created_stack_is_not_full)
{
  TStack<int> st(1);

  EXPECT_FALSE(st.IsFull());
}

TEST(TStack, pushed_value_becomes_top)
{
  TStack<int> st;
  st.Push(42);

  EXPECT_EQ(42, st.Top());
  EXPECT_FALSE(st.IsEmpty());
}

TEST(TStack, size_increases_by_one_after_each_push)
{
  TStack<int> st;
  for (int i = 1; i <= 5; i++)
  {
    st.Push(i * 10);
    EXPECT_EQ(static_cast<size_t>(i), st.Size());
  }
}

TEST(TStack, pop_returns_values_in_reverse_order_of_push)
{
  TStack<char> st;
  st.Push('x');
  st.Push('y');
  st.Push('z');

  EXPECT_EQ('z', st.Pop());
  EXPECT_EQ('y', st.Pop());
  EXPECT_EQ('x', st.Pop());
  EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, pop_of_single_element_empties_stack)
{
  TStack<int> st;
  st.Push(-1);
  st.Pop();

  EXPECT_TRUE(st.IsEmpty());
  EXPECT_EQ(0u, st.Size());
}

TEST(TStack, throws_underflow_when_pop_from_empty_stack)
{
  TStack<int> st;

  ASSERT_THROW(st.Pop(), std::underflow_error);
}

TEST(TStack, throws_underflow_when_top_of_empty_stack)
{
  TStack<int> st;

  ASSERT_THROW(st.Top(), std::underflow_error);
}

TEST(TStack, throws_when_top_of_empty_const_stack)
{
  const TStack<int> st;

  ASSERT_THROW(st.Top(), std::underflow_error);
}

TEST(TStack, throws_when_pop_after_all_elements_removed)
{
  TStack<int> st;
  st.Push(1);
  st.Push(2);
  st.Pop();
  st.Pop();

  ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, top_gives_access_to_modify_top_element)
{
  TStack<int> st;
  st.Push(1);
  st.Push(2);

  st.Top() = 99;

  EXPECT_EQ(99, st.Pop());
  EXPECT_EQ(1, st.Pop());
}

TEST(TStack, top_of_const_stack_returns_last_element)
{
  TStack<int> st;
  st.Push(3);
  st.Push(4);
  const TStack<int>& ref = st;

  EXPECT_EQ(4, ref.Top());
  EXPECT_EQ(2u, ref.Size());
}

TEST(TStack, grows_when_capacity_is_exhausted)
{
  TStack<int> st(2);
  st.Push(1);
  st.Push(2);

  ASSERT_NO_THROW(st.Push(3));
  EXPECT_EQ(3u, st.Size());
  EXPECT_GE(st.Capacity(), 3u);
}

TEST(TStack, capacity_doubles_on_growth)
{
  TStack<int> st(4);
  for (int i = 0; i < 5; i++)
    st.Push(i);

  EXPECT_EQ(8u, st.Capacity());
}

TEST(TStack, keeps_all_values_after_many_reallocations)
{
  TStack<int> st(1);
  const int n = 5000;
  for (int i = 0; i < n; i++)
    st.Push(i * i);

  ASSERT_EQ(static_cast<size_t>(n), st.Size());
  for (int i = n - 1; i >= 0; i--)
    ASSERT_EQ(i * i, st.Pop());
}

TEST(TStack, can_push_own_top_when_reallocation_happens)
{
  TStack<std::string> st(1);
  st.Push("same");

  st.Push(st.Top());

  EXPECT_EQ(2u, st.Size());
  EXPECT_EQ("same", st.Pop());
  EXPECT_EQ("same", st.Pop());
}

TEST(TStack, capacity_never_exceeds_limit_and_overflow_is_reported)
{
  TStack<char> st(3);
  for (size_t i = 0; i < MaxStackSize; i++)
    st.Push('a');

  EXPECT_TRUE(st.IsFull());
  EXPECT_EQ(MaxStackSize, st.Capacity());
  ASSERT_THROW(st.Push('b'), std::overflow_error);
  EXPECT_EQ(MaxStackSize, st.Size());
}

TEST(TStack, stack_is_not_full_again_after_pop)
{
  TStack<char> st(MaxStackSize);
  for (size_t i = 0; i < MaxStackSize; i++)
    st.Push('q');
  st.Pop();

  EXPECT_FALSE(st.IsFull());
  ASSERT_NO_THROW(st.Push('w'));
}

TEST(TStack, clear_removes_all_elements_but_keeps_capacity)
{
  TStack<int> st(4);
  st.Push(1);
  st.Push(2);
  st.Push(3);

  st.Clear();

  EXPECT_TRUE(st.IsEmpty());
  EXPECT_EQ(4u, st.Capacity());
}

TEST(TStack, clear_of_empty_stack_does_nothing)
{
  TStack<int> st;

  ASSERT_NO_THROW(st.Clear());
  EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, can_use_stack_after_clear)
{
  TStack<int> st;
  st.Push(8);
  st.Clear();
  st.Push(9);

  EXPECT_EQ(1u, st.Size());
  EXPECT_EQ(9, st.Top());
}

TEST(TStack, empty_stacks_are_equal)
{
  TStack<int> a(3), b(10);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST(TStack, stacks_with_same_elements_and_different_capacity_are_equal)
{
  TStack<int> a(2), b(50);
  a.Push(5);
  a.Push(6);
  a.Push(7);
  b.Push(5);
  b.Push(6);
  b.Push(7);

  EXPECT_TRUE(a == b);
}

TEST(TStack, stacks_with_different_order_are_not_equal)
{
  TStack<int> a, b;
  a.Push(1);
  a.Push(2);
  b.Push(2);
  b.Push(1);

  EXPECT_TRUE(a != b);
}

TEST(TStack, stacks_with_different_size_are_not_equal)
{
  TStack<int> a, b;
  a.Push(1);
  a.Push(2);
  b.Push(1);

  EXPECT_FALSE(a == b);
}

class TStackWithData : public ::testing::Test
{
protected:
  TStack<int> st;

  TStackWithData()
      : st(3)
  {
    st.Push(10);
    st.Push(20);
    st.Push(30);
  }
};

TEST_F(TStackWithData, copy_is_equal_to_source)
{
  TStack<int> copy(st);

  EXPECT_TRUE(copy == st);
  EXPECT_EQ(st.Capacity(), copy.Capacity());
}

TEST_F(TStackWithData, copy_has_its_own_memory)
{
  TStack<int> copy(st);

  copy.Top() = -1;
  copy.Push(40);

  EXPECT_EQ(30, st.Top());
  EXPECT_EQ(3u, st.Size());
}

TEST_F(TStackWithData, can_assign_stack)
{
  TStack<int> other(1);
  other.Push(77);

  other = st;

  EXPECT_TRUE(other == st);
  EXPECT_EQ(30, other.Pop());
  EXPECT_EQ(20, other.Pop());
  EXPECT_EQ(10, other.Pop());
}

TEST_F(TStackWithData, assigned_stack_is_independent)
{
  TStack<int> other;
  other = st;

  st.Pop();
  st.Push(100);

  EXPECT_EQ(30, other.Top());
}

TEST_F(TStackWithData, self_assignment_keeps_elements)
{
  TStack<int>& alias = st;

  ASSERT_NO_THROW(st = alias);
  EXPECT_EQ(3u, st.Size());
  EXPECT_EQ(30, st.Top());
}

TEST_F(TStackWithData, chain_assignment_works)
{
  TStack<int> a, b;

  a = b = st;

  EXPECT_TRUE(a == st);
  EXPECT_TRUE(b == st);
}

TEST_F(TStackWithData, move_constructor_takes_elements)
{
  TStack<int> expected(st);

  TStack<int> moved(std::move(st));

  EXPECT_TRUE(moved == expected);
  EXPECT_TRUE(st.IsEmpty());
}

TEST_F(TStackWithData, moved_from_stack_can_be_used_again)
{
  TStack<int> moved(std::move(st));

  st.Push(5);

  EXPECT_EQ(1u, st.Size());
  EXPECT_EQ(5, st.Top());
  EXPECT_EQ(3u, moved.Size());
}

TEST_F(TStackWithData, move_assignment_takes_elements)
{
  TStack<int> target(10);
  target.Push(1);

  target = std::move(st);

  EXPECT_EQ(3u, target.Size());
  EXPECT_EQ(30, target.Top());
}

TEST(TStack, works_with_strings)
{
  TStack<std::string> st(2);
  st.Push("first");
  st.Push("second");
  st.Push("third");

  EXPECT_EQ("third", st.Pop());
  EXPECT_EQ("second", st.Pop());
  EXPECT_EQ("first", st.Pop());
}

TEST(TStack, works_with_doubles)
{
  TStack<double> st;
  st.Push(0.125);
  st.Push(-2.5);

  EXPECT_DOUBLE_EQ(-2.5, st.Pop());
  EXPECT_DOUBLE_EQ(0.125, st.Pop());
}

TEST(TStack, can_store_stacks_in_stack)
{
  TStack<int> inner;
  inner.Push(11);
  TStack<TStack<int>> outer;

  outer.Push(inner);
  inner.Push(12);

  EXPECT_EQ(1u, outer.Top().Size());
  EXPECT_EQ(11, outer.Top().Top());
}
