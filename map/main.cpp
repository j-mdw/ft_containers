#include "map.hpp"

int
main(void)
{
	ft::map<int, int> mi;
	mi.insert(ft::pair<int, int>(4, 5));
	mi.insert(ft::pair<int, int>(6, 6));
	mi.insert(ft::pair<int, int>(-1, 6));
	mi.insert(ft::pair<int, int>(43, 6));
	mi.insert(ft::pair<int, int>(0, 6));
	mi.insert(ft::pair<int, int>(72, 6));
	mi.insert(ft::pair<int, int>(-23, 6));
	mi.print();
	return 0;
}