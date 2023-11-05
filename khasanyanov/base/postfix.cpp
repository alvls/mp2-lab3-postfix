#include "postfix.h"


TPostfix::TPostfix() : infix("1+2-3*5") {}

TPostfix::TPostfix(string str) : infix(str) 
{ 
	operators = countOperators(infix);
	priority = { {"(", 1}, {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3},{"~", 4}, {"^", 5}, {"sin", 6}, {"cos", 6}, {"exp", 6}, {"tg", 6}};
	split(); toPostfix();
}

string TPostfix::getInfix() const { return infix; }

string TPostfix::getPostfix() const { return postfix; }

inline bool TPostfix::isOperator(const string s)
{
	auto& end = priority.end();
	return (priority.find(s) != end || s == ")");
}

unsigned int TPostfix::countOperators(string s)
{
	int res = 0;
	for (char& i : s)
		res += isOperator(to_string(i));
	return res;
}

void TPostfix::split()
{
	size_t len = infix.length();
	string elem = "";
	for (const char& cur : infix)
	{
		if (isalnum(cur))
			elem += cur;
		else
		{
			if (!elem.empty())
			{
				lexems.push_back(elem);
				elem = "";
			}
			if (isOperator(string{cur}))
				lexems.push_back(string{ cur });
		}
	}
	if (!elem.empty())
		lexems.push_back(elem);
}

void TPostfix::toPostfix()
{
	unsigned int id = 0, stackSize = (operators + 1) * 2, sz = lexems.size(); 
	TStack<string> stack(stackSize); // max value of operators and brackets
	vector<string> tmp;
	auto& end = priority.end();
	for (auto& l : lexems)
	{
		if (!isOperator(l))
		{
			operands.emplace(l, stod(l));
			tmp.push_back(l);
			postfix += (" " + l);
		}
		else
		{
			switch (l[0])
			{
			case'(':
				stack.push(l);
				break;
			case')':
				while (stack.getTop() != "(")
				{
					string t = stack.pop();
					tmp.push_back(t);
					postfix += t;
				}
				stack.pop();
				break;
			/*case '-':
				if ((isOperator(stack.getTop()) || stack.empty()) && stack.getTop() != ")")
					l = '~';*/
			default:
				if (stack.empty() || priority[l] > priority[stack.getTop()])
					stack.push(l);
				else
				{
					string t = stack.pop();
					tmp.push_back(t);
					t != "~" ? postfix += t : postfix += "-";
				}
				break;
			}
		}
	}
	while (!stack.empty())
	{
		string t = stack.pop();
		tmp.push_back(t);
		postfix += t;
	}
	lexems = tmp;
}



double TPostfix::calculate()
{
	double a, b;
	TStack<double> stack(60); // max value of operands
	auto& end = operands.end();
	auto& _end = unarOperations.end();
	for (auto& l : lexems)
	{
		if (operands.find(l) != end)
			stack.push(operands[l]);
		else
		{
			if (unarOperations.find(l) != _end)
			{
				a = stack.pop();
				stack.push(unarOperations[l](a));
			}
			else
			{
				b = stack.pop(), a = stack.pop();
				stack.push(binarOperations[l](a, b));
			}
		}
	}
	return stack.getTop();
}