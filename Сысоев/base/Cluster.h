#ifndef __CLUSTER_H__
#define __CLUSTER_H__
#include "task.h"
#include <vector>
const int MaxClusterProcessors = MaxNecessaryProcessors;
class Cluster
{
	/*struct Node
	{
		Task t;
		Node* next;
		Node* prev;
		Node(Task _t):t(_t),next(nullptr),prev(nullptr)
		{
		}
		Node():next(nullptr), prev(nullptr)
		{
			Task tmp;
			t = tmp;
		}
		Node(const Node& n)
		{
			t = n.t;
			next = n.next;
			prev = n.prev;
		}
		Node& operator=(const Node& n)
		{
			t = n.t;
			next = n.next;
			prev = n.prev;
		}
	};*/
	vector<Task> tasks;//вектор заданий
	int clock_cycle;//номер тактового цикла
	int free_processors;//число свободных процессоров
	int done;//количество выполненных заданий
	int downtime;//время простоя
	int total_load;//общая загрузка кластера
public:
	Cluster::Cluster(int clock=0) :tasks(0), free_processors(MaxClusterProcessors), done(0), downtime(0), total_load(0)
	{
		if (clock < 0)
			throw ans::negative;
		clock_cycle = clock;
	}
	void Cluster::push_back(Task t)
	{
		tasks.push_back(t);
		free_processors -= t.get_processors_num();
	}
	int Cluster::get_free_porcessors() const
	{
		return free_processors;
	}
	void execute();
	int Done()const
	{
		return done;
	}
	int Total_load() const
	{
		return total_load;
	}
	int Downtime()const
	{
		return downtime;
	}
	int size()
	{
		return tasks.size();
	}
};
#endif