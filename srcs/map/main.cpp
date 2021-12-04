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

void
print_map_const(const m_t &m)
{
	m_t::const_iterator it = m.begin();
	m_t::const_iterator ite = m.end();
	for (int i = 0; it != ite; ++it)
	{
		std::cout << i << ": " << it->first << " ; " << it->second << '\n';
		++i;
	}
}

void
print_map_reverse(m_t &m)
{
	m_t::reverse_iterator rit = m.rbegin();
	m_t::reverse_iterator rite = m.rend();
	for (int i = 0; rit != rite; rit++)
	{
		std::cout << i << ": " << rit->first << " ; " << rit->second << '\n';
	}
}

void
print_map_reverse_const(m_t &m)
{
	m_t::const_reverse_iterator rit = m.rbegin();
	m_t::const_reverse_iterator rite = m.rend();
	for (int i = 0; rit != rite; rit++)
	{
		std::cout << i << ": " << rit->first << " ; " << rit->second << '\n';
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
	print_map_reverse(mi);
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
	print_map_reverse(mi);
	print_map_const(mi);
	print_map_reverse_const(mi);

	std::cout << '\n';
	std::cout << "mi2 post swap\n";
	print_map(mi2);
	print_map_reverse(mi2);
	print_map_const(mi2);
	print_map_reverse_const(mi2);
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
	print_map_const(mi);
	print_map_reverse_const(mi);


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
	print_map_reverse(mi);
	print_map_const(mi);
	print_map_reverse_const(mi);
	
	std::cout << "\nIterator tests\n\n";
	{
	m_t::iterator it = mi.begin();
	m_t::iterator ite = mi.end();
	for (; it != ite; ++it)
		std::cout << "It value: " << it->first << " ; " << it->second << '\n';
	}
	{
		m_t m;
		for (size_t i = 10; i > 0; --i)
		{
			m.insert(NS::pair<int, int>(i, 7));
		}
		m_t::iterator it_lower = m.lower_bound(5);
		m_t::const_iterator itc_lower = m.lower_bound(4);
		m_t::iterator it_upper = m.upper_bound(5);
		m_t::const_iterator itc_upper = m.upper_bound(4);
		NS::pair<m_t::iterator, m_t::iterator> p = m.equal_range(5);
		std::cout << "Lower bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';
		std::cout << "Lower bound: " << itc_lower->first << " ; " <<  itc_lower->second << '\n';
		std::cout << "Upper bound: " << it_upper->first << " ; " <<  it_upper->second << '\n';
		std::cout << "Upper bound: " << itc_upper->first << " ; " <<  itc_upper->second << '\n';
		std::cout << "Equal bound: " << p.first->first << " ; " <<  p.second->first << '\n';
		
		m.erase(5);
		it_lower = m.lower_bound(5);
		itc_lower = m.lower_bound(4);
		it_upper = m.upper_bound(5);
		itc_upper = m.upper_bound(4);
		p = m.equal_range(4);
		std::cout << "Lower bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';
		std::cout << "Lower bound: " << itc_lower->first << " ; " <<  itc_lower->second << '\n';
		std::cout << "Upper bound: " << it_upper->first << " ; " <<  it_upper->second << '\n';
		std::cout << "Upper bound: " << itc_upper->first << " ; " <<  itc_upper->second << '\n';
		std::cout << "Equal bound: " << p.first->first << " ; " <<  p.second->first << '\n';
		m.erase(6);
		it_lower = m.lower_bound(5);
		itc_lower = m.lower_bound(1);
		it_upper = m.upper_bound(5);
		itc_upper = m.upper_bound(1);
		p = m.equal_range(5);

		std::cout << "Lower bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';
		std::cout << "Lower bound: " << itc_lower->first << " ; " <<  itc_lower->second << '\n';
		std::cout << "Upper bound: " << it_upper->first << " ; " <<  it_upper->second << '\n';
		std::cout << "Upper bound: " << itc_upper->first << " ; " <<  itc_upper->second << '\n';
		std::cout << "Equal bound: " << p.first->first << " ; " <<  p.second->first << '\n';
		m.erase(7);
		it_lower = m.lower_bound(7);
		itc_lower = m.lower_bound(1);
		it_upper = m.upper_bound(7);
		itc_upper = m.upper_bound(1);
		p = m.equal_range(7);

		std::cout << "Lower bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';
		std::cout << "Lower bound: " << itc_lower->first << " ; " <<  itc_lower->second << '\n';
		std::cout << "Upper bound: " << it_upper->first << " ; " <<  it_upper->second << '\n';
		std::cout << "Upper bound: " << itc_upper->first << " ; " <<  itc_upper->second << '\n';
		std::cout << "Equal bound: " << p.first->first << " ; " <<  p.second->first << '\n';
		m.erase(8);
		it_lower = m.lower_bound(7);
		itc_lower = m.lower_bound(10);
		it_upper = m.upper_bound(7);
		itc_upper = m.upper_bound(10);
		p = m.equal_range(4);

		std::cout << "Lower bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';
		std::cout << "Lower bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';
		std::cout << "Upper bound: " << it_upper->first << " ; " <<  it_upper->second << '\n';
		std::cout << "Upper bound: " << itc_upper->first << " ; " <<  itc_upper->second << '\n';
		std::cout << "Equal bound: " << p.first->first << " ; " <<  p.second->first << '\n';
		m.erase(9);
		it_lower = m.lower_bound(10);
		std::cout << "Lower bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';
		m.erase(10);
		it_lower = m.lower_bound(10);
		std::cout << "Lower bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';
		// it_lower = m.upper_bound(5);
		// std::cout << "Upper bound: " << it_lower->first << " ; " <<  it_lower->second << '\n';
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
		m_t m1;
		for (size_t i = 10; i > 0; --i)
		{
			m1.insert(NS::pair<int, int>(i, 7));
		}
		m1.erase(5);
		m1.erase(8);
		const m_t m(m1);

		m_t::const_iterator itc_lower = m.lower_bound(4);
		m_t::const_iterator itc_upper = m.upper_bound(4);
		std::cout << "Lower bound: " << itc_lower->first << " ; " <<  itc_lower->second << '\n';
		std::cout << "Upper bound: " << itc_upper->first << " ; " <<  itc_upper->second << '\n';

		itc_lower = m.lower_bound(4);
		itc_upper = m.upper_bound(4);
		std::cout << "Lower bound: " << itc_lower->first << " ; " <<  itc_lower->second << '\n';
		std::cout << "Upper bound: " << itc_upper->first << " ; " <<  itc_upper->second << '\n';
		itc_lower = m.lower_bound(1);
		itc_upper = m.upper_bound(1);
		std::cout << "Lower bound: " << itc_lower->first << " ; " <<  itc_lower->second << '\n';
		std::cout << "Upper bound: " << itc_upper->first << " ; " <<  itc_upper->second << '\n';
		itc_lower = m.lower_bound(1);
		itc_upper = m.upper_bound(1);
		std::cout << "Lower bound: " << itc_lower->first << " ; " <<  itc_lower->second << '\n';
		std::cout << "Upper bound: " << itc_upper->first << " ; " <<  itc_upper->second << '\n';
		itc_lower = m.lower_bound(10);
		itc_upper = m.upper_bound(10);
		std::cout << "Lower bound: " << itc_lower->first << " ; " <<  itc_lower->second << '\n';
		std::cout << "Upper bound: " << itc_upper->first << " ; " <<  itc_upper->second << '\n';
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
		print_map_reverse(my_map);
		print_map_const(mi);
		print_map_reverse_const(mi);

		ite--;
		for (it = my_map.begin(); it != ite; ite--)
		{
			std::cout << "NS It value: " << ite->first << " ; " << ite->second << '\n';
		}
		
		m_t mpit(++my_map.begin(), --my_map.end());
		print_map(mpit);
		const m_t mpitc(++mpit.begin(), --mpit.end());
		print_map_const(mpitc);

		m_t mpit_c = mpit;
		print_map(mpit_c);
		m_t mpitc_c = mpitc;
		print_map_const(mpitc_c);
	}
	{
		m_t mp;
		mp[0] = 1;
		mp[1] = 2;
		mp[2] = 4;
		mp[3] = 8;
		print_map(mp);
		mp[3] = 9;
		print_map(mp);
	}
	return 0;
}