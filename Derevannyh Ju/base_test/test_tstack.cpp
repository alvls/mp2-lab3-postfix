#include "stack.h"
#include <gtest.h>
#include <stdexcept>
TEST(TStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, throws_when_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(TStack<int> st(-1));
}
TEST(TStack, throws_when_create_stack_with_zero_length)
{
    ASSERT_ANY_THROW(TStack<int> st(0));
}
TEST(TStack, throws_when_create_stack_with_too_large_length)
{
    ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}
TEST(TStack, new_stack_is_empty)
{
    TStack<int> st(5);
    EXPECT_TRUE(st.IsEmpty());
    EXPECT_FALSE(st.IsFull());
}
TEST(TStack, stack_is_full_after_pushing_max_elements)
{
    TStack<int> st(3);
    st.Push(1);
    st.Push(2);
    st.Push(3);
    EXPECT_FALSE(st.IsEmpty());
    EXPECT_TRUE(st.IsFull());
}
TEST(TStack, can_push_and_pop_element)
{
    TStack<int> st(5);
    st.Push(42);
    EXPECT_FALSE(st.IsEmpty());
    EXPECT_EQ(42, st.Pop());
    EXPECT_TRUE(st.IsEmpty());
}
TEST(TStack, can_push_and_peek_element)
{
    TStack<int> st(5);
    st.Push(10);
    st.Push(20);
    EXPECT_EQ(20, st.Peek());
    EXPECT_EQ(20, st.Peek()); // Peek не удаляет
    EXPECT_EQ(20, st.Pop());
    EXPECT_EQ(10, st.Peek());
}
TEST(TStack, throws_when_push_to_full_stack)
{
    TStack<int> st(2);
    st.Push(1);
    st.Push(2);
    ASSERT_ANY_THROW(st.Push(3));
}
TEST(TStack, throws_when_pop_from_empty_stack)
{
    TStack<int> st(2);
    ASSERT_ANY_THROW(st.Pop());
}
TEST(TStack, throws_when_peek_from_empty_stack)
{
    TStack<int> st(2);
    ASSERT_ANY_THROW(st.Peek());
}
TEST(TStack, can_create_copy_of_stack)
{
    TStack<int> st(5);
    st.Push(1);
    st.Push(2);
    st.Push(3);
    TStack\<int> copy(st);

    EXPECT_EQ(3, copy.Pop());
    EXPECT_EQ(2, copy.Pop());
    EXPECT_EQ(1, copy.Pop());
    EXPECT_TRUE(copy.IsEmpty());

    EXPECT_EQ(3, st.Pop());
}