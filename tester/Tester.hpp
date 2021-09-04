#ifndef FT_TESTER_HPP
# define FT_TESTER_HPP

# include <iostream>
# include <string>
# include <stdarg.h>
# include <cstdlib>
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
				print_value(ins.at(n));				
				print_value(ins[n]);
			}
			if (!ins.empty())
			{
				print_value(ins.front());
				print_value(ins.back());
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

		// void
		// test_iterators(NS::CONTAINER<T> & ins)
		// {

		// };



	private:

		void
		print(std::string test_name, NS::CONTAINER<T> ins, int flag)
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
		print_attr(NS::CONTAINER<T> ins)
		{
    		std::cout << "Size: " << ins.size()
    		<< "\tCapacity: " << ins.capacity() << std::endl;
		};

		void
		print_all_values(NS::CONTAINER<T> ins)
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
		print_value(typename NS::CONTAINER<T>::value_type v)
		{
			std::cout << v << '|';	//Only works if ins::type defines operator<<
		};
};

int
random_val_genertor(int max)
{
	std::srand(std::time(NULL) + std::clock());
	return rand() % max;
}

#endif
