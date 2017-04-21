#include "postfix.h"
#include "stack.h"

string TPostfix::ToPostfix()
{
	postfix = infix;
	char res;
	char tmp[100];
	TStack<char> stack(100);
	int i;
	int j=0;
	for (i = 0; i < infix.size(); i++)
	{
		if (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')')
		{
			tmp[j] = infix[i];
			j++;
		}
		if (infix[i] == '(')
		{
			res = infix[i];
			stack.Push(res);
		}
		if (infix[i] == ')')
		{
			while (stack.Top() != '(')
			{
				tmp[j] = stack.Pop();
				j++;
			}
			stack.Pop();
		}
		if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
		{
			if (stack.IsEmpty() || stack.Top() == '(')
			{
				res = infix[i];
				stack.Push(res);
			}
			else if (priority(infix[i]) > priority(stack.Top()))
			{
				res = infix[i];
				stack.Push(res);
			}
			else
			{
				while (!stack.IsEmpty() && priority(infix[i]) <= priority(stack.Top()))
				{
					tmp[j] = stack.Pop();
					j++;
				}
				res = infix[i];
				stack.Push(res);
			}
		}

	}

	while (stack.IsEmpty() != 1)
	{
		tmp[j] = stack.Pop();
		j ++;
	}
	tmp[j] = '\0';
	postfix = tmp;


  return postfix;
}

double TPostfix::Calculate()
{
	int i;
	TStack<double> stack(100);
	char copy[100];
	double copy1[100];
	int flag = 0;
	for (i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] != '+' && postfix[i] != '-' && postfix[i] != '*' && postfix[i] != '/')
		{
			flag = 0;
			copy[i] = postfix[i];
			for (int j = 0; j < i; j++)
			{
				if (copy[i] == copy[j])
				{
					flag = 1;
					stack.Push(copy1[j]);
					break;
				}
			}
			if (flag != 1)
			{
				double c;
				cout << "Введите переменную " << postfix[i] << "= ";
				cin >> c;
				copy1[i] = c;
				stack.Push(c);
			}
		}
			else
			{
				if (postfix[i] == '+')
				{
					double number1;
					double number2;
					number1= stack.Pop();
					number2 = stack.Pop();
					double res;
					res = number2 + number1;
					stack.Push(res);
				}
				if (postfix[i] == '-')
				{
					double number1;
					double number2;
					number1 = stack.Pop();
					number2 = stack.Pop();
					double res;
					res = number2 - number1;
					stack.Push(res);
				}
				if (postfix[i] == '/')
				{
					double number1;
					double number2;
					number1 = stack.Pop();
					number2 = stack.Pop();
					double res;
					res = number2/number1;
					stack.Push(res);
				}
				if (postfix[i] == '*')
				{
					double number1;
					double number2;
					number1 = stack.Pop();
					number2 = stack.Pop();
					double res;
					res = number2*number1;
					stack.Push(res);
				}
			}
		}

  return stack.Pop();;
}

int TPostfix::priority(char c)
{
	if ((c == '*') || (c == '/')) return 2;
	if((c == '-') || (c == '+')) return 1;
	if (c == '(') return 0;
	return -2;
}
