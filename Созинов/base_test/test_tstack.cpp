#include "stack.h"
#include <gtest.h>

//test create
TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> stI(5));
	ASSERT_NO_THROW(TStack<double> stD(5));
	ASSERT_NO_THROW(TStack<char> stC(5));
}

TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> stI(-5));
	ASSERT_ANY_THROW(TStack<double> stD(-5));
	ASSERT_ANY_THROW(TStack<char> stC(-5));
}

TEST(TStack, cant_create_stack_with_zero_length)
{
	ASSERT_ANY_THROW(TStack<int> stI(0));
	ASSERT_ANY_THROW(TStack<double> stD(0));
	ASSERT_ANY_THROW(TStack<char> stC(0));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> stI(MaxStackSize + 1));
	ASSERT_ANY_THROW(TStack<double> stD(MaxStackSize + 1));
	ASSERT_ANY_THROW(TStack<char> stC(MaxStackSize + 1));
}

//test push
TEST(TStack, can_push_to_stack)
{
	TStack<int> st(5);

	ASSERT_NO_THROW(st.Push(2));
	EXPECT_EQ(2, st.GetTopElem());
}

TEST(TStack, throw_when_push_to_full_stack)
{
	TStack<int> st(3);
	st.Push(3);
	st.Push(4);
	st.Push(5);

	ASSERT_ANY_THROW(st.Push(6));

}

//test pop
TEST(TStack, can_pop_from_stack)
{
	TStack<int> st(5);
	st.Push(2);
	st.Push(3);

	ASSERT_NO_THROW(st.Pop());
	EXPECT_EQ(2, st.Pop());
}

TEST(TStack, throw_when_pop_from_empty_stack)
{
	TStack<int> st(3);


	ASSERT_ANY_THROW(st.Pop());
}

//test geteltem
TEST(TStack, can_get_top_elem)
{
	TStack<int> st(4);
	st.Push(6);

	EXPECT_EQ(6, st.GetTopElem());
}

TEST(TStack, throw_when_get_in_empty_stack)
{
	TStack<int> st(4);

	ASSERT_ANY_THROW(st.GetTopElem());
}

//test empty
TEST(TStack, check_empty)
{
	TStack<int> st(4);
	EXPECT_EQ(true, st.IsEmpty());
	st.Push(4);
	EXPECT_EQ(false, st.IsEmpty());
}

//test full
TEST(TStack, check_full)
{
	TStack<int> st(2);
	EXPECT_EQ(false, st.IsFull());
	st.Push(4);
	st.Push(3);
	EXPECT_EQ(true, st.IsFull());
}