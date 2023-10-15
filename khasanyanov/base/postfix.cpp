#include "postfix.h"


inline short TPostfix::priority(const char ch)
{
	switch (ch)
	{
	case '(': return 1;
	case '+': case '-': return 2;
	case '*': case '/': return 3;
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
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int TPostfix::countOperators(string s)
{
	int res = 0;
	for (char& i : s)
		res += isOperator(i);
	return res;
}

string TPostfix::ToPostfix(string s)
{
	unsigned int id = 0, openBraackets = 0;
	char ch;
	TStack<char> stack(countOperators(s) * 2); //max value of operands and open brackets  ((1+3)-2)
	string out = "";
	while (s[id] != '\0')
	{
		ch = s[id];
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
		case'+':case'-':case'*':case'/':
			if (stack.top == 0 || priority(ch) > priority(stack.getTop()))
			{
				stack.push(ch);
				id++;
				break;
			}
			else
			{
				while (priority(ch) <= priority(stack.getTop()) && stack.top > 0) 
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

double TPostfix::Calculate()
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
		}
		id++;
	}
	return stod(stack.pMem[0]);
}
