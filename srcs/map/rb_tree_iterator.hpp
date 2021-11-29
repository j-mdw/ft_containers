#ifndef FT_RB_TREE_ITERATOR_HPP
# define FT_RB_TREE_ITERATOR_HPP

# include <iterator> //Necessary for bidirectional_iterator_tag
# include "iterator.hpp"
# include "tree_node.hpp"

namespace ft
{
	typedef enum {
		it_bbegin,
		it_middle,
		it_end
	}		position_t;
	/*
		How it works:
			- iterator is created either with a copy or by calling begin/end
			- Other option is default initialization and then assignation
			- In any case, we must call begin or end to get a tree pointer
			--> When calling begin, position is set to 'middle'
			--> When calling end, position is set to 'end'
			--> decrementing begin sets position to bbegin; _base is not modified
			--> Doing --/++ when position is begin/end sets _base to NULL => there is no getting back from this
		Dependencies:
			- RB Tree has a sentinel node which parent's is always NULL 
	*/
	template<typename T>
	class rb_tree_iterator: public iterator<
		std::bidirectional_iterator_tag,
		T
	> {
		public:
		typedef T					value_type;
		typedef T*					pointer;
		typedef T&					reference;
		typedef TreeNode<T>			base;
		typedef TreeNode<T>*		base_ptr;
		typedef rb_tree_iterator<T>	self;

		base_ptr	_base;
		position_t	_position;

		public:
		rb_tree_iterator(void): _base(), _position(it_middle) {}; // Will base be NULL?
		rb_tree_iterator(const self &cpy) : _base(cpy._base), _position(cpy._position) {};
		rb_tree_iterator(base_ptr base, position_t position) : _base(base), _position(position) {};
		~rb_tree_iterator(void) {};

		self operator =(const self &cpy)
		{
			_base = cpy._base;
			_position = cpy._position;
			return *this;
		};

		reference	operator*()
		{
			if (_position == it_bbegin)
				return _base->left->value; //Segfault
			else if (_position == it_end)
				return _base->right->value; //Segfault
			return _base->value;
		};
		pointer		operator->()
		{
			if (_position == it_bbegin)
				return &_base->left->value; //Address of NULL
			else if (_position == it_end)
				return &_base->right->value; //Address of NULL
			return &_base->value;
		};

		self&	operator++()
		{
			if (_position == it_bbegin)
				_position = it_middle;
			else if (_position == it_end)
				_base = NULL; //Could also do nothing when this case happens
			else
			{
				base_ptr tmp = tree_successor(_base);
				if (tmp->parent == NULL)
					_position = it_end;
				else
					_base = tmp;
			}
			return *this;
		};

		self	operator++(int)
		{
			self current_base(*this);
			if (_position == it_bbegin)
				_position = it_middle;
			else if (_position == it_end)
				_base = NULL;
			else
			{
				base_ptr tmp = tree_successor(_base);
				if (tmp->parent == NULL)
					_position = it_end;
				else
					_base = tmp;
			}
			return current_base;
		}

		self&	operator--()
		{
			if (_position == it_bbegin)
				_base = NULL;
			else if (_position == it_end)
				_position = it_middle;
			else
			{
				base_ptr tmp = tree_predecessor(_base);
				if (tmp->parent == NULL)
					_position = it_bbegin;
				else
					_base = tmp;
			}
			return *this;
		};

		self	operator--(int)
		{
			self current_base(*this);
			if (_position == it_bbegin)
				_base = NULL;
			else if (_position == it_end)
				_position = it_middle;
			else
			{
				base_ptr tmp = tree_predecessor(_base);
				if (tmp->parent == NULL)
					_position = it_bbegin;
				else
					_base = tmp;
			}
			return current_base;
		};

		template<typename U>		
		friend
		bool	operator==(const rb_tree_iterator<U> &lhs, const rb_tree_iterator<U> &rhs);
	};

	template<typename T>
	bool	operator==(const rb_tree_iterator<T> &lhs, const rb_tree_iterator<T> &rhs)
	{
		return (lhs._base == rhs._base && lhs._position == rhs._position);
	};
	
	template<typename T>
	bool	operator!=(const rb_tree_iterator<T> &lhs, const rb_tree_iterator<T> &rhs)
	{
		return !(lhs == rhs);
	};
}

#endif