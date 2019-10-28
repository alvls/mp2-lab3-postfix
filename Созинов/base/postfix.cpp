#include "postfix.h"
#include "stack.h"

TPostfix::TPostfix(std::string s)
{
	infix = s;
}

string TPostfix::CheckOnCorrect()
{
	DelSpace();
	//first symbol is operator * or /?
	if ((infix[0] == '*') || (infix[0] == '/'))
		return ("First symbol is operator");
	//last symbol is operator?
	if (CheckOnOperator(infix[infix.length() - 1]))
		return ("Last symbol is operator");
	//balance Parentheses?
	if (!BalanceParentheses())
		return ("Unbalance parentheses");
	//operand after close or before open parentheses (mistake 4, 5)?
	//operator after open (if * or /) or before close parentheses (mistake 6, 7)?
	//two operators in a row (mistake 8)?
	if ((infix[infix.length() - 1] == ')') && (CheckOnOperator(infix[infix.length() - 2])))
		return ("Operator before close parentheses");
	if ((infix[0] == '(') && ((infix[1] == '*') || (infix[1] == '/')))
		return ("Operator after open parentheses");
	for (unsigned int i = 1; i < (infix.length() - 1); i++)
	{
		if (infix[i] == '(')
		{
			if ((CheckOnSymbol(infix[i - 1])) || (CheckOnNumber(infix[i - 1])))
				return ("Operand before open parentheses");
			else if ((infix[i + 1] == '*') || (infix[i + 1] == '/'))
				return ("Operator after open parentheses");
		}
		if (infix[i] == ')')
		{
			if ((CheckOnSymbol(infix[i + 1])) || (CheckOnNumber(infix[i + 1])))
				return ("Operand after close parentheses");
			else if (CheckOnOperator(infix[i - 1]))
				return ("Operator before close parentheses");
		}
		if ((CheckOnOperator(infix[i])) && (CheckOnOperator(infix[i + 1])))
			return ("Two operators in a row");
	}
	return "All good";
}

bool TPostfix::CheckOnSymbol(char s)
{
	return (Alphabet_string.find(s) == -1) ? false : true;
}

bool TPostfix::CheckOnNumber(char s)
{
	return (Alphabet_number.find(s) == -1) ? false : true;
}

bool TPostfix::CheckOnOperator(char s)
{
	return (Alphabet_operator.find(s) == -1) ? false : true;
}

bool TPostfix::CheckOnNormal()
{
	for(char i : postfix)
	{
		if (CheckOnSymbol(i))
			return true;
	}
	return false;
}

bool TPostfix::BalanceParentheses()
{
	if (infix.length() == 0)
		throw "infix is empty";
	TStack<char> Check(infix.length());
	unsigned int i = 0;
	//поиск 1-ой скобки, если она закрывающаяся, то расстановка не корректна
	while ((i < infix.length()) && (Check.IsEmpty()))
	{
		if (infix[i] == '(')
		{
			Check.Push('(');
		}
		else if (infix[i] == ')')
		{
			return false;
		}
		i++;
	}
	//добавление всех скобок в стек
	for (; i < infix.length(); i++)
	{
		if (infix[i] == '(')
		{
			Check.Push('(');
		}
		else if (infix[i] == ')')
		{
			Check.Push(')');
		}
	}
	//если верхняя скобка открывающаяся, то расстановка некорректна
	if ((!Check.IsEmpty()) && (Check.GetTopElem() == '('))
		return false;
	int count = 0;
	//проверка баланса скобок
	while (!Check.IsEmpty())
	{
		char c = Check.Pop();
		if (c == ')')
		{
			count--;
		}
		else
		{
			count++;
		}
	}
	return (count == 0) ? true : false;
}

int TPostfix::PriorityOpeartor(char c)
{
	if (c == '(')
		return 0;
	else if (c == ')')
		return 1;
	else if ((c == '+') || (c == '-'))
		return 2;
	else if ((c == '/') || (c == '*'))
		return 3;
}

void TPostfix::DelSpace()
{
	string TmpString = "";
	for (unsigned int i = 0; i != infix.length(); i++)
	{
		if (infix[i] != ' ')
		{
			TmpString += infix[i];
		}
	}
	infix = TmpString;
}

void TPostfix::AddZero()
{
	string tmp = "";
	int i = 0;
	if (infix[i] == '-')
	{
		tmp += "0-";
		i++;
	}
	else if (infix[i] == '+')
	{
		i++;
	}
	while(i < infix.length())
	{
		if ((infix[i] == '-') && (infix[i - 1] == '('))
		{
			tmp += "0-";
			i++;
		}
		else if ((infix[i] == '+') && (infix[i - 1] == '('))
		{
			i++;
		}
		tmp += infix[i++];
	}
	infix = tmp;
}

string TPostfix::ToPostfix()
{
	
	if (infix.length() == 0)
		throw "infix is empty";
	DelSpace();
	AddZero();
	postfix = "";
	TStack<char> stack(infix.length());

	bool F = true;
	for (int i = 0; i < infix.length(); i++)
	{
		if ((CheckOnNumber(infix[i])) || (CheckOnSymbol(infix[i])))
		{
			if (infix[i] == '.')
			{
				postfix += ',';
			}
			else
			{
				postfix += infix[i];
			}
			F = true;
		}
		else if((CheckOnOperator(infix[i])) || (infix[i] == '('))
		{
			if (F)
			{
				F = false;
				postfix += " ";
			}
			if((stack.IsEmpty()) || (infix[i] == '('))
			{
				stack.Push(infix[i]);
			}
			else
			{
				if (PriorityOpeartor(stack.GetTopElem()) < PriorityOpeartor(infix[i]))
				{
					stack.Push(infix[i]);
				}
				else
				{
					while((!stack.IsEmpty()) && (PriorityOpeartor(stack.GetTopElem()) >= PriorityOpeartor(infix[i])))
					{
						postfix += stack.Pop();
						postfix += " ";
					}
					stack.Push(infix[i]);
				}
			}
		}
		else if (infix[i] == ')')
		{
			if (F)
			{
				F = false;
				postfix += " ";
			}
			while (stack.GetTopElem() != '(')
			{
				postfix += stack.Pop();
				postfix += " ";
			}
			stack.Pop();
		}	
	}
	postfix += " ";
	while (!stack.IsEmpty())
	{
		postfix += stack.Pop();
		postfix += " ";
	}
	return postfix;
}

double TPostfix::ToDouble(int *i)
{
	int pos = postfix.find(" ", *i);
	string NumString = postfix.substr(*i, pos - *i);
	*i = pos;
	return stod(NumString);
}

double TPostfix::Calculate()
{
	bool F = true;//noSymbols in postfix		
	for (char i : postfix)
	{
		if (CheckOnSymbol(i))
		{
			F = false;
		}
	}
	int i = 0;
	double tmp = 0;
	double res = 0;
	TStack<double> tmpOperand(postfix.length());
	while (i < postfix.length())
	{
		if (CheckOnNumber(postfix[i]))
		{
			tmp = ToDouble(&i);
			tmpOperand.Push(tmp);
		}
		else if (CheckOnOperator(postfix[i]))
		{
			bool Oper1find = false;
			bool Oper2find = false;
			double Oper1 = 0, Oper2 = 0;
			if (!tmpOperand.IsEmpty())
			{
				Oper2 = tmpOperand.Pop();
				Oper2find = true;
			}
			if (!tmpOperand.IsEmpty())
			{
				Oper1 = tmpOperand.Pop();
				Oper1find = true;
			}
			if (!(Oper1find && Oper2find))
				throw "False";
			switch (postfix[i])
			{
			case '+':
				tmp = Oper1 + Oper2;
				break;
			case '*':
				tmp = Oper1 * Oper2;
				break;
			case '-':
				tmp = Oper1 - Oper2;
				break;
			case '/':
				if (Oper2 == 0)
				{
					throw "division by 0";
				}
				else
				{
					tmp = Oper1 / Oper2;
				}
					break;

			default:
				break;
			}
			tmpOperand.Push(tmp);
		}
		i++;
	}
	return tmpOperand.Pop();
}