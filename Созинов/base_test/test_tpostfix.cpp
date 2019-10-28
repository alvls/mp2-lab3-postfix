#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

//create postfix
TEST(TPostfix, can_create_postfix_without_parameter)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_with_parameter)
{
	const string str = "(a - b) + c";
	
	ASSERT_NO_THROW(TPostfix post(str));
}

//can get infix and postfix
TEST(TPostfix, can_get_infix)
{
	const string str = "(a - b * c) + v";
	TPostfix tmp(str);

	EXPECT_EQ(str, tmp.GetInfix());
}

TEST(TPostfix, can_get_postfix)
{
	const string str = "a + b";

	TPostfix tmp(str);
	tmp.ToPostfix();
	EXPECT_EQ("a b + ", tmp.GetPostfix());
}

//can check symbol, operator, number
TEST(TPostfix, can_check_symbol)
{
	const string str = "(a - b * c) + v";

	TPostfix tmp(str);
	string c = tmp.GetInfix();
	
	EXPECT_EQ(true, tmp.CheckOnSymbol(c[1]));
	EXPECT_EQ(false, tmp.CheckOnSymbol(c[0]));
}

TEST(TPostfix, can_check_operator)
{
	const string str = "(a - b * c) + v";

	TPostfix tmp(str);
	string c = tmp.GetInfix();

	EXPECT_EQ(false, tmp.CheckOnOperator(c[1]));
	EXPECT_EQ(true, tmp.CheckOnOperator(c[3]));
}

TEST(TPostfix, can_check_number)
{
	const string str = "(5.5 - 3 * 12) + 10";

	TPostfix tmp(str);
	string c = tmp.GetInfix();

	EXPECT_EQ(false, tmp.CheckOnNumber(c[4]));
	EXPECT_EQ(true, tmp.CheckOnNumber(c[2]));
}

//delete space
TEST(TPostfix, can_delete_space)
{
	const string str = "(a - v) + c";
    TPostfix post(str);
	post.DelSpace();
	
	EXPECT_EQ(post.GetInfix(), "(a-v)+c");
}

TEST(TPostfix, correct_job_if_in_infix_0_space)
{
	const string str = "(a-v)+c";
	TPostfix post(str);
	post.DelSpace();
	
	EXPECT_EQ(post.GetInfix(), "(a-v)+c");
}

//balance parentheses
TEST(TPostfix, can_check_balance_parentheses)
{
	const string str = "(a - v) + c";
	TPostfix post(str);
	
	ASSERT_NO_THROW(post.BalanceParentheses());	
}

TEST(TPostfix, true_when_balance_parentheses)
{
	const string str = "a + (b - c * (d - g))";
	TPostfix post(str);

	EXPECT_EQ(true, post.BalanceParentheses());
}

TEST(TPostfix, false_when_unbalance_parentheses)
{
	const string str = "a + (b - c * ((d - g))";
	TPostfix post(str);

	EXPECT_EQ(false, post.BalanceParentheses());
}

TEST(TPostfix, false_when_first_parentheses_open)
{
	const string str = "a + b - )a * c + d) ";
	TPostfix post(str);

	EXPECT_EQ(false, post.BalanceParentheses());
}

TEST(TPostfix, false_when_last_parentheses_close)
{
	const string str = "a + b - (a * c + d( ";
	TPostfix post(str);

	EXPECT_EQ(false, post.BalanceParentheses());
}

//check correct input
TEST(TPostfix, can_check_correct)
{
	const string str = "a + b - (a * c + d) ";
	TPostfix post(str);

	ASSERT_NO_THROW(post.CheckOnCorrect());
}

TEST(TPostfix, mistake_when_first_symbol_is_operator_multi_or_div)
{
	const string res = "First symbol is operator";
	const string str = "* a + b";
	TPostfix post(str);

	EXPECT_EQ(res, post.CheckOnCorrect());
}

TEST(TPostfix, no_mistake_when_first_symbol_is_operator_add_or_sub)
{
	const string res = "All good";
	const string str = "- a + b";
	TPostfix post(str);

	EXPECT_EQ(res, post.CheckOnCorrect());
}

TEST(TPostfix, mistake_when_last_symbol_is_operator)
{
	const string res = "Last symbol is operator";
	const string str = "a + b *";
	TPostfix post(str);

	EXPECT_EQ(res, post.CheckOnCorrect());
}

TEST(TPostfix, mistake_when_unbalance_parentheses)
{
	const string res = "Unbalance parentheses";
	const string str = "a + (b + c))";
	TPostfix post(str);

	EXPECT_EQ(res, post.CheckOnCorrect());
}

TEST(TPostfix, mistake_when_operator_before_close_parentheses)
{
	const string res = "Operator before close parentheses";
	const string str = "a + (b + c +)";
	TPostfix post(str);

	EXPECT_EQ(res, post.CheckOnCorrect());
}

TEST(TPostfix, mistake_when_operator_multi_or_div_after_open_parentheses)
{
	const string res = "Operator after open parentheses";
	const string str = "a + (* b + c)";
	TPostfix post(str);

	EXPECT_EQ(res, post.CheckOnCorrect());
}

TEST(TPostfix, no_mistake_when_operator_add_or_sub_after_open_parentheses)
{
	const string res = "All good";
	const string str = "a + (+ b + c)";
	TPostfix post(str);

	EXPECT_EQ(res, post.CheckOnCorrect());
}

TEST(TPostfix, mistake_when_operand_before_open_parentheses)
{
	const string res = "Operand before open parentheses";
	const string str = "a + b (b + c)";
	TPostfix post(str);

	EXPECT_EQ(res, post.CheckOnCorrect());
}

TEST(TPostfix, mistake_when_operand_after_close_parentheses)
{
	const string res = "Operand after close parentheses";
	const string str = "a + (b + c)g";
	TPostfix post(str);

	EXPECT_EQ(res, post.CheckOnCorrect());
}

TEST(TPostfix, mistake_when_two_operators_in_a_row)
{
	const string res = "Two operators in a row";
	const string str = "a + (b ++ c)";
	TPostfix post(str);

	EXPECT_EQ(res, post.CheckOnCorrect());
}

//Correct translate in postfix

TEST(ToPostfix, can_translate_in_postfix)
{
	const string inf = "a + b";
	TPostfix post(inf);

	ASSERT_NO_THROW(post.ToPostfix());
}

TEST(TPostfix, correct_translate)
{
	const string inf = "a + b";
	TPostfix post(inf);


	EXPECT_EQ("a b + ", post.ToPostfix());
}

TEST(TPostfix, correct_translate_when_parentheses)
{
	const string inf = "1+2*(3-2)-4";
	TPostfix post(inf);


	EXPECT_EQ("1 2 3 2 - * + 4 - ", post.ToPostfix());
}

TEST(TPostfix, correct_translate_when_first_symbol_operator)
{
	const string inf = "-1-2";
	TPostfix post(inf);


	EXPECT_EQ("0 1 - 2 - ", post.ToPostfix());
}

TEST(TPostfix, correct_calculate)
{
	const string inf = "1+2*(3-2)-4";
	TPostfix post(inf);
	post.ToPostfix();
	
	EXPECT_EQ(-1, post.Calculate());
}

TEST(TPostfix, throw_when_div_0)
{
	const string inf = "1/0";
	TPostfix post(inf);
	post.ToPostfix();

	ASSERT_ANY_THROW(post.Calculate());
}