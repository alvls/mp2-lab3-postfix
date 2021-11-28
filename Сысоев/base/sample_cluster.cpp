#include <iostream>
#include <string>
#include "emulation.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	const int max_string = 6;
	string message[7] = { "Число появившихся заданий: ","Число отказов из-за переполнения очереди: ", "Число выполненных заданий: ", "Число заданий, оставшихся в очереди: ", "Число заданий, оставшихся в кластере: ", "Средняя нагрузка кластера: ", "Число тактов простоя кластера: " };
	pair<vector<int>, double> res = emulation(false);
	for (int i = 0; i < 5; i++)
	{
		cout << message[i] << res.first[i] << endl;
	}
	cout << message[5] << res.second << endl;
	cout << message[6] << res.first[5] << endl;
	system("pause");
}
