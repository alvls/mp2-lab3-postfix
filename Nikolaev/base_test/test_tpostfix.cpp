#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix) {
	ASSERT_NO_THROW(TPostfix p("0"));
}

TEST(TPostfix, can_create_postfix_with_correct_brackets) {
	ASSERT_NO_THROW(TPostfix p("((-1)-(1))"));
}

TEST(TPostfix, throws_when_create_postfix_with_incorrect_placement_of_brackets) {
	ASSERT_ANY_THROW(TPostfix p("0)+(1"));
}

TEST(TPostfix, can_get_infix) {
	TPostfix p("a1 + a2 + 3");
	vector<string>infix{ "a1", "+", "a2", "+", "3" };
	EXPECT_EQ(infix, p.GetInfix());
}

TEST(TPostfix, can_get_string_infix) {
	TPostfix p("a1 + a2 + 3");
	EXPECT_EQ("a1 + a2 + 3 ", p.GetStringInfix());
}

TEST(TPostfix, can_get_postfix) {
	TPostfix p("a1 + a2 + 3");
	vector<string>postfix{ "a1", "a2", "+", "3", "+" };
	EXPECT_EQ(postfix, p.GetPostfix());
}

TEST(TPostfix, can_get_string_postfix_with_operations) {
	TPostfix p("(a + b * c / e - d)");
	EXPECT_EQ("a b c * e / + d - ", p.GetStringPostfix());
}

TEST(TPostfix, can_get_postfix_with_expressions_with_brackets) {
	TPostfix p("a*(b-c)");
	vector<string>postfix{ "a", "b", "c", "-", "*" };
	EXPECT_EQ(postfix, p.GetPostfix());
}

TEST(TPostfix, can_get_string_postfix_with_expressions_with_brackets) {
	TPostfix p("a*(b-c)");
	EXPECT_EQ("a b c - * ", p.GetStringPostfix());
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_plus) {
	TPostfix p("a + b + 3.9");
	EXPECT_EQ(1 + 7 + 3.9, p.Calculate(false, vector<double>{1, 7}));
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_minus) {
	TPostfix p("a - b - 3.9");
	EXPECT_EQ(-7 - (-12) - 3.9, p.Calculate(false, vector<double>{-7, -12}));
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_multiplication) {
	TPostfix p("a * b * 3.9");
	EXPECT_EQ(double(10) / 39 * (-1) * 3.9, p.Calculate(false, vector<double>{(10.0 / 39), -1}));
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_division) {
	TPostfix p("a / b / 1.5");
	EXPECT_EQ(10.0 / 1 / 1.5, p.Calculate(false, vector<double>{10.0, 1}));
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_sin) {
	TPostfix p("sin(3.14159)");
	EXPECT_EQ(sin(3.14159), p.Calculate(false));
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_sin) {
	TPostfix p("sin(a)");
	EXPECT_EQ(sin(1.57), p.Calculate(false, vector<double>{1.57}));
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_cos) {
	TPostfix p("cos(a)");
	EXPECT_EQ(cos(1.57), p.Calculate(false, vector<double>{1.57}));
}

TEST(TPostfix, can_calculate_arithmetic_expression_with_sqrt) {
	TPostfix p("sqrt(4)");
	EXPECT_EQ(sqrt(4), p.Calculate(false));
}

