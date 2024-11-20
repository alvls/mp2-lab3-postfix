#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p("a+b+c"));
}

TEST(TPostfix, throws_exc_when_infix_is_empty)
{
	ASSERT_ANY_THROW(TPostfix p(""));
}

TEST(TPostfix, can_get_infix)
{
	string expr = "a+b+c";

	TPostfix pst(expr);

	EXPECT_EQ(pst.GetInfix(), expr);
}

TEST(TPostfix, can_get_postfix)
{
	string expr = "a+b+c";

	TPostfix pst(expr);

	vector<string> postf;
	postf.push_back("a");
	postf.push_back("b");
	postf.push_back("+");
	postf.push_back("c");
	postf.push_back("+");

	EXPECT_EQ(pst.GetPostfix(), postf);
}

TEST(TPostfix, can_get_operands)
{
	string expr = "a+b+cd";

	TPostfix pst(expr);

	vector<string> op;
	op.push_back("a");
	op.push_back("b");
	op.push_back("cd");

	EXPECT_EQ(pst.GetOperands(), op);
}

TEST(TPostfix, can_get_operands_enclosed_in_parentheses_correctly)
{
	string expr = "(a+b)+c";

	TPostfix pst(expr);

	vector<string> op;
	op.push_back("a");
	op.push_back("b");
	op.push_back("c");

	EXPECT_EQ(pst.GetOperands(), op);
}

TEST(TPostfix, can_get_operands_from_an_expression_with_many_parentheses)
{
	string expr = "((a+b)*c)+d";

	TPostfix pst(expr);

	vector<string> op;
	op.push_back("a");
	op.push_back("b");
	op.push_back("c");
	op.push_back("d");

	EXPECT_EQ(pst.GetOperands(), op);
}

TEST(TPostfix, identical_operands_are_not_duplicated)
{
	string expr = "(a+b+c+a+b+c)*a";

	TPostfix pst(expr);

	vector<string> op;
	op.push_back("a");
	op.push_back("b");
	op.push_back("c");

	EXPECT_EQ(pst.GetOperands(), op);
}

TEST(TPostfix, can_calculate_positive_values_correctly)
{
	string expr = "a+b";
	TPostfix pst(expr);

	map<string, double> val = { {"a",10.0}, {"b",5.0} };

	EXPECT_EQ(15.0, pst.Calculate(val));
}

TEST(TPostfix, can_calculate_positive_and_negative_values_correctly)
{
	string expr = "a+b";
	TPostfix pst(expr);

	map<string, double> val = { {"a",10.0}, {"b",-5.0} };

	EXPECT_EQ(5.0, pst.Calculate(val));
}

TEST(TPostfix, parentheses_change_the_order_of_calculation)
{
	string expr = "(a+b)*d";
	TPostfix pst(expr);

	map<string, double> val = { {"a",10.0}, {"b",5.0}, {"d",3.0}};

	EXPECT_EQ(45.0, pst.Calculate(val));
}

TEST(TPostfix, evaluates_an_expression_with_literal_constants_and_numbers)
{
	string expr = "a+b+3";
	TPostfix pst(expr);

	map<string, double> val = { {"a",10.0}, {"b",5.0},{"3",3.0}};

	EXPECT_EQ(18.0, pst.Calculate(val));
}

TEST(TPostfix, can_evaluate_expression_with_floats)
{
	string expr = "5.5 + a";
	TPostfix pst(expr);

	map<string, double> val = { {"5.5", 5.5},{"a", 4.5} };

	EXPECT_EQ(10, pst.Calculate(val));
}

TEST(TPostfix, evaluates_expressions_with_many_spaces)
{
	string expr = "a            -b+(   a+ b)    /  d";
	TPostfix pst(expr);

	map<string, double> val = { {"a",10.0}, {"b",5.0},{"d",3.0}};

	EXPECT_EQ(10.0, pst.Calculate(val));
}

TEST(TPostfix, throws_an_ecxeption_with_division_by_zero)
{
	string expr = "a/b";
	TPostfix pst(expr);

	map<string, double> val = { {"a",10.0}, {"b",0} };

	ASSERT_ANY_THROW(pst.Calculate(val));
}

TEST(TPostfix, multi_letter_parameters_supported)
{
	string expr = "1 + abc";
	TPostfix pst(expr);

	map<string, double> val = { {"abc", 10.0}, {"1", 1.0}};

	EXPECT_EQ(11.0, pst.Calculate(val));
}

TEST(TPostfix, can_convert_single_operand_to_postfix)
{
	string expr = "a";
	
	ASSERT_NO_THROW(TPostfix pst(expr));
}

TEST(TPostfix, can_calculate_an_single_operand_expression_as_far_as_possible)
{
	string expr = "a";
	TPostfix pst(expr);

	map<string, double> val = { {"a", 10.0} };

	EXPECT_EQ(10.0, pst.Calculate(val));
}

