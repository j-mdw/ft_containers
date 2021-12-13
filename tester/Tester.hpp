#ifndef FT_TESTER_HPP
# define FT_TESTER_HPP

# include <iostream>
# include <string>
# include <stdarg.h>
# include <iterator>
# include "iterator_traits.hpp"

# define PRINT_ATTR 0x01
# define PRINT_VAL	0x02

class stack;
# include "stack.hpp"
# include <stack>
class vector;
# include "vector.hpp"
# include <vector>

template<typename T>
class Tester
{
	public:
	Tester(void) {};
	~Tester(void) {};

	// Tests constructor behavior and assignment operator
	// Needs an value_type and a CONTAINER<value_type> to perform all tests
	void
	test_constructor(size_t n, T val, NS::vector<T> initialized_ins)
	{
		{
			NS::CONTAINER<T> ins;
			print("Default Constructor", ins, PRINT_ATTR | PRINT_VAL);
		}
		{
			NS::CONTAINER<T> ins(n);
			print("Size Constructor", ins, PRINT_ATTR | PRINT_VAL);
		}
		{
			NS::CONTAINER<T> ins(n, val);
			print("Size Constructor with value initializer", ins, PRINT_ATTR | PRINT_VAL);
		}
		{
			NS::CONTAINER<T> ins(initialized_ins);
			print("Copy constructor", ins, PRINT_ATTR | PRINT_VAL);
		}
		{
			NS::CONTAINER<T> ins(initialized_ins.begin(), initialized_ins.end());
			print("Iterator constructor", ins, PRINT_ATTR | PRINT_VAL);
		}
		{
			NS::CONTAINER<T> ins = initialized_ins;
			print("Assignment operator", ins, PRINT_ATTR | PRINT_VAL);
		}
	};

	void
	test_constructor(size_t n, T val, NS::stack<T, NS::vector<T> > initialized_ins)
	{
		(void)n; (void)val;

		print_attr(initialized_ins);
		NS::stack<T, NS::vector<T> > ins;
		print_attr(ins);
	}


	void
	test_instance(NS::vector<T> & ins)
	{
		test_access(ins);
		test_capacity(ins);
	};

	void
	test_instance(NS::stack<T, NS::vector<T> > & ins)
	{
		test_access(ins);
	};

	// void
	// test_limits(void)
	// {

	// };

	void
	test_comparisons(NS::vector<T> & ins)
	{
		if (!ins.empty())
		{
			NS::vector<T> ins_cp = ins;
			
			std::cout << "\nComparison operators\n";
			print_value(ins == ins_cp);
			print_value(ins != ins_cp);
			print_value(ins <= ins_cp);
			print_value(ins >= ins_cp);
			print_value(ins < ins_cp);
			print_value(ins > ins_cp);

			ins_cp.insert(ins_cp.end(), *ins_cp.begin());
			print_value(ins == ins_cp);
			print_value(ins != ins_cp);
			print_value(ins <= ins_cp);
			print_value(ins >= ins_cp);
			print_value(ins < ins_cp);
			print_value(ins > ins_cp);
			std::cout << '\n' << std::endl;
		}
	};

	void
	test_comparisons(NS::stack<T, NS::vector<T> > & ins)
	{
		if (!ins.empty())
		{
			NS::stack<T, NS::vector<T> > ins_cp = ins;
			
			std::cout << "\nComparison operators\n";
			print_value(ins == ins_cp);
			print_value(ins != ins_cp);
			print_value(ins <= ins_cp);
			print_value(ins >= ins_cp);
			print_value(ins < ins_cp);
			print_value(ins > ins_cp);

			ins_cp.pop();
			print_value(ins == ins_cp);
			print_value(ins != ins_cp);
			print_value(ins <= ins_cp);
			print_value(ins >= ins_cp);
			print_value(ins < ins_cp);
			print_value(ins > ins_cp);
			std::cout << '\n' << std::endl;
		}
	};


	// Testing at(), operator[], front(), back()
	void
	test_access(NS::vector<T> & ins)
	{
		for(typename NS::CONTAINER<T>::size_type n = 0;
		n < ins.size(); n++)
		{
			print_valuetype(ins.at(n));				
			print_valuetype(ins[n]);
		}
		if (!ins.empty())
		{
			print_valuetype(ins.front());
			print_valuetype(ins.back());
			std::cout << '\n';
		}
	};

	void
	test_access(NS::stack<T, NS::vector<T> > & ins)
	{
		while (!ins.empty())
		{
			print_valuetype(ins.top());				
			ins.pop();
		}
	};

	void
	test_capacity(NS::CONTAINER<T> & ins)
	{
		NS::CONTAINER<T> ins_cpy(ins);
		std::cout << "Empty: " << ins_cpy.empty()  << '\n';
		print("Capacity: after copy", ins_cpy, PRINT_ATTR);
		
		ins_cpy.resize(ins_cpy.size() * 2);
		print("Capacity: after resize", ins_cpy, PRINT_ATTR | PRINT_VAL);

		ins_cpy.reserve(ins_cpy.size() / 2);
		print("Capacity: reserve of (size / 2)", ins_cpy, PRINT_ATTR | PRINT_VAL);

		ins_cpy.reserve(ins_cpy.size() * 4);
		print("Capacity: reserve of (size * 4)", ins_cpy, PRINT_ATTR | PRINT_VAL);
		ins_cpy.reserve(0);
		print("Capacity: reserve of 0", ins_cpy, PRINT_ATTR | PRINT_VAL);
		ins_cpy.resize(0);
		print("Capacity: resize to 0", ins_cpy, PRINT_ATTR | PRINT_VAL);
	};

	//Tests performed depend on container size. To perform all tests, provide container.size() > 4
	
	template <typename Iterator>
	void
	test_iterator(const NS::CONTAINER<T> & ins, Iterator begin, Iterator end)
	{
		std::cout << "Iterator comparisons: == and !=\n";
		print_value(begin == end);
		print_value(begin != end);
		print_value(begin == begin);
		print_value(begin != begin);

		if (!ins.empty())
		{
			std::cout << "\nIterator begin value: simple begin() call, copy constructor, assignment operator\n";
			print_valuetype(*begin);
			Iterator it1 = begin;
			Iterator it2 = begin;

			if (ins.size() >= 2)
			{
				print_valuetype(*++it1);
				print_valuetype(*it2++);
				print_valuetype(*--it1);
				print_valuetype(*it2--);
				std::cout << '\n';
				typename NS::iterator_traits<typename NS::CONTAINER<T>::iterator>::iterator_category category;
				test_iterator_category(ins, begin, end, category);
			}
			std::cout << '\n';
		}
	};

	void
	test_modifiers(NS::CONTAINER<T> & ins)
	{
		NS::CONTAINER<T> ins_cpy(ins);
		if (ins != ins_cpy)
		{
			std::cout << "Copy constructor error";
		}
		if (ins_cpy.empty())
		{
			std::cout << "test_modifiers: provide non-empty container";
		}
		else
		{
			std::cout << "\nModifiers tests\n";
			NS::CONTAINER<T> ins2;
			
			ins2.assign(ins_cpy.begin(), ins_cpy.end());
			print_value(ins2 == ins_cpy);
			NS::CONTAINER<T> ins3(ins_cpy.size(), *ins_cpy.begin());
			ins2.assign(ins_cpy.size(), *ins_cpy.begin());
			print_value(ins2 == ins3);
			
			ins2.push_back(*ins_cpy.begin());
			print_value(ins2 > ins3);
			
			ins2.pop_back();
			print_value(ins2 > ins3);
			print_value(ins2 == ins3);
			
			ins3.insert(ins3.end(), *ins3.begin());
			print_all_values(ins3);
			ins3.insert(ins3.begin(), *ins3.begin());
			print_all_values(ins3);
			ins2.insert(ins2.begin(), ins3.begin(), ins3.end());
			print_all_values(ins2);
			
			ins2.erase(ins2.begin());
			print_all_values(ins2);

			ins2.erase(ins2.end() - 1);
			print_all_values(ins2);
			ins2.erase(ins2.begin(), ins2.end());
			print_value(ins2.empty());

			ins2.swap(ins3);
			print_all_values(ins2);
			print_value(ins3.empty());

			ins2.clear();
			print_value(ins2.empty());
		}
	};

	private:

	void
	print(const std::string & test_name, NS::CONTAINER<T> & ins, int flag)
	{
		std::cout << "Test: " << test_name << '\n';
		switch (flag & 0x03)
		{
			case PRINT_ATTR:
				print_attr(ins);
				break;
			case PRINT_VAL:
				print_all_values(ins);
				break;
			case PRINT_VAL | PRINT_ATTR:
				print_attr(ins);
				print_all_values(ins);
				break;
			default:
				std::cout << "Printing nothing\n";
				break;
		}
	};

	void
	print_attr(const NS::vector<T> & ins)
	{
		std::cout << "Size: " << ins.size() << std::endl;
	};

	void
	print_attr(NS::stack<T, NS::vector<T> > & ins)
	{
		std::cout << "Size: " << ins.size() << std::endl;
	};


	void
	print_all_values(NS::CONTAINER<T> & ins)
	{
		typename NS::CONTAINER<T>::iterator it = ins.begin();
		for (; it != ins.end(); ++it)
		{
			std::cout << '|' << *it; //Only works if ins::type defines operator<< (could try to check if operator exist before printing)
		}
		if (ins.size() != 0)
			std::cout << "|\n";
	};

	void
	print_valuetype(typename NS::CONTAINER<T>::value_type v)
	{
		std::cout << v << '|';	//Only works if ins::type defines operator<<
	};

	template<typename U>
	void print_value(U val)
	{
		std::cout << val << '|';
	};

	template <typename Iterator>
	void
	test_iterator_category(const NS::CONTAINER<T> & ins, Iterator begin, Iterator end, std::bidirectional_iterator_tag tag)
	{
		(void) tag;
		(void) ins;
		std::cout << "\nBidirectional operator tests:\n";
		Iterator it = begin;
		it++;
		print_valuetype(*--it);
		it++;
		print_valuetype(*it--);
		print_valuetype(*it);

		for (Iterator it1 = begin; it1 != end; ++it1)
		{
			print_valuetype(*it1);
		}
		Iterator it2 = end;
		it2--;
		for (; it2 >= begin; --it2)
		{
			print_valuetype(*it2);
		}
	};

	template <typename Iterator>
	void
	test_iterator_category(const NS::CONTAINER<T> & ins, Iterator begin, Iterator end, std::random_access_iterator_tag tag)
	{
		(void) tag;
		for (Iterator it1 = begin; it1 != end; ++it1)
		{
			print_valuetype(*it1);
		}
		Iterator it2 = end;
		it2--;
		for (; it2 >= begin; --it2)
		{
			print_valuetype(*it2);
		}

		std::cout << "\nRandom access operator tests:\n";
		
		Iterator it = begin;
		it++;
		print_valuetype(*--it);
		it++;
		print_valuetype(*it--);
		print_valuetype(*it);
		print_valuetype(*(it + ins.size() / 2));
		it += ins.size() / 2;
		print_valuetype(*it);
		it = end;
		print_valuetype(*(it - ins.size() / 2));
		it -= ins.size() / 2;
		print_valuetype(*it);
		it = begin;
		print_value(it[ins.size() / 2]);
		it = end;
		print_value(it[-(ins.size() / 2)]);
	};
};

#endif
