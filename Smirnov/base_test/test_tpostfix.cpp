#include "postfix.h"
#include <gtest.h>
#define _USE_MATH_DEFINES
TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_with_argument)
{
	string expression = "5 + 10 ^ 2";

	ASSERT_NO_THROW(TPostfix p(expression));
}

TEST(TPostfix, can_set_infix)
{
	string expression = "5 + 10 ^ 2";
	TPostfix p;

	ASSERT_NO_THROW(p.SetInfix(expression));
}

TEST(TPostfix, can_get_infix)
{
	string expression = "5 + 10 ^ 2";
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(expression, p.GetInfix());
}

TEST(TPostfix, throws_when_open_brackets_nq_closed_brackets)
{
	string expression = "( 5 * 2 ) )";
	TPostfix p(expression);

	ASSERT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, can_calculate_addition_with_integer_numbers)
{
	string expression = "5 + 10";
	double result = 5 + 10;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_addition_with_float_numbers)
{
	string expression = "5,5 + 2,3";
	double result = 5.5 + 2.3;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_DOUBLE_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_subtaction)
{
	string expression = "17 - 27";
	double result = 17 - 27;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_subtaction_with_float_numbers)
{
	string expression = "5,5 - 2,2";
	double result = 5.5 - 2.2;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_DOUBLE_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_unary_minus)
{
	string expression = "-10 + 3";
	double result = -10 + 3;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_multiplication)
{
	string expression = "3 * 10";
	double result = 3 * 10;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_integer_division)
{
	string expression = "10 / 5";
	double result = 10 / 5;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_float_division)
{
	string expression = "4,5 / 2";
	double result = 4.5 / 2;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_DOUBLE_EQ(result, p.Calculate());
}

TEST(TPostfix, throws_when_division_by_zero)
{
	string expression = "10 / 0";
	TPostfix p(expression);
	p.ToPostfix();

	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, can_calculate_sin)
{
	string expression = "2 * sin ( 30 )";
	double result = 2 * sin(30 * M_PI / 180);
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_cos)
{
	string expression = "4 * cos ( 60 )";
	double result = 4 * cos(60 * M_PI / 180);
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_sqrt)
{
	string expression = "sqrt ( 4 ) * 2";
	double result = 4;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_pow)
{
	string expression = "2 ^ 2";
	double result = 4;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(result, p.Calculate());
}

TEST(TPosfix, can_use_constants)
{
	string expression = "pi + e";
	double result = M_PI + M_E;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_DOUBLE_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_ln)
{
	string expression = "ln ( 3 ) - 1,5";
	double result = log(3) - 1.5;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_DOUBLE_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_lg)
{
	string expression = "lg ( 15 ) + 1,5";
	double result = log10(15) + 1.5;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_DOUBLE_EQ(result, p.Calculate());
}

TEST(TPostfix, can_calculate_expression_with_brackets)
{
	string expression = "( 10 + 20 ) / 15";
	double result = (10 + 20) / 15;
	TPostfix p(expression);
	p.ToPostfix();

	EXPECT_EQ(result, p.Calculate());
}

TEST(TPostfix, throws_when_negative_number_under_square_root)
{
	string expression = "sqrt ( -10 ) ";
	TPostfix p(expression);
	p.ToPostfix();

	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPosfix, throws_when_calculate_with_number_of_operands)
{
	string expression = "^ 10 - 15";
	TPostfix p(expression);
	p.ToPostfix();

	ASSERT_ANY_THROW(p.Calculate());
}


