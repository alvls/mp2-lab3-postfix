#include "postfix.h"
#include "stack.h"
#include <iostream>

int TPostfix::prior(char a)
{
	switch (a)
	{
	case '*':return 3;
	case '/':return 3;
	case '+':return 2;
	case '-':return 2;
	case '(':return 1;
	case ')':return 1;
	case ' ':return -1;
	default:return 0;
	}
}
void TPostfix::SetInfix(string t)
{
	int i = 0, k = 0;
	string tp;
	double tmp = 0;
	delete[] p;
	p = new double[t.size()];
	int start = -1;
	t += " ";
	while (i <= t.size())
	{
		if (prior(t[i]) == 0)
		{
			if (start == -1)
				start = i;
		}
		else
		{
			if ((prior(t[i]) == -1) && (start == -1))
			{
				infix = t;
				infix.pop_back();
				return;
			}
			if (start != -1)
			{
				tp = t.substr(start, i - start);
				tmp = atof(tp.c_str());
				t.replace(start, i - start, 1, 65 + k);
				p[k++] = tmp;
				i = i - (i - start + 1) + 1;
				start = -1;
			}
		}
		i++;
	}
}
string TPostfix::ToPostfix()
{
	sc.setsize(infix.size());
	sd.setsize(infix.size());
	char tmp;
	for (int i = 0; i < infix.size(); i++)\
	{
		tmp = infix[i];
		if (prior(tmp) == 0)
			postfix += tmp;
		else
		{
			if ((prior(tmp) == 2) || (prior(tmp) == 3))
			{
				if (sc.empty() == true)
					sc.add(tmp);
				else
				{
					if (prior(tmp) > prior(sc.infotop()))
						sc.add(tmp);
					else
					{
						while (prior(tmp) <= prior(sc.infotop()))
						{
							postfix += sc.gettop();
							if (sc.empty() == true)
								break;
						}
						sc.add(tmp);
					}
				}
			}
			else
				if (tmp == '(')
					sc.add(tmp);
				else
					if (tmp == ')')
					{
						while (sc.infotop() != '(')
							postfix += sc.gettop();
						sc.gettop();
					}
		}
	}
	while (sc.empty() != true)
	{
		postfix += sc.gettop();
	}
	return postfix;
}

double TPostfix::Calculate()
{
	double a, b;
	for (int i = 0; i < postfix.size(); i++)
	{
		switch (postfix[i])
		{
		case'+':a = sd.gettop(); b = sd.gettop();
			sd.add(a + b);
			break;
		case'-': a = sd.gettop();
			if (sd.empty() == true)
				sd.add(0 - a);
			else
			{
				b = sd.gettop();
				sd.add(b - a);
			}
			break;
		case'*': a = sd.gettop(); b = sd.gettop();
			sd.add(a * b);
			break;
		case'/':a = sd.gettop(); b = sd.gettop();
			sd.add(b / a);
			break;
		default:
			a = p[postfix[i] - 65];
			sd.add(a);
			break;
		}
	}
	a = sd.gettop();
	if (sd.empty() != true)
	{
		throw 0;
	}
	return a;
}







