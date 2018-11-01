#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <sstream>

using namespace std;

class TPostfix {
	string infix;
	string postfix;
public:
	TPostfix() {}
	TPostfix(const string &_inf) {
		infix = _inf;
		postfix = "";
	}
	TPostfix(const TPostfix &p) {
		infix = p.infix;
		postfix = p.postfix;
	}
	TPostfix operator=(const TPostfix &p) {
		infix = p.infix;
		postfix = p.postfix;
		return *this;
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
