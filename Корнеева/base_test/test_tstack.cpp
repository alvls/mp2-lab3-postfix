#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, can_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st);
}

TEST(TStack, can_copy_stack)
{
	TStack<int> st1(5);
	st1.Push(1);
	st1.Push(2);
	TStack<int> st2(st1);
	ASSERT_EQ(st1.GetSize(), st2.GetSize());
	ASSERT_EQ(st1.Top(), st2.Top());
}

TEST(TStack, copied_stack_is_independent)
{
	TStack<int> st1(5);
	TStack<int> st2(st1);
	st1.Push(1);
	st2.Push(2);
	ASSERT_NE(st1.Top(), st2.Top());
}

TEST(TStack, can_assign_stack_to_itself) 
{
	TStack<int> st1(5);
	st1.Push(1);
	st1.Push(2);

	ASSERT_NO_THROW(st1 = st1);

	TStack<int> st2(st1);
	st1 = st1;

	EXPECT_EQ(st1, st2);
}

TEST(TStack, can_assign_stack_to_another)
{
	TStack<int> st1(5);
	st1.Push(1);
	st1.Push(2);

	TStack<int> st2(3);
	st2.Push(3);

	st2 = st1;

	EXPECT_EQ(st2, st1);
	EXPECT_EQ(st2.GetSize(), st1.GetSize());
}

TEST(TStack, can_assign_empty_stack_to_another)
{
	TStack<int> st1(5);
	st1.Push(1);
	st1.Push(2);

	TStack<int> st2;

	st2 = st1;

	EXPECT_EQ(st2, st1);
	EXPECT_EQ(st2.GetSize(), st1.GetSize());
}

TEST(TStack, can_assign_stack_to_empty_stack)
{
	TStack<int> st1;

	TStack<int> st2(3);
	st2.Push(3);

	st2 = st1;

	EXPECT_EQ(st2, st1);
	EXPECT_EQ(st2.GetSize(), st1.GetSize());
}

TEST(TStack, equal_operator_returns_true_for_equal_stacks)
{
	TStack<int> st1(5);
	st1.Push(1);
	st1.Push(2);

	TStack<int> st2(5);
	st2.Push(1);
	st2.Push(2);

	ASSERT_TRUE(st1 == st2);
	ASSERT_FALSE(st1 != st2);
}

TEST(TStack, equal_operator_returns_false_for_unequal_stacks)
{
	TStack<int> st1(5);
	st1.Push(1);
	st1.Push(2);

	TStack<int> st2(5);
	st2.Push(2);
	st2.Push(1);

	ASSERT_FALSE(st1 == st2);
	ASSERT_TRUE(st1 != st2);
}

TEST(TStack, get_size_of_empty_stack)
{
	TStack<int> st(5);
	ASSERT_EQ(st.GetSize(), 0);
}

TEST(TStack, get_size_of_non_empty_stack)
{
	TStack<int> st(5);
	st.Push(1);
	st.Push(2);
	ASSERT_EQ(st.GetSize(), 2);
}

TEST(TStack, is_empty_for_empty_stack)
{
	TStack<int> st(5);
	ASSERT_TRUE(st.IsEmpty());
}

TEST(TStack, is_empty_for_non_empty_stack)
{
	TStack<int> st(5);
	st.Push(1);
	ASSERT_FALSE(st.IsEmpty());
}

TEST(TStack, is_full_for_full_stack)
{
	TStack<int> st(2); 
	st.Push(1);
	st.Push(2);
	ASSERT_TRUE(st.IsFull());
}

TEST(TStack, is_full_for_non_full_stack)
{
	TStack<int> st(2);
	st.Push(1);
	ASSERT_FALSE(st.IsFull());
}

TEST(TStack, can_push_element_to_non_full_stack)
{
	TStack<int> st(3); 
	st.Push(1);
	st.Push(2);

	ASSERT_NO_THROW(st.Push(3));
	ASSERT_EQ(st.Top(), 3);
}

TEST(TStack, can_push_element_to_full_stack)
{
	TStack<int> st(2); 
	st.Push(1);
	st.Push(2);

	ASSERT_NO_THROW(st.Push(3));
}

TEST(TStack, can_push_element_to_overflowed_stack)
{
	TStack<int> st(2); 
	st.Push(1);
	st.Push(2);
	st.Push(3);

	ASSERT_EQ(st.GetSize(), 3);
	ASSERT_EQ(st.Top(), 3); 
}

TEST(TStack, can_pop_element_from_non_empty_stack)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(2);

	EXPECT_EQ(st.Pop(), 2);
}

TEST(TStack, throws_when_popping_element_from_empty_stack)
{
	TStack<int> st(2); 
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, top_removed_after_popping_element)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(2);

	st.Pop();

	EXPECT_EQ(st.Top(), 1);
}

TEST(TStack, can_get_top_element)
{
	TStack<int> st(3);
	st.Push(1);
	st.Push(2);
	st.Push(3);

	EXPECT_EQ(st.Top(), 3);
}

TEST(TStack, throws_when_getting_top_element_from_empty_stack)
{
	TStack<int> st;

	ASSERT_ANY_THROW(st.Top());
}

TEST(TStack, top_element_still_exists_after_getting)
{
	TStack<int> st(3);
	st.Push(1);
	st.Push(2);
	st.Push(3);

	st.Top();

	EXPECT_EQ(st.Top(), 3);
}