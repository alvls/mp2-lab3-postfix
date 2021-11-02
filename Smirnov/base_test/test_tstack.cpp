#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, throws_when_create_stack_with_too_large_length)
{
	const int size = MaxStackSize + 1;

	ASSERT_ANY_THROW(TStack<int> st(size));
}

TEST(TStack, can_get_length)
{
	const int size = 5;
	TStack<int> st(size);

	EXPECT_EQ(5, st.GetSize());
}

TEST(TStack, can_check_emptiness)
{
	const int size = 5;
	TStack<int> st(size);

	EXPECT_EQ(true, st.isEmpty());
}

TEST(TStack, can_push)
{
	const int size = 5;
	const int value = 7;
	TStack<int> st(size);
	st.Push(value);

	EXPECT_EQ(value, st.GetTopElem());
}

TEST(TStack, can_check_fullness)
{
	const int size = 5;
	TStack<int> st(size);
	for (size_t i = 0; i < size; i++)
	{
		st.Push(i);
	}

	EXPECT_EQ(true, st.isFull());
}

TEST(TStack, throws_when_push_with_fullness_stack)
{
	const int size = 5;
	TStack<int> st(size);
	for (size_t i = 0; i < size; i++)
	{
		st.Push(i);
	}

	ASSERT_ANY_THROW(st.Push(7));
}

TEST(TStack, can_pop)
{
	const int size = 5;
	const int value = 7;
	TStack<int> st(size);
	st.Push(value);

	EXPECT_EQ(value, st.Pop());
	EXPECT_EQ(true, st.isEmpty());
}

TEST(TStack, throws_when_pop_with_empty_stack)
{
	const int size = 5;
	TStack<int> st(size);

	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, can_create_copied_stack)
{
	const int size = 5;
	TStack<int> st(size);

	ASSERT_NO_THROW(TStack<int> stCopy(st));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
	const int size = 5;
	TStack<int> st(size);
	for (size_t i = 0; i < size; i++)
	{
		st.Push(i);
	}
	TStack<int> copy(st);

	EXPECT_EQ(copy, st);
}

TEST(TStack, can_assign_stack_to_itself)
{
	const int size = 5;
	TStack<int> st(size);

	ASSERT_NO_THROW(st = st);
}

TEST(TStack, can_assign_stacks_of_equal_size)
{
	const int size = 5;
	TStack<int> st1(size);
	TStack<int> st2(size);
	for (size_t i = 0; i < size; i++)
	{
		st1.Push(i);
	}
	st2 = st1;

	EXPECT_EQ(st2, st1);
}

TEST(TStack, assign_operator_change_vector_size)
{
	const int sizeSt1 = 5;
	const int sizeSt2 = 7;
	TStack<int> st1(sizeSt1);
	TStack<int> st2(sizeSt2);
	st1 = st2;

	EXPECT_EQ(st1.GetSize(), sizeSt2);
}

TEST(TStack, can_assign_stacks_of_different_size)
{
	const int sizeSt1 = 5;
	const int sizeSt2 = 7;
	TStack<int> st1(sizeSt1);
	TStack<int> st2(sizeSt2);
	for (size_t i = 0; i < sizeSt1; i++)
	{
		st1.Push(i);
	}
	st2 = st1;

	EXPECT_EQ(st2, st1);
}


