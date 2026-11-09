#include "stack.h"
#include <gtest.h>

#include <stdexcept>

TEST(TStack, can_create_stack_with_positive_length) //создание
{
    ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, can_create_stack_with_max_length)
{
    ASSERT_NO_THROW(TStack<int> st(MaxStackSize));
}

TEST(TStack, cannot_create_stack_with_zero_length)
{
    ASSERT_THROW(TStack<int> st(0), std::invalid_argument);
}

TEST(TStack, cannot_create_stack_with_negative_length)
{
    ASSERT_THROW(TStack<int> st(-1), std::invalid_argument);
}

TEST(TStack, cannot_create_stack_bigger_than_max)
{
    ASSERT_THROW(TStack<int> st(MaxStackSize + 1), std::invalid_argument);
}

TEST(TStack, new_stack_is_empty) //базовое состояние
{
    TStack<int> st(5);
    EXPECT_TRUE(st.IsEmpty());
    EXPECT_FALSE(st.IsFull());
    EXPECT_EQ(0, st.GetCount());
    EXPECT_EQ(5, st.GetSize());
}

TEST(TStack, can_push_and_pop_single_element) //LIFO
{
    TStack<int> st(5);
    st.Push(42);
    EXPECT_EQ(42, st.Pop());
    EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, pop_returns_elements_in_lifo_order)
{
    TStack<int> st(5);
    st.Push(1);
    st.Push(2);
    st.Push(3);

    EXPECT_EQ(3, st.Pop());
    EXPECT_EQ(2, st.Pop());
    EXPECT_EQ(1, st.Pop());
    EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, top_returns_element_without_removing)
{
    TStack<int> st(5);
    st.Push(42);

    EXPECT_EQ(42, st.Top());
    EXPECT_EQ(42, st.Top());
    EXPECT_EQ(1, st.GetCount());
}

TEST(TStack, top_after_push_changes)
{
    TStack<int> st(5);
    st.Push(1);
    st.Push(2);

    EXPECT_EQ(2, st.Top());
    st.Pop();
    EXPECT_EQ(1, st.Top());
}

TEST(TStack, stack_becomes_full_after_size_pushes) //полный стек
{
    TStack<int> st(3);
    st.Push(10);
    st.Push(20);
    st.Push(30);

    EXPECT_TRUE(st.IsFull());
    EXPECT_FALSE(st.IsEmpty());
    EXPECT_EQ(3, st.GetCount());
}

TEST(TStack, push_to_full_stack_throws_overflow) //переполнение/опустошение
{
    TStack<int> st(2);
    st.Push(1);
    st.Push(2);

    ASSERT_THROW(st.Push(3), std::overflow_error);
}

TEST(TStack, pop_from_empty_stack_throws_underflow)
{
    TStack<int> st(3);
    ASSERT_THROW(st.Pop(), std::underflow_error);
}

TEST(TStack, top_from_empty_stack_throws_underflow)
{
    TStack<int> st(3);
    ASSERT_THROW(st.Top(), std::underflow_error);
}

TEST(TStack, clear_makes_stack_empty) //Clear
{
    TStack<int> st(5);
    st.Push(1);
    st.Push(2);
    st.Push(3);

    st.Clear();
    EXPECT_TRUE(st.IsEmpty());
    EXPECT_EQ(0, st.GetCount());
}

TEST(TStack, can_push_after_clear)
{
    TStack<int> st(2);
    st.Push(1);
    st.Push(2);
    st.Clear();

    ASSERT_NO_THROW(st.Push(3));
    EXPECT_EQ(3, st.Pop());
}

TEST(TStack, copy_constructor_copies_elements) //копирование
{
    TStack<int> a(3);
    a.Push(1);
    a.Push(2);

    TStack<int> b(a);
    EXPECT_EQ(2, b.GetCount());
    EXPECT_EQ(2, b.Pop());
    EXPECT_EQ(2, a.GetCount()); //оригинал не изменён
}

TEST(TStack, assignment_copies_elements)
{
    TStack<int> a(3);
    a.Push(1);
    a.Push(2);

    TStack<int> b(2);
    b = a;

    EXPECT_EQ(2, b.GetCount());
    EXPECT_EQ(2, b.Pop());
    EXPECT_EQ(2, a.GetCount());
}

TEST(TStack, copied_stack_is_independent)
{
    TStack<int> a(3);
    a.Push(1);

    TStack<int> b(a);
    b.Push(2);

    EXPECT_EQ(1, a.GetCount());
    EXPECT_EQ(2, b.GetCount());
}

TEST(TStack, works_with_char) //шаблонность
{
    TStack<char> st(3);
    st.Push('a');
    st.Push('b');

    EXPECT_EQ('b', st.Pop());
    EXPECT_EQ('a', st.Pop());
}

TEST(TStack, works_with_double)
{
    TStack<double> st(3);
    st.Push(1.5);
    st.Push(2.5);

    EXPECT_DOUBLE_EQ(2.5, st.Pop());
    EXPECT_DOUBLE_EQ(1.5, st.Top());
}
