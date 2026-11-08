#include "postfix.h"
#include <gtest.h>

#include <iostream>
#include <sstream>
#include <stdexcept>

class CinRedirect
{
    std::streambuf* old;
public:
    explicit CinRedirect(std::istream& in) { old = std::cin.rdbuf(in.rdbuf()); }
    ~CinRedirect() { std::cin.rdbuf(old); }
};

TEST(TPostfix, can_create_with_default_constructor)
{
    ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, default_constructor_sets_default_expression)
{
    TPostfix p;
    EXPECT_EQ("a + b", p.GetInfix());
    EXPECT_TRUE(p.GetPostfix().empty());
}

TEST(TPostfix, can_create_with_expression)
{
    ASSERT_NO_THROW(TPostfix p("2+3"));
    TPostfix p("2+3");
    EXPECT_EQ("2+3", p.GetInfix());
}

TEST(TPostfix, set_infix_changes_expression)
{
    TPostfix p("2+3");
    p.SetInfix("4*5");
    EXPECT_EQ("4*5", p.GetInfix());
    EXPECT_TRUE(p.GetPostfix().empty());
}

TEST(TPostfix, to_postfix_simple_sum)
{
    TPostfix p("2+3");
    EXPECT_EQ("2 3 +", p.ToPostfix());
}

TEST(TPostfix, to_postfix_respects_precedence)
{
    TPostfix p("2+3*4");
    EXPECT_EQ("2 3 4 * +", p.ToPostfix());
}

TEST(TPostfix, to_postfix_respects_precedence2)
{
    TPostfix p("2*3+4");
    EXPECT_EQ("2 3 * 4 +", p.ToPostfix());
}

TEST(TPostfix, to_postfix_handles_parens)
{
    TPostfix p("(2+3)*4");
    EXPECT_EQ("2 3 + 4 *", p.ToPostfix());
}

TEST(TPostfix, to_postfix_handles_nested_parens)
{
    TPostfix p("2 + 3 * (4 - 1)");
    EXPECT_EQ("2 3 4 1 - * +", p.ToPostfix());
}

TEST(TPostfix, to_postfix_handles_variables)
{
    TPostfix p("a + b");
    EXPECT_EQ("a b +", p.ToPostfix());
}

TEST(TPostfix, to_postfix_handles_variables_and_numbers)
{
    TPostfix p("a * b + 1");
    EXPECT_EQ("a b * 1 +", p.ToPostfix());
}

TEST(TPostfix, to_postfix_handles_decimal_numbers)
{
    TPostfix p("3.5 + 1.5");
    EXPECT_EQ("3.5 1.5 +", p.ToPostfix());
}

TEST(TPostfix, to_postfix_handles_multi_digit_numbers)
{
    TPostfix p("10 + 20");
    EXPECT_EQ("10 20 +", p.ToPostfix());
}

TEST(TPostfix, to_postfix_is_idempotent)
{
    TPostfix p("2+3");
    EXPECT_EQ("2 3 +", p.ToPostfix());
    EXPECT_EQ("2 3 +", p.ToPostfix());
}

TEST(TPostfix, to_postfix_throws_on_missing_close_paren)
{
    TPostfix p("(2+3");
    ASSERT_THROW(p.ToPostfix(), std::runtime_error);
}

TEST(TPostfix, to_postfix_throws_on_missing_open_paren)
{
    TPostfix p("2+3)");
    ASSERT_THROW(p.ToPostfix(), std::runtime_error);
}

TEST(TPostfix, to_postfix_throws_on_unknown_character)
{
    TPostfix p("2+3@");
    ASSERT_THROW(p.ToPostfix(), std::runtime_error);
}

TEST(TPostfix, calculate_simple_sum)
{
    TPostfix p("2+3");
    EXPECT_DOUBLE_EQ(5.0, p.Calculate());
}

TEST(TPostfix, calculate_calls_to_postfix_if_not_called)
{
    TPostfix p("2+3");
    ASSERT_TRUE(p.GetPostfix().empty());
    EXPECT_DOUBLE_EQ(5.0, p.Calculate());
    EXPECT_FALSE(p.GetPostfix().empty());
}

TEST(TPostfix, calculate_complex_expression)
{
    TPostfix p("2 + 3 * (4 - 1)");
    EXPECT_DOUBLE_EQ(11.0, p.Calculate());
}

TEST(TPostfix, calculate_negative_result)
{
    TPostfix p("2 - 5");
    EXPECT_DOUBLE_EQ(-3.0, p.Calculate());
}

TEST(TPostfix, calculate_division_exact)
{
    TPostfix p("10 / 2");
    EXPECT_DOUBLE_EQ(5.0, p.Calculate());
}

TEST(TPostfix, calculate_division_inexact)
{
    TPostfix p("1 / 3");
    EXPECT_NEAR(1.0 / 3.0, p.Calculate(), 1e-12);
}

TEST(TPostfix, calculate_throws_on_division_by_zero)
{
    TPostfix p("1/0");
    ASSERT_THROW(p.Calculate(), std::domain_error);
}

TEST(TPostfix, calculate_throws_on_division_by_zero_in_expression)
{
    TPostfix p("(2-2)/(3-3)");
    ASSERT_THROW(p.Calculate(), std::domain_error);
}

TEST(TPostfix, calculate_after_explicit_to_postfix)
{
    TPostfix p("7 + 8");
    p.ToPostfix();
    EXPECT_DOUBLE_EQ(15.0, p.Calculate());
}

TEST(TPostfix, calculate_reads_variables_from_cin)
{
    std::istringstream input("3\n5\n");
    CinRedirect guard(input);

    TPostfix p("a + b");
    EXPECT_DOUBLE_EQ(8.0, p.Calculate());
}

TEST(TPostfix, calculate_variables_and_numbers)
{
    std::istringstream input("2\n4\n");
    CinRedirect guard(input);

    TPostfix p("a * b + 1");
    EXPECT_DOUBLE_EQ(9.0, p.Calculate());
}

TEST(TPostfix, calculate_same_variable_asked_once)
{
    std::istringstream input("3\n");
    CinRedirect guard(input);

    TPostfix p("a + a * 2");
    EXPECT_DOUBLE_EQ(9.0, p.Calculate());
}

TEST(TPostfix, calculate_default_expression)
{
    std::istringstream input("10\n20\n");
    CinRedirect guard(input);

    TPostfix p;
    EXPECT_DOUBLE_EQ(30.0, p.Calculate());
}

TEST(TPostfix, calculate_throws_when_variable_missing)
{
    std::istringstream input("");
    CinRedirect guard(input);

    TPostfix p("a + b");
    ASSERT_THROW(p.Calculate(), std::runtime_error);
}