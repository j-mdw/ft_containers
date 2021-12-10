#ifndef FT_SET_HPP
# define FT_SET_HPP

# include <set> //DELETE
# include <functional>
# include "../utils/pair/pair.hpp"
# include "../utils/pair/make_pair.hpp"
# include "../utils/rb_tree/rb_tree_iterator.hpp"
# include "../utils/iterator/reverse_iterator.hpp"
# include "../utils/rb_tree/rb_tree.hpp"
# include "../utils/lexicographical_compare/lexicographical_compare.hpp"
# include "../utils/equal/equal.hpp"

namespace ft
{
	template <
		class T,
		class Compare = std::less<T>,
		class Alloc = std::allocator<T>
	>
	class set
	{
		public:

		typedef	T									key_type;
		typedef	T									value_type;
		typedef	Compare								key_compare;
		typedef key_compare							value_compare;
		typedef	Alloc												allocator_type;
		typedef	typename allocator_type::reference					reference;
		typedef	typename allocator_type::const_reference			const_reference;
		typedef	typename allocator_type::pointer					pointer;
		typedef	typename allocator_type::const_pointer				const_pointer;
		typedef	rb_tree_iterator<value_type>						iterator;
		typedef	rb_tree_const_iterator<value_type>					const_iterator;
		typedef	reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef	reverse_iterator<iterator>							reverse_iterator;
		typedef	typename iterator_traits<iterator>::difference_type	difference_type;
		typedef	size_t												size_type;

		private:
		key_compare		_compare;
		allocator_type	_allocator;
		rb_tree<value_type, value_compare, allocator_type> _tree;

		public:
		// Constructors
		explicit set(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()):
			  _compare(comp),
			  _allocator(alloc),
			  _tree(comp, _allocator)
			  {};

		template <class InputIterator>
  		set(InputIterator first, InputIterator last,
       		const key_compare& comp = key_compare(),
       		const allocator_type& alloc = allocator_type()):
			   _compare(comp),
			   _allocator(alloc),
			   _tree(comp, _allocator)
		{
				this->insert(first, last);
		};

		set(const set& x):
			_compare(x._compare),
			_allocator(x._allocator),
			_tree(x._tree)
		{};

		set& operator= (const set& x)
		{
			_compare = x._compare;
			_tree = x._tree;
			return (*this);
		};

		//Destructor
		~set(void) {};

		bool empty(void) const
		{
			if (_tree.size() == 0)
				return true;
			return false;
		};

		size_type size() const { return _tree.size(); };
		
		size_type max_size() const { return this->_tree.max_size(); };

		// Iterators:
		iterator		begin() { return _tree.begin(); };
		const_iterator	begin() const { return _tree.begin(); };
		
		iterator		end() { return _tree.end(); };
		const_iterator	end() const { return _tree.end(); };
		
		reverse_iterator		rbegin() { return reverse_iterator(this->end()); };
		const_reverse_iterator	rbegin() const { return reverse_iterator(this->end()); };
		
		reverse_iterator		rend() { return reverse_iterator(this->begin()); };
		const_reverse_iterator	rend() const { return reverse_iterator(this->begin()); };

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
				value_type v(*first);
				++first;
				_tree.insert(v);
			}
		};

		void erase (iterator position)
		{
			_tree.remove(*position);
		};

		size_type erase (const value_type& k)
		{
			// value_type p(k, mapped_type());
			if (_tree.remove(k))
				return 1;
			return 0;
		};

		void erase (iterator first, iterator last)
		{
			while (first != last)
			{
				value_type v = *first;
				++first;
				_tree.remove(v);
			}
		};

	#ifdef DEBUG
		void print(void) { _tree.print_tree(); }; // TEST --> To remove
	#endif

		void swap (set& x)
		{
			_tree.swap(x._tree);
		};

		void clear()
		{
			_tree.delete_tree();
		};

		key_compare key_comp() const { return _compare; };

		value_compare value_comp() const { return _compare; };

		iterator find (const value_type& k)
		{
			// value_type p(k, mapped_type());
			return _tree.find(k);
		};

		const_iterator find (const value_type& k) const
		{
			// value_type p(k, mapped_type());
			return _tree.find(k);
		};

		size_type count (const value_type& k) const
		{
			// value_type p(k, mapped_type());
			if (_tree.search(k) != NULL)
				return 1;
			return 0;
		};

		allocator_type get_allocator() const
		{
			return _allocator;
		};

		iterator lower_bound (const value_type& k)
		{
			// value_type p(k, mapped_type());
			return _tree.lower_bound(k);
		};

		const_iterator lower_bound (const value_type& k) const
		{
			// value_type p(k, mapped_type());
			return _tree.lower_bound(k);
		};

		iterator upper_bound (const value_type& k)
		{
			// value_type p(k, mapped_type());
			return _tree.upper_bound(k);
		};

		const_iterator upper_bound (const value_type& k) const
		{
			// value_type p(k, mapped_type());
			return _tree.upper_bound(k);
		};

		pair<iterator,iterator>	equal_range (const value_type& k)
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		};

		pair<const_iterator,const_iterator> equal_range (const value_type& k) const
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		};
	};

	template< class T, class Compare, class Alloc >
	bool operator==( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template< class T, class Compare, class Alloc >
	bool operator!=( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	};

	template< class T, class Compare, class Alloc >
	bool operator<( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template< class T, class Compare, class Alloc >
	bool operator<=( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	};

	template< class T, class Compare, class Alloc >
	bool operator>=( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	};

	template< class T, class Compare, class Alloc >
	bool operator>( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	};

	template < class T, class Compare, class Alloc >
  void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
	{
		x.swap(y);
	};
}

#endif