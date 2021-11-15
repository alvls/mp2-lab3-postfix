#ifndef __STACK_H__
#define __STACK_H__

const int MAX_STACK_SIZE = 100;

template <typename T>
class TStack
{
  T *pMem;
  int size;
  int top = -1;
public:
  TStack(int _size);
  TStack(int _size, T value);
  TStack(const TStack& object);
  ~TStack();
  T back();
  T pop();
  void push(const T& object);
  int stack_size();
  int current_size();
  bool is_empty();
  bool is_full();
  bool operator== (const TStack& object) const;
  bool operator!=(const TStack& object) const;
  TStack& operator=(const TStack& object);
};

template <typename T>
TStack<T>::TStack(int _size) {
  size = _size;
  if (size < 1 || size > MAX_STACK_SIZE)
    throw "wrong size.";
  pMem = new T[size];
}

template <typename T>
TStack<T>::TStack(int _size, T value) {
  size = _size;
  if (size < 1 || size > MAX_STACK_SIZE)
    throw "wrong size.";
  pMem = new T[size];
  pMem[++top] = value;
}

template <typename T>
TStack<T>::TStack(const TStack& object) {
  size = object.size;
  pMem = new T[size];
  std::copy (object.pMem, object.pMem + object.size, pMem);
}

template <typename T>
TStack<T>::~TStack() {
  delete[] pMem;
}

template <typename T>
T TStack<T>::back() {
  return pMem[top];
}

template <typename T>
T TStack<T>::pop() {
  return pMem[top--];
}

template <typename T>
void TStack<T>::push(const T& object) {
  pMem[++top] = object;
}

template <typename T>
int TStack<T>::stack_size() {
  return size;
}

template <typename T>
int TStack<T>::current_size() {
  return top + 1;
}

template <typename T>
bool TStack<T>::is_empty() {
  return top == -1;
}

template <typename T>
bool TStack<T>::is_full() {
  return top == size - 1;
}

template <typename T>
bool TStack<T>::operator==(const TStack& object) const {
  if (size != object.size)
    return false;
  for (int i = 0; i < size; i++) {
    if (pMem[i] != object.pMem[i])
      return false;
  }
  return true;
}

template <typename T>
bool TStack<T>::operator!=(const TStack& object) const {
  return !(*this == object);
}

template <typename T>
TStack<T>& TStack<T>::operator=(const TStack& object) {
  if (this == &object)
    return *this;
  size = object.size;
  T* ptr = new T[size];
  delete[] pMem;
  pMem = ptr;
  std::copy (object.pMem, object.pMem + object.size, pMem);
  return *this;
}

#endif
