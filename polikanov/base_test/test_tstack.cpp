#include "stack.h"
#include <gtest.h>

TEST(TStack, canCreateStackWithPositiveLength) {
	ASSERT_NO_THROW(TStack<int> st(4));
}

TEST(TStack, cantCreateTooLargeStack) {
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, cantCreateStackWithNegativeLength) {
	ASSERT_ANY_THROW(TStack<int> st(-3));
}

TEST(TStack, canSetAndGetLastElement) {
	TStack<int> st(5);
	st.push(7);
	EXPECT_EQ(7, st.pop());
}

TEST(TStack, canSetAndCheckLastElement) {
	TStack<int> st(5);
	st.push(10);
	EXPECT_EQ(10, st.peek());
}

TEST(TStack, canDefineFullStack) {
	TStack<int> st(2);
	st.push(2);
	st.push(1);
	EXPECT_EQ(true, st.full());
}