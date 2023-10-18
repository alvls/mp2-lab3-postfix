#include "postfix.h"


TPostfix::TPostfix() :infix("1+2-3*5"), isFormula(0) {}

TPostfix::TPostfix(string str) : infix(str), postfix(this->toPostfix()) {}

string TPostfix::getInfix() const { return infix; }

string TPostfix::getPostfix() const { return postfix; }

inline short TPostfix::priority(const char ch)
{
	switch (ch)
	{
	case '(': return 1;
	case '+': case '-': return 2;
	case '*': case '/': return 3;
	case '^': return 4;
	default: return 0;
	}
}

inline bool TPostfix::isDigit(const char ch)
{
	return(ch >= '0' && ch <= '9');
}

inline bool TPostfix::isVariable(const char ch)
{
	return((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

bool TPostfix::isOperator(const char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

unsigned int TPostfix::countOperators(string s)
{
	int res = 0;
	for (char& i : s)
		res += isOperator(i);
	return res;
}

string TPostfix::toPostfix()
{
	unsigned int id = 0, openBraackets = 0, size = countOperators(infix) * 2;
	char ch;
	if (size == 0)
		throw invalid_argument("invalid expression");
	TStack<char> stack(size); //max value of operators and open brackets  ((1+3)-2)
	string out = "";
	while (infix[id] != '\0')
	{
		ch = infix[id];
		if (ch == ' ')
		{
			id++;
			continue;
		}
		else if (isDigit(ch))
		{
			out += ch;
			id++;
			continue;
		}
		else if ( isVariable(ch))
		{
			isFormula = true;
			out += ch;
			id++;
			continue;
		}
		else if (ch != '(')	out += ' ';			
		switch (ch)
		{
		case '(':
			openBraackets++;
			stack.push(ch);
			id++;
			break;
		case'+':case'-':case'*':case'/':case'^':
			if (stack.top == 0 || priority(ch) > priority(stack.getTop()))
			{
				stack.push(ch);
				id++;
				break;
			}
			else
			{
				while (stack.top > 0 && priority(ch) <= priority(stack.getTop()))
				{
					out += stack.pop();
					out += ' ';
				}
				stack.push(ch);
				id++;
				break;
			}
		case ')':
			while (stack.getTop() != '(')
				out += stack.pop();
			stack.pop();
			openBraackets--;
			id++;
			break;
		default:
			id++;
			break;
		}
	}
	if (openBraackets != 0)
		throw exception("syntax error");
	while (stack.top > 0)
	{
		out += ' ';
		out += stack.pop();
	}
	return out;
}

double TPostfix::calculate()
{
	unsigned int id = 0;
	TStack<string> stack(countOperators(postfix) + 1); // max value of operands
	char current;
	string elem = "";
	if (isFormula == 1)
		throw exception("Сan't be calculated");
	while (postfix[id] != '\0')
	{
		current = postfix[id];
		if (isDigit(current))
		{
			elem += current;
			id++;
			continue;
		}
		if (elem != "")
		{
			stack.push(elem);
			elem = "";
			id++;
			continue;
		}
		switch (current)
		{
		case ' ':
			break;
		case'+':
			stack.push(to_string(stod(stack.pop()) + stod(stack.pop())));
			break;
		case'-':
			stack.push(to_string(-1 * stod(stack.pop()) + stod(stack.pop())));
			break;
		case'*':
			stack.push(to_string(stod(stack.pop()) * stod(stack.pop())));
			break;
		case'/':
			stack.push(to_string(1 / stod(stack.pop()) * stod(stack.pop())));
			break;
		case'^':
			double degree = stod(stack.pop()), foot = stod(stack.pop());
			stack.push(to_string(pow(foot, degree)));
			break;
		}
		id++;
	}
	return stod(stack.pMem[0]);
}
