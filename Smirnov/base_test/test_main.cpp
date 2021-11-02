#include <gtest.h>
#include <iostream>
#include <stack.h>
#include <postfix.h>
#include <postfix.cpp>

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
