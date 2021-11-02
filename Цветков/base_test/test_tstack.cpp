#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int>  st1(-1));
}
TEST(TStack, cant_create_stack_with_biggest_length)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}
TEST(TStack, cant_create_stack_with_zero_length)
{
	ASSERT_ANY_THROW(TStack<int>  st1(0));
}
TEST(TStack, can_add_elem_in_stack)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(st.add(5));
}
TEST(TStack, can_true_empty)
{
	TStack<int> st(5);
	EXPECT_EQ(true, st.empty());
}
TEST(TStack, can_true_full)
{
	TStack<int> st(1);
	st.add(2);
	EXPECT_EQ(true, st.full());
}
TEST(TStack, cant_add_excess_elem)
{
	TStack<int> st(10);
	for (int i = 0; i < 10; i++)
		st.add(i);
	ASSERT_ANY_THROW(st.add(1));
}
TEST(TStack, cant_get_elem_from_empty_stack)
{
	TStack<int> st(2);
	ASSERT_ANY_THROW(st.gettop());
}
TEST(TStack, cant_get_info_elem_from_empty_stack)
{
	TStack<int> st(2);
	ASSERT_ANY_THROW(st.infotop());
}
TEST(TStack, can_get_info_elem_from_stack)
{
	TStack<int> st(2);
	st.add(2);
	EXPECT_EQ(2, st.infotop());
}
TEST(TStack, can_get_elem_from_stack)
{
	TStack<int> st(1);
	st.add(2);
	st.gettop();
	EXPECT_EQ(true, st.empty());
}
TEST(TStack, can_get_size_stack)
{
	TStack<int> st(2);
	EXPECT_EQ(2, st.getsize());
}
TEST(TStack, can_set_size_stack)
{
	TStack<int> st(2);
	st.setsize(3);
	EXPECT_EQ(3, st.getsize());
}