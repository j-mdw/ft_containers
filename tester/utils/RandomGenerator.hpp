#ifndef RANDOMGENERATOR_H
# define RANDOMGENERATOR_H

# include <cstdlib>
# include <string>
# include <ctime>

class RandomGenerator
{
	public:

    	RandomGenerator(void);
    	RandomGenerator(RandomGenerator const & src);
    	~RandomGenerator(void);
		
		RandomGenerator &  operator=(RandomGenerator const & src);

		static size_t		generate_unsigned(size_t max);
		static std::string	generate_string(size_t sizemin, size_t sizemax);

};

#endif
