#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<int> st);
}
TEST(TStack, cant_pop_from_empty_stack)
{
	TStack<int> st;
	ASSERT_ANY_THROW(st.Pop());
}
TEST(TStack, peek_does_not_remove_top_element)
{
	TStack<int> st;
	st.Push(9);
	st.Peek();
	ASSERT_FALSE(st.IsEmpty());
}
TEST(TStack, pop_from_empty_stack_throws_exception)
{
	TStack<int> st;
	ASSERT_THROW(st.Pop(), const char*);
}
TEST(TStack, can_peek_top_element)
{
	TStack<int> st;
	st.Push(2);
	ASSERT_EQ(2, st.Peek());
}
TEST(TStack, peek_throws_exception_when_stack_is_empty)
{
	TStack<int> st;
	ASSERT_THROW(st.Peek(), const char*);
}
TEST(TStack, pop_throws_exception_when_stack_is_empty)
{
	TStack<int> st;
	ASSERT_THROW(st.Pop(), const char*);
}
TEST(TStack, can_push_and_pop_element)
{
	TStack<int> st;
	st.Push(1);
	ASSERT_EQ(1, st.Pop());
}