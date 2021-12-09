#include "stack.hpp"
#include "Tester.hpp"
#include <stack>
#include <string>
#include "RandomGenerator.hpp"

#include "Person.hpp"

int main(void)
{
	{
		NS::stack<int, NS::vector<int> > stk_i;
		for (int i = 0; i < 5; i++)
		{
			stk_i.push(i);
		}
		Tester<int> tst_i;
		tst_i.test_constructor(10, 41, stk_i);
		tst_i.test_instance(stk_i);
		tst_i.test_comparisons(stk_i);
	}

	{
		NS::stack<char, NS::vector<char> > stk_c;
		for (int i = 0; i < 26; i++)
		{
			stk_c.push(i + '0');
		}
		Tester<char> tst_c;
		tst_c.test_constructor(10, 'k', stk_c);
		tst_c.test_instance(stk_c);
		tst_c.test_comparisons(stk_c);
	}

	{
		NS::stack<std::string, NS::vector<std::string> > stk_s;
		for (int i = 0; i < 50; i++)
		{
			stk_s.push(RandomGenerator::generate_string(3, 10));
		}
		Tester<std::string> tst_s;
		tst_s.test_constructor(20, "hello", stk_s);
		tst_s.test_instance(stk_s);
		tst_s.test_comparisons(stk_s);
	}
	
	{
		NS::stack<Person, NS::vector<Person> > stk_tc;
		for (int i = 0; i < 25; i++)
		{
			stk_tc.push(Person(RandomGenerator::generate_unsigned(100), RandomGenerator::generate_string(3, 10)));
		}
		Tester<Person> tst_s;
		tst_s.test_constructor(20, Person(), stk_tc);
		tst_s.test_instance(stk_tc);
		tst_s.test_comparisons(stk_tc);
	}
	return (0);
}