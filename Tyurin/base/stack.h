#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;
using namespace std;

template <class T>
class TStack
{
   T* pMem;
   size_t size;
   int top;

public:

   TStack(size_t _size = MaxStackSize) : size(_size), top(-1)
   {
      if ((size < 1) || (size > MaxStackSize))
         throw "Invalid Size";
      pMem = new T[size];
   }

   TStack(const TStack& otherStack) : size(otherStack.size), top(otherStack.top), pMem(new T[otherStack.size])
   {
      copy(otherStack.pMem, otherStack.pMem + top + 1, pMem);
   }

   ~TStack() { delete[] pMem; }

   bool isEmpty() const { return top == -1; }

   size_t getSize() const { return top + 1; }

   T getTopElem()
   {
      if (top < 0)
         throw "Stack is Empty";
      return pMem[top];
   }

   void Push(const T& value)
   {
      if (top == size - 1)
         throw "Stack Overflow";
      pMem[++top] = value;
   }

   T Pop()
   {
      if (top < 0)
         throw "Stack is Empty";
      return pMem[top--];
   }

   TStack& operator=(TStack otherStack)
   {
      if (this != &otherStack) {
         T* tmp_pMem = new T[otherStack.size];
         top = otherStack.top;
         size = otherStack.size;
         delete[] pMem;
         pMem = tmp_pMem;
         for (size_t i = 0; i < size; i++)
         {
            pMem[i] = otherStack.pMem[i];
         }
      }
      return *this;
   }
};

#endif
