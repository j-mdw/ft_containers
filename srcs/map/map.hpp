#ifndef FT_MAP_HPP
# define FT_MAP_HPP

# include <functional>
# include "pair.hpp"
# include "rb_tree_iterator.hpp"
# include "reverse_iterator.hpp"
# include <map> //Remove
# include "rb_tree.hpp"

namespace ft
{
	template <
		class Key,
		class T,                
		class Compare = std::less<Key>,    
		class Alloc = std::allocator<pair<const Key, T> >
	>
	class map
	{
		public:

		typedef	Key									key_type;
		typedef	T									mapped_type;
		typedef	pair<const key_type, mapped_type>	value_type;
		typedef	Compare								key_compare;

		class value_compare
        : public std::binary_function<value_type, value_type, bool> // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
		{
			private:
			friend class map;

			protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

			public:
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		typedef	Alloc												allocator_type;
		typedef	typename allocator_type::reference					reference;
		typedef	typename allocator_type::const_reference			const_reference;
		typedef	typename allocator_type::pointer					pointer;
		typedef	typename allocator_type::const_pointer				const_pointer;
		typedef	rb_tree_iterator<value_type>						iterator;
		// typedef	map_iterator<const value_type>				const_iterator;
		typedef	reverse_iterator<iterator>							reverse_iterator;
		// typedef	reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef	typename iterator_traits<iterator>::difference_type	difference_type;
		typedef	size_t										size_type;

		private:
		key_compare		_compare;
		allocator_type	_allocator;
		rb_tree<value_type, value_compare, allocator_type> _tree;

		public:
		// Constructors
		explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) :
			  _compare(comp),
			  _allocator(alloc),
			  _tree(value_comp(), _allocator)
			  {};

		// template <class InputIterator>
  		// map(InputIterator first, InputIterator last,
       	// 	const key_compare& comp = key_compare(),
       	// 	const allocator_type& alloc = allocator_type());

		// map(const map& x);

		//Destructor
		~map(void) {};

		bool empty(void) const
		{
			if (_tree.size() == 0)
				return true;
			return false;
		};

		size_type size() const { return _tree.size(); };
		
		size_type max_size() const { return this->_tree.max_size(); };

		// Not Implemented: /!\
			// Iterators:

		iterator begin() { return _tree.begin(); };
		// const_iterator begin() const { return _tree.begin(); };
		iterator end() { return _tree.end(); };
		// const_iterator end() const { return _tree.end(); };
		reverse_iterator rbegin() { return _tree.end(); };
		// const_reverse_iterator rbegin() const { return _tree.end(); };
    	reverse_iterator rend() { return _tree.begin(); };
		// const_reverse_iterator rend() const { return _tree.begin(); };

			// Operators:
		mapped_type& operator[] (const key_type& k);

			// Modifiers: 
		pair<iterator, bool> insert (const value_type& val) // returning void for testing
		{
			return _tree.insert(val);
		};

		iterator insert (iterator position, const value_type& val)
		{
			(void) position;
			return _tree.insert(val).first;
		};

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_tree.insert(*first);
				++first;
			}
		};

		void erase (iterator position)
		{
			_tree.remove(*position);
		};

		size_type erase (const key_type& k)
		{
			value_type p(k, mapped_type());
			if (_tree.remove(p))
				return 1;
			return 0;
		}
		void erase (iterator first, iterator last)
		{
			while (first != last)
			{
				_tree.remove(*first);
				++first;
			}
		}

		void print(void) { _tree.print_tree(); }; // TEST --> To remove

		void swap (map& x)
		{
			_tree.swap(x._tree);
		};

		void clear()
		{
			_tree.delete_tree();
		};

		key_compare key_comp() const { return _compare; };
		
		value_compare value_comp() const { return value_compare(_compare); };

		iterator find (const key_type& k)
		{
			value_type p(k, mapped_type());
			return _tree.find(p);
		};
		// const_iterator find (const key_type& k) const;



		size_type count (const key_type& k) const
		{
			value_type p(k, mapped_type());
			if (_tree.search(p) != NULL)
				return 1;
			return 0;
		};




		allocator_type get_allocator() const
		{
			return _allocator;
		};
	};
}

#endif