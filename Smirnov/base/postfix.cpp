#include "postfix.h"
#include "stack.h"

bool TPostfix::CheckBrackets()
{
	TStack<string> bracketsStack;
	lexemes = Split();
	for (string word : lexemes)
	{
		if (word == "(")
			bracketsStack.Push("(");
		else if (word == ")")
		{
			if (bracketsStack.isEmpty())
				return false;
			bracketsStack.Pop();
		}	
	}
	return bracketsStack.isEmpty();
}

bool TPostfix::IsOperation(const string& str, Operation& op, int& operationIndex)
{
	if (str == "+")
	{
		op = operation[plusOp];
		operationIndex = plusOp;
		return true;
	}
	else if (str == "-")
	{
		op = operation[minusOp];
		operationIndex = minusOp;
		return true;
	}
	else if (str == "*")
	{
		op = operation[multiplyOp];
		operationIndex = multiplyOp;
		return true;
	}
	else if (str == "/")
	{
		op = operation[divideOp];
		operationIndex = divideOp;
		return true;
	}
	else if (str == "(")
	{
		op = operation[bracketOp];
		operationIndex = bracketOp;
		return true;
	}
	else if (str == "sin")
	{
		op = operation[sinOp];
		operationIndex = sinOp;
		return true;
	}
	else if (str == "cos")
	{
		op = operation[cosOp];
		operationIndex = cosOp;
		return true;
	}
	else if (str.find("^") != string::npos)
	{
		op = operation[powOp];
		operationIndex = powOp;
		return true;
	}
	else if (str == "ln")
	{
		op = operation[lnOp];
		operationIndex = lnOp;
		return true;
	}
	else if (str == "lg")
	{
		op = operation[lgOp];
		operationIndex = lgOp;
		return true;
	}
	else if (str == "sqrt")
	{
		op = operation[sqrtOp];
		operationIndex = sqrtOp;
		return true;
	}
	else
		return false;
}

bool TPostfix::IsConstant(const string& str, int& constIndex)
{
	for (size_t i = 0; i < countConstants; i++)
	{
		if (str == "pi")
		{
			constIndex = pi;
			return true;
		}
		else if (str == "e")
		{
			constIndex = e;
			return true;
		}
	}
	return false;
}

bool IsNumber(const string& str)
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
		throw string("Количество открывающих скобок не равно количеству закрывающих");
	if (!postfix.empty())
		postfix.clear();
	Operation op;
	int indexOperation = -1;
	TStack<Operation> stack(lexemes.size() + reserve);
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
		if (IsOperation(lexemes[i], op, indexOperation))
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
		if (IsNumber(lexemes[i]))
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
	int indexOperation = -1;
	int indexConst = -1;

	for (size_t i = 0; i < postfix.size(); i++)
	{
		if (IsOperation(postfix[i], op,indexOperation))
		{
			if(op.GetArity() == 2 && result.GetTopIndex() < 1)
				throw string("Недостаточно операндов для вычисления операции: " + op.GetName());
			switch (indexOperation)
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
					throw string("Деление на 0");
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
				temp = result.GetTopElem();
				if (temp < 0)
					throw string("Отрицательное число под квадратным корнем");
				result.Push(sqrt(result.Pop()));
				break;
			default:
				break;
			}
			continue;
		}
		if (IsNumber(postfix[i]))
		{
			result.Push(stod(postfix[i])); 
			continue;
		}
		if (IsConstant(postfix[i], indexConst))
		{
			result.Push(constants[indexConst]);
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

void TPostfix::PrintPostfix()
{
	if (!postfix.empty())
		for (size_t i = 0; i < postfix.size(); i++)
		{
			cout << postfix[i] << " ";
		}
	else
		cout << "Не произведен перевод в постфиксную форму!";
}
