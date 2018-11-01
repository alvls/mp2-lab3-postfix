#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix {
	string infix;
	string postfix;
public:
	TPostfix(string _infix = "");
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	bool delim(char);
	bool is_op(char);
	int priority(char);
	void process_op(TStack<double> &, char);
	double execute();
	bool correct();
};

#endif
