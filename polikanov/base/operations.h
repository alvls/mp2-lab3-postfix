#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <map>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Operations {
private:
	map<string, vector<int>> operations;
public:
	Operations() {
		operations.emplace("+", vector<int>{ 1, 2 });
		operations.emplace("-", vector<int>{ 1, 2 });
		operations.emplace("*", vector<int>{ 2, 2 });
		operations.emplace("/", vector<int>{ 2, 2 });
		operations.emplace("(", vector<int>{ 0, 0 });
		operations.emplace(")", vector<int>{ 0, 0 });
		operations.emplace("sqrt", vector<int>{ 3, 1 });
		operations.emplace("sin", vector<int>{ 3, 1 });
		operations.emplace("cos", vector<int>{ 3, 1 });

	}

	int GetPriority(const string& elem) { return operations[elem][0]; }
	int GetArity(const string& elem) { return operations[elem][1]; }
	bool IsOperation(const string& elem) const { return operations.find(elem) != operations.end(); }

	double Calc(const string& elem, double right, double left = 0) {
		if (elem == "sqrt") {
			return sqrt(right);
		}

		if (elem == "sin") {
			return sin(right);
		}


		if (elem == "cos") {
			return cos(right);
		}

		if (elem == "*") {
			return right * left;
		}

		if (elem == "/") {
			return  right / left;
		}

		if (elem == "+") {
			return  right + left;
		}

		if (elem == "-") {
			return right - left;
		}

	}
};


#endif