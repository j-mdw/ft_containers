#ifndef FT_MAP_HPP
# define FT_MAP_HPP

# include <functional>
# include "pair.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template <
		class Key,
		class T,                
		class Compare = std::less<Key>,    
		class Alloc = std::allocator<pair<const Key,T> >
	>
	class map
	{
		public:

		typedef	Key											key_type;
		typedef	T											mapped_type;
		typedef	pair<const key_type,mapped_type>			value_type;
		typedef	Compare										key_compare;
		typedef												value_compare;
		typedef	Alloc										allocator_type;
		typedef	allocator_type::reference					reference;
		typedef	allocator_type::const_reference				const_reference;
		typedef	allocator_type::pointer						pointer;
		typedef	allocator_type::const_pointer				const_pointer;
		typedef												iterator;
		typedef												const_iterator;
		typedef	reverse_iterator<iterator>					reverse_iterator;
		typedef	reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef	iterator_traits<iterator>::difference_type	difference_type;
		typedef	size_t										size_type;

		private:
			key_compare		_compare;
			allocator_type	_allocator;
			size_type		_size;

		public:
		// Constructors
		explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) :
			  _compare(comp),
			  _allocator(alloc),
			  _size(0)
			  {};

		template <class InputIterator>
  		map (InputIterator first, InputIterator last,
       		const key_compare& comp = key_compare(),
       		const allocator_type& alloc = allocator_type());

		map (const map& x);

		//Destructor
		~map(void);

		bool empty(void) const
		{
			if (_size == 0)
				return true;
			return false;
		};

		size_type size() const { return _size; };
		
		size_type max_size() const
		{
			long long max_size = std::numeric_limits<size_t>::max() >> 1;
			int divisor = sizeof(T) / 2;
			if (divisor > 1)
				return max_size / divisor;
			return max_size;
		};

		// Not Implemented: /!\
			// Iterators:
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
    	reverse_iterator rend();
		const_reverse_iterator rend() const;

			// Operators:
		mapped_type& operator[] (const key_type& k);

			// Modifiers:
		pair<iterator,bool> insert (const value_type& val);

		iterator insert (iterator position, const value_type& val);

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last);

		void erase (iterator position);
		size_type erase (const key_type& k);
		void erase (iterator first, iterator last);
		void swap (map& x);
		void clear();


		key_compare key_comp() const { return _compare; };
		value_compare value_comp() const;
	};
}

#endif