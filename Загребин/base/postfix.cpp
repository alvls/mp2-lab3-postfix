#include "postfix.h"
#define DEBUG(x) std::cout << "Debug: " << x << std::endl;


std::string TPostfix::ToPostfix(){
	std::string word, pf; int i; bool last_is_func = true;
	TStack<operation> ops;

	for (std::istringstream is("( " + infix + " )"); is >> word;) {
		if (word == "(") {	// (
			if (!last_is_func)
				throw -1; // err	5(
			ops.push(funcs[0]);
			continue;
		}
		if(word == ")") {	// )
			if (last_is_func)
				throw -1; // err	()  +)
			while (ops.Top().name != "(")
				pf += ops.pop().name + " ";
			ops.pop();
			continue;
		}
						// operation
		for (i = 1; i < F_Size; i++)
			if (word == funcs[i].name)
				break;
		if (i != F_Size) {
			while(ops.Top().priority >= funcs[i].priority) {
				pf += ops.pop().name + " ";
			}
			if (i == 2 && ops.Top().name == "(" && last_is_func) // - 5
				pf += "0 ";
			
			ops.push(funcs[i]);
			last_is_func = true;
			continue;
		}
		
		if (!last_is_func)
			throw -1; // err	operand operand
		try {	// operand number
			stod(word); 
		}
		catch (...) { // operand variable 
			if (!(word.size() < 3 &&
				((word[0] >= 'a' && word[0] <= 'z')
					|| (word[0] >= 'A' && word[0] <= 'Z'))))
				throw -1; // err	wrong name 
		}
		pf += word + " ";
		last_is_func = false;
	}
  return postfix = pf;
}

double TPostfix::Calculate(){// Ввод переменных, вычисление по постфиксной форме
	TStack<double> st; std::map<std::string, double> var;
	std::string word; int i = 0; double tmp;

	if (postfix == "")
		return 0;

	for (std::istringstream is(postfix); is >> word;) {
		for (i = 1; i < F_Size; i++)
			if (word == funcs[i].name)
				break;
		switch (i) {
		case 1:
			st.push(st.pop() + st.pop());
			break;
		case 2:
			tmp = st.pop();
			st.push(st.pop() - tmp);
			break;
		case 3:
			st.push(st.pop() * st.pop());
			break;
		case 4:
			tmp = st.pop();
			st.push(st.pop() / tmp);
			break;
		case 5: // pow
			tmp = st.pop();
			st.push(pow(st.pop(), tmp));
			break;
		case 6:	// exp
			st.push(exp(st.pop()));
			break;
		case 7:
			st.push(sqrt(st.pop()));
			break;
		case 8:
			st.push(log(st.pop()));
			break;
		case 9: // sin
			st.push(sin(st.pop()));
			break;
		default:
			try {	// number
				st.push(stod(word));
			}
			catch (...) { // variable 
				if (var.find(word) == var.end()) { // new var
					std::cout << "Введите значение ( 1.4 ): " << word << " = ";
					std::cin >> tmp;
					var[word] = tmp;
					st.push(tmp);
				}
				else
					st.push(var[word]);
			}
		}
	}
  return st.pop();
}