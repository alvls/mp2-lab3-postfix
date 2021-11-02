#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}
TEST(TStack, cant_create_stack_with_zero_length)
{
	ASSERT_ANY_THROW(TStack<int> st(0));
}
TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}
TEST(TStack, cant_push_to_full_stack)
{
	TStack<int> st(2);
	st.push(1);
	st.push(2);
	ASSERT_ANY_THROW(st.push(4));
}
TEST(TStack, cant_pop_of_clear_stack)
{
	TStack<int> st(2);
	ASSERT_ANY_THROW(st.Pop());
}
TEST(TStack, cant_top_of_clear_stack)
{
	TStack<int> st(2);
	ASSERT_ANY_THROW(st.Top());
}
TEST(TStack, can_top_of_stack)
{
	TStack<int> st(5);
	st.push(4);
	st.push(1);
	st.push(77);
	EXPECT_EQ(77, st.Top());
}
TEST(TStack, can_pop_of_stack)
{
	TStack<int> st(5);
	st.push(4);
	st.push(1);
	st.push(77);
	EXPECT_EQ(77, st.Pop());
}
TEST(TStack, can_push_and_pop)
{
	TStack<int> st(5);
	st.push(4);
	st.push(5);
	EXPECT_EQ(5, st.Pop());
	EXPECT_EQ(4, st.Top());
}
TEST(TStack, isEmpty_false_of_full_stack)
{
	TStack<int> st(2);
	st.push(4);
	st.push(4);
	ASSERT_FALSE(st.isEmpty());
}
TEST(TStack, isEmpty_true_of_clear_stack)
{
	TStack<int> st(2);
	ASSERT_TRUE(st.isEmpty());
}
TEST(TStack, IsFull_true_of_full_stack)
{
	TStack<int> st(2);
	st.push(4);
	st.push(4);
	ASSERT_TRUE(st.isFull());
}
TEST(TStack, IsFull_false_of_clear_stack)
{
	TStack<int> st(2);
	ASSERT_FALSE(st.isFull());
}
