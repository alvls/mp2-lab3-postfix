#include <iostream>
#include <string>
#include "postfix.h"
#include "operations.h"

using namespace std;

void cleaner()
{
	while (getchar() != '\n');
	cin.clear();
}

int main()
{
	int exitprog = 1; // Проверка на выход из программы
	while (exitprog != 2)
	{
		cout << "\n\tRules:\n\t0) You can write as many spaces as you want\n";
		cout << "\t1) Variable names are entered without spaces\n\t(for example, not like \"a b\" but like \"ab\")\n";
		cout << "\t2) The variable name does not start with a digit\n";
		cout << "\t3) Floating-point numbers are written with a dot (for example: 3.7)\n";
		cout << "\t4) Supported operations:\n\t" << Operations::str_op() << "\n\n";
		try
		{
			string expression;
			cout << "Enter an arithmetic expression: ";
			getline(cin, expression);
			TPostfix postfix(expression);
			cout << "\nArithmetic expression:\n" << postfix.GetStringInfix() << endl;
			cout << "\nPostfix form:\n" << postfix.GetStringPostfix() << endl;
			int exitloop = 1;
			while (exitloop != 2)
			{
				double res = postfix.Calculate();
				cout << "\nResult:\n" << res << endl;
				cout << "\nContinue processing of the current postfix form?\n(a special thing for working with other variable values)\n\t1 - Yes\n\t2 - No\n\t";
				cin >> exitloop;
				cleaner();
			}
			cout << "\nContinue using the program?\n\t1 - Yes\n\t2 - No\n\t";
			cin >> exitprog;
			cleaner();
			system("cls");
		}
		catch (string exc)
		{
			cout << '\n' << exc << '\n';
		}
	}
	system("pause");
	return 0;
}
