#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
  ASSERT_NO_THROW(TStack<double> t(3));
  ASSERT_NO_THROW(TStack<float> f(3));
  ASSERT_NO_THROW(TStack<char> c(2));
  ASSERT_NO_THROW(TStack<bool> b(6));
}
TEST(Tstack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-1));
}
TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}
TEST(TStack, empty_stack_shows_that_empty)
{
	TStack<int> s(0);
	bool b = s.is_empty();
	EXPECT_EQ(true, b);
	b = s.is_full();
	EXPECT_EQ(false, b);
}
TEST(TStack, full_stack_shows_that_full)
{
	TStack<int> s(MaxStackSize);
	bool b = s.is_empty();
	EXPECT_EQ(false, b);
	b = s.is_full();
	EXPECT_EQ(true, b);
}
TEST(TStack, stack_can_get_size)
{
	TStack<double> s(3);
	ASSERT_NO_THROW(s.getsize());
	EXPECT_EQ(s.getsize(), 3);
	TStack<bool> b(7);
	ASSERT_NO_THROW(b.getsize());
	EXPECT_EQ(b.getsize(), 7);
}
TEST(TStack, can_create_copied_stack)
{
	TStack<int> t(4);
	ASSERT_NO_THROW(TStack<int> t2(t));
}
TEST(TStack, copied_stack_has_own_memory)
{
	TStack<char> t(3);
	TStack<char> t1(t);
	EXPECT_NE(&t1, &t);
}
TEST(TStack, operator_of_indexation_works)
{
	TStack<float> t(1);
	ASSERT_NO_THROW(t[0]);
}
TEST(TStack, operator_of_indexation_throws_when_index_is_too_large)
{
	TStack<char> c(3);
	ASSERT_ANY_THROW(c[3]);
}
TEST(TStack, operator_of_indexation_throws_when_index_is_negative)
{
	TStack<char> c(3);
	ASSERT_ANY_THROW(c[-1]);
}
TEST(TStack, can_put_element)
{
	TStack<int> t;
	t.put(15);
	EXPECT_EQ(t.getsize(), 1);
	EXPECT_EQ(t[0], 15);
}
TEST(TStack, can_get_element)
{
	TStack<int> t(0);
	t.put(15);
	EXPECT_EQ(t.get(), 15);
	EXPECT_EQ(t.getsize(), 0);
}
