#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include "stack.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

class TPostfix {
private:
	vector<string> infix;
	vector<string> postfix;
	TPostfix(const TPostfix&) = delete;
	void operator=(const TPostfix&) = delete;
	bool IsBracketsCorrect(string& str) const;
	void ToInfix(string& str);
	void ToPostfix();
	vector<string> GetVecOfVariables() const;

public:
	TPostfix(string str) {
		if (!IsBracketsCorrect(str))
			throw string("The brackets in expression are incorrect");
		ToInfix(str);
		ToPostfix();
	}

	vector<string> GetInfix() const { return infix; }

	vector<string> GetPostfix() const { return postfix; }

	string GetStringInfix() const {
		string tmp;
		for (const string& elem : infix)
			tmp += elem + ' ';
		return tmp;
	}

	string GetStringPostfix() const {
		string tmp;
		for (const string& elem : postfix)
			tmp += elem + ' ';
		return tmp;
	}

	double Calculate(bool interface = true,
		vector<double> vecofvalues = {}) const;
};

#endif