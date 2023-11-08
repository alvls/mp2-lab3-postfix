#include "postfix.h"
#include "stack.h"

map<char, int> TPostfix::priority = {
	{'(', 0 },
	{'-', 1 },
	{'+', 1 },
	{'*', 2 },
	{'/', 2 },
	{'^', 3 },
};

TPostfix::TPostfix(string infx) : infix(infx)
{
	if (!BracketsCorrect(infx))
	{
		throw invalid_argument("Скобки расставлены некорректно");
	}
	ToPostfix();
}

bool TPostfix::BracketsCorrect(const string& str) const
{
	TStack<bool> stack;

	for (const char& elem : str)
	{
		if (elem == '(')
		{
			stack.Push(true);
		}
		if (elem == ')')
		{
			if (stack.IsEmpty())
				return false;
			stack.Pop();
		}
	}

	if (!stack.IsEmpty())
	{
		return false;
	}

	return true;
}

string TPostfix::GetInfix() const
{
	return infix;
}

string TPostfix::GetPostfix() const
{
	return postfix;
}

bool TPostfix::isOperand(char ch)
{
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9');
}

bool TPostfix::isOperator(char ch)
{
	return string("+-*/^").find(ch) != string::npos;
}

void TPostfix::ToPostfix()
{
	TStack<char> st;
	postfix = "";
	bool unaryMinus = true;  // Флаг для определения унарного минуса

	for (size_t i = 0; i < infix.size(); i++)
	{
		char ch = infix[i];

		if (isOperand(ch))
		{
			postfix += ch;
			unaryMinus = false;
		}
		else if (ch == '(')
		{
			st.Push(ch);
			unaryMinus = true;
		}
		else if (ch == ')')
		{
			while (!st.IsEmpty() && st.Top() != '(')
				postfix += st.Pop();
			st.Pop();
			unaryMinus = false;
		}
		else if (isOperator(ch))
		{
			if (unaryMinus && (ch == '-' || ch == '+'))
			{
				postfix += '0';
				st.Push(ch);
			}
			else
			{
				while (!st.IsEmpty() && st.Top() != '(' && priority[ch] <= priority[st.Top()])
					postfix += st.Pop();
				st.Push(ch);
				unaryMinus = true;
			}
		}
	}

	while (!st.IsEmpty())
		postfix += st.Pop();
}

double TPostfix::Calculate()
{
	TStack<double> st;

	for (char item : postfix)
	{
		if (isOperand(item))
		{
			if (isalpha(item))
			{
				if (values.find(item) != values.end())
				{
					st.Push(values[item]);
				}
				else
				{
					throw invalid_argument("Переменная не определена: " + string(1, item));
				}
			}
			else {
				st.Push(item - '0');
			}
		}
		else
		{
			double rightOperand = st.Pop();
			double leftOperand = st.Pop();

			switch (item) {

			case '+':
				st.Push(leftOperand + rightOperand);
				break;

			case '-':
				st.Push(leftOperand - rightOperand);
				break;

			case '*':
				st.Push(leftOperand * rightOperand);
				break;

			case '/':
				if (rightOperand == 0)
					throw invalid_argument("Деление на ноль");
				st.Push(leftOperand / rightOperand);
				break;

			case '^':
				st.Push(pow(leftOperand, rightOperand));
				break;

			default:
				throw invalid_argument("Неподдерживаемая операция");
			}
		}
	}
	if (st.IsEmpty())
		throw invalid_argument("Ошибка в выражении");

	double res = st.Pop();
	if (!st.IsEmpty())
		throw invalid_argument("Ошибка в выражении");

	return res;
}

void TPostfix::SetVariable(char variable, double value)
{
	values[variable] = value;
}

void TPostfix::SetVariables(const map<char, double>& variableValues)
{
	for (const auto& pair : variableValues)
	{
		values[pair.first] = pair.second;
	}
}