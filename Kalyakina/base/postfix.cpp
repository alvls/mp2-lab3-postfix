#include "postfix.h"
#include "stack.h"

TPostfix::TPostfix(string str)
{
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] == ' ')
			str.erase(i, 1);
	infix_str = str;
	ToInfix();
	CheckOfExpression();
	ToPostfix();
}

void TPostfix::ToInfix()
{
	string element, operand;
	Operations op;
	for (size_t i = 0; i < infix_str.size(); i++)
	{
		element = infix_str[i];
		if (!op.IfIsOperation(element))
			operand += element;
		else
		{
			if (operand != "")
			{
				infix.push_back(operand);
				operand = "";
			}
			if ((element == "-") && ((infix.size() == 0) || (infix[infix.size() - 1] == "(")))
			{
				infix.push_back("0");
			}
			infix.push_back(element);
		}
	}
	if (operand != "")
		infix.push_back(operand);
}

void TPostfix::CheckOfExpression()
{
	int count_of_left = 0, count_of_right = 0;
	Operations op;
	if (op.IfIsOperation(infix[0]))
	{
		if (infix[0] == "(")
			count_of_left++;
		if (infix[0] == ")")
			throw "Expression is wrong, check operations";
		if ((op.GetArity(infix[0]) > 1) && (infix[0] != "-"))
			throw "Expression is wrong, check operations";
	}
	else
	{
		if (!((infix[0].find_first_not_of("0123456789,") == string::npos)
			|| ((infix[0].find_first_of("0123456789") > infix[0].find_last_not_of("0123456789"))
				&& (infix[0].find_first_of(".,<>?/|!@#$&={}[]:;\"'") == string::npos))))
			throw "Expression is wrong, check operands";
	}
	if ((op.IfIsOperation(infix[infix.size() - 1])) && (infix[infix.size() - 1] != ")"))
		throw "Expression is wrong, check operations";
	for (size_t i = 1; i < infix.size(); i++)
	{
		if (op.IfIsOperation(infix[i]))
		{
			if (infix[i] == "(")
				count_of_left++;
			if (infix[i] == ")")
				count_of_right++;
			if ((op.IfIsOperation(infix[i - 1]))
				&& ((op.GetArity(infix[i]) > 1) && (infix[i] != "-") && (infix[i - 1] != ")")
					|| (infix[i] == "-") && (infix[i - 1] != "(")
					|| (infix[i - 1] == ")") && (op.GetArity(infix[i]) == 1)))
				throw "Expression is wrong, check operations";
			else if (!op.IfIsOperation(infix[i - 1]) && (op.GetArity(infix[i]) < 2) && (infix[i] != ")"))
				throw "Expression is wrong, check operations";
		}
		else
		{
			if ((!op.IfIsOperation(infix[i - 1])) || (infix[i - 1] == ")"))
				throw "Expression is wrong, check operands";
			if (!((infix[i].find_first_not_of("0123456789,") == string::npos)
				|| ((infix[i].find_first_of("0123456789") > infix[i].find_last_not_of("0123456789"))
					&& (infix[i].find_first_of(".,<>?/|!@#$&={}[]:;\"'") == string::npos))))
				throw "Expression is wrong, check operands";
		}
	}
	if (count_of_left != count_of_right)
		throw - 1;
}

void TPostfix::ToPostfix()
{
	TStack<string> st(infix.size());
	Operations op;
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (op.IfIsOperation(infix[i]))
		{
			if (infix[i] == "(")
				st.push(infix[i]);
			else if (infix[i] == ")")
			{
				while (st.getTop() != "(")
					postfix.push_back(st.pop());
				st.pop();
			}
			else
			{
				while (!((st.empty()) || (op.GetPriority(infix[i]) > op.GetPriority(st.getTop()))))
					postfix.push_back(st.pop());
				st.push(infix[i]);
			}
		}
		else
		{
			if ((infix[i].find_first_not_of("0123456789,") == string::npos) && (constants.count(infix[i]) == 0))
				constants.emplace(infix[i], stod(infix[i]));
			else if (operands.count(infix[i]) == 0)
				operands.emplace(infix[i], 0);
			postfix.push_back(infix[i]);
		}
	}
	while (!st.empty())
		postfix.push_back(st.pop());
	for (string element : postfix)
	{
		postfix_str += element;
	}
}

double TPostfix::Calculate(vector<double> values_of_operands)
{
	int i = 0;
	Operations op;
	TStack<double> st(postfix.size());
	if (values_of_operands.size() == 0)
	{
		cout << endl << "Введите значения переменных" << endl;
		for (auto it = operands.begin(); it != operands.end(); it++, i++)
		{
			cout << "Введите значение переменной " << it->first << ": ";
			cin >> it->second;
		}
	}
	else
	{
		if (operands.size() != values_of_operands.size())
			throw "Wrong count of values";
		for (auto it = operands.begin(); it != operands.end(); it++, i++)
			it->second = values_of_operands[i];
	}
	for (const string& element : postfix)
	{
		if (!op.IfIsOperation(element))
		{
			if (operands.count(element) > 0)
				st.push(operands.at(element));
			else
				st.push(constants.at(element));
		}
		else
		{
			if (op.GetArity(element) == 1)
			{
				st.getTop();
				st.push(op.Calculation(element, st.pop()));
			}
			else
			{
				double first = st.pop();
				st.push(op.Calculation(element, first, st.pop()));
			}
		}
	}
	return st.pop();
}