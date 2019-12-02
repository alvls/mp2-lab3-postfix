#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>
#include <string>

TEST(TPostfix, can_create_postfix){
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TStack, can_create_copied_postfix){
	TPostfix p;
	ASSERT_NO_THROW(TPostfix p1(p));
}

TEST(TPostfix, can_get_infix){
	TPostfix p("a+b");
	EXPECT_EQ("a+b", p.GetInfix());
}


TEST(TPostfix, can_create_postfix_from_infix){
	TPostfix p("a+(b-c)*d-e+f");
	p.ToPostfix();
	EXPECT_EQ("a,b,c,-,d,*,+,e,-,f,+,", p.GetPostfix());
}

TEST(TPostfix, CheckInfix_return_true_when_infix_is_correct){
	TPostfix p("a+b");
	EXPECT_TRUE(p.CheckInfix());
}

TEST(TPostfix, CheckInfix_return_false_when_infix_is_invalid){
	TPostfix p("(a+-b");
	EXPECT_FALSE(p.CheckInfix());
}

TEST(TStack, throw_when_division_by_zero){
	TPostfix p("2+2/0");
	ASSERT_ANY_THROW(p.Calculate());
}


TEST(TPostfix, can_calculate_expression){
	TPostfix p("(1+2)-3/6*2");
	EXPECT_EQ(2, p.Calculate());
}