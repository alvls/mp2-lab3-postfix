#include "postfix.h"
#include "stack.h"

map<char, int> TPostfix::priority = {
	{'(', 0 },
	{'-', 1 },
	{'+', 1 },
	{'*', 2 },
	{'/', 2 }
};

TPostfix::TPostfix(string infx) : infix(infx)
{
	if (infx.empty())
		throw invalid_argument("Infix is empty");
	ToPostfix();
}

string TPostfix::GetInfix() const { return infix; }

vector<string> TPostfix::GetPostfix() const { return postfix; }

vector<string> TPostfix::GetOperands() const
{
	vector<string> op;
	for (const auto& item : operands)
	{
		if (item.first.empty()) 
			continue;
		op.push_back(item.first);
	}

	return op;
}

void TPostfix::Parse()
{
	string buf = "";
	for (char ch : infix)
	{
		if (ch == ')' || (priority.find(ch) != priority.end()))
		{
			if (!buf.empty())
				lexems.push_back(buf);
			lexems.push_back(string{ ch });
			buf = "";
			continue;
		}
		buf += ch;
	}
	if (!buf.empty())
		lexems.push_back(buf);
}

void TPostfix::ToPostfix()
{
	Parse();

	TStack<string> stack;
	string stackItem;
	size_t i = 0;

	for (string item : lexems)
	{
		switch (item[0])
		{
		case '(':
			stack.push(item);
			break;
		case ')':
			stackItem = stack.pop();
			while (stackItem[0] != '(')
			{
				postfix.push_back(stackItem);
				stackItem = stack.pop();
			}
			break;
		case '-': case '+': case '*': case '/':
			if (item[0] == '-' && (postfix.empty() ||
				(!stack.is_empty() && stack.top() == "(") && lexems[i - 1] != ")"))
			{
				postfix.push_back("");
			}
			while (!stack.is_empty())
			{
				stackItem = stack.pop();
				if (priority[item[0]] <= priority[stackItem[0]])
				{
					postfix.push_back(stackItem);
				}
				else
				{
					stack.push(stackItem);
					break;
				}
			}
			stack.push(item);
			break;
		default:
			operands.insert({ item, 0.0 });
			postfix.push_back(item);
		}
		i++;
	}

	while (!stack.is_empty())
	{
		stackItem = stack.pop();
		postfix.push_back(stackItem);
	}
};

double TPostfix::Calculate(const map<string, double>& values)
{
	for (auto& value : values)
	{
		const auto& opValue = operands.find(value.first);
		if (opValue == operands.end())
			continue;
		(*opValue).second = value.second;
	}

	TStack<double> stack;
	double leftOperand, rightOperand;

	for (string lexem : postfix)
	{
		switch (lexem[0])
		{
		case '-':
			rightOperand = stack.pop();
			leftOperand = stack.pop();
			stack.push(leftOperand - rightOperand);
			break;
		case '+':
			rightOperand = stack.pop();
			leftOperand = stack.pop();
			stack.push(leftOperand + rightOperand);
			break;
		case '*':
			rightOperand = stack.pop();
			leftOperand = stack.pop();
			stack.push(leftOperand * rightOperand);
			break;
		case '/':
			rightOperand = stack.pop();
			leftOperand = stack.pop();
			stack.push(leftOperand / rightOperand);
			break;
		default:
			stack.push(operands[lexem]);
		}
	}

	return stack.pop();
}
