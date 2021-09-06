#ifndef FT_TESTER_HPP
# define FT_TESTER_HPP

# include <iostream>
# include <string>
# include <stdarg.h>


# include <iterator>
# include "iterator_traits.hpp"

// # define NS ft
// # define CONTAINER vector

# define PRINT_ATTR 0x01
# define PRINT_VAL	0x02


template<typename T>
class Tester
{
	public:
		Tester(void) {};
		~Tester(void) {};

		// Tests constructor behavior and assignment operator
		void
		test_constructor(size_t n, T val, NS::CONTAINER<T> initialized_ins)
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
		test_instance(NS::CONTAINER<T> & ins)
		{
			test_access(ins);
			test_capacity(ins);
		};

		// void
		// test_limits(void)
		// {

		// };

		// void
		// test_comparisons(NS::CONTAINER<T> ins1, NS::CONTAINER<T> ins2)
		// {

		// };

		// Testing at(), operator[], front(), back()
		void
		test_access(NS::CONTAINER<T> & ins)
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
		test_capacity(NS::CONTAINER<T> & ins)
		{
			NS::CONTAINER<T> ins_cpy(ins);
			std::cout << "Max size: " << ins_cpy.max_size() << '\n';
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
		void
		test_iterator(NS::CONTAINER<T> & ins)
		{
			std::cout << "Iterator comparisons: == and !=\n";
			print_value(ins.begin() == ins.begin());
			print_value(ins.begin() != ins.begin());
			print_value(ins.begin() == ins.end());
			print_value(ins.begin() != ins.end());

			if (!ins.empty())
			{
				std::cout << "\nIterator begin value: simple begin() call, copy constructor, assignment operator\n";
				print_valuetype(*ins.begin());
				typename NS::CONTAINER<T>::iterator it1(ins.begin());
				print_valuetype(*it1);
				typename NS::CONTAINER<T>::iterator it2 = ins.begin();
				print_valuetype(*it2);

				if (ins.size() >= 2)
				{
					print_valuetype(*++it1);
					print_valuetype(*it2++);
					std::cout << '\n';
					typename NS::iterator_traits<typename NS::CONTAINER<T>::iterator>::iterator_category category;
					test_iterator_category(ins, category);
				}
				std::cout << '\n';
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
		print_attr(const NS::CONTAINER<T> & ins)
		{
    		std::cout << "Size: " << ins.size()
    		<< "\tCapacity: " << ins.capacity() << std::endl;
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

		void
		test_iterator_category(NS::CONTAINER<T> & ins, std::bidirectional_iterator_tag tag)
		{
			(void) tag;
			std::cout << "Bidirectional operator tests:\n";
			typename NS::CONTAINER<T>::iterator it = ins.begin();
			it++;
			print_valuetype(*--it);
			it++;
			print_valuetype(*it--);
			print_valuetype(*it);
		};

		void
		test_iterator_category(NS::CONTAINER<T> & ins, std::random_access_iterator_tag tag)
		{
			(void) tag;
			std::cout << "Random access operator tests:\n";
			typename NS::CONTAINER<T>::iterator it = ins.begin();
			it++;
			print_valuetype(*--it);
			it++;
			print_valuetype(*it--);
			print_valuetype(*it);
			print_valuetype(*(it + ins.size() / 2));
			it += ins.size() / 2;
			print_valuetype(*it);
			it = ins.end();
			print_valuetype(*(it - ins.size() / 2));
			it -= ins.size() / 2;
			print_valuetype(*it);
			it = ins.begin();
			print_value(it[ins.size() / 2]);
			it = ins.end();
			print_value(it[-(ins.size() / 2)]);
		};

};

#endif
