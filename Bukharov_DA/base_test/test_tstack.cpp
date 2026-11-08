#include <gtest.h>
#include "stack.h"

TEST(TStack, Can_Create_Stack_With_Default_Capacity) {
    ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, Can_Create_Stack_With_Custom_Capacity) {
    ASSERT_NO_THROW(TStack<int> s(10));
}

TEST(TStack, Throws_When_Create_Stack_With_Zero_Capacity) {
    ASSERT_THROW(TStack<int> s(0), std::invalid_argument);
}

TEST(TStack, New_Stack_Is_Empty) {
    TStack<int> s(5);
    EXPECT_TRUE(s.empty());
    EXPECT_FALSE(s.full());
}

TEST(TStack, Full_Reports_True_When_Stack_Is_Filled) {
    TStack<int> s(2);
    s.push(1);
    s.push(2);

    EXPECT_TRUE(s.full());
    EXPECT_FALSE(s.empty());
}

TEST(TStack, Can_Push_And_Get_Top_Element) {
    TStack<int> s(5);
    s.push(42);

    EXPECT_EQ(42, s.top());
    EXPECT_FALSE(s.empty());
}

TEST(TStack, Pop_Returns_Correct_Element_And_Reduces_Size) {
    TStack<int> s(5);
    s.push(10);
    s.push(20);

    EXPECT_EQ(20, s.pop());
    EXPECT_EQ(10, s.top());
}

TEST(TStack, LIFO_Order_Is_Maintained) {
    TStack<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_EQ(3, s.pop());
    EXPECT_EQ(2, s.pop());
    EXPECT_EQ(1, s.pop());
    EXPECT_TRUE(s.empty());
}

TEST(TStack, Throws_On_Overflow) {
    TStack<int> s(2);
    s.push(1);
    s.push(2);

    ASSERT_THROW(s.push(3), std::out_of_range);
}

TEST(TStack, Throws_On_Pop_From_Empty_Stack) {
    TStack<int> s(5);
    ASSERT_THROW(s.pop(), std::out_of_range);
}

TEST(TStack, Throws_On_Top_From_Empty_Stack) {
    TStack<int> s(5);
    ASSERT_THROW(s.top(), std::out_of_range);
}

TEST(TStack, Can_Create_Copied_Stack) {
    TStack<int> s1(5);
    s1.push(100);

    ASSERT_NO_THROW(TStack<int> s2(s1));
}

TEST(TStack, Copied_Stack_Has_Its_Own_Memory) {
    TStack<int> s1(5);
    s1.push(10);

    TStack<int> s2(s1);
    s2.pop();
    s2.push(20);

    EXPECT_EQ(10, s1.top());
    EXPECT_EQ(20, s2.top());
}

TEST(TStack, Can_Assign_Stack_To_Another) {
    TStack<int> s1(5);
    s1.push(77);

    TStack<int> s2(10);
    s2 = s1;

    EXPECT_EQ(77, s2.top());
}

TEST(TStack, Can_Assign_Stack_To_Itself) {
    TStack<int> s(5);
    s.push(55);

    ASSERT_NO_THROW(s = s);
    EXPECT_EQ(55, s.top());
}

TEST(TStack, Works_With_Different_Data_Types) {
    TStack<std::string> strStack(3);
    strStack.push("abc");
    strStack.push("def");

    EXPECT_EQ("def", strStack.pop());
    EXPECT_EQ("abc", strStack.top());
}