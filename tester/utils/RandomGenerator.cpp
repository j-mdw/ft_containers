#include "RandomGenerator.hpp"

RandomGenerator::RandomGenerator(void) {}

RandomGenerator::RandomGenerator(RandomGenerator const & src)
{
    (void)src;
}

RandomGenerator::~RandomGenerator(void) {}

RandomGenerator &
RandomGenerator::operator=(RandomGenerator const & src)
{
	(void)src;
    return (*this);
}

size_t
RandomGenerator::generate_unsigned(size_t max)
{
	return rand() % max;
}

std::string
RandomGenerator::generate_string(size_t sizemin, size_t sizemax)
{
	size_t str_len = generate_unsigned(sizemax - sizemin) + sizemin;
	std::string str;
	for (size_t i = 0; i < str_len; i++)
	{
		str += (generate_unsigned(94) + 32);
	}
	return str;
}
