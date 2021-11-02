#include "postfix.h"
#include "stack.h"


//double addition(double one, double two);
//double subtraction(double one, double two);
//double multiplication(double one, double two);
//double division(double one, double two);

double addition(double one, double two)
{
	return (one + two);
}
double subtraction(double one, double two)
{
	return (one - two);
}
double multiplication(double one, double two)
{
	return (one * two);
}
double division(double one, double two)
{
	return (one / two);
}
double exponentation(double one, double two)
{
	return (pow(one, two));
}

//Содержит неточности из-за проблем перевода. Автоматический вариант не работает
double getdb(string str)
{
	int line = str.size();
	char* symbol = new char[line];
	int i = 0;
	for (; i < str.size(); i++)
		symbol[i] = str[i];

	double integer = 0.0; // целая часть числа
	double fractional = 0.0; // дробная часть числа
	double tmp; // дополнительная переменная для дробной части
	double res;//итоговое число
	bool posdeg = true;// положительная ли текущая степень 10
	bool negative = false; // является ли число отрицательным
	int j = 1;// второй счётчик
	int t; // третий счётчик
	int a;// целое для (возможно) более безопасного пребразования типов
	if (symbol[0] == '-')
	{
		i = 1;
		negative = true;
	}
	else
		i = 0;
	for (i; i < line; i++)
	{
		if (posdeg)
			if (symbol[i] == '.')
				posdeg = false;
			else
			{
				integer *= 10;
				a = symbol[i] - '0';
				integer += a;
			}
		else
		{
			a = symbol[i] - '0';
			tmp = a;
			for (t = 0; t < j; t++)
				tmp /= 10;
			fractional += tmp;
			j++;
		}
	}
	res = integer + fractional;
	if (negative)
		res *= -1;
	return res;
}
bool TPostfix::is_current_bigger_or_eq(string current, string next) const
{
	priority cur_pr, next_pr;
	if (current == "-" || current == "+")
		cur_pr = priority::addition_and_substraction;
	else
		if (current == "*" || current == "/")
			cur_pr = priority::multiplication_and_division;
		else
			if (current == "(")
				cur_pr = priority::leftbracket;
			else
				cur_pr = priority::exponentation;
	if (next == "-" || next == "+")
		next_pr = priority::addition_and_substraction;
	else
		if (next == "*" || next == "/")
			next_pr = priority::multiplication_and_division;
		else
			if (next == "(")
				next_pr = priority::leftbracket;
		else
			next_pr = priority::exponentation;
	if (cur_pr < next_pr)
		return false;
	else 
		return true;
}
void TPostfix::ToPostfix()
{
	const string emptystring = "";
	string operand = emptystring;
	TStack<string> operation_stack;
	char c;
	string top = emptystring;
	string fake_string = emptystring;
	int tos;
	for (int i=0;i<infix.size();i++)
	{
		c = infix[i];
sw:		switch (c)
		{
		case '(':
			operation_stack.put(string(1, c));
			break;
		case ')':
			tos = operation_stack.getsize();
			while (operation_stack[--tos] != "(")
				;
			while (tos < operation_stack.getsize())
			{
				expression.push_back(operation_stack[tos]);
				tos++;
			}
			break;
		case '+':case '-':case'*':case'/': case '^':
			fake_string = string(1, c);
			if (!operation_stack.is_empty())
			{
				top = operation_stack.top_of_stack();
				if (is_current_bigger_or_eq(top, fake_string))
					expression.push_back(operation_stack.get());
			}
			operation_stack.put(fake_string);
			break;
		default:
			while (c != '+' && c != '-' && c != '*' && c != '/' && c != '^' && c != ')' && c != '('&&i<infix.size())
			{
				operand.push_back(c);
				i++;
				c = infix[i];
			}
			expression.push_back(operand);
			operand = emptystring;
			if (i < infix.size())
				goto sw;
			else
				break;
		}
	}
	while (!operation_stack.is_empty())
		expression.push_back(operation_stack.get());
	postfix = emptystring;
	for (int i = 0; i < expression.size(); i++)
		postfix += expression[i];
}
vector<double> TPostfix::GetValues()
{
	vector < pair<string, double>> operands;
	const string operations[5] = { "+", "-", "*", "/", "^" };
	for (int i = 0; i < expression.size(); i++)
	{
		int j = 0;
		for (; j < 5; j++)
			if (expression[i] == operations[j])
				break;
		if (j == 5)
			operands.push_back(pair<string, double>(expression[i], 0));
	}
	vector<int> used;//показывает, что значение с данным индексом уже заполнено
	for (int i = 0; i < operands.size(); i++)
	{
		for(int j='0';j<'9';j++)
			if (operands[i].first[0] == i)
			{
				operands[i].second = getdb(operands[i].first);
				used.push_back(i);
				break;
			}
		if (operands[i].first[0] == '-')
		{
			operands[i].second = getdb(operands[i].first);
			used.push_back(i);
		}
		try
		{
			operands[i].second = stof(operands[i].first);//если сработает, то это будет бомба
			used.push_back(i);
		}
		catch (...)
		{
			continue;
		}
	}
	for (int i = 0; i < operands.size(); i++)
	{
		vector<int> eq;//индексы операндов, одинаковых для i-ого
		for (int j = 0; j < used.size(); j++)
			if (used[j] == i)
				goto cont;
		for (int j = i + 1; j < operands.size(); j++)
			if (operands[i] == operands[j])
			{
				eq.push_back(j);
				used.push_back(j);
			}
		cout << "Введите значение для " << operands[i].first << ' ';
		cin >> operands[i].second;
	cont:		for (int j = 0; j < eq.size(); j++)
		operands[eq[j]].second = operands[i].second;
	}
	vector<double> values;
	for (int i = 0; i < operands.size(); i++)
		values.push_back(operands[i].second);
	return values;
}
double TPostfix::Calculate()
{
	vector<double> values = GetValues();
	const int max = 5;
	const string signes_of_operations[max] = { "+", "-", "*", "/", "^" };
	double first_operand = 13.3, second_operand = 0;
	typedef double(*change)(double, double);
	change funk[max] = { addition, subtraction, multiplication, division, exponentation };
	//TStack<double> operands; Нихатю со стеком, он злюка

	//вектор - сила!
	vector<double> variables;//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	for (int i = 0; i < expression.size(); i++)
	{
		int j = 0;
		for (; j < max; j++)
			if (expression[i] == signes_of_operations[j])
			{
				variables[0] = (funk[j](variables[0], variables[1]));
				variables.pop_back();
				break;
			}
		if (j == max)
		{
			variables.push_back(values[0]);
			values.erase(values.begin());
		}
	}
	return variables[0];
}
