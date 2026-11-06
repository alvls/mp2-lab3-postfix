#include "stack.h"
#include <gtest.h>
#include <utility>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, can_create_stack_with_negative_length) {
	ASSERT_ANY_THROW(TStack<int> st(-5));
}
TEST(TStack, cant_create_too_large_stack) {
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize+1));
}
TEST(TStack, is_empty_for_new_stack){
	TStack<int> st(5);
	ASSERT_TRUE(st.is_empty());
}
TEST(TStack, can_push_element) {
	TStack<int> st(5);
	st.push(10);
	ASSERT_TRUE(st.peek() == 10);
}
TEST(TStack, can_pop_element) {
	TStack<int> st(5);
	st.push(10);
	st.push(29);
	int a = st.pop();
	ASSERT_TRUE(a == 29 && st.peek() == 10);
}
TEST(TStack, peek_does_not_remove_element) {
	TStack<int> st(5);
	st.push(10);
	st.peek();
	st.peek();
	ASSERT_FALSE(st.is_empty());
}
TEST(TStack, can_empty_stack) {
	TStack<int> st(5);
	st.push(10);
	st.push(15);
	st.push(50);
	st.pop();
	st.pop();
	st.pop();
	ASSERT_TRUE(st.is_empty());
}
TEST(TStack, throws_when_stack_is_full) {
	TStack<int> st(3);
	st.push(10);
	st.push(11);
	st.push(12);
	ASSERT_ANY_THROW(st.push(14));
}
TEST(TStack, throws_when_pop_from_empty_stack) {
	TStack<int> st(5);
	ASSERT_ANY_THROW(st.pop());
}
TEST(TStack, throws_when_peek_from_empty_stack) {
	TStack<int> st(5);
	ASSERT_ANY_THROW(st.peek());
}
TEST(TStack, can_copy_construct_stack) {
	TStack<int> st(5);
	st.push(10);
	st.push(12);
	TStack<int> st1(st);
	ASSERT_TRUE((st.peek() == st1.peek()) && (st1.is_empty() == false));
}
TEST(TStack, copied_stack_has_its_own_memory) {
	TStack<int> st(5);
	st.push(10);
	st.push(12);
	TStack<int> st1(st);
	st.pop();
	ASSERT_TRUE(st1.peek() == 12 && st.peek() == 10);
}
TEST(TStack, can_assign_stack) {
	TStack<int> st(5);
	st.push(10);
	st.push(12);
	TStack<int> st1(10);
	st1 = st;
	ASSERT_TRUE((st1.is_empty() == false) && (st1.peek() == 12));
}
TEST(TStack, can_assign_stack_to_itself) {
	TStack<int> st(5);
	st.push(42);
	st = st;
	ASSERT_EQ(st.peek(), 42);
}
TEST(TStack, can_assign_empty_stack) {
	TStack<int> st(5), st1(10);
	st1.push(23);
	st1 = st;
	ASSERT_TRUE(st1.is_empty());
}
TEST(TStack, can_move_construct_stack) {
	TStack<int> st(5);
	st.push(42);
	TStack<int> st1(std::move(st)); 
	ASSERT_EQ(st1.peek(), 42);     
	ASSERT_TRUE(st.is_empty());     
}
TEST(TStack, can_move_assign_stack) {
	TStack<int> st(5);
	st.push(42);
	TStack<int> st1(10);
	st1 = std::move(st);
	ASSERT_EQ(st1.peek(), 42);
	ASSERT_TRUE(st.is_empty());
}