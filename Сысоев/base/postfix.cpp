#include "postfix.h"
#include "stack.h"

string TPostfix::ToPostfix()
{
  postfix = string("ab+");
  return postfix;
}

double TPostfix::Calculate()
{
  return 0;
}
