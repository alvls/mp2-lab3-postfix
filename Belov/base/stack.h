#ifndef __STACK_H__
#define __STACK_H__

#include <stdexcept>

const int MAX_STACK_SIZE = 100;

using namespace std;

template<class T>
class TDynamicList
{
private:
	size_t length;
	size_t memSize;
	T* pMem;

public:
	//TDynamicList() : length(0), memSize(1), pMem(new T[memSize]) { }
	TDynamicList(size_t capacity = 5) : memSize(capacity > 0 ? capacity : throw invalid_argument("List capacity must be positive")), length(0), pMem(new T[capacity]) { }
	~TDynamicList() { delete[] pMem; }

	size_t size() const { return length; }
	bool is_empty() const { return length == 0; }

	void add(const T& value)
	{
		if (length == memSize)
		{
			memSize *= 2;
			T* tmpMem = new T[memSize];
			std::copy(pMem, pMem + length, tmpMem);
			delete[] pMem;
			pMem = tmpMem;
		}
		pMem[length++] = value;
	}

	void remove(size_t index)
	{
		copy(pMem + index + 1, pMem + length, pMem + index);
		length--;
	}

	T& operator[](const size_t index)
	{
		return pMem[index];
	}
	const T& operator[](const size_t index) const
	{
		return pMem[index];
	}

	TDynamicList& operator=(const TDynamicList& other)
	{
		if (this == &other)
			return *this;

		TDynamicList<T> tmp(other);
		swap(*this, tmp);
		return *this;
	}

	TDynamicList& operator=(TDynamicList&& other) noexcept
	{
		swap(*this, other);
		return *this;
	}

	friend void swap(TDynamicList& lhs, TDynamicList& rhs) noexcept
	{
		swap(lhs.pMem, rhs.pMem);
		swap(lhs.capacity, rhs.capacity);
		swap(lhs.length, rhs.length);
	}
};

template<typename T>
class TStack
{
private:
	TDynamicList<T> list;

public:
	TStack(size_t capacity = 6) : list(capacity <= MAX_STACK_SIZE ? capacity : throw out_of_range("Stack size must not exceed the allowed value")) { }

	void push(const T& element)
	{
		if (size() == MAX_STACK_SIZE)
		{
			throw length_error("Stack overflow");
		}
		list.add(element);
	}

	T top()
	{
		if (list.size() == 0)
		{
			throw logic_error("Stack is empty");
		}
		return list[list.size() - 1];
	}

	T pop()
	{
		if (list.size() == 0)
		{
			throw logic_error("Stack is empty");
		}
		T tmp = list[list.size() - 1];

		list.remove(list.size() - 1);
		return tmp;
	}

	bool is_empty() const noexcept(noexcept(list.is_empty()))
	{
		return list.is_empty();
	}

	size_t size() const noexcept(noexcept(list.size()))
	{
		return list.size();
	}
};

#endif
