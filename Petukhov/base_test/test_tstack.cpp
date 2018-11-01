#include "stack.h"
#include <gtest.h>
#include <iostream>
using namespace std;
TEST(TStack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(TStack<int> st(10));
}
TEST(TStack, can_not_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(TStack<int> st(-10));
}

TEST(TStack, can_not_create_stack_with_large_size)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 10));
}
TEST(TStack, stack_not_empty)
{
	TStack<int> st(5);
	EXPECT_EQ(true, st.empty());
}
TEST(TStack, check_stack_for_full)
{
	TStack<int> st(10);
	for (int i = 0; i < 10; i++)
		st.push(i);
	EXPECT_EQ(true, st.full());
}
TEST(TStack, correct_pop)
{
	TStack<int> st(10);
	for (int i = 0; i < 10; i++)
		st.push(i);
	st.pop();
	EXPECT_EQ(false, st.full());
}
TEST(TStack, correct_front)
{
	TStack<int> st(10);
	for (int i = 0; i < 10; i++)
		st.push(i);
	EXPECT_EQ(9, st.front());
}
TEST(TStack, correct_front_then_pop)
{
	TStack<int> st(10);
	for (int i = 0; i < 10; i++)
		st.push(i);
	double res = st.front();
	st.pop();
	EXPECT_EQ(true, (!st.full() && res == 9));
}
TEST(TStack, correct_clear)
{
	TStack<int> st(10);
	for (int i = 0; i < 10; i++)
		st.push(i);
	st.clear();
	EXPECT_EQ(true, st.empty());
}