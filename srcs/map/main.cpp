#include "map.hpp"
#include <vector>
#include "vector.hpp"
#include <cstdlib> // used for rand()

#ifndef NS
# define NS ft
#endif

typedef NS::map<int, int> m_t;

void
print_map(m_t &m)
{
	m_t::iterator it = m.begin();
	m_t::iterator ite = m.end();
	for (int i = 0; it != ite; ++it)
	{
		std::cout << i << ": " << it->first << " ; " << it->second << '\n';
		++i;
	}
}

int
main(void)
{
	m_t mi;

	for (size_t i = 20; i > 0; --i)
	{
		NS::pair<m_t::iterator, bool> inserted = mi.insert(NS::pair<int, int>(std::rand() % 5, 7));
		std::cout << "Node inserted: " << inserted.first->first << " ; " << inserted.first->second;
		if (inserted.second)
			std::cout << "'true'";
		else
			std::cout << "'false'";
		std::cout  << " size: " << mi.size() << '\n';
		m_t::iterator it = mi.insert(inserted.first, NS::pair<int, int>(std::rand() % 10, 8));
		std::cout << "Node inserted: " << (*it).first << " ; " << (*it).second;
		std::cout  << " size: " << mi.size() << '\n';
	}
	print_map(mi);
	m_t::iterator it = mi.begin();
	for (size_t i = 0; i < mi.size() / 2; ++i)
	{
		it++;
	}
	m_t mi2;
	mi2.insert(mi.begin(), it);
	std::cout << "mi2\n";
	print_map(mi2);
	
	//SWAP
	mi.swap(mi2);
	std::cout << "mi post swap\n";
	print_map(mi);
	std::cout << '\n';
	std::cout << "mi2 post swap\n";
	print_map(mi2);

	//ERASE
	mi2.erase(mi2.begin(), mi2.end());
	std::cout << "mi2\n";
	// print_map(mi2);

	int del = mi.erase(7);
	if (del)
		std::cout << "Elem 7 deleted\n";
	else
		std::cout << "No elem deleted\n";
	print_map(mi);
	mi.erase(mi.begin());
	std::cout << "Deleting 1st elem\n";
	mi.erase(--mi.end());
	std::cout << "Deleting last elem\n";
	print_map(mi);


	for (size_t i = 2; i > 0; --i)
	{
		mi.insert(NS::pair<int, int>(i, 7));
	}
		std::cout << '\n';
	print_map(mi);
	{
	m_t::iterator it = mi.begin();
	m_t::iterator ite = mi.end();
	for (; it != ite; ++it)
		std::cout << "It value: " << it->first << " ; " << it->second << '\n';
	}
	mi.erase(2);
	std::cout << '\n';
	print_map(mi);

	std::cout << "\nIterator tests\n\n";
	{
	m_t::iterator it = mi.begin();
	m_t::iterator ite = mi.end();
	for (; it != ite; ++it)
		std::cout << "It value: " << it->first << " ; " << it->second << '\n';
	}

	m_t m;
	for (size_t i = 10; i > 0; --i)
	{
		m.insert(NS::pair<int, int>(i, 7));
	}
	m.erase(5);
	m.erase(6);
	m.erase(7);
	m.erase(8);
	m.erase(9);
	m.erase(10);
	// m_t::iterator it_lower = m.lower_bound(5);
	// std::cout << "Lower bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';
	// it_lower = m.upper_bound(5);
	// std::cout << "Upper bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';

	{
	m_t::iterator it = m.begin();
	m_t::iterator ite = m.end();
	it--;
	if (it == ite)
		std::cout << "yap\n";
	ite--;
	for (; it != ite; --ite)
		std::cout << "STD It value: " << ite->first << " ; " << ite->second << '\n';
	}
	{
		m_t my_map;
		for (size_t i = 0; i < 20; i++)
		{
			my_map.insert(NS::pair<int, int>(i, 7));
		}
		m_t::iterator it = my_map.begin();
		m_t::iterator ite = my_map.end();
		for (; it != ite; it++)
		{
			std::cout << "NS It value: " << it->first << " ; " << it->second << '\n';
		}
		print_map(my_map);
		ite--;
		for (it = my_map.begin(); it != ite; ite--)
		{
			std::cout << "NS It value: " << ite->first << " ; " << ite->second << '\n';
		}
		
	}
	return 0;
}