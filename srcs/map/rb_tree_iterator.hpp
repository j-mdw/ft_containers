#ifndef FT_RB_TREE_ITERATOR_HPP
# define FT_RB_TREE_ITERATOR_HPP

# include <iterator> //Necessary for bidirectional_iterator_tag
# include "rb_tree.hpp"

namespace ft
{
	template<typename T>
	class rb_tree_iterator: public iterator<
		std::bidirectional_iterator_tag,
		T
	> {
		public:
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference
		typedef Node<T>				base;
		typedef Node<T>*			base_ptr;
		typedef rb_tree_iterator<T>	self;

		private:
		base_ptr	_base;

		public:
		rb_tree_iterator(void): _base() {}; // Will base be NULL?
		rb_tree_iterator(const self &cpy) : _base() {};
		~rb_tree_iterator(void) {};

		self operator =(const self &cpy) { _base = cpy._base};

		reference	operator*() { return _base->value; };
		pointer		operator->() { return &_base->value; };

		self&	operator++()
		{
			_base = tree_successor(_base);
			return *this;
		};

		self	operator++(int)
		{
			self current_base(_base);
			_base = tree_successor(_base);
			return current_base;
		}

		self&	operator--()
		{
			_base = tree_predecessor(_base);
			return *this;
		};

		self	operator--(int)
		{
			self current_base(_base);
			_base = tree_predecessor(_base);
			return current_base;
		};
		template<typename T>		
		friend
		bool	operator==(const Iter &lhs, const Iter &rhs);
	};

	template<typename T>
	bool	operator==(const rb_tree_iterator<T> &lhs, const rb_tree_iterator<T> &rhs)
	{
		return lhs._base == rhs._base;
	};
	
	template<typename T>
	bool	operator!=(const rb_tree_iterator<T> &lhs, const rb_tree_iterator<T> &rhs)
	{
		return !(lhs == rhs);
	};
}

#endif