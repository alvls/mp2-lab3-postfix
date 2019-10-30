#include "postfix.h"
#include <gtest.h>
//Проверка создания постфикса
TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);//Ожидание отсутствия исключений
}
//Проверка создания постфикса с недопустимым символом
TEST(TPostfix, cant_create_postfix_with_bad_symbols)
{
	//Попытка создать выражение с символами ! и &
	ASSERT_ANY_THROW(TPostfix p("a+b&c!d"));//Ожидание исключений
}
//Проверка работы метода ToPostfix
TEST(TPostfix, convert_infix_to_postfix)
{
	TPostfix p("a+b/c*d-h+k");//Создали выражение
	p.ToPostfix();//Вызвали метод преобразования
	EXPECT_EQ(p.GetPostfix(), "abc/d*+h-k+");//Ожидание равенства
}
//Проверка, в случае если infix сосотоит только из пробелов
TEST(TPostfix, throws_when_infix_with_spaces_only)
{
	ASSERT_ANY_THROW(TPostfix p("      "));//Ожидание исключений
}
//Проверка, выражение заканчивается некорректно
TEST(TPostfix, throws_when_operation_behind)
{
	ASSERT_ANY_THROW(TPostfix p("a-b*"));//Ожидание исключений
}
//Проверка, выражение начинается некорректно
TEST(TPostfix, throws_when_operation_ahead)
{
	ASSERT_ANY_THROW(TPostfix p("+a-b"));//Ожидание исключений
}
//Проверка, ошибка в записи скобок (слишком много "(")
TEST(TPostfix, throws_when_too_many_left_brackets)
{
	ASSERT_ANY_THROW(TPostfix p("(a+(b*c)"));//Ожидание исключений
}
//Проверка, ошибка в записи скобок (слишком много ")")
TEST(TPostfix, throws_when_too_many_right_brackets)
{
	ASSERT_ANY_THROW(TPostfix p("(a+(b*c))+d))"));//Ожидание исключений
}
//Проверка, постфикс с переменными идущими подряд
TEST(TPostfix, cant_create_postfix_with_long_names)
{
	ASSERT_ANY_THROW(TPostfix p("a+bcd"));//Ожидание исключений
}
//Попытка обработать выражение со скобками
TEST(TPostfix, convert_infix_with_brackets)
{
	TPostfix p("(a+b)*c");//Создали выражение
	p.ToPostfix();//Применили метод преобразования
	EXPECT_EQ(p.GetPostfix(), "ab+c*");//Ожидание равенства
}
//Равные выражения преобразуются в один итот же результат
TEST(TPostfix, convert_equal_expression)
{
	TPostfix p1("(a+b)");//Создали первое выражение
	p1.ToPostfix();//Применили метод преобразования
	TPostfix p2("a+b");//Создали второе выражение
	p2.ToPostfix();
	EXPECT_EQ(p1.GetPostfix(), p2.GetPostfix());//Ожидание равенства
}
//Проверка работы метода calculate
TEST(TPostfix, calculation_is_correct)
{
	TPostfix p("(5+6)*2");//Создали выражение
	p.ToPostfix();//Применили метод преобразования
	EXPECT_EQ(p.Calculate(), 22);//Ожидание равенства
}

