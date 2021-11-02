#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> v(5));
}

TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> v(-5));
}
TEST(TStack, cant_create_too_large_stack) 
{
	ASSERT_ANY_THROW(TStack<int> v(MaxStackSize + 1));
}

TEST(TStack, cant_create_stack_with_zero_length) 
{
	ASSERT_ANY_THROW(TStack<int> v(0));
}
 

TEST(TStack, cant_put_to_FULL_stack) 
{
	TStack<int> v(2);
	v.Put(1);
	v.Put(2);
	ASSERT_ANY_THROW(v.Put(4));
}

TEST(TStack, cant_get_of_CLEAR_stack) 
{
	TStack<int> v(5);
	ASSERT_ANY_THROW(v.Get());
}



TEST(TStack, can_get_of_stack_about_one)//òåñò
{
	TStack<int> v(5);
	v.Put(4);
	EXPECT_EQ(4, v.Get());
}

TEST(TStack, can_get_of_stack_about_two)//òåñò
{
	TStack<int> v(5);
	v.Put(4);
	v.Put(7);
	EXPECT_EQ(7, v.Get());
}

TEST(TStack, can_get_of_stack_about_three)//òåñò
{
	TStack<int> v(5);
	v.Put(4);
	v.Put(1);
	v.Put(10);
	EXPECT_EQ(10, v.Get());
}


TEST(TStack, IsEmpty_false_of_full_stack) 
{
	TStack<int> v(3);
	v.Put(5);
	v.Put(5);
	ASSERT_FALSE(v.IsEmpty());
}

TEST(TStack, IsEmpty_true_of_clear_stack) 
{
	TStack<int> v(2);
	ASSERT_TRUE(v.IsEmpty());
}

TEST(TStack, IsEmpty_false_of_any_stack) 
{
	TStack<int> v(2);
	v.Put(4);
	ASSERT_FALSE(v.IsEmpty());
}

TEST(TStack, IsFull_true_of_full_stack) 
{
	TStack<int> v(2);
	v.Put(4);
	v.Put(4);
	ASSERT_TRUE(v.IsFull());
}

TEST(TStack, IsFull_false_of_clear_stack)  
{
	TStack<int> v(2);
	ASSERT_FALSE(v.IsFull());
}

TEST(TStack, IsFull_false_of_any_stack) 
{
	TStack<int> v(2);
	v.Put(4);
	ASSERT_FALSE(v.IsFull());
}