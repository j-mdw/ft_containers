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

	private:
		container_type	_ctnr;

	public:
		explicit stack(const container_type& ctnr = container_type()) : _ctnr(ctnr) {};
		
		~stack(void) {};

		bool				empty(void) const { return _ctnr.empty(); };
		size_type			size(void) const { return _ctnr.size(); };
		value_type&			top(void) { return _ctnr.back(); };
		const value_type&	top(void) const { return _ctnr.back(); };
		void				push(const value_type& val) { _ctnr.push_back(val); };
		void				pop() { _ctnr.pop_back(); };


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
	return (lhs._ctnr == rhs._ctnr);
};

template <class T, class Container>
bool operator!= (const stack<T, Container>& lhs, const stack<T,Container>& rhs)
{
	return !(lhs == rhs);
};

template <class T, class Container>
bool operator<  (const stack<T, Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs._ctnr < rhs._ctnr);
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