#pragma once
#include <string>
using namespace std;

class Operation
{
private:
	string _name;
	int _cost;
	int _index;
public:
	Operation(string name = "default", int cost = 0, int index = -1) : _name(name), _cost(cost), _index(index)
	{}

	int GetCost() { return _cost; };
	string GetName() { return _name; };
	int GetIndex() { return _index; };

	bool operator>(const Operation& otherOp) const { return _cost > otherOp._cost ? true : false; };
	bool operator<(const Operation& otherOp) const { return _cost < otherOp._cost ? true : false; };
	bool operator>=(const Operation& otherOp) const { return _cost >= otherOp._cost ? true : false; };
	bool operator<=(const Operation& otherOp) const { return _cost <= otherOp._cost ? true : false; };
	bool operator==(const Operation& otherOp) const { return _name == otherOp._name; };
};

