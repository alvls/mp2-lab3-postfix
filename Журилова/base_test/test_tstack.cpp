#include "stack.h"
#include <gtest.h>
//Создание стека с правильной длиной(размером)
TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(10));//Ожидание отсутствия исключений
}
//Создание стека с отрицательной(ым) длиной(размером)
TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-10));//Ожидание исключений
}
//Создание стека с недопустимо большим размером
TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));//Ожидание исключений
}
//Попытка добавления элемента в переполненный стек
TEST(TStack, cant_push_if_stack_full)
{
	TStack<int> st(5);//Создали стек
	for (int i = 0; i < 5; i++)//Заполнили
		st.push(i);
	//Попытка положить 6 в 6 элемент из 5
	ASSERT_ANY_THROW(st.push(6));//Ожидание исключений
}
//Попытка взятия элемента из пустого стек
TEST(TStack, cant_pop_if_stack_empty)
{
	TStack<int> st(3);//Создали стек(он пуст)
	//Попытка взять элемент из пустого стека
	ASSERT_ANY_THROW(st.pop());//Ожидание исключений
}
//Проверка на правильность push и pop
TEST(TStack, can_push_and_pop_element)
{
	TStack<int> st(4);//Создали стек(он пуст)
	st.push(10);//Положили в него число 10
	//10 = элемент из стека?
	EXPECT_EQ(10, st.pop());//Ожидание равенства
}
//Проверка полноты верна?
TEST(TStack, function_full_is_correct)
{
	TStack<int> st(2);//Создали стек(он пуст)
	EXPECT_EQ(st.full(), false);//Ожидание равенства(стек пока не заполнен)
	//Заполнили стек
	st.push(0);
	st.push(1);
	EXPECT_EQ(st.full(), true);//Ожидание равенства(стек заполнен)
}
//Проверка пустоты верна?
TEST(TStack, function_empty_is_correct)
{
	TStack<int> st(2);//Создали стек(он пуст)
	EXPECT_EQ(st.empty(), true);//Ожидание равенства(стек пуст)
	st.push(0);//Положили в стек элемент
	EXPECT_EQ(st.empty(), false);//Ожидание равенства(стек не пуст)
}