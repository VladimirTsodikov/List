#include "Linear_List.h"
#include <gtest.h>

TEST(Iterator, can_create_iterator)
{
	List<> a;
	ASSERT_NO_THROW(List<>::iterator it(a.begin()));
}

TEST(Iterator, copy_constructor_available)
{
	List<> a;
	List<>::iterator it_1(a.begin());
	ASSERT_NO_THROW(List<>::iterator it_2(it_1));
}

TEST(Iterator, operator_of_redeference_available)
{
	List<> a;
	List<>::iterator it(a.begin());
	ASSERT_NO_THROW(*it);
}

TEST(Iterator, operator_of_arrowhead_available_and_correct)
{
	List<> a(21);
	List<>::iterator it(a.begin());
	ASSERT_NO_THROW(it->data);
	EXPECT_EQ(21, it->data);
}

TEST(Iterator, operator_of_prefix_plus_plus_is_correct)	
{
	List<> a(21);
	a.insert(14, 2);
	List<>::iterator it(a.begin());
	++it;
	EXPECT_EQ(it->data, 14);

}

TEST(Iterator, operator_of_equal_is_correct)
{
	List<> a(21);
	List<>::iterator it_1(a.begin());
	List<>::iterator it_2(a.begin());
	ASSERT_TRUE(it_1 == it_2);
}

TEST(Iterator, operator_of_not_equal_is_correct)
{
	List<> a(21);
	a.insert(14, 2);
	List<>::iterator it_1(a.begin());
	List<>::iterator it_2(++a.begin());
	ASSERT_TRUE(it_1 != it_2);
}

TEST(List, can_create_int_list_with_head)
{
	ASSERT_NO_THROW(List<> a);
}

TEST(List, can_create_double_list_with_head)
{
	ASSERT_NO_THROW(List<double> a);
}

TEST(List, constructor_with_parameter_is_available_and_correct)
{
	ASSERT_NO_THROW(List<> a(21));
	
	List<> b(14);
	EXPECT_EQ(14, b.begin()->data);
}

TEST(List, can_insert_in_first_position_correctly)
{
	List<> a; a.insert(2);		//случай, когда изначально список пуст
	List<> b(12); b.insert(2);	//случай, когда в нЄм есть элементы

	EXPECT_EQ(2, a.begin()->data);
	EXPECT_EQ(2, b.begin()->data);

}

TEST(List, can_insert_in_last_position_correctly)
{
	List<>a(23); a.insert(24); a.insert(25); a.insert(26);	//4 элемента в списке
	a.insert(27, 5);		//вставл€ем на максимально возможную, п€тую позицию
	List<>::iterator it(a.begin());
	for (int i = 1; i < 5; i++)
		++it;

	EXPECT_EQ(27, it->data);

}

TEST(List, can_insert_in_middle_position_correctly)
{
	List<>a(23); a.insert(24); a.insert(25); a.insert(26); //4 элемента в списке
	a.insert(9, 3);
	List<>::iterator it(a.begin());
	for (int i = 1; i < 3; i++)
		++it;

	EXPECT_EQ(9, it->data);
}

TEST(List, throw_then_incorrect_position_insert)
{
	List<>a(23);
	ASSERT_ANY_THROW(a.insert(7, 3));	//т.к. вставл€ть тут можно только на 1 или 2 позиции
}

TEST(List, can_erase_element_by_index)
{
	List<>a(11); 
	a.insert(12, 2);
	ASSERT_NO_THROW(a.erase(1));
	EXPECT_EQ(12, a.begin()->data);
}

TEST(List, throw_then_incorrect_position_erase)
{
	List<> a(-3);
	ASSERT_ANY_THROW(a.erase(5));
}

TEST(List, can_search_element_by_value_correctly)
{
	List<>a(11); a.insert(3); a.insert(7); a.insert(-18); a.insert(4);
	EXPECT_EQ(true, a.search(3));
	EXPECT_EQ(false, a.search(18));
}

TEST(List, can_check_for_emptiness_correctly)
{
	List<> a(11); a.insert(3);
	EXPECT_EQ(false, a.empty());

	a.erase(1); a.erase(1);
	EXPECT_EQ(true, a.empty());
}

TEST(List, can_return_front_correctly)
{
	List<> a(43); EXPECT_EQ(43, a.front());
	a.insert(26); EXPECT_EQ(26, a.front());
	a.erase(1); a.erase(1); ASSERT_ANY_THROW(a.front());
}

TEST(List, can_clear_list)
{
	List<> a(8); a.insert(9); a.insert(10);
	ASSERT_NO_THROW(a.clear());
	EXPECT_EQ(true, a.empty());
}

TEST(List, return_count_of_elements_correctly)
{
	List<> a; EXPECT_EQ(0, a.GetCount());
	a.insert(6), a.insert(-34); EXPECT_EQ(2, a.GetCount());
	a.clear(); EXPECT_EQ(0, a.GetCount());
}