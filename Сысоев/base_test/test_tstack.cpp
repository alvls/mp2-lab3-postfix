#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(1));
}
TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}
TEST(TStack, can_push_element)
{
	TStack<int> st(1);
	ASSERT_NO_THROW(st.push(10));
}
TEST(TStack, can_pop_element)
{
	TStack<int> st(1);
	int tmp = 1;
	st.push(tmp);
	EXPECT_EQ(st.pop(), tmp);
}
TEST(TStack, correct_stack_operation_when_add_and_delete_elements)
{
	TStack<char> st(4);
	st.push('+');
	st.push('-');
	st.pop();
	st.push('*');
	st.push('/');
	st.push('-');
	st.pop();
	st.pop();
	st.push('-');
	st.pop();
	st.pop();
	EXPECT_EQ(st.pop(), '+');
}
TEST(TStack, can_check_stack_is_empty)
{
	TStack<int> st(1);
	EXPECT_EQ(st.isempty(), true);
}
TEST(TStack, can_check_stack_is_full)
{
	TStack<int> st(1);
	st.push(1);
	EXPECT_EQ(st.isfull(), true);
}
TEST(TStack, can_get_size)
{
	TStack<char> st(3);
	st.push('+');
	st.push('-');
	EXPECT_EQ(st.get_size(), 2);
}