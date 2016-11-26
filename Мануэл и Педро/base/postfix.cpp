#include "postfix.h"

#include "stack.h"



vector<string> TPostfix::ToPostfix()

{ 

	TStack<string>stack(infix.size());

	for(int i = 0 ;i < infix.size();i++)

	{

		if(searchInTable(infix[i]) == -1 )

		{

			postfix.push_back(infix[i]);

			continue;

		}

		if(infix[i] == string("("))

		{

			stack.push(infix[i]);

			continue;

		}

		if(searchInTable(infix[i]) != -1)

		{

			if(infix[i] == string(")"))

			{

				while(stack.getTopElem() != string("(") )

				{

					postfix.push_back(stack.pop());

				}

				stack.pop();

				continue;

			}

			while(!stack.isEmpty())

			{

				if(table[searchInTable(infix[i])].priority <= table[searchInTable(stack.getTopElem())].priority)

					postfix.push_back(stack.pop());

				else

				{

					stack.push(infix[i]);

					break;

				}

				

			}

			if(stack.isEmpty())

			{

				stack.push(infix[i]);

				continue;

			}

	    }

	

	 }



	while(!stack.isEmpty())

		postfix.push_back(stack.pop());



	return postfix;

}

	

  



void TPostfix::createTable()

{

	ifstream fin(FILE_NAME);

	for(int i = 0 ; i < SIZE_OF_TABLE;i++)

		fin >> table[i].operation >> table[i].priority >> table[i].quanity_arguments;

	fin.close();

}



TPostfix::TPostfix(string str)

{

	status = not_converted;                  //ïîñòôèêñíàÿ ôîðìà åùå íå ñôîðìèðîâàíà 

	createTable();                           //ñîçäàåì òàáëèöó  

	splitString(str);                        //ðàçáèâàåì ñòðîêó íà ýëåìåíòû 

}	









int TPostfix::searchInTable(string symb)

{

	for(int i = 0 ; i < SIZE_OF_TABLE;i++)

		if(table[i].operation == symb) return i;

	return -1;



}

string TPostfix::getPostfix()

{

	if(status == not_converted)

	{

		postfix = ToPostfix();

		status = converted;

	}
	string post;
	for(int i = 0 ; i < postfix.size();++i)
		post += postfix[i];

	return post;

}



void TPostfix::splitString(string str)

{

	

	string s = "";

	
	int i = 0;

	
	const string bao = "()+-*/^";             // basic_arithmetic_operations
	if(str[0] == '-')
		infix.push_back("0");
	

	for(int i = 0; i < str.length();i++) 

	{
		if(i > 0 && str[i] == '-' && str[i-1] == '(')
			infix.push_back("0");

		if(bao.find(str[i]) != string::npos )

			{

				if(s != "")

				{

					infix.push_back(s);

					s = str[i];

					infix.push_back(s);

					s = "";

					

					continue;

				}

				s = str[i];

				infix.push_back(s);

				s = "";

				

				continue;

			}

			if(str[i] == ' ')

			{

				

				continue;

			}

			s += str[i];

			

	}

	if(s != "")
		infix.push_back(s);
	
}


double TPostfix::Calculate()

{

	TStack<double>stack(postfix.size());

	for(int i = 0 ; i < postfix.size();i++)

	{

		double val;

		if(searchInTable(postfix[i]) == -1)                           // åñëè îïåðàíä òî ââîäèì åãî çíà÷åíèÿ è êëàäåì â ñòåê

		{

			if(!isNumber(postfix[i]))

			{

			cout << endl << "Enter : " << postfix[i] << endl;

			cin >> val;

			stack.push(val);

			}



			else                                                             //number

			{

				stack.push(atoi(postfix[i].c_str()));			

			}

		}

		else

		{

			

			if(postfix[i] == "+"){

				stack.push(stack.pop() + stack.pop());

				continue;}



			if(postfix[i] == "-"){

				double right = stack.pop();
				double left = stack.pop();
				stack.push(left - right);

				continue;}



			if(postfix[i] == "*"){

				stack.push(stack.pop() * stack.pop());

				continue;}



			if(postfix[i] == "/"){
				double right = stack.pop();
				double left = stack.pop();
				stack.push(left / right);
				

				continue;
			}



			if(postfix[i] == "^"){

				stack.push(pow(stack.pop(),stack.pop()));

				continue;}



			if(postfix[i] == "sin"){

				stack.push(sin(stack.pop()));

				continue;}



			if(postfix[i] == "cos"){

				stack.push(cos(stack.pop()));

				continue;}



			if(postfix[i] == "tg"){

				stack.push(tan(stack.pop()));

				continue;}



			if(postfix[i] == "ctg"){

				stack.push(1 / tan(stack.pop()));

				continue;}

					

					

		}

		

	

	}

	return stack.pop();

}



bool isNumber(string str)

{

	string num = "1234567890";

	int size = str.size();

	for(int i = 0 ; i < size;i++)

	{

		if(num.find(str[i]) == string::npos)

			return false;

	}

	return true;

	

}                                                          