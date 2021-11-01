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
				if (current == "^")
					cur_pr = priority::exponentation;
				else
					throw wrong::undefined_value;
	if (next == "-" || next == "+")
		next_pr = priority::addition_and_substraction;
	else
		if (next == "*" || next == "/")
			next_pr = priority::multiplication_and_division;
		else
			/*if (next == "(")
				next_pr = priority::leftbracket;//Это не будет просмотрено, так как ранее не был выбран случай '('
			else*/
				if (next == "^")
					next_pr = priority::exponentation;
				else
					throw wrong::undefined_value;
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
	char c = '0';
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
				cout << "top = " << top << "\n";
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
			goto sw;
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
	for (int i = 1; i < operands.size(); i++)
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
		try
		{
			operands[i].second = stod(operands[i].first);//если сработает, то это будет бомба
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
		cout << operands[i].first << ' ';
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
	double first_operand, second_operand;
	bool first_is_empty = true;
	typedef double(*change)(double, double);
	change funk[max] = { addition, subtraction, multiplication,division, exponentation };
	for (int i = 0; i < expression.size(); i++)
	{
		int j = 0;
		for (; j < max; j++)
			if (expression[i] == signes_of_operations[j])
			{
				values.insert(values.begin(), funk[j](first_operand, second_operand));
				break;
			}
		if (j == max)
			if (first_is_empty)
			{
				first_operand = values[0];
				values.erase(values.begin());
			}
			else
			{
				second_operand = values[0];
				values.erase(values.begin());
			}
	}
	return 0;
}
