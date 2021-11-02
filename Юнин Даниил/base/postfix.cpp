#include "postfix.h"
#include "stack.h"

double TPostfix::Calculate() {
	//1. заменить все лексемы на числа.
	////1.1. Пробежаться по вектору (если первый символ строки не цифра(за иключением операций), то запросить ввести число и поменять его (нужно создать
	//			новый изменённый постфикс)
	vector<string> postfix_new(postfix);
	for (int i = 0; i < postfix_new.size(); i++) {
		string temp = postfix_new[i];
		if ((temp[0] != '0') && (temp[0] != '1') && (temp[0] != '2') && (temp[0] != '3') && (temp[0] != '4') && (temp[0] != '5') && (temp[0] != '6')
			&& (temp[0] != '7') && (temp[0] != '8') && (temp[0] != '9') && (temp[0] != '(') && (temp[0] != ')') && (temp[0] != '+') && (temp[0] != '-')
			&& (temp[0] != '/') && (temp[0] != '*')) {//можно ли проще? 
			string number;
			cout << "Если вводите дробное число, используйте запятую, чтобы ограничить целую и дробную части!" << endl;
			cout << "Введите значение для переменной " << postfix_new[i] << " :";
			cin >> number;
			postfix_new[i] = number;
		}
	}
	//2. посчитать результат с помощью стека.
	TStack<double> work_st;
	string str_to_double;
	for (int i = 0; i < postfix_new.size(); i++) {
		if (postfix_new[i] == "+") {
			double val_for_st = work_st.Get() + work_st.Get();
			work_st.Put(val_for_st);
			continue;
		}
		else if (postfix[i] == "-") {
			double temp = work_st.Get();
			double val_for_st = work_st.Get() - temp;
			work_st.Put(val_for_st);
			continue;
		}
		else if (postfix[i] == "*") {
			double val_for_st = work_st.Get() * work_st.Get();
			work_st.Put(val_for_st);
			continue;
		}
		else if (postfix[i] == "/") {
			double temp = work_st.Get();
			double val_for_st = work_st.Get() / temp;
			work_st.Put(val_for_st);
			continue;
		}
		else {
			str_to_double = postfix_new[i];
			double val_for_st = stod(str_to_double);
			work_st.Put(val_for_st);
		}
	}
	//3. Вернуть значение.
	double res = work_st.Get();
	//cout << res << endl;
	return res;
}

void TPostfix::ChangeInfixToPostfix() {
	vector<string> infix_record;
	TStack<string> st;
	//(a+b)*c
	FindAndChangeUnaryMinusOnBinaryMinus();
	CheckerBrackets();
	vector<int> v_priority = { 0,1,2,2,3,3 };
	vector<string> v_operations = { "(",")","+","-","*","/" };
	ChangeStringToVectorForInfix(infix_record);
	/*for (int i = 0; i < infix_record.size(); i++)
	{
		cout << endl << infix_record[i];
	}*/
	for (int i = 0; i < infix_record.size(); i++) {
		if ((infix_record[i] != "(") && (infix_record[i] != ")") && (infix_record[i] != "+") && (infix_record[i] != "-") && (infix_record[i] != "/") && 
			(infix_record[i] != "*")) {
			postfix.push_back(infix_record[i]);
		}
		else {
			if (infix_record[i] == "(") {
				st.Put("(");
				continue;
			}
			if (st.IsEmpty()) {
				st.Put(infix_record[i]);
				continue;
			}
			if (infix_record[i] == ")") {
				string temp_str = st.Get();
				while (temp_str != v_operations[0]) {
					postfix.push_back(temp_str);
					temp_str = st.Get();
				}
				continue;
			}
			string top_of_stack = st.Get();
			int top_of_stack_priority = DetermineOperation(v_operations, v_priority, top_of_stack);
			int infix_i_priority = DetermineOperation(v_operations, v_priority, infix_record[i]);
			if (infix_i_priority > top_of_stack_priority) {
				st.Put(top_of_stack);
				st.Put(infix_record[i]);
				continue;
			}
			else {
				while (infix_i_priority <= top_of_stack_priority) {
					postfix.push_back(top_of_stack);
					if (st.IsEmpty()) {
						break;
					}
					top_of_stack = st.Get();
					top_of_stack_priority = DetermineOperation(v_operations, v_priority, top_of_stack);
				}						
				if (top_of_stack_priority == 0) {
					st.Put(top_of_stack);
				}
				st.Put(infix_record[i]);
				continue;
			}
		}
	}
	while (!st.IsEmpty()){
		string temp = st.Get();
		postfix.push_back(temp);
	}
	/*cout << "=======================" << endl;
	for (int i = 0; i < postfix.size(); i++)
	{
		cout << endl << postfix[i];
	}*/
}

int TPostfix::DetermineOperation(const vector<string>& operations, const vector<int>& v_priority, const string& symbol) {
	for (int i = 0; i < operations.size(); i++) {
		if (symbol == operations[i]) {
			return v_priority[i];
		}
	}
}

void TPostfix::ChangeStringToVectorForInfix(vector<string>& v) {
	string temp;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == '(') {
			v.push_back("(");
		}
		else if (infix[i] == ')') {
			if (temp.size() > 0) {
				v.push_back(temp);
				temp = "";
			}
			v.push_back(")");
		}
		else if (infix[i] == '+') {
			if (temp.size() > 0) {
				v.push_back(temp);
				temp = "";
			}
			v.push_back("+");
		}
		else if (infix[i] == '-') {
			if (temp.size() > 0) {
				v.push_back(temp);
				temp = "";
			}
			v.push_back("-");
		}
		else if (infix[i] == '/') {
			if (temp.size() > 0) {
				v.push_back(temp);
				temp = "";
			}
			v.push_back("/");
		}
		else if (infix[i] == '*') {
			if (temp.size() > 0) {
				v.push_back(temp);
				temp = "";
			}
			v.push_back("*");
		}
		else {
			temp += infix[i];
		}
	}
	if (temp != "") {
		v.push_back(temp);
	}
}

void TPostfix::FindAndChangeUnaryMinusOnBinaryMinus() {
	if (infix[0] == '-') {
		infix.insert(0, "0");
		//ChangeUnaryMinusOnBinaryMinus(str,-1);
	}
	string sub = "(-";
	int n = 0, from = 0;
	while ((n = infix.find(sub, from)) != string::npos) {
		infix.insert(n + 1, "0");
		from = n + sub.size();
	}
}

void TPostfix::CheckerBrackets() { //Поправить
	TStack<char> st; 
	int Count_errors = 0;
	char temp;
	for (int i = 0; i < infix.size(); i++) {
		temp = infix[i+1];
		if (infix[i] == '(') {
			st.Put(infix[i]);
		}
		if (infix[i] == ')') {
			if (st.IsEmpty()) {
				throw "ERROR! Close baskets more then open braskets!";
				//Count_errors++;
				//continue;
			}
			if (temp == '(') {
				throw "ERROR! Close and open braskets are together without sigh!";
				//Count_errors++;
			}
			st.Get();
		}
		if (i == infix.size() - 1) {
			if (!st.IsEmpty()) {
				for (int j = 0; j < st.GetTop() + 1; j++) {
					throw "ERROR! Open braskets more then close braskets!";
					//Count_errors++;
					//st.Get();
				}
			}
		}
		if ((infix[i] != '(') && (infix[i] != ')')) {
			continue;
		}
		
	}
	//cout << "Выражение: " << infix << endl;
	//cout << "Количество ошибок: " << Count_errors << endl;
}
