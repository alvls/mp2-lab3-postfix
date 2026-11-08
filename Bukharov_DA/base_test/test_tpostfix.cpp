#include <gtest.h>
#include "postfix.h"

TEST(TPostfix, Can_Calculate_Simple_Addition) {
    TPostfix expr("2 + 3");
    EXPECT_EQ("2 3 +", expr.ToPostfix());
    EXPECT_DOUBLE_EQ(5.0, expr.Calculate({}));
}

TEST(TPostfix, Respects_Operator_Precedence) {
    TPostfix expr("2 + 2 * 2");
    EXPECT_EQ("2 2 2 * +", expr.ToPostfix());
    EXPECT_DOUBLE_EQ(6.0, expr.Calculate({}));
}

TEST(TPostfix, Supports_Floating_Point_Division) {
    TPostfix expr("5 / 2");
    EXPECT_EQ("5 2 /", expr.ToPostfix());
    EXPECT_DOUBLE_EQ(2.5, expr.Calculate({}));
}

TEST(TPostfix, Handles_Parentheses) {
    TPostfix expr("(2 + 2) * 2");
    EXPECT_EQ("2 2 + 2 *", expr.ToPostfix());
    EXPECT_DOUBLE_EQ(8.0, expr.Calculate({}));
}

TEST(TPostfix, Handles_Nested_Parentheses) {
    TPostfix expr("((3 + 2) * 2 - 4) / 3");
    EXPECT_DOUBLE_EQ(2.0, expr.Calculate({}));
}

TEST(TPostfix, Handles_Unary_Minus_At_Start) {
    TPostfix expr("-5 + 3");
    EXPECT_DOUBLE_EQ(-2.0, expr.Calculate({}));
}

TEST(TPostfix, Handles_Unary_Minus_Inside_Expression) {
    TPostfix expr("4 * -2");
    EXPECT_DOUBLE_EQ(-8.0, expr.Calculate({}));
}

TEST(TPostfix, Handles_Unary_Minus_With_Parentheses) {
    TPostfix expr("-(2 + 3) * 2");
    EXPECT_DOUBLE_EQ(-10.0, expr.Calculate({}));
}

TEST(TPostfix, Extracts_Variables_Correctly) {
    TPostfix expr("x + y * x - z");
    expr.tokenize();

    vector<string> vars = expr.GetVariables();
    ASSERT_EQ(3, vars.size());
    EXPECT_EQ("x", vars[0]);
    EXPECT_EQ("y", vars[1]);
    EXPECT_EQ("z", vars[2]);
}

TEST(TPostfix, Calculates_Expression_With_Variables) {
    TPostfix expr("a + b * 2");
    expr.ToPostfix();

    map<string, double> values = {{"a", 10.0}, {"b", 5.0}};
    EXPECT_DOUBLE_EQ(20.0, expr.Calculate(values));
}

TEST(TPostfix, Throws_When_Variable_Value_Is_Missing) {
    TPostfix expr("x + 1");
    expr.ToPostfix();

    map<string, double> emptyValues;
    EXPECT_THROW(expr.Calculate(emptyValues), std::runtime_error);
}

TEST(TPostfix, Check_Catches_Unbalanced_Open_Bracket) {
    TPostfix expr("(1 + 2");
    expr.tokenize();

    string msg;
    size_t pos;
    EXPECT_FALSE(expr.check(msg, pos));
    EXPECT_EQ(0, pos);
}

TEST(TPostfix, Check_Catches_Unbalanced_Close_Bracket) {
    TPostfix expr("1 + 2)");
    expr.tokenize();

    string msg;
    size_t pos;
    EXPECT_FALSE(expr.check(msg, pos));
    EXPECT_EQ(5, pos);
}

TEST(TPostfix, Check_Catches_Consecutive_Operators) {
    TPostfix expr("1 + * 2");
    expr.tokenize();

    string msg;
    size_t pos;
    EXPECT_FALSE(expr.check(msg, pos));
}

TEST(TPostfix, Throws_On_Division_By_Zero) {
    TPostfix expr("10 / 0");
    expr.ToPostfix();

    EXPECT_THROW(expr.Calculate({}), std::runtime_error);
}