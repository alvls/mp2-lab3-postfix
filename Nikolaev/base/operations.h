#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <map>
#include <cmath>

using namespace std;

class Operations {
private:
	map<string, vector<int>> ops;
public:
	Operations() {
		ops.emplace("sqrt", vector<int>{ 3, 1 });
		ops.emplace("sin", vector<int>{ 3, 1 });
		ops.emplace("cos", vector<int>{ 3, 1 });
		ops.emplace("*", vector<int>{ 2, 2 });
		ops.emplace("/", vector<int>{ 2, 2 });
		ops.emplace("+", vector<int>{ 1, 2 });
		ops.emplace("-", vector<int>{ 1, 2 });
		ops.emplace("(", vector<int>{ 0, 0 });
		ops.emplace(")", vector<int>{ 0, 0 });
	}

	bool IsOperation(const string& elem) const { return ops.find(elem) != ops.end(); }
	int GetPriority(const string& elem) { return ops[elem][0]; }
	int GetArity(const string& elem) { return ops[elem][1]; }
	double Calc(const string& elem, double right, double left = 0) {
		if (elem == "sqrt")
			return sqrt(right);
		if (elem == "sin")
			return sin(right);
		if (elem == "cos")
			return cos(right);
		if (elem == "*")
			return right * left;
		if (elem == "/")
			return  right / left;
		if (elem == "+")
			return  right + left;
		if (elem == "-")
			return right - left;
	}
};

#endif