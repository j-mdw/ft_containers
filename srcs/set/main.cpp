#include "set.hpp"
#include <set>
#include <vector>
#include "vector.hpp"
#include <cstdlib> // used for rand()
#include <list>
#ifndef NS
# define NS ft
#endif

typedef NS::set<int> m_t;

void
print_set(m_t &m)
{
	m_t::iterator it = m.begin();
	m_t::iterator ite = m.end();
	for (int i = 0; it != ite; ++it)
	{
		std::cout << i << ": " << *it << '\n';
		++i;
	}
}

void
print_set_const(const m_t &m)
{
	m_t::const_iterator it = m.begin();
	m_t::const_iterator ite = m.end();
	for (int i = 0; it != ite; ++it)
	{
		std::cout << i << ": " << *it << '\n';
		++i;
	}
}

void
print_set_reverse(m_t &m)
{
	m_t::reverse_iterator rit = m.rbegin();
	m_t::reverse_iterator rite = m.rend();
	for (int i = 0; rit != rite; rit++)
	{
			std::cout << i << ": " << *rit << '\n';
	}
}

void
print_set_reverse_const(m_t &m)
{
	m_t::const_reverse_iterator rit = m.rbegin();
	m_t::const_reverse_iterator rite = m.rend();
	for (int i = 0; rit != rite; rit++)
	{
			std::cout << i << ": " << *rit << '\n';
	}
}

int
main(void)
{
	m_t mi;

	for (size_t i = 20; i > 0; --i)
	{
		NS::pair<m_t::iterator, bool> inserted = mi.insert(std::rand() % 5);
		std::cout << "Node inserted: " << *inserted.first << '\n';
		if (inserted.second)
			std::cout << "'true'";
		else
			std::cout << "'false'";
		std::cout  << " size: " << mi.size() << '\n';
		m_t::iterator it = mi.insert(inserted.first, (std::rand() % 10));
		std::cout << "Node inserted: " << *it << '\n';
		std::cout  << " size: " << mi.size() << '\n';
	}
	print_set(mi);
	print_set_reverse(mi);
	m_t::iterator it = mi.begin();
	for (size_t i = 0; i < mi.size() / 2; ++i)
	{
		it++;
	}
	m_t mi2;
	mi2.insert(mi.begin(), it);
	std::cout << "mi2\n";
	print_set(mi2);
	
	//SWAP
	mi.swap(mi2);
	std::cout << "mi post swap\n";
	print_set(mi);
	print_set_reverse(mi);
	print_set_const(mi);
	print_set_reverse_const(mi);

	std::cout << '\n';
	std::cout << "mi2 post swap\n";
	print_set(mi2);
	print_set_reverse(mi2);
	print_set_const(mi2);
	print_set_reverse_const(mi2);
	//ERASE
	mi2.erase(mi2.begin(), mi2.end());
	std::cout << "mi2\n";
	// print_set(mi2);

	int del = mi.erase(7);
	if (del)
		std::cout << "Elem 7 deleted\n";
	else
		std::cout << "No elem deleted\n";
	print_set(mi);
	mi.erase(mi.begin());
	std::cout << "Deleting 1st elem\n";
	mi.erase(--mi.end());
	std::cout << "Deleting last elem\n";
	print_set(mi);
	print_set_const(mi);
	print_set_reverse_const(mi);

	for (size_t i = 2; i > 0; --i)
	{
		mi.insert(i);
	}
	std::cout << '\n';
	print_set(mi);
	{
		m_t::iterator it = mi.begin();
		m_t::iterator ite = mi.end();
		for (; it != ite; ++it)
			std::cout << "It value: " << *it << '\n';
	}
	mi.erase(2);
	std::cout << '\n';
	print_set(mi);
	print_set_reverse(mi);
	print_set_const(mi);
	print_set_reverse_const(mi);
	
	std::cout << "\nIterator tests\n\n";
	{
	m_t::iterator it = mi.begin();
	m_t::iterator ite = mi.end();
	for (; it != ite; ++it)
		std::cout << "It value: " << *it << '\n';
	}
	{
		m_t m;
		for (size_t i = 10; i > 0; --i)
		{
			m.insert(i);
		}
		m_t::iterator it_lower = m.lower_bound(5);
		m_t::const_iterator itc_lower = m.lower_bound(4);
		m_t::iterator it_upper = m.upper_bound(5);
		m_t::const_iterator itc_upper = m.upper_bound(4);
		NS::pair<m_t::iterator, m_t::iterator> p = m.equal_range(5);
		std::cout << "Lower bound: " << *it_lower << '\n';
		std::cout << "Lower bound: " << *itc_lower << '\n';
		std::cout << "Upper bound: " << *it_upper << '\n';
		std::cout << "Upper bound: " << *itc_upper << '\n';
		std::cout << "Equal bound: " << *p.first << '\n';
		
		m.erase(5);
		it_lower = m.lower_bound(5);
		itc_lower = m.lower_bound(4);
		it_upper = m.upper_bound(5);
		itc_upper = m.upper_bound(4);
		p = m.equal_range(4);
		std::cout << "Lower bound: " << *it_lower << '\n';
		std::cout << "Lower bound: " << *itc_lower << '\n';
		std::cout << "Upper bound: " << *it_upper << '\n';
		std::cout << "Upper bound: " << *itc_upper << '\n';
		std::cout << "Equal bound: " << *p.first << '\n';
		m.erase(6);
		it_lower = m.lower_bound(5);
		itc_lower = m.lower_bound(1);
		it_upper = m.upper_bound(5);
		itc_upper = m.upper_bound(1);
		p = m.equal_range(5);

		std::cout << "Lower bound: " << *it_lower << '\n';
		std::cout << "Lower bound: " << *itc_lower << '\n';
		std::cout << "Upper bound: " << *it_upper << '\n';
		std::cout << "Upper bound: " << *itc_upper << '\n';
		std::cout << "Equal bound: " << *p.first << '\n';
		m.erase(7);
		it_lower = m.lower_bound(7);
		itc_lower = m.lower_bound(1);
		it_upper = m.upper_bound(7);
		itc_upper = m.upper_bound(1);
		p = m.equal_range(7);

		std::cout << "Lower bound: " << *it_lower << '\n';
		std::cout << "Lower bound: " << *itc_lower << '\n';
		std::cout << "Upper bound: " << *it_upper << '\n';
		std::cout << "Upper bound: " << *itc_upper << '\n';
		std::cout << "Equal bound: " << *p.first << '\n';
		m.erase(8);
		it_lower = m.lower_bound(7);
		itc_lower = m.lower_bound(10);
		it_upper = m.upper_bound(7);
		p = m.equal_range(4);

		std::cout << "Lower bound: " << *it_lower << '\n';
		std::cout << "Lower bound: " << *itc_lower << '\n';
		std::cout << "Upper bound: " << *it_upper << '\n';
		std::cout << "Upper bound: " << *itc_upper << '\n';
		std::cout << "Equal bound: " << *p.first << '\n';
		m.erase(9);
		it_lower = m.lower_bound(10);
		std::cout << "Lower bound: " << *it_lower << '\n';

		m_t::iterator it = m.begin();
		m_t::iterator ite = m.end();
	it--;
	ite--;
	for (; it != ite; --ite)
		std::cout << "STD It value: " << *ite << '\n';
	}
	{
		m_t m1;
		for (size_t i = 10; i > 0; --i)
		{
			m1.insert(i);
		}
		m1.erase(5);
		m1.erase(8);
		const m_t m(m1);

		m_t::const_iterator itc_lower = m.lower_bound(4);
		m_t::const_iterator itc_upper = m.upper_bound(4);
		std::cout << "Lower bound: " << *itc_lower << '\n';
		std::cout << "Upper bound: " << *itc_upper << '\n';

		itc_lower = m.lower_bound(4);
		itc_upper = m.upper_bound(4);
		std::cout << "Lower bound: " << *itc_lower << '\n';
		std::cout << "Upper bound: " << *itc_upper << '\n';
		itc_lower = m.lower_bound(1);
		itc_upper = m.upper_bound(1);
		std::cout << "Lower bound: " << *itc_lower << '\n';
		std::cout << "Upper bound: " << *itc_upper << '\n';
		itc_lower = m.lower_bound(1);
		itc_upper = m.upper_bound(1);
		std::cout << "Lower bound: " << *itc_lower << '\n';
		std::cout << "Upper bound: " << *itc_upper << '\n';
		itc_lower = m.lower_bound(10);
		std::cout << "Lower bound: " << *itc_lower << '\n';
	}
	{
		m_t my_map;
		for (size_t i = 0; i < 20; i++)
		{
			my_map.insert(i);
		}
		m_t::iterator it = my_map.begin();
		m_t::iterator ite = my_map.end();
		for (; it != ite; it++)
		{
			std::cout << "NS It value: " << *it << '\n';
		}
		print_set(my_map);
		print_set_reverse(my_map);
		print_set_const(mi);
		print_set_reverse_const(mi);

		ite--;
		for (it = my_map.begin(); it != ite; ite--)
		{
			std::cout << "NS It value: " << *ite << '\n';
		}
		
		m_t mpit(++my_map.begin(), --my_map.end());
		print_set(mpit);
		const m_t mpitc(++mpit.begin(), --mpit.end());
		print_set_const(mpitc);

		m_t mpit_c = mpit;
		print_set(mpit_c);
		m_t mpitc_c = mpitc;
		print_set_const(mpitc_c);
	}
	return 0;
}