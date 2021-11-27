#include <gtest.h>
#include "task.h"
TEST(Task, can_create_task)
{
	ASSERT_NO_THROW(Task t);
}
TEST(Task, can_create_task_with_params)
{
	ASSERT_NO_THROW(Task t(1, 3, 5));
}
TEST(Task, throws_when_appearance_is_negative)
{
	ASSERT_ANY_THROW(Task t(-1, 3, 5));
}
TEST(Task, throws_when_duration_is_too_large)
{
	ASSERT_ANY_THROW(Task t(1, MaxDuration + 1, 5));
}
TEST(Task, throws_when_duration_is_negative)
{
	ASSERT_ANY_THROW(Task t(1, -3, 5));
}
TEST(Task, throws_when_processors_num_is_too_large)
{
	ASSERT_ANY_THROW(Task t(1, 3, MaxNecessaryProcessors + 1));
}
TEST(Task, throws_when_processors_num_is_negative)
{
	ASSERT_ANY_THROW(Task t(-1, 3, -1));
}
TEST(Task, can_get_processors_num)
{
	Task t(1, 3, 5);
	EXPECT_EQ(5, t.get_processors_num());
}
TEST(Task, can_start)
{
	Task t(1, 3, 5);
	ASSERT_NO_THROW(t.start(3));
}
TEST(Task, cant_start_with_negative_clock_cycle)
{
	Task t(1, 3, 5);
	ASSERT_ANY_THROW(t.start(-1));
}
TEST(Task, cant_start_more_then_one_time)
{
	Task t(1, 3, 5);
	t.start(3);
	ASSERT_ANY_THROW(t.start(1));
}
TEST(Task, can_get_is_new)
{
	Task t(1, 3, 5);
	EXPECT_EQ(true, t.is_new());
	t.start(3);
	EXPECT_EQ(false, t.is_new());
}
TEST(Task, function_of_execution_works)
{
	Task t(1, 3, 5);
	for (int i = 0; i < 2; i++)
		EXPECT_EQ(false, t.execute());
	EXPECT_EQ(true, t.execute());
}