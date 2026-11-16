#include "postfix.h"
#include <gtest.h>
#include <stdexcept>
TEST(TPostfix, can_translate_simple_addition)
{
    TPostfix p("2 + 3");
    EXPECT_EQ("2 3 + ", p.ToPostfix());
}
TEST(TPostfix, can_translate_expression_with_priorities)
{
    TPostfix p("2 + 3 * 4");
    EXPECT_EQ("2 3 4 * + ", p.ToPostfix());
}
TEST(TPostfix, can_translate_expression_with_brackets)
{
    TPostfix p("(2 + 3) * 4");
    EXPECT_EQ("2 3 + 4 * ", p.ToPostfix());
}
TEST(TPostfix, can_translate_expression_with_power)
{
    TPostfix p("2 ^ 3 ^ 2"); // 2^(3^2) = 2^9
    EXPECT_EQ("2 3 2 ^ ^ ", p.ToPostfix());
}
TEST(TPostfix, can_translate_expression_with_variables)
{
    TPostfix p("a + b * c");
    EXPECT_EQ("a b c * + ", p.ToPostfix());
}
TEST(TPostfix, can_calculate_simple_addition)
{
    TPostfix p("2 + 3");
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(5.0, p.Calculate());
}
TEST(TPostfix, can_calculate_with_priorities)
{
    TPostfix p("2 + 3 * 4");
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(14.0, p.Calculate());
}
TEST(TPostfix, can_calculate_with_brackets)
{
    TPostfix p("(2 + 3) * 4");
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(20.0, p.Calculate());
}
TEST(TPostfix, can_calculate_with_float_numbers)
{
    TPostfix p("1.5 + 2.5");
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(4.0, p.Calculate());
}
TEST(TPostfix, can_calculate_subtraction_and_division)
{
    TPostfix p("10 - 4 / 2");
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(8.0, p.Calculate());
}
TEST(TPostfix, can_calculate_with_variables)
{
    TPostfix p("a + b * c");
    p.SetVariable('a', 5);
    p.SetVariable('b', 10);
    p.SetVariable('c', 2);
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(25.0, p.Calculate());
}
TEST(TPostfix, throws_if_variable_is_not_set)
{
    TPostfix p("x + 5");
    p.ToPostfix();
    ASSERT_ANY_THROW(p.Calculate());
}
TEST(TPostfix, throws_on_division_by_zero)
{
    TPostfix p("5 / 0");
    p.ToPostfix();
    ASSERT_ANY_THROW(p.Calculate());
}
TEST(TPostfix, throws_on_invalid_expression_missing_operand)
{
    TPostfix p("5 +");
    p.ToPostfix();
    ASSERT_ANY_THROW(p.Calculate());
}
// --- Тесты на работу с переменными (SetVariable) ---
TEST(TPostfix, can_calculate_with_multiple_new_variables)
{
    TPostfix p("x + y * z");
    p.SetVariable('x', 10);
    p.SetVariable('y', 5);
    p.SetVariable('z', 2);
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(20.0, p.Calculate());
}
TEST(TPostfix, can_overwrite_variable_value)
{
    TPostfix p("a + b");
    p.SetVariable('a', 1);
    p.SetVariable('b', 2);
    p.SetVariable('a', 10);
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(12.0, p.Calculate());
}
TEST(TPostfix, is_case_sensitive_for_variables)
{
    TPostfix p("A + a");
    p.SetVariable('A', 100);
    p.SetVariable('a', 5);
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(105.0, p.Calculate());
}
TEST(TPostfix, does_not_fail_with_unused_variables)
{
    TPostfix p("a + b");
    p.SetVariable('a', 5);
    p.SetVariable('b', 10);
    p.SetVariable('c', 15);
    p.SetVariable('D', 20);
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(15.0, p.Calculate());
}
TEST(TPostfix, throws_if_one_of_variables_is_not_set)
{
    TPostfix p("a + b + c");
    p.SetVariable('a', 5);
    p.SetVariable('b', 10);
    p.ToPostfix();
    ASSERT_ANY_THROW(p.Calculate());
}
TEST(TPostfix, can_calculate_complex_expression_with_new_variables)
{
    TPostfix p("(a - 2) * (b + 3) / c");
    p.SetVariable('a', 10);
    p.SetVariable('b', 7);
    p.SetVariable('c', 5);
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(16.0, p.Calculate());
}