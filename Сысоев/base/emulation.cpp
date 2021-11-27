#include "emulation.h"
using namespace std;
pair<vector<int >,double>create_stats(int task_num,int overflows,int done, int queue_remains, int cluster_remains, double average_load,int downtime)
{
	pair<vector<int>, double>stats;
	stats.first = { task_num, overflows, done, queue_remains, cluster_remains, downtime };
	stats.second = average_load;
	return stats;
}
pair<vector<int>,double> emulation(bool predetermined,double _q, int _max_cycle)
{
	double q;
	double max_cycle;
	if (predetermined == true)
	{
		q = _q;
		max_cycle = _max_cycle;
	}
	else
	{
		cout << "¬ведите число от нул€ до единицы. ќно будет обратно веро€тности по€влени€ нового задани€. ƒробную часть отдел€йте точкой\n";
		cin >> q;
		cout << "¬ведите номер последнего цикла\n";
		cin >> max_cycle;
	}
	Tqueue<Task> queue;//очередь заданий
	Cluster cluster(0);//единственный кластер
	double q1;
	unsigned int tmp_q;
	mt19937 generate(time(NULL));
	int overflows = 0;//число ошибок из-за переполнени€ очереди
	int task_num = 0;//число по€вившихс€ заданий
	for (int i = 0; i < max_cycle; i++)
	{
		tmp_q = generate();
		q1 = double(tmp_q) / double(generate.max());
		if (q1 >= q)
		{
			try
			{
				Task t(i, 1 + generate() % MaxDuration, 1 + (generate() % MaxNecessaryProcessors));
				task_num++;
				queue.push(t);
			}
			catch (...)
			{
				overflows++;
			}
		}
		while (!queue.is_empty())
			if (cluster.get_free_porcessors() >= queue.get().get_processors_num())
				cluster.push_back(queue.pop());
			else
				break;
		cluster.execute();
	}
	double average_load = double(cluster.Total_load()) / double(max_cycle * MaxClusterProcessors);//средн€€ нагрузка кластера
	return create_stats(task_num, overflows, cluster.Done(), queue.size(), cluster.size(), average_load, cluster.Downtime());

}