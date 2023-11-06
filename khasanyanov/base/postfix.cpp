#include "postfix.h"


TPostfix::TPostfix() : infix("1+2-3*5") {}

TPostfix::TPostfix(string str) : infix(str) 
{ 
	operators = countOperators(infix);
	split(); toPostfix();
}

string TPostfix::getInfix() const { return infix; }

string TPostfix::getPostfix() const { return postfix; }

double factorial(size_t n) { return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n; }

map<string, double> TPostfix :: getOperands() const {return operands;}

map<string, unsigned int> TPostfix::priority = { 
	{"(", 1}, {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3},{"~", 4}, {"^", 5}, {"!", 5}, {"sin", 6}, {"cos", 6}, {"exp", 6}, {"tg", 6}};

map<string, function<double(double, double)> > TPostfix:: binaryOperations = {
	{"+", [](double a, double b) {return a + b; }},
	{"-", [](double a, double b) {return a - b; }},
	{"/", [](double a, double b) {return a / b; }},
	{"*", [](double a, double b) {return a * b; }},
	{"^", [](double a, double b) {return pow(a,b); }},
};

map<string, function<double(double)>> TPostfix :: unaryOperations = {
	{"~", [](double a) {return -a; }},
	{"!", [](double a) {return factorial(size_t(a)); }},
	{"sin", [](double a) {return sin(a); }},
	{"cos", [](double a) {return cos(a); }},
	{"exp", [](double a) {return exp(a); }},
	{"tg", [](double a) {return sin(a) / cos(a); }},
};

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
	string elem = "";
	for (const char& cur : infix)
	{
		if (isalnum(cur))
			elem += cur;
		else if(isOperator(string{ cur }))
		{
			if (!elem.empty())
			{
				lexems.push_back(elem);
				elem = "";
			}
			lexems.push_back(string{ cur });
		}
	}
	if (!elem.empty())
		lexems.push_back(elem);
}

void TPostfix::toPostfix()
{
	TStack<string> stack(lexems.size()); 
	vector<string> tmp;
	unsigned int  brackets = 0, i = 0;
	for (auto& l : lexems)
	{
		if (!isOperator(l))
		{
			try
			{
				operands.emplace(l, stod(l));
			}
			catch (...) {
				operands.emplace(l, 0);
			}
			tmp.push_back(l);
			postfix += (" " + l);
		}
		else
		{
			switch (l[0])
			{
			case'(':
				stack.push(l);
				brackets++;
				break;
			case')':
				brackets++;
				while (stack.getTop() != "(")
				{
					string t = stack.pop();
					tmp.push_back(t);
					postfix += (t == "~" ? "-" : t);
				}
				stack.pop();
				break;
			case '-':
				if (i == 0 || lexems[i-1] == "(")
					l = "~";
			default:
				while(!stack.empty() && priority[l] <= priority[stack.getTop()])
				{
					string t = stack.pop();
					tmp.push_back(t);
					postfix += (t == "~" ? "-" : t);
				}
				stack.push(l);
				break;
			}
			i++;
		}
	}
	if (brackets % 2 != 0)
		throw invalid_argument("syntax error");
	while (!stack.empty())
	{
		string t = stack.pop();
		tmp.push_back(t);
		postfix += (t == "~" ? "-" : t);
	}
	lexems = tmp;
}

double TPostfix::calculate(map<string, double> values)
{
	double a, b;
	TStack<double> stack(lexems.size()); 
	auto& end = values.end();
	auto& _end = unaryOperations.end();
	for (auto& l : lexems)
	{
		if (values.find(l) != end)
			stack.push(values[l]);
		else
		{
			if (unaryOperations.find(l) != _end)
			{
				a = stack.pop();
				stack.push(unaryOperations[l](a));
			}
			else
			{
				b = stack.pop(), a = stack.pop();
				stack.push(binaryOperations[l](a, b));
			}
		}
	}
	return stack.getTop();
}