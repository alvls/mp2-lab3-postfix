#include <iostream>
#include <string>
#include "postfix.h"
#include "stack.h"
#include "operations.h"

using namespace std;

bool TPostfix::BracketsCorrect(string& str) const
{
	TStack<bool> stack; // Стек для проверки наличия '('
	for (const char& elem : str)
	{
		if (elem == '(')
		{
			stack.push(true);
			continue;
		}
		if (elem == ')')
		{
			if (stack.empty()) // Если стек пуст, то нет пары для ')' -> ошибка
				return false;
			stack.pop();
			continue;
		}
	}
	if (!stack.empty()) // Если стек не пуст, то слишком мало ')' -> ошибка
		return false;
	return true;
}

void TPostfix::ToInfix(string& str)
{
	string elem;
	Operations op;
	for (int i = 0; i < str.size();)
	{
		string tmp;
		elem = str[i];
		
		if (op.IsOperation(elem))
		{
			tmp = elem;
			i++;
		}
		else
		{
			while (!op.IsOperation(elem) && i < str.size())
			{
				if (elem != " ")
					tmp += elem;
				elem = str[++i];
			}
		}
		
		if ((tmp == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size()-1] == "("))) // Превращение унарного минуса в бинарный
			infix.push_back("0");
		
		if (tmp.find_first_of("0123456789") == 0 && tmp.find_first_not_of("0123456789.") != string::npos) // Проверка на корректность имени переменной, если это переменная
		{
			string exc = "Invalid format of variable: " + tmp;
			throw exc;
		}

		if (tmp.size() != 0)
			infix.push_back(tmp);
	}
}

void TPostfix::ToPostfix()
{
	Operations op;
	TStack<string> opstack;
	/*
	а) Проходимся по всему вектору infix:
		0) Если перед нами лексема, помещаем её в postfix
		1) Если встречаем открывающуюся скобку, сразу записываем её в стек
		2) Если встречаем закрывающуюся скобку, (помещаем в postfix) с удалением из стека все операции
		до открывающейся скобки (которую также удаляем),
		забранные значения помещаем в postfix
		3) Если последняя операция в стеке имеет больший приоритет, чем у текущей операции, то
		помещаем в postfix (с удалением из стека) все операции, пока выполняется это условие
		4) Если стек пустой, то заполняем его текущей операцией, иначе, если приоритет
		текущей операции больше, чем приоритет последней операции в стеке, то добавляем в конец стека
		текущую операцию
	б) Оставшиеся в стеке операции помещаем в postfix
	*/

	for (int i = 0; i < infix.size(); i++)
	{
		string tmp = infix[i];
		if (!op.IsOperation(tmp))
		{
			postfix.push_back(tmp);
			continue;
		}
		else
		{
			if (tmp == "(")
			{
				opstack.push(tmp);
				continue;
			}
			
			if (tmp == ")")
			{
				while (opstack.tos() != "(")
					postfix.push_back(opstack.pop());
				opstack.pop();
				continue;
			}
			
			while (!opstack.empty() && op.GetPriority(opstack.tos()) >= op.GetPriority(tmp))
				postfix.push_back(opstack.pop());
			
			if (opstack.empty())
			{
				opstack.push(tmp);
				continue;
			}
			else
			{
				if (op.GetPriority(opstack.tos()) < op.GetPriority(tmp)) 
				{
					opstack.push(tmp);
					continue;
				}
			}
		}
	}
	while (!opstack.empty())
		postfix.push_back(opstack.pop());
}

vector<string> TPostfix::GetVecOfVariables() const
{
	Operations op;
	vector<string> tmp;
	for (const string& elem : postfix)
	{
		if (elem.find_first_not_of("0123456789") == 0 && !op.IsOperation(elem))
		{
			int different = 0;
			for (const string& element : tmp) // Если tmp.size() == 0, то не произойдёт ни одной итерации и останется different == 0 -> добавится первый элемент
				if (element != elem)
					different++;
			if (different == tmp.size())
				tmp.push_back(elem);
		}
	}
	return tmp;
}

double TPostfix::Calculate(bool interface, vector<double> vecofvalues) const // По умолчанию interface == true, vecofvalues == {}
{
	map<string, double> values;
	vector<string> variables = GetVecOfVariables();
	if (interface)
	{
		if (variables.size() > 0)
		{
			cout << "\nEnter the values of the undefined variables:\n";
			for (string& elem : variables)
			{
				double value;
				cout << "\t" << elem << " = ";
				cin >> value;
				values.emplace(elem, value);
			}
		}
	}
	else
	{
		if (variables.size() != vecofvalues.size())
			throw string("Arrays of names and values have different sizes");
		for (int i = 0; i < variables.size(); i++)
			values.emplace(variables[i], vecofvalues[i]);
	}

	double res = 0;
	TStack<double> arguments;
	Operations op;
	for (const string& elem : postfix)
	{
		if (!op.IsOperation(elem))
		{
			if (find(variables.begin(), variables.end(), elem) != variables.end()) // Если elem - переменная
				arguments.push(values[elem]);
			else
				arguments.push(stod(elem));
		}
		else
		{
			if (op.GetArity(elem) == 1)
				arguments.push(op.Calc(elem, arguments.pop())); // Передаём для вычисления последнее значение
			else // if (op.GetArity(elem) == 2), т.к. в postfix нет скобок
				arguments.push(op.Calc(elem, arguments.pop(), arguments.pop())); // Передаём для вычисления последние два значения
		}
	}
	res = arguments.pop(); // Последний элемент в стеке - ответ
	return res;
}
