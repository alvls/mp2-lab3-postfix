#include "stack.h"
#include <gtest.h>

TEST(StackTest, PushPop) 
{
  TStack<int> stack(10);
  stack.Push(1);
  EXPECT_EQ(stack.Pop(), 1);
}

TEST(StackTest, IsEmpty) 
{
  TStack<int> stack(10);
  EXPECT_TRUE(stack.IsEmpty());
}

TEST(StackTest, IsNotEmptyAfterPush) 
{
  TStack<int> stack(10);
  stack.Push(1);
  EXPECT_FALSE(stack.IsEmpty());
}

TEST(StackTest, IsEmptyAfterPop) 
{
  TStack<int> stack(10);
  stack.Push(1);
  stack.Pop();
  EXPECT_TRUE(stack.IsEmpty());
}

TEST(StackTest, Peek) 
{
  TStack<int> stack(10);
  stack.Push(1);
  EXPECT_EQ(stack.Peek(), 1);
}

TEST(StackTest, PopOrder) 
{
  TStack<int> stack(10);
  stack.Push(1);
  stack.Push(2);
  EXPECT_EQ(stack.Pop(), 2);
  EXPECT_EQ(stack.Pop(), 1);
}

TEST(StackTest, Overflow) 
{
  TStack<int> stack(1);
  stack.Push(1);
  EXPECT_ANY_THROW(stack.Push(2));
}

TEST(StackTest, Underflow) 
{
  TStack<int> stack(10);
  EXPECT_ANY_THROW(stack.Pop());
}

TEST(StackTest, PeekEmptyStack) 
{
  TStack<int> stack(10);
  EXPECT_ANY_THROW(stack.Peek());
}
