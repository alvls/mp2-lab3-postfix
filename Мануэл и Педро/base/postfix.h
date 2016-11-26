#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

const int SIZE_OF_TABLE = 11;  
const string FILE_NAME = "table_operation.txt";

class TPostfix
{
	
	struct SOperation
	{
		string operation;
		int quanity_arguments;
		int priority;
	};

  enum StatusPostfix{converted , not_converted};


  StatusPostfix status ;                       // статус поле tpostfix
  SOperation table[SIZE_OF_TABLE];             // таблицa
  vector<string> infix;
  vector<string> postfix;


  vector<string> ToPostfix();                  // метод переводит из инфиксной формы в постфиксную
  void splitString(string );
  void createTable();
  int searchInTable(string)  ;                 //поиск элемента по таблице


public:

  TPostfix(string str);
  string getInfix() const 
  {
	  string inf;
	  for(int i = 0 ; i < infix.size();i++)
		  inf += infix[i];
	  return inf;
  }
  string getPostfix();
  double Calculate();                         // Ввод переменных, вычисление по постфиксной форме

};

bool isNumber(string str);



#endif