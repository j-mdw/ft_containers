#include "map.hpp"

int
main(void)
{
	ft::map<int, int> mi;

	for (size_t i = 2; i > 0; --i)
	{
		mi.insert(ft::pair<int, int>(i, 7));
	}

	// std::cout << "Left rotate:\n";
	// mi.left_rotate();
	// mi.print();

	// std::cout << "+ node\n";
	// mi.insert(ft::pair<int, int>(243, 6));
	mi.print();
	mi.remove(ft::pair<int, int>(1, 7));

	std::cout << '\n';
	mi.print();
	mi.remove(ft::pair<int, int>(2, 7));

	std::cout << '\n';
	mi.print();

	for (size_t i = 2; i > 0; --i)
	{
		mi.insert(ft::pair<int, int>(i, 7));
	}
		std::cout << '\n';
	mi.print();
	// mi.remove(ft::pair<int, int>(1, 7));
	// std::cout << '\n';
	// mi.print();

	// mi.remove(ft::pair<int, int>(8, 7));
	// mi.remove(ft::pair<int, int>(6, 7));
	// mi.remove(ft::pair<int, int>(2, 7));
	// std::cout << '\n';
	// mi.print();

	// mi.remove(ft::pair<int, int>(5, 7));
	// std::cout << '\n';
	// mi.print();

	// mi.remove(ft::pair<int, int>(7, 7));
	// std::cout << '\n';
	// mi.print();
	
	// mi.remove(ft::pair<int, int>(4, 7));
	// std::cout << '\n';
	// mi.print();
	// std::cout << "Right rotate:\n";
	// mi.right_rotate();
	// mi.print();
	return 0;
}