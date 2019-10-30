#include "postfix.h"
#include "stack.h"

string TPostfix::ToPostfix()
{
	TStack<char> opStack(MaxStackSize);
	string operacii = "+-*/()";
	int len = infix.length();
	for (int i = 0; i < len; i++)//Проходимся по infix
	{
		if (operacii.find(infix[i]) == string::npos)//если 1 символ не операция
		{
			postfix += infix[i];
		}
		if ((infix[i] >= '0') && (infix[i] <= '9'))//Если i элемент цифра
		{
			if (i != len)
			{
				if ((infix[i + 1] < '0') || (infix[i + 1] > '9'))//И i+1 не цифра
					postfix += '.';
			}
			else
				postfix += '.';
		}
		if (infix[i] == '(')
		{
			opStack.push(infix[i]);
		}
		if (infix[i] == ')')
		{
			char temp = opStack.pop();
			while (temp != '(')
			{
				postfix += temp;
				temp = opStack.pop();
			}
		}
		if (Operandy.find(infix[i]) != string::npos)
		{
			if (opStack.empty() == true)
			{
				opStack.push(infix[i]);
			}
			else
			{
				int index2 = Operandy.find(infix[i]);
				while (opStack.empty() == false)
				{
					char temp = opStack.pop();
					if (temp == '(')
					{
						opStack.push(temp);
						break;
					}
					int index1 = Operandy.find(temp);
					if (Prioritet[index2] <= Prioritet[index1])
						postfix += temp;
					else
					{
						opStack.push(temp);
						break;
					}
				}
				opStack.push(infix[i]);
			}
		}
	}
	while (opStack.empty()==false)
	{
		postfix += opStack.pop();
	}
	return postfix;
}

double TPostfix::Calculate()
{
	if (postfix.length() == 0)
	{
		ToPostfix();//Создать постфиксную форму
	}
	int length = postfix.length();
	TStack<double> res(MaxStackSize);
	string nameForm;
	double *form = new double[length];
	for (int i = 0; i < length; i++)
	{
		if (Operandy.find(postfix[i]) == string::npos)//Символ не операция
		{
			double p;//Значение предполагаемой переменной(вводится ниже)
			if ((postfix[i] < '0') || (postfix[i] > '9'))//Символ не цифра
			{
				//Символ переменная
				if (nameForm.find(postfix[i]) == string::npos)//Встретилась первый раз
				{
					nameForm += postfix[i];
					cout << "Введите значение переменной - " << postfix[i] << endl;
					cin >> p;
					form[nameForm.length() - 1] = p;//записали в массив заначений
				}
				else
				{
					p = form[nameForm.find(postfix[i])];//Уже встречалась
				}
			}
			else//Символ цифра
			{
				string number;
				while (postfix[i] != '.')//Ищем конец числа
				{
					number += postfix[i];
					i++;
				}
				p = stoi(number);//Преобразование в целое число строки
			}
			res.push(p);//Положили переменную или число в стек
		}
		else//Символ операция
		{
			double zn1, zn2, Res;
			//Взяли из стека 2 последних элемента
			zn2 = res.pop();
			zn1 = res.pop();
			switch (postfix[i])//Какая это операция??
			{
			case '+': Res = zn1 + zn2; break;
			case '-': Res = zn1 - zn2; break;
			case '*': Res = zn1 * zn2; break;
			case '/': Res = zn1 / zn2; break;
			}
			res.push(Res);//Положили в стек результат операции
		}
	}
	delete[] form;//Удаляем массив значений
	return res.pop();//Возвращаем последний элемент стека = результату всего выражения
}
bool TPostfix::StringIsRight(string s)
{
	string nevozmozhno = "!@#^&.,<>{}[]|=_?";//Символы, которых не должно быть в выражении
	int ckob = 0, k = 0, countOperation = 0;
	int length = s.length();
	if ((Operandy.find(s[0]) != string::npos) || (Operandy.find(s[length - 1]) != string::npos))
	{
		return false;//Выражение началось или закончилось с операнда
	}
	for (int i = 0; i < length; i++)//Начинаем проверку вводных данных
	{
		if (nevozmozhno.find(s[i]) != string::npos)//Проверка символов строки s на невозможные символы
		{
			return false;//Нашли 
		}
		//Проверка на закрытие скобок
		if (s[i] == '(')
		{
			ckob++;
		}
		if (s[i] == ')')
		{
			ckob--;
		}
		//Счетчик переменных
		if ((s[i] - 'a' >= 0) && (s[i] - 'a' <= 26))
		{
			k++;
		}
		else
		{
			k = 0;
		}
		//Счетчик операций (символов)
		if (Operandy.find(s[i]) != string::npos)
		{
			countOperation++;
		}
		else
		{
			countOperation = 0;
		}
		if ((k > 1) || (countOperation > 1))//Переменные или операции идут подряд, т.е. ab+-
		{
			return false;
		}
	}
	if (ckob != 0)//Ошибка в скобках
	{
		return false;
	}
	return true;
}
