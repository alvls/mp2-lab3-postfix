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
//
//void TPostfix::split()
//{
//	unsigned int openBraackets = 0;
//	char* ch = &infix[0];
//	string digit = "", variable = "";
//	while (*ch != '\0')
//	{
//		while (*ch == ' ')
//			ch++;
//		if (isDigit(*ch))
//		{
//			digit += *ch;
//			ch++;
//			continue;
//		}
//		else if (isVariable(*ch))
//		{
//			variable += *ch;
//			ch++;
//			continue;
//		}
//
//		if (variable != "")
//			lexems.push_back(Lexem(variable, isFunction(variable) ? Lexem::Type::FUNCTION : Lexem::Type::VARIABLE));
//		else if (digit != "")
//			lexems.push_back(Lexem(digit, Lexem::Type::DIGIT));
//		digit = ""; variable = "";
//
//		switch (*ch)
//		{
//		case'+':case'-':case'*':case'/':case'^':
//			lexems.push_back(Lexem(to_string(*ch), Lexem::Type::OPERATOR));
//			ch++;
//			break;
//		case'(':
//			lexems.push_back(Lexem(to_string(*ch), Lexem::Type::L_BRACKET));
//			ch++; openBraackets++;
//			break;
//		case')':
//			lexems.push_back(Lexem(to_string(*ch), Lexem::Type::R_BRACKET));
//			ch++; openBraackets++;
//			break;
//		default:
//			ch++;
//			break;
//		}
//	}
//	if (openBraackets % 2 != 0)
//		throw invalid_argument("invalid expression");
//}
//
//void TPostfix::toPostfix()
//{
//	unsigned int id = 0, stackSize = countOperators(infix) * 2, sz = lexems.size(); // max value of operators and brackets
//	TStack<Lexem> stack(stackSize);
//	vector<Lexem> tmp;
//	while (id < sz)
//	{
//		switch (lexems[id].type)
//		{
//		case Lexem::Type::L_BRACKET:
//			stack.push(lexems[id]);
//			id++;
//			break;
//		case Lexem::Type::DIGIT: case Lexem::Type::VARIABLE:
//			tmp.push_back(lexems[id]);
//			id++;
//			break;
//		case Lexem::Type::OPERATOR: case Lexem::Type::FUNCTION:
//			if (stack.top == 0 || priority[lexems[id].data] > priority[stack.getTop().data])
//			{
//				stack.push(lexems[id]);
//				id++;
//				break;
//			}
//			else 
//			{
//				while (stack.top > 0 && priority[lexems[id].data] <= priority[stack.getTop().data])
//					tmp.push_back(stack.pop());
//				stack.push(lexems[id]);
//				id++;
//				break;
//			}
//		case Lexem::Type::R_BRACKET:
//			while (stack.getTop().type != Lexem::Type::L_BRACKET)
//				tmp.push_back(stack.pop());
//			stack.pop();
//			break;
//		}
//		id++;
//	}
//	while (stack.top > 0)
//		tmp.push_back(stack.pop());
//	for (auto& t : tmp)
//	{
//		if (t.type == Lexem::Type::DIGIT || t.type == Lexem::Type::VARIABLE)
//			postfix += " ";
//		postfix += t.data;
//	}
//}
//
//double TPostfix::calculate()
//{
//	unsigned int id = 0;
//	double degree = 0, foot = 0, x = 0;
//	TStack<string> stack(countOperators(postfix) + 1); // max value of operands
//	for (auto& l : lexems)
//	{
//		if(l.type == Lexem::Type::DIGIT)
//		{
//			stack.push(l.data);
//			continue;
//		}
//		switch (l.data[0])
//		{
//		case'+':
//			stack.push(to_string(stod(stack.pop()) + stod(stack.pop())));
//			break;
//		case'-':
//			if(stack.size == 1)
//				stack.push(to_string(-1 * stod(stack.pop())));
//			else
//				stack.push(to_string(-1 * stod(stack.pop()) + stod(stack.pop())));
//			break;
//		case'*':
//			stack.push(to_string(stod(stack.pop()) * stod(stack.pop())));
//			break;
//		case'/':
//			stack.push(to_string(1 / stod(stack.pop()) * stod(stack.pop())));
//			break;
//		case'^':
//			degree = stod(stack.pop()); foot = stod(stack.pop());
//			stack.push(to_string(pow(foot, degree)));
//			break;
//		case's':
//			stack.push(to_string(sin(stod(stack.pop()))));
//			break;
//		case'c':
//			stack.push(to_string(cos(stod(stack.pop()))));
//			break;
//		case'e':
//			stack.push(to_string(exp(stod(stack.pop()))));
//			break;
//		case't':
//			x = stod(stack.pop());
//			stack.push(to_string(sin(x)/cos(x)));
//			break;
//		}
//	}
//	return stod(stack.pMem[0]);
//}







void TPostfix::split()
{
	size_t len = infix.length();
	string elem = "";
	char cur;
	for (size_t i = 0; i < len; i++)
	{
		cur = infix[i];
		if (isalnum(cur))
			elem += cur;
		else
		{
			if (!(elem.empty()))
			{
				lexems.push_back(elem);
				elem = "";
			}
			auto& it = priority.find(&cur);
			if (isOperator(it->first))
				lexems.push_back(to_string(cur));
		}
	}
	if (!(elem.empty()))
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
		if (!(isOperator(l)))
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
			case '-':
				if ((isOperator(stack.getTop()) || stack.empty()) && stack.getTop() != ")")
					l = '~';
				goto def;
			def:default:
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
	while (!(stack.empty()))
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
	TStack<double> stack(operators + 1); // max value of operands
	auto& end = operands.end();
	auto& _end = unarOperations.end();
	for (auto& l : lexems)
	{
		if (operands.find(l) == end)
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