#include <iostream>
#include "Linear_List.h"


int main()
{
	List<> a(2);
	a.Print(); std::cout << std::endl;
	a.insert(5, 2);
	a.Print(); std::cout << std::endl;
	a.erase(1);
	a.Print(); std::cout << std::endl;
	a.erase(1);
	a.Print(); std::cout << a.empty() << std::endl;

	List<> b(3);
	b.insert(4);
	b.insert(5);



	std::cout << b.search(5) << std::endl;
	b.clear();
	std::cout << b.empty();
	std::cout << b.search(2) << std::endl;

	List<>c;
	c.insert(2);
	c.Print();
}