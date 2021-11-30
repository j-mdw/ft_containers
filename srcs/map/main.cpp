#include "map.hpp"
#include <vector>
#include "vector.hpp"
int
main(void)
{
	typedef ft::map<int, int> m_t;
	m_t mi;

	std::cout <<'f';
	for (size_t i = 5; i > 0; --i)
	{
		mi.insert(ft::pair<int, int>(i, 7));
	}
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
	{
	m_t::iterator it = mi.begin();
	m_t::iterator ite = mi.end();
	for (; it != ite; ++it)
		std::cout << "It value: " << it->first << " ; " << it->second << '\n';
	}
	mi.remove(ft::pair<int, int>(2, 7));
	std::cout << '\n';
	mi.print();

	std::cout << "\nIterator tests\n\n";
	{
	m_t::iterator it = mi.begin();
	m_t::iterator ite = mi.end();
	for (; it != ite; ++it)
		std::cout << "It value: " << it->first << " ; " << it->second << '\n';
	}

	std::map<int, int> m;
	for (size_t i = 5; i > 0; --i)
	{
		m.insert(std::pair<int, int>(i, 7));
	}
	{
	std::map<int, int>::iterator it = m.begin();
	std::map<int, int>::iterator ite = m.end();
	it--;
	if (it == ite)
		std::cout << "yap\n";
		ite--;
	for (; it != ite; --ite)
		std::cout << "STD It value: " << ite->first << " ; " << ite->second << '\n';
	}
	{
		ft::map<int, int> my_map;
		for (size_t i = 0; i < 20; i++)
		{
			my_map.insert(ft::pair<int, int>(i, 7));
		}
		ft::map<int, int>::iterator it = my_map.begin();
		ft::map<int, int>::iterator ite = my_map.end();
		for (; it != ite; it++)
		{
			std::cout << "FT It value: " << it->first << " ; " << it->second << '\n';
		}
		my_map.print();
		ite--;
		for (it = my_map.begin(); it != ite; ite--)
		{
			std::cout << "FT It value: " << ite->first << " ; " << ite->second << '\n';
		}
		
	}
	


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