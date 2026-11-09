#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, my_custom_push_and_pop_test)
{
    TStack<int> stack(10);
    stack.Push(5);
    stack.Push(10);

    EXPECT_EQ(stack.Pop(), 10);
    EXPECT_EQ(stack.Pop(), 5);  
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStack, my_test_stack_overflow)
{
    TStack<int> stack(2); 
    stack.Push(1);
    stack.Push(2);

    ASSERT_ANY_THROW(stack.Push(3));
}
TEST(TStack, my_test_stack_is_initially_empty)
{
    TStack<int> stack(5);
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStack, my_test_push_and_pop)
{
    TStack<int> stack(5);
    stack.Push(10);
    stack.Push(20);
    EXPECT_EQ(stack.Pop(), 20);
    EXPECT_EQ(stack.Pop(), 10);
}

TEST(TStack, my_test_top_method)
{
    TStack<int> stack(5);
    stack.Push(42);
    EXPECT_EQ(stack.Top(), 42);
    EXPECT_EQ(stack.Top(), 42); 
    EXPECT_FALSE(stack.IsEmpty());
}

TEST(TStack, my_test_pop_empty_stack)
{
    TStack<int> stack(5);
    ASSERT_ANY_THROW(stack.Pop());
}

TEST(TStack, my_test_char_stack)
{
    TStack<char> stack(3);
    stack.Push('A');
    stack.Push('B');
    EXPECT_EQ(stack.Pop(), 'B');
    EXPECT_EQ(stack.Pop(), 'A');
}

TEST(TStack, my_test_double_stack)
{
    TStack<double> stack(5);
    stack.Push(3.14);
    stack.Push(2.71);
    EXPECT_DOUBLE_EQ(stack.Pop(), 2.71);
    EXPECT_DOUBLE_EQ(stack.Pop(), 3.14);
}

TEST(TStack, my_test_top_does_not_pop)
{
    TStack<int> stack(5);
    stack.Push(100);
    stack.Top(); 
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_EQ(stack.Pop(), 100);   
}

