#include "vector.hpp"
#include "Tester.hpp"
#include <vector>
#include <string>
#include "RandomGenerator.hpp"

int main(void)
{
	{
		NS::CONTAINER<int> vec_i;
		for (int i = 0; i < 5; i++)
		{
			vec_i.push_back(i);
		}
		
		Tester<int> tst_i;
		// tst_i.test_constructor(10, 41, vec_i);
		// tst_i.test_instance(vec_i);
		tst_i.test_comparisons(vec_i);
		
		// tst_i.test_iterator(vec_i, vec_i.begin(), vec_i.end());
		// tst_i.test_iterator(vec_i, vec_i.rbegin(), vec_i.rend());
		// NS::CONTAINER<int>::const_iterator cit = vec_i.begin();
		// NS::CONTAINER<int>::const_iterator cite = vec_i.end();
		// tst_i.test_iterator(vec_i, cit, cite);
		// NS::CONTAINER<int>::reverse_iterator rit = vec_i.rbegin();
		// NS::CONTAINER<int>::reverse_iterator rite = vec_i.rend();
		// tst_i.test_iterator(vec_i, rit, rite);
		// NS::CONTAINER<int>::const_reverse_iterator crit(vec_i.rbegin());
		// NS::CONTAINER<int>::const_reverse_iterator crite(vec_i.rend());
		// tst_i.test_iterator(vec_i, crit, crite);
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
		
		tst_s.test_comparisons(vec_s);
		
		tst_s.test_instance(vec_s);


		tst_s.test_iterator(vec_s, vec_s.begin(), vec_s.end());
		tst_s.test_iterator(vec_s, vec_s.rbegin(), vec_s.rend());
	}
	return (0);
}