#include "Cluster.h"	
void Cluster::execute()
{
	if (tasks.size() == 0)
		downtime++;
	else
		for (int i = 0; i < tasks.size(); i++)
		{
			if (tasks[i].is_new())
				tasks[i].start(clock_cycle);
			if (tasks[i].execute())
			{
				total_load += tasks[i].get_processors_num();
				free_processors += tasks[i].get_processors_num();
				tasks.erase(tasks.begin() + i);
				done++;
			}
			else
				total_load += tasks[i].get_processors_num();
		}
	clock_cycle++;
}
