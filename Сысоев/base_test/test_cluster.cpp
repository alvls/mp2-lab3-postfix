#include <gtest.h>
#include "Cluster.h"
TEST(Cluster, can_create_cluster)
{
	ASSERT_NO_THROW(Cluster c);
}
TEST(Cluster, throws_when_clock_cycle_is_negative)
{
	ASSERT_ANY_THROW(Cluster c(-1));
}
TEST(Cluster, can_push_element)
{
	Cluster c;
	Task t(1, 3, 5);
	ASSERT_NO_THROW(c.push_back(t));
}
TEST(Cluster, function_of_execution_works)
{
	Cluster c(2);
	Task t(1, 3, 5);
	c.push_back(t);
	for (int i = 0; i < 3; i++)
		c.execute();
	EXPECT_EQ(5 * 3, c.Total_load());
	c.execute();
	EXPECT_EQ(1, c.Downtime());
	EXPECT_EQ(5 * 3, c.Total_load());
	EXPECT_EQ(MaxClusterProcessors, c.get_free_porcessors());
	EXPECT_EQ(1, c.Done());
}