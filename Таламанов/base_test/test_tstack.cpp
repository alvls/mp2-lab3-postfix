#include "stack.h"
#include <gtest.h>

template <class T>
class TStackTest : public ::testing::Test 
{
protected:
	TStack<T> *stack;
	TStackTest() : stack(NULL) {};

	void CreateStack(int _size)  
	{
		stack = new TStack(_size);
	}
};



//TEST(TStack, can_create_stack_with_positive_length)
//{
//	ASSERT_NO_THROW(TStack<int> stack(5)); 
//}
//
//TEST(TStack, cant_create_stack_with_negative_length)
//{
//	ASSERT_ANY_THROW(TStack<int> stack(-5)); 
//}
//
//
//
//TEST(TStack, cant_create_stack_with_too_large_length)
//{
//	ASSERT_ANY_THROW(TStack<int> stack(MAX_STACK_SIZE + 1)); 
//}
//
//
//TEST(TStack, cant_create_stack_with_too_large_length)
//{
//	ASSERT_ANY_THROW(TStack<int> stack(MAX_STACK_SIZE + 1)); 
//}