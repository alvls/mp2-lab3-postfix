#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
   ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, can_create_stack_with_negative_length)
{
   ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, cant_create_too_large_stack)
{
   ASSERT_ANY_THROW(TStack<int> st(500));
}

TEST(TStack, can_push_and_pop_element)
{
   TStack<int> st;
   st.Push(5);
   ASSERT_EQ(5, st.Pop());
}

TEST(TStack, cant_push_element_to_full_stack)
{
   TStack<int> st(2);
   st.Push(1);
   st.Push(2);
   ASSERT_ANY_THROW(st.Push(3));
}

TEST(TStack, can_get_top_element)
{
   TStack<int> st;
   st.Push(5);
   ASSERT_EQ(5, st.getTopElem());
}

TEST(TStack, stack_is_empty)
{
   TStack<int> st(5);
   EXPECT_TRUE(st.isEmpty());
}

TEST(TStack, cant_pop_element_from_empty_stack)
{
   TStack<int> st(1);
   ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, cant_get_top_element_from_empty_stack)
{
   TStack<int> st(1);
   ASSERT_ANY_THROW(st.getTopElem());
}

TEST(TStack, getTopElem_does_not_remove_top_element)
{
   TStack<int> st;
   st.Push(3);
   st.getTopElem();
   ASSERT_FALSE(st.isEmpty());
}

TEST(TStack, stack_is_not_empty_after_push)
{
   TStack<int> st;
   st.Push(5);
   ASSERT_FALSE(st.isEmpty());
}

TEST(TStack, stack_size_is_correct_after_pushes_and_pops)
{
   TStack<int> st;
   st.Push(5);
   st.Push(7);
   st.Push(8);
   st.Pop();
   ASSERT_EQ(2, st.getSize());
}
