#ifndef __STACK_H__
#define __STACK_H__

using namespace std;

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;      // стек
  size_t size;  // размер стека
  int top;      // вершина стека

public:
	TStack(size_t _size = 1) : size(_size), top(-1)
	{
		if (size < 1 || size > MaxStackSize) {
			throw invalid_argument("Некорректный размер стека");
		}
		pMem = new T[size];
	}

	~TStack()
	{
	  delete [] pMem;
	}

	TStack(const TStack& stack) : size(stack.size), top(stack.top) // Конструктор копирования
	{
		pMem = new T[size];
		for (int i = 0; i <= top; i++) 
		{
			pMem[i] = stack.pMem[i];
		}
	}

	TStack& operator=(const TStack& other) // Оператор присваивания
	{
		if (this == &other)
		{
			return *this;
		}

		TStack temp(other);

		swap(pMem, temp.pMem);
		swap(size, temp.size);
		swap(top, temp.top);

		return *this;
	}

	bool operator==(const TStack<T>& other) const
	{
		if (GetSize() != other.GetSize()) 
		{
			return false;
		}

		for (size_t i = 0; i < GetSize(); i++) 
		{
			if (pMem[i] != other.pMem[i]) 
			{
				return false;
			}
		}

		return true;
	}

	bool operator!=(const TStack<T>& other) const
	{
		return !(*this == other);
	}

	size_t GetSize() const
	{
		return top + 1;
	}

	bool IsEmpty() const // Метод, определяющий, пуст ли стек
	{
		return top == -1;
	}
   
	bool IsFull() const // Метод, определяющий, полон ли стек
	{
		return top == size - 1;
	}
   
	void Push(const T& val) // Метод для добавления элемента в вершину стека
	{
		if (IsFull()) 
		{
			size *= 2;
			if (size > MaxStackSize)
				throw length_error("Превышен максимально допустимый размер стека");

			T* newMem = new T[size];
			for (int i = 0; i <= top; i++) 
			{
				newMem[i] = pMem[i];
			}
			delete[] pMem;
			pMem = newMem;
		}
		pMem[++top] = val;
	}
   
	T Pop() // Метод для извлечения элемента из вершины стека
	{
		if (IsEmpty()) 
		{
			throw std::underflow_error("Попытка извлечения элемента из пустого стека");
		}
		return pMem[top--];
	}

	T Top() const // Метод для получения значения элемента из вершины стека
	{
		if (IsEmpty()) 
		{
			throw std::underflow_error("Попытка получения элемента из пустого стека");
		}
		return pMem[top];
	}
};

#endif
