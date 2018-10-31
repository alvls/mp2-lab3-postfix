#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <sstream>

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
public:
	TPostfix() {}
	TPostfix(const string &_inf) {
		infix = _inf;
		postfix = "";
	}
	void Set(const string &_inf) {
		infix = _inf;
		postfix = "";
	}
	string GetInfix() { return infix; }
	string GetPostfix();
	double Calculate();
};

#endif
