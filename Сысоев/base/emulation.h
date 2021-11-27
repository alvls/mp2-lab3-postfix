#ifndef __EMULATION_H__
#define __EMULATION_H__
#include <vector>
#include "Cluster.h"
#include "queue.h"
#include <iostream>
#include <random>
#include <ctime>
#include <locale>
pair<vector<int >, double>create_stats(int task_num, int overflows, int done, int queue_remains, int cluster_remains, double average_load, int downtime);
pair<vector<int>, double> emulation(bool predetermined, double _q = 0, int _max_cycle = 0);
#endif