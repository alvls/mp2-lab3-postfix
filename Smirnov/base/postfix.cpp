#include "postfix.h"
#include "stack.h"

bool TPostfix::CheckBrackets()
{
	TStack<string> bracketsStack;
	vector<string> words = Split();
	for (string word : words)
	{
		if (word == "(")
			bracketsStack.Push("(");
		else if (word == ")")
			bracketsStack.Pop();
	}
	return bracketsStack.isEmpty();
}

bool TPostfix::IsOperation(const string& str, Operation& op)
{
	if (str == "+")
	{
		op = operation[plusOp];
		return true;
	}
	else if (str == "-")
	{
		op = operation[minusOp];
		return true;
	}
	else if (str == "*")
	{
		op = operation[multiplyOp];
		return true;
	}
	else if (str == "/")
	{
		op = operation[divideOp];
		return true;
	}
	else if (str == "(")
	{
		op = operation[4];
		return true;
	}
	else if (str == "sin")
	{
		op = operation[sinOp];
		return true;
	}
	else if (str == "cos")
	{
		op = operation[cosOp];
		return true;
	}
	else if (str.find("^") != string::npos)
	{
		op = operation[powOp];
		return true;
	}
	else if (str == "ln")
	{
		op = operation[lnOp];
		return true;
	}
	else if (str == "lg")
	{
		op = operation[lgOp];
		return true;
	}
	else if (str == "sqrt")
	{
		op = operation[sqrtOp];
		return true;
	}
	else
		return false;
}

bool TPostfix::IsConstant(const string& str, int& index)
{
	for (size_t i = 0; i < countConstants; i++)
	{
		if (str == "pi")
		{
			index = pi;
			return true;
		}
		else if (str == "e")
		{
			index = e;
			return true;
		}
	}
	return false;
}

bool isNumber(const string& str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] > '9' || str[i] < '0' && str[i] != ',')
			return false;
	}
	return true;
}

void TPostfix::ToPostfix()
{
	if (!CheckBrackets())
		throw "bad";
	vector<string> lexemes = Split();
	Operation op;
	TStack<Operation> stack(lexemes.size() + offset);
	for (size_t i = 0; i < lexemes.size(); i++)
	{
		if (lexemes[i] == "(")
		{
			stack.Push(operation[bracketOp]);
			continue;
		}
		else if (lexemes[i] == ")")
		{
			while (stack.GetTopElem().GetName() != "(")
			{
				postfix.push_back(stack.Pop().GetName());
			}
			stack.Pop();
			continue;
		}
		if (IsOperation(lexemes[i], op))
		{
			if (stack.isEmpty() || op > stack.GetTopElem())
				stack.Push(op);
			else
			{
				while (!stack.isEmpty() && op <= stack.GetTopElem())
				{
					postfix.push_back(stack.Pop().GetName());
				}
				stack.Push(op);
			}
			continue;
		}
		if (isNumber(lexemes[i]))
		{
			postfix.push_back(lexemes[i]);
			continue;
		}
		if (lexemes[i][0] == '-')
		{
			postfix.push_back("0");
			lexemes[i].erase(0,1);
			postfix.push_back(lexemes[i]);
			stack.Push(operation[minusOp]);
			continue;
		}
		postfix.push_back(lexemes[i]);
	}
	while (!stack.isEmpty())
	{
		postfix.push_back(stack.Pop().GetName());
	}
}

double TPostfix::Calculate()
{
	Operation op;
	TStack<double> result;
	double temp;
	int index = -1;
	for (size_t i = 0; i < postfix.size(); i++)
	{
		if (IsOperation(postfix[i], op))
		{
			switch (op.GetIndex())
			{
			case plusOp:
				result.Push(result.Pop() + result.Pop());
				break;
			case minusOp:
				temp = result.Pop();
				result.Push(result.Pop() - temp);
				break;
			case multiplyOp:
				result.Push(result.Pop() * result.Pop());
				break;
			case divideOp:
				temp = result.Pop();
				if (temp == 0)
					throw string("Divided By Zero");
				result.Push(result.Pop() / temp);
				break;
			case powOp:
				temp = result.Pop();
				result.Push(pow(result.Pop(), temp));
				break;
			case sinOp:
				result.Push(sin(result.Pop() * M_PI / 180));
				break;
			case cosOp:
				result.Push(cos(result.Pop() * M_PI / 180));
				break;
			case lnOp:
				result.Push(log(result.Pop()));
				break;
			case lgOp:
				result.Push(log10(result.Pop()));
				break;
			case sqrtOp:
				result.Push(sqrt(result.Pop()));
				break;
			default:
				break;
			}
			continue;
		}
		if (isNumber(postfix[i]))
		{
			result.Push(stod(postfix[i])); 
			continue;
		}
		if (IsConstant(postfix[i], index))
		{
			result.Push(constants[index]);
			continue;
		}
		string value;
		cout << "Введите значение переменной " + postfix[i] + " = ";
		cin >> value;
		postfix[i] = value;
		result.Push(stod(postfix[i]));
	}
	return result.Pop();
}

vector<string> TPostfix::Split()
{
	vector<string> result;
	string word;
	for (istringstream is(infix); is>>word;)
	{
		result.push_back(word);
	}
	return result;
}
