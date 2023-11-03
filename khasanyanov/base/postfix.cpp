#include "postfix.h"


TPostfix::TPostfix() : infix("1+2-3*5") {}

TPostfix::TPostfix(string str) : infix(str) 
{ 
	priority = { {"(", 1}, {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3}, {"^", 4}, {"sin", 5}, {"cos", 5}, {"exp", 5}, {"tg", 5} };
	split(); 
	toPostfix(); 
}

string TPostfix::getInfix() const { return infix; }

string TPostfix::getPostfix() const { return postfix; }

//inline short TPostfix::priority(const char ch)
//{
//	switch (ch)
//	{
//	case '(': return 1;
//	case '+': case '-': return 2;
//	case '*': case '/': return 3;
//	case '^': return 4;
//	default: return 0;
//	}
//}

inline bool TPostfix::isDigit(const char ch)
{
	return(ch >= '0' && ch <= '9');
}

inline bool TPostfix::isVariable(const char ch)
{
	return((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

inline bool TPostfix::isOperator(const char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

inline bool TPostfix::isFunction(const string s)
{
	return (s == "sin" || s == "cos" || s == "exp" || s == "tg");
}

unsigned int TPostfix::countOperators(string s)
{
	int res = 0;
	for (char& i : s)
		res += isOperator(i);
	return res;
}

void TPostfix::split()
{
	unsigned int openBraackets = 0;
	char* ch = &infix[0];
	string digit = "", variable = "";
	while (*ch != '\0')
	{
		while (*ch == ' ')
			ch++;
		if (isDigit(*ch))
		{
			digit += *ch;
			ch++;
			continue;
		}
		else if (isVariable(*ch))
		{
			variable += *ch;
			ch++;
			continue;
		}

		if (variable != "")
			lexems.push_back(Lexem(variable, isFunction(variable) ? Lexem::Type::FUNCTION : Lexem::Type::VARIABLE));
		else if (digit != "")
			lexems.push_back(Lexem(digit, Lexem::Type::DIGIT));
		digit = ""; variable = "";

		switch (*ch)
		{
		case'+':case'-':case'*':case'/':case'^':
			lexems.push_back(Lexem(to_string(*ch), Lexem::Type::OPERATOR));
			ch++;
			break;
		case'(':
			lexems.push_back(Lexem(to_string(*ch), Lexem::Type::L_BRACKET));
			ch++; openBraackets++;
			break;
		case')':
			lexems.push_back(Lexem(to_string(*ch), Lexem::Type::R_BRACKET));
			ch++; openBraackets++;
			break;
		default:
			ch++;
			break;
		}
	}
	if (openBraackets % 2 != 0)
		throw invalid_argument("invalid expression");
}

void TPostfix::toPostfix()
{
	unsigned int id = 0, stackSize = countOperators(infix) * 2, sz = lexems.size(); // max value of operators and brackets
	TStack<Lexem> stack(stackSize);
	vector<Lexem> tmp;
	while (id < sz)
	{
		switch (lexems[id].type)
		{
		case Lexem::Type::L_BRACKET:
			stack.push(lexems[id]);
			id++;
			break;
		case Lexem::Type::DIGIT: case Lexem::Type::VARIABLE:
			tmp.push_back(lexems[id]);
			id++;
			break;
		case Lexem::Type::OPERATOR: case Lexem::Type::FUNCTION:
			if (stack.top == 0 || priority[lexems[id].data] > priority[stack.getTop().data])
			{
				stack.push(lexems[id]);
				id++;
				break;
			}
			else 
			{
				while (stack.top > 0 && priority[lexems[id].data] <= priority[stack.getTop().data])
					tmp.push_back(stack.pop());
				stack.push(lexems[id]);
				id++;
				break;
			}
		case Lexem::Type::R_BRACKET:
			while (stack.getTop().type != Lexem::Type::L_BRACKET)
				tmp.push_back(stack.pop());
			stack.pop();
			break;
		}
		id++;
	}
	while (stack.top > 0)
		tmp.push_back(stack.pop());
	for (auto& t : tmp)
	{
		if (t.type == Lexem::Type::DIGIT || t.type == Lexem::Type::VARIABLE)
			postfix += " ";
		postfix += t.data;
	}
}

double TPostfix::calculate()
{
	unsigned int id = 0;
	double degree = 0, foot = 0, x = 0;
	TStack<string> stack(countOperators(postfix) + 1); // max value of operands
	for (auto& l : lexems)
	{
		if(l.type == Lexem::Type::DIGIT)
		{
			stack.push(l.data);
			continue;
		}
		switch (l.data[0])
		{
		case'+':
			stack.push(to_string(stod(stack.pop()) + stod(stack.pop())));
			break;
		case'-':
			if(stack.size == 1)
				stack.push(to_string(-1 * stod(stack.pop())));
			else
				stack.push(to_string(-1 * stod(stack.pop()) + stod(stack.pop())));
			break;
		case'*':
			stack.push(to_string(stod(stack.pop()) * stod(stack.pop())));
			break;
		case'/':
			stack.push(to_string(1 / stod(stack.pop()) * stod(stack.pop())));
			break;
		case'^':
			degree = stod(stack.pop()); foot = stod(stack.pop());
			stack.push(to_string(pow(foot, degree)));
			break;
		case's':
			stack.push(to_string(sin(stod(stack.pop()))));
			break;
		case'c':
			stack.push(to_string(cos(stod(stack.pop()))));
			break;
		case'e':
			stack.push(to_string(exp(stod(stack.pop()))));
			break;
		case't':
			x = stod(stack.pop());
			stack.push(to_string(sin(x)/cos(x)));
			break;
		}
	}
	return stod(stack.pMem[0]);
}
