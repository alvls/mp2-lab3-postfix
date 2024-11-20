#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>


// ExpessionError

TEST(ExpressionError, can_create_error_with_message_and_position) {
    ASSERT_NO_THROW(ExpressionError("Error message", 5));
}

TEST(ExpressionError, can_get_message) {
    ExpressionError error("Test message", 5);
    ASSERT_STREQ(error.what(), "Test message");
}

TEST(ExpressionError, can_get_position) {
    ExpressionError error("Test message", 5);
    ASSERT_EQ(error.getPosition(), 5);
}

// MissingOperandValueError

TEST(MissingOperandValueError, can_create_error_with_message) {
    ASSERT_NO_THROW(MissingOperandValueError("Error message"));
}

TEST(MissingOperandValueError, can_get_message) {
    MissingOperandValueError error("a");
    ASSERT_STREQ(error.what(), "Missing value for operand: a");
}

// ExpressionValidator

TEST(ExpressionValidator, can_validate_expression_with_valid_characters) {
    ASSERT_NO_THROW(ExpressionValidator::Validate("a + 3 * (sin(x) + 5.5)"));
}

TEST(ExpressionValidator, throws_on_invalid_character) {
    ASSERT_THROW(ExpressionValidator::Validate("2 + 3 & 5"), ExpressionError);
}

TEST(ExpressionValidator, can_detect_unmatched_closing_parenthesis) {
    ASSERT_THROW(ExpressionValidator::Validate("2 + 3 * (5 + 6))"), ExpressionError);
}

TEST(ExpressionValidator, can_detect_unmatched_opening_parenthesis) {
    ASSERT_THROW(ExpressionValidator::Validate("((2 + 3) * 5 + 6"), ExpressionError);
}

// Parser 

TEST(Parser, can_parse_simple_expression) {
    vector<string> expected = { "2", "+", "3" };
    ASSERT_EQ(Parser::Parse("2 + 3"), expected);
}

TEST(Parser, can_parse_expression_with_functions) {
    vector<string> expected = { "sin", "(", "x", ")", "+", "cos", "(", "y", ")" };
    ASSERT_EQ(Parser::Parse("sin(x) + cos(y)"), expected);
}

TEST(Parser, can_handle_unary_minus) {
    vector<string> expected = { "_", "2", "+", "_", "3" };
    ASSERT_EQ(Parser::Parse("-2 + -3"), expected);
}

TEST(Parser, can_handle_factorials) {
    vector<string> expected = { "5", "!" };
    ASSERT_EQ(Parser::Parse("5!"), expected);
}

// InfixToPostfixConverter

TEST(InfixToPostfixConverter, can_convert_simple_expression) {
    map<string, double> operands;
    ASSERT_EQ(InfixToPostfixConverter::Convert("2 + 3", operands), "2 3 + ");
}

TEST(InfixToPostfixConverter, can_convert_expression_with_functions) {
    map<string, double> operands;
    ASSERT_EQ(InfixToPostfixConverter::Convert("sin(x) + cos(y)", operands), "x sin y cos + ");
}

TEST(InfixToPostfixConverter, can_convert_expression_with_unary_minus) {
    map<string, double> operands;
    ASSERT_EQ(InfixToPostfixConverter::Convert("-2 + 3", operands), "2 _ 3 + ");
}

TEST(InfixToPostfixConverter, can_convert_expression_with_factorial) {
    map<string, double> operands;
    ASSERT_EQ(InfixToPostfixConverter::Convert("5!", operands), "5 ! ");
}

// PostfixCalculator

TEST(PostfixCalculator, can_calculate_simple_expression) {
    map<string, double> operands;
    operands["x"] = 5;
    ASSERT_EQ(PostfixCalculator::Calculate("2 3 + ", operands), 5);
}

TEST(PostfixCalculator, can_calculate_expression_with_functions) {
    map<string, double> operands;
    const double PI = 3.14159265358979323846;
    operands["x"] = PI / 2;
    ASSERT_NEAR(PostfixCalculator::Calculate("x sin ", operands), 1.0, 1e-9);
}

TEST(PostfixCalculator, can_calculate_expression_with_unary_minus) {
    map<string, double> operands;
    ASSERT_EQ(PostfixCalculator::Calculate("2 _ 3 + ", operands), 1);
}

TEST(PostfixCalculator, can_calculate_expression_with_factorial) {
    map<string, double> operands;
    ASSERT_EQ(PostfixCalculator::Calculate("5 ! ", operands), 120);
}

TEST(PostfixCalculator, throw_on_division_by_zero) {
    map<string, double> operands;
    ASSERT_THROW(PostfixCalculator::Calculate("2 0 / ", operands), std::runtime_error);
}

TEST(PostfixCalculator, throw_on_factorial_of_negative_number) {
    map<string, double> operands;
    ASSERT_THROW(PostfixCalculator::Calculate("5 _ ! ", operands), std::runtime_error);
}

TEST(PostfixCalculator, throw_on_factorial_of_non_integer_number) {
    map<string, double> operands;
    ASSERT_THROW(PostfixCalculator::Calculate("5.5 ! ", operands), std::runtime_error);
}

// TArithmeticExpression

TEST(TArithmeticExpression, can_create_with_valid_expression) {
    ASSERT_NO_THROW(TArithmeticExpression expr("2 + 3"));
}

TEST(TArithmeticExpression, throw_on_invalid_expression) {
    ASSERT_THROW(TArithmeticExpression expr("2 + 3 &"), ExpressionError);
}

TEST(TArithmeticExpression, can_get_infix) {
    TArithmeticExpression expr("2 + 3");
    ASSERT_EQ(expr.GetInfix(), "2 + 3");
}

TEST(TArithmeticExpression, can_get_postfix) {
    TArithmeticExpression expr("2 + 3");
    ASSERT_EQ(expr.GetPostfix(), "2 3 + ");
}

TEST(TArithmeticExpression, can_calculate_expression) {
    TArithmeticExpression expr("2 + 3");
    map<string, double> values;
    ASSERT_EQ(expr.Calculate(values), 5);
}

TEST(TArithmeticExpression, can_calculate_expression_with_variables) {
    TArithmeticExpression expr("2 + y");
    map<string, double> values = { {"y", 3} };
    ASSERT_EQ(expr.Calculate(values), 5);
}

TEST(TArithmeticExpression, cant_calculate_with_missing_operand_value) {
    TArithmeticExpression expr("x + y");
    map<string, double> values = { {"x", 2} };
    ASSERT_THROW(expr.Calculate(values), MissingOperandValueError);
}

TEST(TArithmeticExpression, can_calculate_expression_with_all_operand_values) {
    TArithmeticExpression expr("x + y");
    map<string, double> values = { {"x", 2}, {"y", 3} };
    ASSERT_EQ(expr.Calculate(values), 5);
}

TEST(TArithmeticExpression, can_get_operands_from_expression_with_variables) {
    TArithmeticExpression expr("-x + sqrt(y) * z^2 + y * cos(x) - z!");
    vector<string> expectedOperands = { "x", "y", "z" };
    ASSERT_EQ(expr.GetOperands(), expectedOperands);
}

TEST(TArithmeticExpression, ignores_numeric_constants_in_operands) {
    TArithmeticExpression expr("2 + x + y + 0.5");
    vector<string> expectedOperands = { "x", "y" }; 
    ASSERT_EQ(expr.GetOperands(), expectedOperands);
}

TEST(TArithmeticExpression, returns_empty_if_only_numeric_constants) {
    TArithmeticExpression expr("3 + 4.2 * 7");
    vector<string> expectedOperands = {}; 
    ASSERT_EQ(expr.GetOperands(), expectedOperands);
}



