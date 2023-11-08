#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	// Проверка создания объекта
	ASSERT_NO_THROW(TPostfix p("a+b"));
}

TEST(TPostfix, can_create_postfix_with_valid_infix)
{
	// Проверка создания объекта из корректной инфиксной строки
	ASSERT_NO_THROW(TPostfix p("3 + 4 * (2 - 1)"));
}

TEST(TPostfix, can_create_postfix_with_parenthesis)
{
	// Проверка создания объекта из корректной инфиксной строки с наличием скобок
	ASSERT_NO_THROW(TPostfix p("(a+b)*c"));
}

TEST(TPostfix, throws_exception_for_invalid_infix)
{
	// Проверка выброса исключения при некорректной инфиксной строке с наличием скобок
	ASSERT_ANY_THROW(TPostfix p("3 + 4 * (2 - 1"));
}

TEST(TPostfix, can_convert_to_postfix)
{
	// Проверка правильности преобразования инфиксной строки в постфиксную
	TPostfix p("(a+b)*c");
	EXPECT_EQ(p.GetPostfix(), "ab+c*");
}

TEST(TPostfix, can_handle_multiple_operators)
{
	// Проверка обработки выражений с несколькими операторами
	TPostfix p("a+b-c*d/e");
	EXPECT_EQ(p.GetPostfix(), "ab+cd*e/-");
}

TEST(TPostfix, calculate_test)
{
	// Проверка вычисления значения постфиксного выражения с числами
	TPostfix p("5+2-3*4/6");
	EXPECT_EQ(p.Calculate(), 5);
}

TEST(TPostfix, throws_exception_for_division_by_zero)
{
	// Проверка выброса исключения при делении на ноль
	TPostfix p("1/0");
	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, can_handle_variables)
{
	// Проверка работы с переменными
	TPostfix p("x + y");
	p.SetVariable('x', 5);
	p.SetVariable('y', 3);
	EXPECT_EQ(p.Calculate(), 8);
}

TEST(TPostfix, throws_exception_for_undefined_variable)
{
	// Проверка выброса исключения при использовании неопределенной переменной
	TPostfix p("x + y");
	p.SetVariable('x', 5);
	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, can_set_multiple_variables)
{
	// Проверка установки нескольких переменных
	TPostfix p("x + y");
	map<char, double> variables = { {'x', 5}, {'y', 3} };
	p.SetVariables(variables);
	EXPECT_EQ(p.Calculate(), 8);
}

TEST(TPostfix, can_handle_variables_in_complex_expression)
{
	// Проверка обработки переменных в сложных выражениях
	TPostfix p("x + y * z");
	map<char, double> variables = { {'x', 2}, {'y', 3}, {'z', 4} };
	p.SetVariables(variables);
	EXPECT_EQ(p.Calculate(), 14);
}
TEST(TPostfix, can_handle_unary_minus)
{
	// Проверка обработки унарного минуса
	TPostfix postfix("-5");
	EXPECT_EQ(postfix.Calculate(), -5);
}

TEST(TPostfix, can_handle_unary_minus_with_variables)
{
	// Проверка обработки более сложных выражений с унарным минуса
	TPostfix postfix("-x + y");
	postfix.SetVariable('x', 3);
	postfix.SetVariable('y', 2);
	EXPECT_EQ(postfix.Calculate(), -1);
}

TEST(TPostfix, can_handle_exponentiation)
{
	// Проверка обработки возведения в степень
	TPostfix p("2^3");
	EXPECT_EQ(p.Calculate(), 8);
}

TEST(TPostfix, can_handle_negative_exponentiation)
{
	// Проверка обработки возведения в отрицательную степень
	TPostfix p("2^(-3)");
	EXPECT_NEAR(p.Calculate(), 0.125, 1e-6); // Ожидаем результат, близкий к 0.125
}

TEST(TPostfix, can_handle_complex_expression_and_zero_exponent)
{
	// Проверка обработки сложных выражений и возведения в нулевую степень
	TPostfix p("(2 + 3 * 4)^0");
	EXPECT_EQ(p.Calculate(), 1);
}