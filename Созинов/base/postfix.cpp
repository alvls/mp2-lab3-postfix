#include "postfix.h"
#include "stack.h"

TPostfix::TPostfix(std::string s)
{
	infix = s;
	DelSpace();
}

string TPostfix::CheckOnCorrect()
{
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
/*int TPostfix::CheckOnCorrect()
{
	//first symbol is operator * or /?
	if ((infix[0] == '*') || (infix[0] == '/'))
		return 1;
	//last symbol is operator?
	if (CheckOnOperator(infix[infix.length() - 1]))
		return 2;
	//balance Parentheses?
	if (!BalanceParentheses())
		return 3;
	//operand after close or before open parenthess (mistake 4, 5)?
	//operator after open (if * or /) or before close parenthess (mistake 6, 7)?
	//two operators in a row (mistake 8)?
	if ((infix[infix.length() - 1] == ')') && (CheckOnOperator(infix[infix.length() - 2])))
	    return 7;
	if ((infix[0] == '(') && ((infix[1] == '*') || (infix[1] == '/')))
		return 6;
	for (unsigned int i = 1; i < (infix.length()- 1); i++)
	{
		if (infix[i] == '(')
			if ((CheckOnSymbol(infix[i - 1])) || (CheckOnNumber(infix[i - 1])))
				return 5;
			else if ((infix[i + 1] == '*') || (infix[i + 1] == '/'))
				return 6;
		if (infix[i] == ')')
			if ((CheckOnSymbol(infix[i + 1])) || (CheckOnNumber(infix[i + 1])))
				return 4;
			else if (CheckOnOperator(infix[i - 1]))
				return 7;
		if ((CheckOnOperator(infix[i])) && (CheckOnOperator(infix[i + 1])))
			return 8;
	}
	return 0;
}*/
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

bool TPostfix::BalanceParentheses()
{
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

string TPostfix::ToPostfix()
{
	if (infix == "")
		throw "infix is empty";
	postfix = string("ab+");
	return postfix;
}

double TPostfix::Calculate()
{

	return 0;
}
