#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>
#pragma once 

using namespace std;
//////////////////////////////////////////////////стэк
template<class t>
class stack {
	int r, rr;
	t*cont;
public:
	stack();
	stack(const stack& s);
	stack(const int g);
	~stack();
	void push(const t& el);
	int size();
	bool empty();
	t pop();
	const t& onthetop();
	bool operator==(stack s);
	stack& operator=(const stack& s);
};

template <class t>
stack<t>::stack() {
	r = 0;
	rr = 8;
	cont = new t[rr];
	for (int i = 0; i < rr; i++)
		cont[i] = 0;
}

template <class t>
stack<t>::stack(const int g) {
	r = g;
	rr = g;
	cont = new t[rr];
	for (int i = 0; i < rr; i++)
		cont[i] = 0;
}

template<class t>
stack<t>::stack(const stack<t>& s) {
	int i;
	r = s.r;
	rr = s.rr;
	cont = new t[rr];
	for (i = 0; i < r; i++)
		cont[i] = s.cont[i];
	for (i = r; i < rr; i++)
		cont[i] = 0;
}

template<class t>
stack<t>::~stack() {
	delete[] cont;
}

template<class t>
void stack<t>::push(const t& el) {
	if (r == rr) {
		int i;
		rr = r + r / 3;
		t* b = new t[r];
		for (i = 0; i < r; i++)
			b[i] = cont[i];
		delete[] cont;
		cont = new t[rr];
		for (i = 0; i < r; i++)
			cont[i] = b[i];
		delete[] b;
		for (i = r; i < rr; i++)
			cont[i] = 0;
		cont[r] = el;
		r++;
	}
	else {
		cont[r] = el;
		r++;
	}
}

template<class t>
int stack<t>::size() {
	return r;
}

template<class t>
bool stack<t>::empty() {
	if (r == 0)
		return true;
	else return false;
}

template<class t>
t stack<t>::pop() {
	if (!(this->empty())) {
		if ((r = rr / 3) && (r > 8)) {
			int i;
			rr = r * 2;
			t* b = new t[rr];
			for (i = 0; i < r; i++)
				b[i] = cont[i];
			delete[] cont;
			cont = b;
			for (i = r; i < rr; i++)
				cont[i] = 0;
			delete[] b;
			cont[r - 1] = 0;
			r--;
		}
		else {
			cont[r - 1] = 0;
			r--;

		}
	}
	else
		throw "not correct";
	return cont[r - 1];
}

template<class t>
const t& stack<t>::onthetop() {
	if (this->empty())
		throw "not correct";
	else
		return cont[r - 1];
}

template<class t>
bool stack<t>::operator==(stack<t> s) {
	if (this != &s) {
		bool a = false;
		if (r == s.r) {
			int summa = 0;
			for (int i = 0; i < r; i++)
				if (cont[i] == s.cont[i])
					summa++;
			if (summa == r)
				a = true;
		}
		return a;
	}
	else
		return true;
}

template<class t>
stack<t>& stack<t>::operator=(const stack<t>& s) {
	if (this != &s) {
		int i;
		delete[] cont;
		r = s.r;
		rr = s.rr;
		cont = new t[rr];
		for (i = 0; i < r; i++)
			cont[i] = s.cont[i];
		for (i = r; i < rr; i++)
			cont[i] = 0;
	}
	return *this;
}


#endif
