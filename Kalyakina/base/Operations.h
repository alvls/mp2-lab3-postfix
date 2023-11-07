#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Operations
{
	map<string, vector<int>> operation;

public:
	Operations()
	{
		operation.emplace("(", vector<int>{ 0, 0 });
		operation.emplace(")", vector<int>{ 0, 0 });
		operation.emplace("+", vector<int>{ 1, 2 });
		operation.emplace("-", vector<int>{ 1, 2 });
		operation.emplace("*", vector<int>{ 2, 2 });
		operation.emplace("/", vector<int>{ 2, 2 });
		operation.emplace("%", vector<int>{ 2, 2 });
		operation.emplace("^", vector<int>{ 3, 2 });
		operation.emplace("abs", vector<int>{ 3, 1 });
		operation.emplace("sqrt", vector<int>{ 3, 1 });
		operation.emplace("ln", vector<int>{ 3, 1 });
		operation.emplace("sin", vector<int>{ 3, 1 });
		operation.emplace("cos", vector<int>{ 3, 1 });
		operation.emplace("tg", vector<int>{ 3, 1 });
	};

	bool IfIsOperation(string op) const
	{
		return(!(operation.find(op) == operation.end()));
	};

	int GetPriority(string op) const
	{
		return operation.at(op)[0];
	};

	int GetArity(string op) const
	{
		return operation.at(op)[1];
	};

	double Calculation(const string& op, double first, double second = 0)
	{
		if (op == "+")
			return (first + second);
		if (op == "-")
			return (second - first);
		if (op == "*")
			return (first * second);
		if (op == "/")
			return (second / first);
		if (op == "%")
			return ((int)second % (int)first);
		if (op == "^")
			return (pow(second, first));
		if (op == "abs")
			return (abs(first));
		if (op == "sqrt")
			return (sqrt(first));
		if (op == "ln")
			return (log(first));
		if (op == "sin")
			return (sin(first));
		if (op == "cos")
			return (cos(first));
		if (op == "tg")
			return (tan(first));
		return 0;
	};
};

#endif