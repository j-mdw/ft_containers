#include "enable_if.hpp"
#include <iostream>

int main(void)
{
	is_int myf;
	
	myf.isint(8);
	std::cout << myf.value << '\n';

	return 0;
}
