#pragma once
#include "queue.h"
const int MaxNecessaryProcessors = 32;//максимальное число необходимых процессоров
const int MaxDuration = 6;//максимальная длительность работы
using namespace std;
class Task
{
	int appearance;//такт появления
	int duration;//длительность работы
	int processors_num;//число необходимых процессоров
	int begin_of_execution;//номер такта, на котором начинается выполнение
	int remains;//остаток времени выполнения
public:
	Task(int _ap = 0, int _d = 0, int _pr = 0) :begin_of_execution(-1)
	{
		if (_ap < 0)
			throw ans::negative;
		appearance = _ap;
		if (_d > MaxDuration)
			throw ans::too_large;
		if (_d < 0)
			throw ans::negative;
		duration = _d;
		if (_pr > MaxNecessaryProcessors)
			throw ans::too_large;
		if (_pr < 0)
			throw ans::negative;
		processors_num = _pr;
		remains = duration;
	}
	int get_processors_num() const
	{
		return processors_num;
	}
	bool execute()
	{
		remains--;
		return !(remains > 0);
	}
	bool is_new() const
	{
		return !(begin_of_execution > -1);
	}
	void start(int clock_cycle_num)
	{
		if (clock_cycle_num < 0)
			throw ans::negative;
		if (!is_new())
			throw ans::too_large;
		begin_of_execution = clock_cycle_num;
	}
};