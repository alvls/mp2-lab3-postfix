#include "postfix.h"
#include <gtest.h>


TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, can_translate_simple_expression) {
    TPostfix p("a + b"); 
    string result = p.ToPostfix();
    ASSERT_EQ(result, "a b + ");
}
TEST(TPostfix, can_translate_expression_with_priorities) {
    TPostfix p("a + b * c");
    string result = p.ToPostfix();
    ASSERT_EQ(result, "a b c * + ");
}
TEST(TPostfix, can_translate_expression_with_brackets) {
    TPostfix p("a*(b+c)");
    string result = p.ToPostfix();
    ASSERT_EQ(result, "a b c + * ");
}
TEST(TPostfix, can_translate_expression_with_functions) {
    TPostfix p("sin(a)");
    string result = p.ToPostfix();
    ASSERT_EQ(result, "a sin ");
}
TEST(TPostfix, can_calculate_simple_expression) {
    TPostfix p("a + b");
    p.SetVariable('a', 5.0);
    p.SetVariable('b', 10.0);
    p.ToPostfix();
    ASSERT_DOUBLE_EQ(p.Calculate(), 15.0);
}
TEST(TPostfix, can_calculate_with_priorities) {
    TPostfix p("2 + 3 * 4");
    p.ToPostfix();
    ASSERT_DOUBLE_EQ(p.Calculate(), 14.0);
}
TEST(TPostfix, can_calculate_with_functions) {
    TPostfix p("sqrt(16) + cos(0)");
    p.ToPostfix();
    ASSERT_DOUBLE_EQ(p.Calculate(), 5.0);
}
TEST(TPostfix, can_calculate_with_floats) {
    setlocale(LC_ALL, "Russian");
    TPostfix p("2,5 + 1,5");
    p.ToPostfix();
    ASSERT_DOUBLE_EQ(p.Calculate(), 4.0);
}
TEST(TPostfix, throws_when_variable_is_not_set) {
    TPostfix p("x + 1");
    p.ToPostfix();
    ASSERT_ANY_THROW(p.Calculate());
}
TEST(TPostfix, can_translate_complex_expression) {
    TPostfix p("(a + b) * (c - d)");
    ASSERT_EQ(p.ToPostfix(), "a b + c d - * ");
}
TEST(TPostfix, can_translate_number_and_var) {
    TPostfix p("12 + a");
    ASSERT_EQ(p.ToPostfix(), "12 a + ");
}
TEST(TPostfix, can_calculate_with_variables) {
    TPostfix p("a + b * c");
    p.SetVariable('a', 2.0);
    p.SetVariable('b', 3.0);
    p.SetVariable('c', 4.0);
    p.ToPostfix();

    ASSERT_DOUBLE_EQ(p.Calculate(), 14.0);
}

TEST(TPostfix, can_calculate_with_brackets) {
    TPostfix p("(a + b) * c");
    p.SetVariable('a', 2.0);
    p.SetVariable('b', 3.0);
    p.SetVariable('c', 4.0);
    p.ToPostfix();

    ASSERT_DOUBLE_EQ(p.Calculate(), 20.0);
}
TEST(TPostfix, can_calculate_subtraction_and_division) {
    TPostfix p("10 - 4 / 2");
    p.ToPostfix();

    ASSERT_DOUBLE_EQ(p.Calculate(), 8.0);
}