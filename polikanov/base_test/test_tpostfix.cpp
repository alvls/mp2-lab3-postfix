#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, canCreatePostfix) {
	ASSERT_NO_THROW(TPostfix p("0"));
}

TEST(TPostfix, canCreatePostfixOkBrackets) {
	ASSERT_NO_THROW(TPostfix p("(1 + 1) * ((8)) + (2*(-1))"));
}

TEST(TPostfix, cantCreatePostfixInvalidBrackets) {
	ASSERT_ANY_THROW(TPostfix p("1) + 23 ("));
}

TEST(TPostfix, canGetInfix) {
	TPostfix p("x1 + x2 + x3");
	vector<string>infix{ "x1", "+", "x2", "+", "x3" };
	EXPECT_EQ(infix, p.GetInfix());
}

TEST(TPostfix, canGetUnfixString) {
	TPostfix p("x1 + x2 + 3");
	EXPECT_EQ("x1 + x2 + 3 ", p.GetStringInfix());
}

TEST(TPostfix, canGetPostfix) {
	TPostfix p("x1 + x2 + 3");
	vector<string>postfix{ "x1", "x2", "+", "3", "+" };
	EXPECT_EQ(postfix, p.GetPostfix());
}

TEST(TPostfix, canGetStringPostfix) {
	TPostfix p("(a + b * c / e - d)");
	EXPECT_EQ("a b c * e / + d - ", p.GetStringPostfix());
}

TEST(TPostfix, canGetPostfixWithExpressions_) {
	TPostfix p("a*(b-c)");
	vector<string>postfix{ "a", "b", "c", "-", "*" };
	EXPECT_EQ(postfix, p.GetPostfix());
}

TEST(TPostfix, canCalculateArithmeticExpressionWithPlus) {
	TPostfix p("a + b + 3");
	EXPECT_EQ(1 + 2 + 3, p.Calculate(false, vector<double>{1, 2}));
}

TEST(TPostfix, canCalculateArithmeticExpressionWithMinus) {
	TPostfix p("a - b - 3");
	EXPECT_EQ(-1 - (-2) - 3, p.Calculate(false, vector<double>{-1, -2}));
}

TEST(TPostfix, canCalcArithmeticExpressionWithMult) {
	TPostfix p("a * b * 3");
	EXPECT_EQ(double(10) / 3 * (-1) * 3, p.Calculate(false, vector<double>{(10.0 / 3), -1}));
}

TEST(TPostfix, canCalcArithmeticExpressionWithDiv) {
	TPostfix p("a / b / 1.5");
	EXPECT_EQ(10.0 / 1 / 1.5, p.Calculate(false, vector<double>{10.0, 1}));
}

TEST(TPostfix, canCalcArithmeticExpressionWithSin) {
	TPostfix p("sin(a)");
	EXPECT_EQ(sin(3.14), p.Calculate(false, vector<double>{3.14}));
}

TEST(TPostfix, canCalcArithmeticExpressionWithCos) {
	TPostfix p("cos(a)");
	EXPECT_EQ(cos(1.57), p.Calculate(false, vector<double>{1.57}));
}

TEST(TPostfix, canCalcArithmeticExpressionWithSqrt) {
	TPostfix p("sqrt(36)");
	EXPECT_EQ(sqrt(36), p.Calculate(false));
}