#pragma once
#include <string>
using namespace std;

class Operation
{
private:
	string _name;
	int _cost;
	int _arity;
public:
	Operation(string name = "default", int cost = 0, int arity = -1) : _name(name), _cost(cost), _arity(arity)
	{}

	int GetCost() { return _cost; };
	string GetName() { return _name; };
	int GetArity() { return _arity; };

	bool operator>(const Operation& otherOp) const { return _cost > otherOp._cost ? true : false; };
	bool operator<(const Operation& otherOp) const { return _cost < otherOp._cost ? true : false; };
	bool operator>=(const Operation& otherOp) const { return _cost >= otherOp._cost ? true : false; };
	bool operator<=(const Operation& otherOp) const { return _cost <= otherOp._cost ? true : false; };
	bool operator==(const Operation& otherOp) const { return (_name == otherOp._name) && (_cost == otherOp._cost); };
};

