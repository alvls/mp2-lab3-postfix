#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

using namespace tabl;

TEST(TPostfix, can_create_postfix_obj)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_get_infix) {
	TPostfix p;
	ASSERT_NO_THROW(p.GetInfix());
}

TEST(TPostfix, can_create_postfix_form) {
	TPostfix p;
	ASSERT_NO_THROW(p.ToPostfix());
}

TEST(TPostfix, can_get_postfix) {
	TPostfix p;
	p.ToPostfix();
	ASSERT_NO_THROW(p.GetPostfix());
}

TEST(TPostfix, can_calculate_expression_with_abc) {
	TPostfix p("a+b+c");
	p.ToPostfix();
	ASSERT_NO_THROW(p.Calculate());
	//EXPECT_EQ(p.Calculate(), 60);
}

TEST(TPostfix, can_calculate_standard_expression) {
	TPostfix p("1+2+3+4*5-(6*7)/8");
	p.ToPostfix();
	ASSERT_NO_THROW(p.Calculate());
}

TEST(TPostfix, can_create_postfix_if_expression_is_written_with_or_without_spaces) {
	TPostfix p("1+ 2+3 + 4*5 -( 6* 7 )/ 8");
	ASSERT_NO_THROW(p.ToPostfix());
}

TEST(TPostfix, throw_when_expression_without_operands) {
	TPostfix p("+");
	ASSERT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, can_calculate_expression_with_letters_from_table_and_numbers) {
	TPostfix p("(a - 5) + b * 3");
	ASSERT_NO_THROW(p.Calculate());
}