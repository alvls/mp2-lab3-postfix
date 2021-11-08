#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p("a+b"));
}

TEST(TPostfix, correct_proverka_na_razlozhenie_1)
{
	TPostfix p;
	vector<string> v;
	v.push_back("t");
	v.push_back("r");
	//string s = "fdx";
	EXPECT_EQ(p.proverka_na_razlozhenie(v), true);
}
TEST(TPostfix, correct_proverka_na_razlozhenie_2)
{
	TPostfix p;
	vector<string> v;
	v.push_back("t");
	v.push_back("r");
	v.push_back("fdx");
	EXPECT_EQ(p.proverka_na_razlozhenie(v), false);
}

TEST(TPostfix, correct_make_postfix_1)
{
	TPostfix p("-a+b");
	string s = "a-b+";
	p.ToPostfix();
	EXPECT_EQ(p.GetPostfix(),s);
}
TEST(TPostfix, correct_make_postfix_2)
{
	TPostfix p("a/(c+d)");
	string s = "acd+/";
	p.ToPostfix();
	EXPECT_EQ(p.GetPostfix(), s);
}
TEST(TPostfix, correct_make_postfix_3)
{
	TPostfix p("(a+b)/(c+d)");
	string s = "ab+cd+/";
	p.ToPostfix();
	EXPECT_EQ(p.GetPostfix(), s);
}
TEST(TPostfix, correct_make_list_of_operands)
{
	TPostfix p("a*b/c");
	vector<string> o;
	//p.ToPostfix();
	o.push_back("a");
	o.push_back("b");
	o.push_back("c");
	o.push_back("*");
	o.push_back("/");
	vector<string> r;
	r.push_back("a");
	r.push_back("b");
	r.push_back("c");
	EXPECT_EQ(p.make_list_of_operands(o), r);
}
TEST(TPostfix, correct_make_prisvaivanie)
{
	TPostfix p("a*b/c");
	vector<string> o;
	//p.ToPostfix();
	o.push_back("a");
	o.push_back("b");
	o.push_back("c");
	o.push_back("*");
	o.push_back("/");
	vector <double> val;
	val.push_back(10.5);
	val.push_back(7);
	val.push_back(11);
	vector<string> r;
	r.push_back("10.500000");
	r.push_back("7.000000");
	r.push_back("11.000000");
	r.push_back("*");
	r.push_back("/");
	EXPECT_EQ(p.prisvaivanie(o, val), r);
}

TEST(TPostfix, correct_make_vstavka_string_1)
{
	TPostfix p;
	vector<string> v;
	v.push_back("10");
	v.push_back("5");
	v.push_back("*");
	string vstavka="50";
	vector<string> tmp;
	tmp.push_back(vstavka);
	EXPECT_EQ(p.vstavka(v, vstavka, 0, 3), tmp);
}
TEST(TPostfix, correct_make_vstavka_string_2)
{
	TPostfix p;
	vector<string> v;
	v.push_back("10");
	v.push_back("10");
	v.push_back("10");
	v.push_back("5");
	v.push_back("*");
	string vstavka = "50";
	vector<string> tmp;
	tmp.push_back("10");
	tmp.push_back("10");
	tmp.push_back(vstavka);
	EXPECT_EQ(p.vstavka(v, vstavka, 2, 3), tmp);
}