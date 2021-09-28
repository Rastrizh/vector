
#include "Vector.h"

#include <iostream>

int main()
{
	Vector<int> v;
	v.push_back(1);
	v.push_back(12);
	v.push_back(123);
	for (size_t i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << ' ';
	}

	std::cin.get();
	return 0;
}