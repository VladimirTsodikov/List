#include <iostream>
#include "Linear_List.h"


int main()
{
	List<> a;
	int num;
	std::cout << "Enter the number of items in the list:\n";
	std::cin >> num;

	int t;
	List<>::iterator it(a.begin());		//����� �� �� �����, ��� � a.end()
	for (int i = 0; i < num; i++)
	{
		std::cin >> t;
		a.insert(t, *it);
		++it;
	}
	//a.Print();
	

	//���������� ���������� ������. ������ ����� ���� � �������� �������.  ����� �� ����� - ������� �������� ������ Print

	List<>::iterator it_next=a.begin()->next;
	List<>::iterator it_next_next=it_next->next;
	
	it = a.begin();
	it->next = *a.end();
	
	for (it = a.begin(); it != a.end(); )
	{
		it_next->next = *it;
		it = it_next;
		it_next = it_next_next;
		++it_next_next;
	}

	a.Print();
}