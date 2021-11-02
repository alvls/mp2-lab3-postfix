#include "postfix.h"
#include <gtest.h>
#include "postfix.cpp"

TEST (TPostfix, can_create_postfix) {
  ASSERT_NO_THROW (TPostfix p);
}

TEST (TPostfix, can_get_infix) {
  TPostfix p("a + b");
  EXPECT_EQ ("a + b", p.get_infix());
}

TEST (TPostfix, can_get_postfix) {
  TPostfix p("a + b");
  EXPECT_EQ ("ab+", p.get_postfix());
}

TEST (TPostfix, can_set_infix) {
  TPostfix p;
  p.set_infix("a + b");
  EXPECT_EQ ("a + b", p.get_infix());
}

TEST (TPostfix, throws_when_creating_infix_with_wrong_number_of_quotes) {
	ASSERT_ANY_THROW (TPostfix p("((a+b)"));
}

TEST (TPostfix, calculate_returns_right_value) {
  TPostfix p("(((1+23)*1-22)+5)*2-7");
  std::vector<double> values;
  values.push_back(1);
  values.push_back(23);
  values.push_back(1);
  values.push_back(22);
  values.push_back(5);
  values.push_back(2);
  values.push_back(7);
  EXPECT_EQ (7, p.calculate(values));
}

TEST (TPostfix, operands_counter_returns_right_value) {
  TPostfix p("a + b - c");
  EXPECT_EQ (3, p.operands_counter());
}
