#include "vector.hpp"
#include "Tester.hpp"
#include <vector>

int main(void)
{
	NS::CONTAINER<int> vec_i;
	for (int i = 0; i < 5; i++)
	{
		vec_i.push_back(i);
	}
	Tester<int> tst_i;
	tst_i.test_constructor(10, 41, vec_i);
	tst_i.test_instance(vec_i);

	NS::CONTAINER<char> vec_c;
	for (int i = 0; i < 26; i++)
	{
		vec_c.push_back(i + '0');
	}
	Tester<char> tst_c;
	tst_c.test_constructor(10, 'k', vec_c);
	tst_c.test_instance(vec_c);
	return (0);
}