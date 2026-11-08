#include "postfix.h"
#include <gtest.h>
#include <cmath>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

typedef std::map<std::string, double> Values;
typedef std::vector<std::string> Names;

// ---------------------------------------------------------------
// Creation
// ---------------------------------------------------------------

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, default_expression_is_a_plus_b)
{
  TPostfix p;

  EXPECT_EQ("a + b", p.GetInfix());
  EXPECT_EQ("a b +", p.GetPostfix());
}

TEST(TPostfix, can_create_postfix_from_string)
{
  ASSERT_NO_THROW(TPostfix p("x*(y+1)"));
}

TEST(TPostfix, infix_is_stored_exactly_as_entered)
{
  TPostfix p(" a +  b*c ");

  EXPECT_EQ(" a +  b*c ", p.GetInfix());
}

TEST(TPostfix, copy_has_same_expression)
{
  TPostfix p("u-v");
  TPostfix copy(p);

  EXPECT_EQ(p.GetInfix(), copy.GetInfix());
  EXPECT_EQ(p.GetPostfix(), copy.GetPostfix());
  EXPECT_EQ(p.GetVariables(), copy.GetVariables());
}

// ---------------------------------------------------------------
// Conversion to postfix form (parameterized)
// ---------------------------------------------------------------

struct ConversionCase
{
  const char* infix;
  const char* postfix;
};

std::ostream& operator<<(std::ostream& os, const ConversionCase& c)
{
  return os << "\"" << c.infix << "\" -> \"" << c.postfix << "\"";
}

class TPostfixConversion : public ::testing::TestWithParam<ConversionCase>
{
};

TEST_P(TPostfixConversion, builds_correct_postfix_form)
{
  TPostfix p(GetParam().infix);

  EXPECT_EQ(GetParam().postfix, p.GetPostfix());
}

const ConversionCase conversionCases[] = {
  { "a+b",               "a b +"                 },
  { "a-b-c",             "a b - c -"             },
  { "a/b*c",             "a b / c *"             },
  { "a+b*c",             "a b c * +"             },
  { "a*b+c",             "a b * c +"             },
  { "(a+b)*c",           "a b + c *"             },
  { "a*(b-c)/d",         "a b c - * d /"         },
  { "a+b*(c-d^e)/f",     "a b c d e ^ - * f / +" },
  { "a^b^c",             "a b c ^ ^"             },
  { "(a^b)^c",           "a b ^ c ^"             },
  { "a*b^c",             "a b c ^ *"             },
  { "((a))",             "a"                     },
  { "-a",                "a neg"                 },
  { "-a*b",              "a neg b *"             },
  { "a*-b",              "a b neg *"             },
  { "-a^2",              "a 2 ^ neg"             },
  { "a^-2",              "a 2 neg ^"             },
  { "--a",               "a neg neg"             },
  { "-(a-b)",            "a b - neg"             },
  { "+a-+b",             "a b -"                 },
  { "sin(x)",            "x sin"                 },
  { "sqrt(a*a+b*b)",     "a a * b b * + sqrt"    },
  { "ln(exp(x))",        "x exp ln"              },
  { "-sin(x)^2",         "x sin 2 ^ neg"         },
  { "abs(x-1)*tg(y)",    "x 1 - abs y tg *"      },
  { "2*(3+4)",           "2 3 4 + *"             },
  { " 12.5 *\tvalue_1 ", "12.5 value_1 *"        }
};

INSTANTIATE_TEST_CASE_P(Table, TPostfixConversion, ::testing::ValuesIn(conversionCases));

// ---------------------------------------------------------------
// Calculation of constant expressions (parameterized)
// ---------------------------------------------------------------

struct CalcCase
{
  const char* infix;
  double result;
};

std::ostream& operator<<(std::ostream& os, const CalcCase& c)
{
  return os << "\"" << c.infix << "\" = " << c.result;
}

class TPostfixCalculation : public ::testing::TestWithParam<CalcCase>
{
};

TEST_P(TPostfixCalculation, gives_correct_result)
{
  TPostfix p(GetParam().infix);

  EXPECT_NEAR(GetParam().result, p.Calculate(Values()), 1e-9);
}

const CalcCase calcCases[] = {
  { "100",            100  },
  { "2+3*4",          14   },
  { "(2+3)*4",        20   },
  { "10-2-3",         5    },
  { "20/4/5",         1    },
  { "7/2",            3.5  },
  { "1.5+2.25",       3.75 },
  { "0.1+0.2",        0.3  },
  { "2^10",           1024 },
  { "2^3^2",          512  },
  { "(2^3)^2",        64   },
  { "4^0.5",          2    },
  { "-2^2",           -4   },
  { "(-2)^2",         4    },
  { "(-2)^3",         -8   },
  { "2^-1",           0.5  },
  { "-3*-3",          9    },
  { "--7",            7    },
  { "+5-+2",          3    },
  { "2*(3+(4-1)*2)",  18   },
  { "abs(-7)",        7    },
  { "sqrt(81)",       9    },
  { "sqrt(abs(-16))", 4    },
  { "sin(0)+cos(0)",  1    },
  { "tg(0)",          0    },
  { "ln(1)",          0    },
  { "exp(0)*3",       3    },
  { "ln(exp(2.5))",   2.5  },
  { "-sqrt(4)^2",     -4   }
};

INSTANTIATE_TEST_CASE_P(Table, TPostfixCalculation, ::testing::ValuesIn(calcCases));

// ---------------------------------------------------------------
// Variables
// ---------------------------------------------------------------

TEST(TPostfix, variables_are_listed_in_order_of_first_appearance)
{
  TPostfix p("b*a+c-a");
  Names expected;
  expected.push_back("b");
  expected.push_back("a");
  expected.push_back("c");

  EXPECT_EQ(expected, p.GetVariables());
}

TEST(TPostfix, repeated_variable_is_listed_once)
{
  TPostfix p("x*x*x+x");

  ASSERT_EQ(1u, p.GetVariables().size());
  EXPECT_EQ("x", p.GetVariables()[0]);
}

TEST(TPostfix, numbers_and_function_names_are_not_variables)
{
  TPostfix p("sin(t)+2*cos(w)-3.5");
  Names expected;
  expected.push_back("t");
  expected.push_back("w");

  EXPECT_EQ(expected, p.GetVariables());
}

TEST(TPostfix, constant_expression_has_no_variables)
{
  TPostfix p("(1+2)*sqrt(9)");

  EXPECT_TRUE(p.GetVariables().empty());
}

TEST(TPostfix, variable_names_may_contain_digits_and_underscores)
{
  TPostfix p("x1+rate_2*x1");
  Names expected;
  expected.push_back("x1");
  expected.push_back("rate_2");

  EXPECT_EQ(expected, p.GetVariables());
  EXPECT_EQ("x1 rate_2 x1 * +", p.GetPostfix());
}

TEST(TPostfix, variable_names_are_case_sensitive)
{
  TPostfix p("a+A");

  EXPECT_EQ(2u, p.GetVariables().size());
  Values v;
  v["a"] = 1;
  v["A"] = 10;
  EXPECT_DOUBLE_EQ(11, p.Calculate(v));
}

TEST(TPostfix, name_that_only_starts_like_function_is_variable)
{
  TPostfix p("sinx+lnx");
  Names expected;
  expected.push_back("sinx");
  expected.push_back("lnx");

  EXPECT_EQ(expected, p.GetVariables());
}

// ---------------------------------------------------------------
// Calculation with values from map
// ---------------------------------------------------------------

TEST(TPostfix, can_calculate_with_variables)
{
  TPostfix p("a+b*c");
  Values v;
  v["a"] = 1;
  v["b"] = 2;
  v["c"] = 3;

  EXPECT_DOUBLE_EQ(7, p.Calculate(v));
}

TEST(TPostfix, can_calculate_with_long_names)
{
  TPostfix p("distance/time_total");
  Values v;
  v["distance"] = 150;
  v["time_total"] = 2.5;

  EXPECT_DOUBLE_EQ(60, p.Calculate(v));
}

TEST(TPostfix, same_expression_can_be_calculated_with_different_values)
{
  TPostfix p("k*k-1");
  Values v1, v2;
  v1["k"] = 4;
  v2["k"] = -3;

  EXPECT_DOUBLE_EQ(15, p.Calculate(v1));
  EXPECT_DOUBLE_EQ(8, p.Calculate(v2));
}

TEST(TPostfix, extra_values_are_ignored)
{
  TPostfix p("m+1");
  Values v;
  v["m"] = 2;
  v["unused"] = 1000;

  EXPECT_DOUBLE_EQ(3, p.Calculate(v));
}

TEST(TPostfix, can_calculate_complex_expression_with_variables)
{
  TPostfix p("(a+b*c)/(d-e)^2 - sqrt(f)");
  Values v;
  v["a"] = 2;
  v["b"] = 3;
  v["c"] = 6;
  v["d"] = 7;
  v["e"] = 5;
  v["f"] = 25;

  EXPECT_DOUBLE_EQ(0, p.Calculate(v));
}

TEST(TPostfix, unary_minus_works_with_negative_variable)
{
  TPostfix p("-n");
  Values v;
  v["n"] = -8;

  EXPECT_DOUBLE_EQ(8, p.Calculate(v));
}

TEST(TPostfix, calculate_does_not_change_expression)
{
  TPostfix p("q/2");
  Values v;
  v["q"] = 9;
  p.Calculate(v);

  EXPECT_EQ("q/2", p.GetInfix());
  EXPECT_EQ("q 2 /", p.GetPostfix());
}

TEST(TPostfix, throws_out_of_range_when_value_is_missing)
{
  TPostfix p("a+b");
  Values v;
  v["a"] = 1;

  ASSERT_THROW(p.Calculate(v), std::out_of_range);
}

// ---------------------------------------------------------------
// Calculation errors
// ---------------------------------------------------------------

TEST(TPostfix, throws_domain_error_on_division_by_zero)
{
  TPostfix p("1/(a-a)");
  Values v;
  v["a"] = 3;

  ASSERT_THROW(p.Calculate(v), std::domain_error);
}

TEST(TPostfix, throws_domain_error_on_sqrt_of_negative)
{
  TPostfix p("sqrt(0-4)");

  ASSERT_THROW(p.Calculate(Values()), std::domain_error);
}

TEST(TPostfix, throws_domain_error_on_ln_of_not_positive)
{
  TPostfix p1("ln(0)");
  TPostfix p2("ln(-1)");

  ASSERT_THROW(p1.Calculate(Values()), std::domain_error);
  ASSERT_THROW(p2.Calculate(Values()), std::domain_error);
}

TEST(TPostfix, throws_domain_error_on_zero_in_negative_power)
{
  TPostfix p("0^-1");

  ASSERT_THROW(p.Calculate(Values()), std::domain_error);
}

TEST(TPostfix, throws_domain_error_on_fractional_power_of_negative)
{
  TPostfix p("(-8)^(1/3)");

  ASSERT_THROW(p.Calculate(Values()), std::domain_error);
}

TEST(TPostfix, throws_domain_error_on_tg_of_half_pi)
{
  TPostfix p("tg(x)");
  Values v;
  v["x"] = std::acos(-1.0) / 2;

  ASSERT_THROW(p.Calculate(v), std::domain_error);
}

TEST(TPostfix, zero_divided_by_number_is_zero)
{
  TPostfix p("0/5");

  EXPECT_DOUBLE_EQ(0, p.Calculate(Values()));
}

// ---------------------------------------------------------------
// Syntax errors
// ---------------------------------------------------------------

// Returns position of the syntax error or -1 if there is no error
static int ErrorPosition(const std::string& expression)
{
  try
  {
    TPostfix p(expression);
  }
  catch (const TSyntaxError& e)
  {
    return static_cast<int>(e.GetPosition());
  }
  return -1;
}

TEST(TPostfix, syntax_error_is_invalid_argument)
{
  ASSERT_THROW(TPostfix p("a+"), std::invalid_argument);
}

TEST(TPostfix, throws_on_empty_expression)
{
  ASSERT_THROW(TPostfix p(""), TSyntaxError);
  ASSERT_THROW(TPostfix p(" \t "), TSyntaxError);
}

TEST(TPostfix, throws_on_unknown_symbols)
{
  ASSERT_THROW(TPostfix p("a&b"), TSyntaxError);
  ASSERT_THROW(TPostfix p("a=b"), TSyntaxError);
  ASSERT_THROW(TPostfix p("a%2"), TSyntaxError);
  ASSERT_THROW(TPostfix p("[a]"), TSyntaxError);
}

TEST(TPostfix, throws_on_badly_written_numbers)
{
  ASSERT_THROW(TPostfix p("1.2.3"), TSyntaxError);
  ASSERT_THROW(TPostfix p("5.+1"), TSyntaxError);
  ASSERT_THROW(TPostfix p(".5"), TSyntaxError);
  ASSERT_THROW(TPostfix p("2,5"), TSyntaxError);
}

TEST(TPostfix, throws_when_operand_is_missing)
{
  ASSERT_THROW(TPostfix p("a+"), TSyntaxError);
  ASSERT_THROW(TPostfix p("*a"), TSyntaxError);
  ASSERT_THROW(TPostfix p("a*/b"), TSyntaxError);
  ASSERT_THROW(TPostfix p("a^"), TSyntaxError);
  ASSERT_THROW(TPostfix p("-"), TSyntaxError);
}

TEST(TPostfix, throws_when_operation_is_missing)
{
  ASSERT_THROW(TPostfix p("a b"), TSyntaxError);
  ASSERT_THROW(TPostfix p("2x"), TSyntaxError);
  ASSERT_THROW(TPostfix p("3 4"), TSyntaxError);
  ASSERT_THROW(TPostfix p("a(b)"), TSyntaxError);
  ASSERT_THROW(TPostfix p("(a)(b)"), TSyntaxError);
  ASSERT_THROW(TPostfix p("(a)b"), TSyntaxError);
}

TEST(TPostfix, throws_on_unbalanced_brackets)
{
  ASSERT_THROW(TPostfix p("(a+b"), TSyntaxError);
  ASSERT_THROW(TPostfix p("a+b)"), TSyntaxError);
  ASSERT_THROW(TPostfix p("((a)"), TSyntaxError);
  ASSERT_THROW(TPostfix p(")a("), TSyntaxError);
}

TEST(TPostfix, throws_on_empty_brackets)
{
  ASSERT_THROW(TPostfix p("()"), TSyntaxError);
  ASSERT_THROW(TPostfix p("a*()"), TSyntaxError);
  ASSERT_THROW(TPostfix p("(a+)"), TSyntaxError);
}

TEST(TPostfix, throws_on_wrong_function_call)
{
  ASSERT_THROW(TPostfix p("sin x"), TSyntaxError);
  ASSERT_THROW(TPostfix p("sqrt"), TSyntaxError);
  ASSERT_THROW(TPostfix p("cos()"), TSyntaxError);
  ASSERT_THROW(TPostfix p("ln-x"), TSyntaxError);
  ASSERT_THROW(TPostfix p("x sin(y)"), TSyntaxError);
}

TEST(TPostfix, reports_position_of_unknown_symbol)
{
  EXPECT_EQ(6, ErrorPosition("12 + 3$"));
}

TEST(TPostfix, reports_position_of_missing_operand)
{
  EXPECT_EQ(4, ErrorPosition("a + * b"));
}

TEST(TPostfix, reports_position_of_missing_operation)
{
  EXPECT_EQ(2, ErrorPosition("a b"));
}

TEST(TPostfix, reports_end_of_expression_for_unclosed_bracket)
{
  EXPECT_EQ(4, ErrorPosition("(a+b"));
}

TEST(TPostfix, reports_position_of_extra_closing_bracket)
{
  EXPECT_EQ(3, ErrorPosition("a+b)"));
}

TEST(TPostfix, no_error_position_for_correct_expression)
{
  EXPECT_EQ(-1, ErrorPosition("(a+b)*c"));
}

// ---------------------------------------------------------------
// Changing the expression
// ---------------------------------------------------------------

TEST(TPostfix, set_infix_replaces_expression)
{
  TPostfix p("a+b");

  p.SetInfix("p*q");

  EXPECT_EQ("p*q", p.GetInfix());
  EXPECT_EQ("p q *", p.GetPostfix());
  Names expected;
  expected.push_back("p");
  expected.push_back("q");
  EXPECT_EQ(expected, p.GetVariables());
}

TEST(TPostfix, wrong_set_infix_keeps_previous_expression)
{
  TPostfix p("a-b");

  ASSERT_THROW(p.SetInfix("a-"), TSyntaxError);
  EXPECT_EQ("a-b", p.GetInfix());
  EXPECT_EQ("a b -", p.GetPostfix());
}

// ---------------------------------------------------------------
// Big expressions (the stack has to grow)
// ---------------------------------------------------------------

TEST(TPostfix, can_process_deeply_nested_brackets)
{
  const int depth = 200;
  std::string expr = std::string(depth, '(') + "z" + std::string(depth, ')') + "+1";
  TPostfix p(expr);
  Values v;
  v["z"] = 41;

  EXPECT_EQ("z 1 +", p.GetPostfix());
  EXPECT_DOUBLE_EQ(42, p.Calculate(v));
}

TEST(TPostfix, can_calculate_long_sum)
{
  std::string expr = "1";
  for (int i = 0; i < 499; i++)
    expr += "+1";
  TPostfix p(expr);

  EXPECT_DOUBLE_EQ(500, p.Calculate(Values()));
}

TEST(TPostfix, can_calculate_long_right_associative_chain)
{
  std::string expr = "1";
  for (int i = 0; i < 300; i++)
    expr += "^1";
  TPostfix p(expr);

  EXPECT_DOUBLE_EQ(1, p.Calculate(Values()));
}
