#include "queue.h"
#include <gtest.h>
TEST(Tqueue, can_create_queue)
{
	ASSERT_NO_THROW(Tqueue<int>q);
}
TEST(Tqueue, empty_queue_shows_that_empty)
{
	Tqueue<int> q;
	EXPECT_EQ(true, q.is_empty());
}
TEST(Tqueue, queue_can_get_size)
{
	Tqueue<int> q;
	EXPECT_EQ(0, q.size());
}
TEST(Tqueue, can_create_copied_queue)
{
	Tqueue<int> q;
	ASSERT_NO_THROW(Tqueue<int>q1(q));
}
TEST(Tqueue, copied_queue_has_own_memory)
{
	Tqueue<char> q;
	Tqueue<char> q1 = q;
	EXPECT_NE(&q1, &q);
}
TEST(Tqueue, operator_of_indexation_works)
{
	Tqueue<float> q;
	q.push(3.8);
	ASSERT_NO_THROW(q[0]);
}
TEST(Tqueue, operator_of_indexation_throws_when_index_is_too_large)
{
	Tqueue<char> q;
	ASSERT_ANY_THROW(q[1]);
}
TEST(Tqueue, operator_of_indexation_throws_when_index_is_negative)
{
	Tqueue<char> q;
	ASSERT_ANY_THROW(q[-1]);
}
TEST(Tqueue, can_push_element)
{
	Tqueue<int> q;
	q.push(15);
	q.push(3);
	EXPECT_EQ(15, q[0]);
	EXPECT_EQ(3, q[1]);
}
TEST(Tqueue, cant_push_to_full_queue)
{
	Tqueue<int> q;
	for (int i = 0; i < MaxQueueSize; i++)
		q.push(i);
	ASSERT_ANY_THROW(q.push(7));
}
TEST(Tqueue, full_queue_shows_that_full)
{
	Tqueue<int> q;
	for (int i = 0; i < MaxQueueSize; i++)
		q.push(i);
	EXPECT_EQ(false, q.is_empty());
	EXPECT_EQ(true, q.is_full());
}
TEST(Tqueue, can_get_element_without_deleting)
{
	Tqueue<int> q;
	q.push(15);
	EXPECT_EQ(15, q.get());
	EXPECT_EQ(1, q.size());
}
TEST(Tqueue, cant_get_element_from_empty_queue)
{
	Tqueue<int> q;
	ASSERT_ANY_THROW(q.get());
}
TEST(Tqueue, can_pop_element_with_deleting)
{
	Tqueue<int> q;
	q.push(15);
	EXPECT_EQ(15,q.pop());
	EXPECT_EQ(0, q.size());
}
TEST(Tqueue, cant_pop_element_from_empty_queue)
{
	Tqueue<int> q;
	ASSERT_ANY_THROW(q.pop());
}