#include "postfix.h"
#include "stack.h"

string TPostfix::ToPostfix()
{
	postfix = ' ';
	TStack<char> operation(MaxStackSize);
	for (int i = 0; i < infix.length(); i++)
	{
		if ((((int)infix[i] >= 48) && (int)infix[i] <= 57) || (infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z'))
		{
			postfix += infix[i];
			continue;
		}
		if (Check_op(infix[i]))
		{
			if (infix[i] == '(')
				operation.Push(infix[i]);
			if(infix[i]==')')
				{
				    while (operation.GetTopElem() != '(')
						postfix += (operation.Pop());
					if (!(operation.Empty()))
					operation.Pop();
				}
			if(infix[i] != '(' && infix[i]!=')')
			{
				if (operation.Empty())
					operation.Push(infix[i]);
				else
				{
					while ((Priority(operation.GetTopElem()) >= Priority(infix[i])) && (!operation.Empty()) && (operation.GetTopElem()!= ')') && (operation.GetTopElem() != '('))
						postfix += operation.Pop();
					operation.Push(infix[i]);
				}
			}
		}
		}
	while (!operation.Empty())
		postfix += (operation.Pop());
	return postfix;
	}

		

double TPostfix::Calculate()
{
	TStack <double> value(postfix.length()+1);
	int flag;
	double tmp[L];
	string elements = "";
	double elem, arg1, arg2;
	for (int i = 0; i < postfix.length(); i++)
	{

		if (!Check_op(postfix[i]))
		{
			flag = 0;
			for (int j = 0; j < elements.length(); j++)
			{
				if (postfix[i] == elements[j])
				{
					flag = 1;
					value.Push(elements[j]);
					
				}
			}
			if (flag==0)
			{
				cout << postfix[i]<< "=" << " ";
				cin >> elem;
				elements += postfix[i];
				tmp[elements.length() - 1] = elem;
				value.Push(elem);
			}
			flag = 1;
		}
		else
		{
			if (postfix[i] == '+')
			{
				arg1 = value.Pop();
				arg2 = value.Pop();
				value.Push(arg2 + arg1);
			}
			if (postfix[i] == '-')
			{
				arg1 = value.Pop();
				arg2 = value.Pop();
				value.Push(arg2 - arg1);
			}
			if (postfix[i] == '/')
			{
				arg1 = value.Pop();
				arg2 = value.Pop();
				value.Push(arg2 / arg1);
			}
			if (postfix[i] == '*')
			{
				arg1 = value.Pop();
				arg2 = value.Pop();
				value.Push(arg2 * arg1);
			}
		}
	}
	return value.Pop();
}


int TPostfix::Priority(char c)
{
	switch (c)
	{
	case '+':
	{
		return 1;
	}
	case '-':
	{
		return 1;
	}
	case '*':
	{
		return 2;
	}
	case '/':
	{
		return 2;
	}
	}	
}
bool TPostfix::Check_op(char element)
{
	char operations[Z] = { '+', '-', '*', '/', '(', ')' };
	for (int i = 0; i < Z; i++)
		if (element == operations[i])
			return true;
	return false;
}
