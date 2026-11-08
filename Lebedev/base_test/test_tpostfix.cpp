#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_from_expression)
{
  ASSERT_NO_THROW(TPostfix p("a+b*c"));
}

TEST(TPostfix, can_get_infix)
{
  TPostfix p("a+b*c");

  EXPECT_EQ("a+b*c", p.GetInfix());
}

TEST(TPostfix, can_convert_simple_expression)
{
  TPostfix p("a+b");

  EXPECT_EQ("a b +", p.GetPostfix());
}

TEST(TPostfix, spaces_are_ignored)
{
  TPostfix p("  a   +  b ");

  EXPECT_EQ("a b +", p.GetPostfix());
}

TEST(TPostfix, multiplication_has_higher_priority)
{
  TPostfix p("a+b*c");

  EXPECT_EQ("a b c * +", p.GetPostfix());
}

TEST(TPostfix, brackets_change_order)
{
  TPostfix p("(a+b)*c");

  EXPECT_EQ("a b + c *", p.GetPostfix());
}

TEST(TPostfix, operations_with_equal_priority_are_left_associative)
{
  TPostfix p("a-b+c");

  EXPECT_EQ("a b - c +", p.GetPostfix());
}

TEST(TPostfix, power_is_right_associative)
{
  TPostfix p("a^b^c");

  EXPECT_EQ("a b c ^ ^", p.GetPostfix());
}

TEST(TPostfix, can_convert_unary_minus)
{
  TPostfix p("-a+b");

  EXPECT_EQ("a ~ b +", p.GetPostfix());
}

TEST(TPostfix, can_convert_function)
{
  TPostfix p("sin(a)+b");

  EXPECT_EQ("a sin b +", p.GetPostfix());
}

TEST(TPostfix, can_convert_complex_expression)
{
  TPostfix p("(a+b*c)*(c/d-e)");

  EXPECT_EQ("a b c * + c d / e - *", p.GetPostfix());
}

TEST(TPostfix, can_convert_expression_with_nested_brackets)
{
  TPostfix p("((a+b)*(c-d))/e");

  EXPECT_EQ("a b + c d - * e /", p.GetPostfix());
}

TEST(TPostfix, can_get_operands)
{
  TPostfix p("a+b*c");
  vector<string> expected = { "a", "b", "c" };

  EXPECT_EQ(expected, p.GetOperands());
}

TEST(TPostfix, operands_are_not_repeated)
{
  TPostfix p("a+b*a-b");
  vector<string> expected = { "a", "b" };

  EXPECT_EQ(expected, p.GetOperands());
}

TEST(TPostfix, numbers_are_not_operands)
{
  TPostfix p("2*x+5");
  vector<string> expected = { "x" };

  EXPECT_EQ(expected, p.GetOperands());
}

TEST(TPostfix, function_names_are_not_operands)
{
  TPostfix p("sqrt(x)+sin(y)");
  vector<string> expected = { "x", "y" };

  EXPECT_EQ(expected, p.GetOperands());
}

TEST(TPostfix, expression_with_numbers_only_has_no_operands)
{
  TPostfix p("1+2");

  EXPECT_TRUE(p.GetOperands().empty());
}

TEST(TPostfix, can_use_multiletter_variables)
{
  TPostfix p("speed*time");
  vector<string> expected = { "speed", "time" };

  EXPECT_EQ("speed time *", p.GetPostfix());
  EXPECT_EQ(expected, p.GetOperands());
}

TEST(TPostfix, can_use_variables_with_digits_and_underscore)
{
  TPostfix p("x1+my_var2");
  vector<string> expected = { "x1", "my_var2" };

  EXPECT_EQ(expected, p.GetOperands());
}

TEST(TPostfix, can_calculate_multiletter_variables)
{
  TPostfix p("speed*time");
  p.SetValue("speed", 60);
  p.SetValue("time", 2.5);

  EXPECT_DOUBLE_EQ(150, p.Calculate());
}

TEST(TPostfix, can_calculate_integer_numbers)
{
  TPostfix p("1+2");

  EXPECT_DOUBLE_EQ(3, p.Calculate());
}

TEST(TPostfix, can_calculate_multidigit_numbers)
{
  TPostfix p("125+375");

  EXPECT_DOUBLE_EQ(500, p.Calculate());
}

TEST(TPostfix, can_calculate_real_numbers)
{
  TPostfix p("1.5*2+0.25");

  EXPECT_DOUBLE_EQ(3.25, p.Calculate());
}

TEST(TPostfix, can_calculate_numbers_starting_or_ending_with_dot)
{
  TPostfix p(".5+5.");

  EXPECT_DOUBLE_EQ(5.5, p.Calculate());
}

TEST(TPostfix, can_calculate_expression_with_variables)
{
  TPostfix p("a+b*c");
  p.SetValue("a", 1);
  p.SetValue("b", 2);
  p.SetValue("c", 3);

  EXPECT_DOUBLE_EQ(7, p.Calculate());
}

TEST(TPostfix, can_calculate_with_map_of_values)
{
  TPostfix p("a-b");
  map<string, double> vals = { { "a", 10 }, { "b", 4 } };

  EXPECT_DOUBLE_EQ(6, p.Calculate(vals));
}

TEST(TPostfix, can_set_values_with_map)
{
  TPostfix p("a/b");
  map<string, double> vals = { { "a", 9 }, { "b", 2 } };
  p.SetValues(vals);

  EXPECT_DOUBLE_EQ(4.5, p.Calculate());
}

TEST(TPostfix, can_calculate_same_expression_with_different_values)
{
  TPostfix p("a*a");
  p.SetValue("a", 3);
  double res1 = p.Calculate();
  p.SetValue("a", 5);
  double res2 = p.Calculate();

  EXPECT_DOUBLE_EQ(9, res1);
  EXPECT_DOUBLE_EQ(25, res2);
}

TEST(TPostfix, calculate_respects_priority)
{
  TPostfix p("2+3*4");

  EXPECT_DOUBLE_EQ(14, p.Calculate());
}

TEST(TPostfix, calculate_respects_brackets)
{
  TPostfix p("(2+3)*4");

  EXPECT_DOUBLE_EQ(20, p.Calculate());
}

TEST(TPostfix, can_calculate_subtraction_and_division_from_left_to_right)
{
  TPostfix p1("10-4-3");
  TPostfix p2("16/4/2");

  EXPECT_DOUBLE_EQ(3, p1.Calculate());
  EXPECT_DOUBLE_EQ(2, p2.Calculate());
}

TEST(TPostfix, can_calculate_division_with_fraction)
{
  TPostfix p("7/2");

  EXPECT_DOUBLE_EQ(3.5, p.Calculate());
}

TEST(TPostfix, can_calculate_power)
{
  TPostfix p("2^10");

  EXPECT_DOUBLE_EQ(1024, p.Calculate());
}

TEST(TPostfix, can_calculate_power_from_right_to_left)
{
  TPostfix p("2^3^2");

  EXPECT_DOUBLE_EQ(512, p.Calculate());
}

TEST(TPostfix, can_calculate_unary_minus)
{
  TPostfix p1("-5+3");
  TPostfix p2("2*-3");
  TPostfix p3("-(2+3)");

  EXPECT_DOUBLE_EQ(-2, p1.Calculate());
  EXPECT_DOUBLE_EQ(-6, p2.Calculate());
  EXPECT_DOUBLE_EQ(-5, p3.Calculate());
}

TEST(TPostfix, unary_minus_has_lower_priority_than_power)
{
  TPostfix p("-2^2");

  EXPECT_DOUBLE_EQ(-4, p.Calculate());
}

TEST(TPostfix, can_calculate_double_unary_minus)
{
  TPostfix p("--3");

  EXPECT_DOUBLE_EQ(3, p.Calculate());
}

TEST(TPostfix, can_calculate_functions)
{
  TPostfix p1("sin(0)");
  TPostfix p2("cos(0)");
  TPostfix p3("sqrt(16)");
  TPostfix p4("abs(-3)");

  EXPECT_DOUBLE_EQ(0, p1.Calculate());
  EXPECT_DOUBLE_EQ(1, p2.Calculate());
  EXPECT_DOUBLE_EQ(4, p3.Calculate());
  EXPECT_DOUBLE_EQ(3, p4.Calculate());
}

TEST(TPostfix, can_calculate_nested_functions)
{
  TPostfix p("sqrt(abs(-16))");

  EXPECT_DOUBLE_EQ(4, p.Calculate());
}

TEST(TPostfix, can_calculate_function_of_expression)
{
  TPostfix p("sqrt(a*a+b*b)");
  p.SetValue("a", 3);
  p.SetValue("b", 4);

  EXPECT_DOUBLE_EQ(5, p.Calculate());
}

TEST(TPostfix, can_calculate_complex_expression)
{
  TPostfix p("(a+b*c)*(c/d-e)");
  map<string, double> vals = { { "a", 1 }, { "b", 2 }, { "c", 3 }, { "d", 1.5 }, { "e", 1 } };

  EXPECT_DOUBLE_EQ(7, p.Calculate(vals));
}

TEST(TPostfix, throws_when_set_value_of_unknown_operand)
{
  TPostfix p("a+b");

  ASSERT_ANY_THROW(p.SetValue("c", 1));
}

TEST(TPostfix, throws_when_calculate_without_values)
{
  TPostfix p("a+b");
  p.SetValue("a", 1);

  ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, throws_when_divide_by_zero)
{
  TPostfix p("a/(b-2)");
  p.SetValue("a", 1);
  p.SetValue("b", 2);

  ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, throws_when_sqrt_of_negative_number)
{
  TPostfix p("sqrt(-4)");

  ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, throws_when_expression_is_empty)
{
  ASSERT_ANY_THROW(TPostfix p(""));
  ASSERT_ANY_THROW(TPostfix p("   "));
}

TEST(TPostfix, throws_when_expression_has_unknown_symbol)
{
  ASSERT_ANY_THROW(TPostfix p("a&b"));
  ASSERT_ANY_THROW(TPostfix p("a+b=c"));
}

TEST(TPostfix, throws_when_number_is_wrong)
{
  ASSERT_ANY_THROW(TPostfix p("1.2.3+a"));
  ASSERT_ANY_THROW(TPostfix p(".+a"));
}

TEST(TPostfix, throws_when_operation_has_no_operand)
{
  ASSERT_ANY_THROW(TPostfix p("a+"));
  ASSERT_ANY_THROW(TPostfix p("*a"));
  ASSERT_ANY_THROW(TPostfix p("a+*b"));
}

TEST(TPostfix, throws_when_operands_without_operation)
{
  ASSERT_ANY_THROW(TPostfix p("a b"));
  ASSERT_ANY_THROW(TPostfix p("2a"));
  ASSERT_ANY_THROW(TPostfix p("a(b)"));
  ASSERT_ANY_THROW(TPostfix p("(a)(b)"));
}

TEST(TPostfix, throws_when_bracket_is_not_closed)
{
  ASSERT_ANY_THROW(TPostfix p("(a+b"));
  ASSERT_ANY_THROW(TPostfix p("((a+b)*c"));
}

TEST(TPostfix, throws_when_extra_closing_bracket)
{
  ASSERT_ANY_THROW(TPostfix p("a+b)"));
  ASSERT_ANY_THROW(TPostfix p(")a+b("));
}

TEST(TPostfix, throws_when_brackets_are_empty)
{
  ASSERT_ANY_THROW(TPostfix p("()"));
  ASSERT_ANY_THROW(TPostfix p("a+()"));
}

TEST(TPostfix, throws_when_function_without_brackets)
{
  ASSERT_ANY_THROW(TPostfix p("sin a"));
  ASSERT_ANY_THROW(TPostfix p("sqrt"));
  ASSERT_ANY_THROW(TPostfix p("sin()"));
}
