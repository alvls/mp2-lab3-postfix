#ifndef __STACK_H__
#define __STACK_H__

#include <cstddef>
#include <stdexcept>

const size_t DefaultStackSize = 16;
const size_t MaxStackSize = 1000000;

template <typename T>
class TStack
{
  T* pMem;
  size_t capacity;
  size_t count;

  void Expand()
  {
    size_t newCapacity = capacity * 2;
    if (newCapacity == 0)
      newCapacity = DefaultStackSize;
    if (newCapacity > MaxStackSize)
      newCapacity = MaxStackSize;

    T* pNew = new T[newCapacity];
    for (size_t i = 0; i < count; i++)
      pNew[i] = pMem[i];
    delete[] pMem;
    pMem = pNew;
    capacity = newCapacity;
  }

public:
  explicit TStack(size_t startCapacity = DefaultStackSize)
  {
    if (startCapacity == 0 || startCapacity > MaxStackSize)
      throw std::out_of_range("TStack: недопустимый размер стека");
    capacity = startCapacity;
    count = 0;
    pMem = new T[capacity];
  }

  TStack(const TStack& other)
  {
    capacity = other.capacity;
    count = other.count;
    pMem = new T[capacity];
    for (size_t i = 0; i < count; i++)
      pMem[i] = other.pMem[i];
  }

  TStack(TStack&& other) noexcept
  {
    pMem = other.pMem;
    capacity = other.capacity;
    count = other.count;
    other.pMem = nullptr;
    other.capacity = 0;
    other.count = 0;
  }

  ~TStack()
  {
    delete[] pMem;
  }

  TStack& operator=(const TStack& other)
  {
    if (this == &other)
      return *this;
    if (capacity != other.capacity)
    {
      T* pNew = new T[other.capacity];
      delete[] pMem;
      pMem = pNew;
      capacity = other.capacity;
    }
    count = other.count;
    for (size_t i = 0; i < count; i++)
      pMem[i] = other.pMem[i];
    return *this;
  }

  size_t Size() const { return count; }
  size_t Capacity() const { return capacity; }
  bool IsEmpty() const { return count == 0; }
  bool IsFull() const { return count == MaxStackSize; }

  void Push(const T& value)
  {
    if (IsFull())
      throw std::overflow_error("TStack: стек переполнен");
    T copy = value;
    if (count == capacity)
      Expand();
    pMem[count] = copy;
    count++;
  }

  T Pop()
  {
    if (IsEmpty())
      throw std::underflow_error("TStack: извлечение из пустого стека");
    count--;
    return pMem[count];
  }

  T& Top()
  {
    if (IsEmpty())
      throw std::underflow_error("TStack: стек пуст, вершины нет");
    return pMem[count - 1];
  }

  const T& Top() const
  {
    if (IsEmpty())
      throw std::underflow_error("TStack: стек пуст, вершины нет");
    return pMem[count - 1];
  }

  void Clear() { count = 0; }

  bool operator==(const TStack& other) const
  {
    if (count != other.count)
      return false;
    for (size_t i = 0; i < count; i++)
      if (!(pMem[i] == other.pMem[i]))
        return false;
    return true;
  }

  bool operator!=(const TStack& other) const
  {
    return !(*this == other);
  }
};

#endif
