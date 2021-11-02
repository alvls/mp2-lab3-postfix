#include "postfix.h"
#include "stack.h"
#include <iostream>
using namespace std;

bool TPostfix::ChekInPostfix(int i)
{
	if ((postfix[i] != '+') && (postfix[i] != '-') && (postfix[i] != '*') && (postfix[i] != '/'))
		return true;
	return false;
};

string TPostfix::ToPostfix()
{
	char result[MaxStackSize];
	int result_pos = 0;
	TStack<char> stack_(MaxStackSize);
	for (int i = 0; i < infix.length(); i++)
	{
		//--1-- Константы и переменные кладутся в формируемую запись в порядке их появления в исходном массиве
		if ((infix[i] != '(') && (infix[i] != ')') && (infix[i] != '+') && (infix[i] != '-') && (infix[i] != '*') && (infix[i] != '/'))
		{
			result[result_pos++] = infix[i];
			result[result_pos] = '\0';
		}
		//--2-- открывающая скобка кладётся в стек
		if (infix[i] == '(')
			stack_.push(infix[i]);
		//--3-- pакрывающая скобка выталкивает из стека в формируемую запись все операции до ближайшей открывающей скобки, открывающая скобка
		//удаляется из стека
		if (infix[i] == ')')
		{
			while (stack_.Top() != '(')//пока
			{
				result[result_pos++] = ' ';
				result[result_pos++] = stack_.Pop();
				result[result_pos] = '\0';
			}
			stack_.Pop();
		}
		if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/'))
		{
			result[result_pos++] = ' ';
			// если в стеке пусто или вверху стека открывающая скобка, операции кладутся в стек
			if (stack_.isEmpty() || stack_.Top() == '(')
				stack_.push(infix[i]);
			// если новая операции имеет бОльший приоритет, чем верхняя операции в стеке, то новая операции кладётся в стек
			else if (Priority(infix[i]) > Priority(stack_.Top()))
				stack_.push(infix[i]);
			else
			{
				while (!stack_.isEmpty() && Priority(infix[i]) <= Priority(stack_.Top()))
				{
					// в формируемую запись
					result[result_pos++] = stack_.Pop();
					result[result_pos] = '\0';
				}
				result[result_pos++] = ' ';
				// новая операция кладется в стек
				stack_.push(infix[i]);
			}
		}
	}
	// оставшиеся операции в стеке в ответ
	while (!stack_.isEmpty())
	{
		result[result_pos++] = ' ';
		result[result_pos++] = stack_.Pop();
		result[result_pos] = '\0';
	}
	postfix = result;
	return postfix;
};

double TPostfix::Calculate()
{
	double array_double[MaxStackSize];
	string prom_res;
	double variables;
	int j = 0;
	TStack<double> stack(MaxStackSize);

	for (int i = 0; i < postfix.length(); i++)
	{
		if (ChekInPostfix(i))
		{
			if (postfix[i] != ' ')
				prom_res = prom_res + postfix[i];
			if ((postfix[i] == ' ') && ChekInPostfix(i - 1))
			{
				size_t found = prom_res.find_first_not_of("0123456789");
				if ((found == std::string::npos) && (postfix[i] == ' '))
				{
					array_double[j] = stoi(prom_res); // преобразовать символы к типу int
					//cout << "b" << "["<< j << "]="<< b[j] << endl;
				}
				else // для выражений на буквах
				{
					cout << postfix[i - 1] << "=";
					cin >> variables;
					array_double[j] = variables;
				}
				stack.push((double)array_double[j]);
				prom_res = "";
				j++;
			}
		}
		else
		{ // выгружаем последние два элемента из стека и производим действие над ними, ответ на вершину стека
			double tmp1 = stack.Pop();
			double tmp2 = stack.Pop();
			if (postfix[i] == '+')
			{
				stack.push(tmp2 + tmp1);
			}
			if (postfix[i] == '-')
			{
				stack.push(tmp2 - tmp1);
			}
			if (postfix[i] == '/')
			{
				if (tmp1 == 0) // деление не ноль невозможно 
					throw exception();
				stack.push(tmp2 / tmp1);
			}
			if (postfix[i] == '*')
			{
				stack.push(tmp2 * tmp1);
			}
		}

	}
	return stack.Pop();
};
