#include "../vector/vector.hpp"

#ifndef STACK_H
# define STACK_H

namespace ft
{

template <class T, class Container = vector<T> >
class stack
{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

	protected:
		container_type	c;

	public:
		explicit stack(const container_type& ctnr = container_type()) : c(ctnr) {};
		
		~stack(void) {};

		bool				empty(void) const { return c.empty(); };
		size_type			size(void) const { return c.size(); };
		value_type&			top(void) { return c.back(); };
		const value_type&	top(void) const { return c.back(); };
		void				push(const value_type& val) { c.push_back(val); };
		void				pop() { c.pop_back(); };


		template <class T1, class Container1>
		friend
		bool operator==(const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs);

		template <class T1, class Container1>
		friend
		bool operator< (const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs);
};

template <class T, class Container>
bool operator== (const stack<T, Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs.c == rhs.c);
};

template <class T, class Container>
bool operator!= (const stack<T, Container>& lhs, const stack<T,Container>& rhs)
{
	return !(lhs == rhs);
};

template <class T, class Container>
bool operator<  (const stack<T, Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs.c < rhs.c);
};

template <class T, class Container>
bool operator<= (const stack<T, Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs < rhs) || (lhs == rhs);
};

template <class T, class Container>
bool operator>  (const stack<T, Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs != rhs) && !(lhs < rhs);
};

template <class T, class Container>
bool operator>= (const stack<T, Container>& lhs, const stack<T,Container>& rhs)
{
	return !(lhs < rhs);
};

}

#endif