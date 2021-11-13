#include "map.hpp"

int
main(void)
{
	ft::map<int, int> mi;

	for (size_t i = 15; i > 0; --i)
	{
		mi.insert(ft::pair<int, int>(i, 7));
	}

	// std::cout << "Left rotate:\n";
	// mi.left_rotate();
	// mi.print();

	// std::cout << "+ node\n";
	// mi.insert(ft::pair<int, int>(243, 6));
	mi.print();

	// std::cout << "Right rotate:\n";
	// mi.right_rotate();
	// mi.print();
	return 0;
}