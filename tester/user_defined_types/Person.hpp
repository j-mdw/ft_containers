#include <vector>
#include <string>
#include <ostream>

class Person
		{
		private:
			size_t age;
			std::string name;
			std::vector<int> v;
		public:
			Person(void) : age(10), name("henri"), v(10, 42) {};
			Person(int age, std::string name) : age(age), name(name), v(10, 42) {};
			Person(const Person & ins) : age(ins.age), name(ins.name), v(ins.v) {};
			~Person(void) {};

			Person &	operator= (const Person & ins)
			{
				age = ins.age; name = ins.name; v = ins.v;
				return (*this);
			};

			const std::string & getName(void) const { return name; };
			size_t				getAge(void) const { return age; };

			std::string & operator* () { return name; };
			bool operator== (const Person & lhs) const
			{
				if (age == lhs.getAge() && name == lhs.getName())
					return true;
				return false;
			};
			bool operator!= (const Person & lhs) const { return !(*this == lhs); };
			bool operator<= (const Person & lhs) const { return age <= lhs.getAge(); };
			bool operator>= (const Person & lhs) const { return age >= lhs.getAge(); };
			bool operator> (const Person & lhs) const { return !(*this <= lhs); };
			bool operator< (const Person & lhs) const { return age < lhs.getAge(); };
		};


std::ostream & operator<< (std::ostream & o, const Person & ins)
{
	o << ins.getName() << " : " << ins.getAge() << " years old\n";
	return (o);
}