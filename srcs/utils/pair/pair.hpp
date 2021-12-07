#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP

// #include <utility> //remove
namespace ft
{
	template<typename T1, typename T2>
	class pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

			//Constructors
			pair(void) : first(), second() {};
			
			template<class U, class V>
			pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {};

			pair (const first_type& a, const second_type& b) : first(a), second(b) {};

			//Destructor
			~pair(void) {};

			//Assignation operator
			pair & operator=(const pair & pr)
			{
				first = pr.first;
				second = pr.second;
				return *this;
			}

	};

template <class T1, class T2>
bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
	return lhs.first==rhs.first && lhs.second==rhs.second;
}

template <class T1, class T2>
bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
	return !(lhs==rhs);
}

template <class T1, class T2>
bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
	return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
}

/*
1st false:
lhs.first >= rhs.first
2nd false:
rhs.first < lhs.first
||
rhs == lhs && lhs.second >= rhs.second
2nd true:
rhs == lhs && lhs.second < rhs.second
*/

template <class T1, class T2>
bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
	return !(rhs<lhs);
}

template <class T1, class T2>
bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
	return rhs<lhs;
}

template <class T1, class T2>
bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{
	return !(lhs<rhs);
}

}

#endif