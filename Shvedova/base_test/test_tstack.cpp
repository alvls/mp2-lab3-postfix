#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st);
}
TEST(TStack, can_push)
{
	TStack<int> st;
	ASSERT_NO_THROW(st.Push(5));
}
TEST(TStack, can_get_size)
{
	TStack<int> st;
	st.Push(1);
	st.Push(2);
	st.Push(3);
	EXPECT_EQ(3, st.GetSize());
}
TEST(TStack, can_get_size_of_empty_stack)
{
	TStack<int> st;
	EXPECT_EQ(0, st.GetSize());
}
TEST(TStack, can_check_not_empty_stack)
{
	TStack<int> st;
	st.Push(1);
	st.Push(2);
	st.Push(3);
	EXPECT_FALSE(st.IsEmpty());
}
TEST(TStack, can_check_empty_stack)
{
	TStack<int> st;
	EXPECT_TRUE(st.IsEmpty());
}
TEST(TStack, cant_pop_from_empty_stack)
{
	TStack<int> st;
	ASSERT_ANY_THROW(st.Pop());
}
TEST(TStack, can_pop)
{
	TStack<int> st;
	st.Push(1);
	st.Push(2);
	st.Push(3);
	EXPECT_EQ(3, st.Pop());
}