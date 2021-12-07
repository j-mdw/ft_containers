#include "vector.hpp"
#include "Tester.hpp"
#include <vector>
#include <string>
#include "RandomGenerator.hpp"
#include "Person.hpp"
#include <iterator> //DELETE

// std::vector<int> v;

int main(void)
{
	{
		NS::CONTAINER<int> vec_i;
		for (int i = 0; i < 5; i++)
		{
			vec_i.push_back(i);
		}
		
		Tester<int> tst_i;
		tst_i.test_constructor(10, 41, vec_i);
		tst_i.test_instance(vec_i);
		tst_i.test_comparisons(vec_i);
		
		tst_i.test_iterator(vec_i, vec_i.begin(), vec_i.end());
		tst_i.test_iterator(vec_i, vec_i.rbegin(), vec_i.rend());
		NS::CONTAINER<int>::const_iterator cit = vec_i.begin();
		NS::CONTAINER<int>::const_iterator cite = vec_i.end();
		tst_i.test_iterator(vec_i, cit, cite);
		NS::CONTAINER<int>::reverse_iterator rit = vec_i.rbegin();
		NS::CONTAINER<int>::reverse_iterator rite = vec_i.rend();
		tst_i.test_iterator(vec_i, rit, rite);
		NS::CONTAINER<int>::const_reverse_iterator crit(vec_i.rbegin());
		NS::CONTAINER<int>::const_reverse_iterator crite(vec_i.rend());
		tst_i.test_iterator(vec_i, crit, crite);

		tst_i.test_modifiers(vec_i);
	}

	{
		NS::CONTAINER<char> vec_c;
		for (int i = 0; i < 26; i++)
		{
			vec_c.push_back(i + '0');
		}
		Tester<char> tst_c;
		tst_c.test_constructor(10, 'k', vec_c);
		tst_c.test_instance(vec_c);
		tst_c.test_comparisons(vec_c);

		tst_c.test_iterator(vec_c, vec_c.begin(), vec_c.end());
		tst_c.test_iterator(vec_c, vec_c.rbegin(), vec_c.rend());
	}

	{
		NS::CONTAINER<std::string> vec_s;
		for (int i = 0; i < 50; i++)
		{
			vec_s.push_back(RandomGenerator::generate_string(3, 10));
		}
		Tester<std::string> tst_s;
		tst_s.test_constructor(20, "hello", vec_s);
		tst_s.test_instance(vec_s);
		tst_s.test_comparisons(vec_s);

		tst_s.test_iterator(vec_s, vec_s.begin(), vec_s.end());
		tst_s.test_iterator(vec_s, vec_s.rbegin(), vec_s.rend());
	}
	
	{
		NS::CONTAINER<Person> vec_tc;
		for (int i = 0; i < 25; i++)
		{
			vec_tc.push_back(Person(RandomGenerator::generate_unsigned(100), RandomGenerator::generate_string(3, 10)));
		}
		Tester<Person> tst_s;
		tst_s.test_constructor(20, Person(), vec_tc);
		tst_s.test_instance(vec_tc);
		tst_s.test_comparisons(vec_tc);

		tst_s.test_iterator(vec_tc, vec_tc.begin(), vec_tc.end());
		tst_s.test_iterator(vec_tc, vec_tc.rbegin(), vec_tc.rend());
	}

	{
		NS::vector<int> vct(5);
		NS::vector<int>::iterator it = vct.begin(), ite = vct.end();

		std::cout << "len: " << (ite - it) << std::endl;
		for (; it != ite; ++it)
			*it = (ite - it);

		it = vct.begin();
		NS::vector<int> vct_range(it, --(--ite));
		for (int i = 0; it != ite; ++it)
			*it = ++i * 5;

		it = vct.begin();
		NS::vector<int> vct_copy(vct);
		for (int i = 0; it != ite; ++it)
			*it = ++i * 7;
		vct_copy.push_back(42);
		vct_copy.push_back(21);

		std::cout << "\t-- PART ONE --" << std::endl;
		// printSize(vct);
		// printSize(vct_range);
		// printSize(vct_copy);

		vct = vct_copy;
		vct_copy = vct_range;
		vct_range.clear();

		std::cout << "\t-- PART TWO --" << std::endl;
		// printSize(vct);
		// printSize(vct_range);
		// printSize(vct_copy);
	}
	{
		const int size = 5;
		NS::vector<int> vct(size);
		NS::vector<int>::reverse_iterator it = vct.rbegin();
		NS::vector<int>::const_reverse_iterator ite = vct.rbegin();

		for (int i = 0; i < size; ++i)
			it[i] = (size - i) * 5;

		it = it + 5;
		it = 1 + it;
		it = it - 4;
		std::cout << *(it += 2) << std::endl;
		std::cout << *(it -= 1) << std::endl;

		std::cout << *(ite + 2) << std::endl;
		std::cout << *(3 + ite) << std::endl;

		*(it -= 2) = 42;
		*(it += 2) = 21;

		// std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

		// std::cout << "(it == const_it): " << (ite == it) << std::endl;
		// std::cout << "(const_ite - it): " << (ite - it) << std::endl;
		// std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
	}
	return (0);
}