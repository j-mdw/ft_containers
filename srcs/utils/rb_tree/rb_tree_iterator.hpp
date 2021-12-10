#ifndef FT_RB_TREE_ITERATOR_HPP
# define FT_RB_TREE_ITERATOR_HPP

# include <iterator> //Necessary for bidirectional_iterator_tag
# include "../iterator/iterator.hpp"
# include "tree_node.hpp"
namespace ft
{
	typedef enum {
		it_bbegin,
		it_middle,
		it_end
	}		position_t;

	template<typename T>
	class rb_tree_iterator: public ft::iterator<
		std::bidirectional_iterator_tag,
		T
	> {
		private:
		typedef TreeNode<T>			base;
		typedef TreeNode<T>*		base_ptr;
		typedef rb_tree_iterator<T>	self;

		public:
		typedef std::bidirectional_iterator_tag  iterator_category;
		typedef T         value_type;
		typedef typename std::ptrdiff_t  difference_type;
		typedef T*   pointer;
		typedef T& reference;

		private:
		base_ptr	_base;
		base_ptr *	_tree_root;
		position_t	_position;

		public:
		rb_tree_iterator(void):
			_base(),
			_tree_root(NULL),
			_position(it_middle)
		{};

		template<typename Iter>
		rb_tree_iterator(const rb_tree_iterator<Iter>& cpy):
			_base(cpy.get_base()),
			_tree_root(cpy.get_root()),
			_position(cpy.get_position())
		{};

		rb_tree_iterator(base_ptr base, base_ptr *root_ptr, position_t position = it_middle):
			_base(base),
			_tree_root(root_ptr),
			_position(position)
		{};

		~rb_tree_iterator(void) {};

		base_ptr get_base() const { return this->_base; };
		base_ptr *get_root() const { return this->_tree_root; };
		position_t get_position() const { return this->_position; };

		rb_tree_iterator operator =(const rb_tree_iterator &cpy)
		{
			_base = cpy.get_base();
			_tree_root = cpy.get_root();
			_position = cpy.get_position();
			return *this;
		};

		reference	operator*() const
		{
			if (_position == it_bbegin)
				return _base->left->value; //Segfault
			else if (_position == it_end)
				return _base->right->value; //Segfault
			return _base->value;
		};
		pointer		operator->() const
		{
			if (_position == it_bbegin)
				return &_base->left->value; //Address of NULL
			else if (_position == it_end)
				return &_base->right->value; //Address of NULL
			return &_base->value;
		};

		rb_tree_iterator&	operator++()
		{
			if (_position == it_bbegin)
			{
				_base = this->tree_minimum(*_tree_root);
				_position = it_middle;
			}
			else if (_position != it_end)
			{
				base_ptr tmp = tree_successor(_base);
				if (tmp->parent == NULL)
					_position = it_end;
				else
					_base = tmp;
			}
			return *this;
		};

		rb_tree_iterator	operator++(int)
		{
			rb_tree_iterator current_base(*this);
			if (_position == it_bbegin)
			{
				_base = this->tree_minimum(*_tree_root);
				_position = it_middle;
			}
			else if (_position != it_end)
			{
				base_ptr tmp = tree_successor(_base);
				if (tmp->parent == NULL)
					_position = it_end;
				else
					_base = tmp;
			}
			return current_base;
		};

		rb_tree_iterator&	operator--()
		{
			if (_position == it_end)
			{
				_base = this->tree_maximum(*_tree_root);
				_position = it_middle;
			}
			else if (_position != it_bbegin)
			{
				base_ptr tmp = tree_predecessor(_base);
				if (tmp->parent == NULL)
					_position = it_bbegin;
				else
					_base = tmp;
			}
			return *this;
		};

		rb_tree_iterator	operator--(int)
		{
			rb_tree_iterator current_base(*this);
			if (_position == it_end)
			{
				_base = this->tree_maximum(*_tree_root);
				_position = it_middle;
			}
			else if (_position != it_bbegin)
			{
				base_ptr tmp = tree_predecessor(_base);
				if (tmp->parent == NULL)
					_position = it_bbegin;
				else
					_base = tmp;
			}
			return current_base;
		};
	
		private:
		base_ptr tree_minimum(base_ptr start) const
		{
			if (start == NULL || start->left == NULL)
				return NULL;
			base_ptr node = start;
			while (node->left->left != NULL)
			{
				node = node->left;
			}
			return node;
		};

		base_ptr tree_maximum(base_ptr start) const
		{
			if (start == NULL || start->right == NULL)
				return NULL;
			base_ptr node = start;
			while (node->right->right != NULL)
			{
				node = node->right;
			}
			return node;
		};

		base_ptr	tree_predecessor(base_ptr node) const
		{
			if (node == NULL || node->parent == NULL)
				return NULL;
			else if (node->left->parent != NULL) //Left node is not the sentinel
				return tree_maximum(node->left);
			else
			{
				while (node->parent->parent != NULL && node->parent->left == node)
				{
					node = node->parent;
				}
			}
			return node->parent;
		};

		base_ptr	tree_successor(base_ptr node) const
		{
			if (node->right->right != NULL)
			{
				return tree_minimum(node->right);
			}
			base_ptr parent = node->parent;
			while (parent->parent != NULL && parent->right == node)
			{
				node = parent;
				parent = parent->parent;
			}
			return parent;
		};

		friend
		bool	operator==(const rb_tree_iterator &lhs, const rb_tree_iterator &rhs)
		{
			if (lhs.get_position() == it_end && rhs.get_position() == it_end)
				return true;
			return (lhs._base == rhs._base && lhs._position == rhs._position);
		};

		friend
		bool	operator!=(const rb_tree_iterator &lhs, const rb_tree_iterator &rhs)
		{
			return !(lhs == rhs);
		};
	};

	template<typename T>
	class rb_tree_const_iterator: public ft::iterator<
		std::bidirectional_iterator_tag,
		T
	> {
		private:
		typedef TreeNode<T>					base;
		typedef base *						base_ptr;
		typedef rb_tree_const_iterator<T>	self;

		public:
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef const T         				value_type;
		typedef typename std::ptrdiff_t			difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;

		private:
		base_ptr	_base;
		base_ptr *	_tree_root;
		position_t	_position;

		public:
		rb_tree_const_iterator(void):
			_base(),
			_tree_root(NULL),
			_position(it_middle)
		{};
		
		rb_tree_const_iterator(rb_tree_iterator<T> it):
			_base(it.get_base()),
			_tree_root(it.get_root()),
			_position(it.get_position())
		{};

		template<typename Iter>
		rb_tree_const_iterator(const rb_tree_const_iterator<Iter>& cpy):
			_base(cpy.get_base()),
			_tree_root(cpy.get_root()),
			_position(cpy.get_position())
		{};

		rb_tree_const_iterator(base_ptr base, base_ptr const *root,  position_t position = it_middle):
			_base(base),
			_tree_root(const_cast<base_ptr *>(root)),
			_position(position)
		{};

		~rb_tree_const_iterator(void) {};

		rb_tree_const_iterator operator =(const rb_tree_const_iterator &cpy)
		{
			_base = cpy.get_base();
			_tree_root = cpy.get_root();
			_position = cpy.get_position();
			return *this;
		};

		base_ptr get_base() const { return this->_base; };
		base_ptr *get_root() const { return this->_tree_root; };
		position_t get_position() const { return this->_position; };

		reference	operator*() const
		{
			if (_position == it_bbegin)
				return _base->left->value; //Segfault
			else if (_position == it_end)
				return _base->right->value; //Segfault
			return _base->value;
		};
		pointer		operator->() const
		{
			if (_position == it_bbegin)
				return &_base->left->value; //Address of NULL
			else if (_position == it_end)
				return &_base->right->value; //Address of NULL
			return &_base->value;
		};

		rb_tree_const_iterator&	operator++()
		{
			if (_position == it_bbegin)
			{
				_base = this->tree_minimum(*_tree_root);
				_position = it_middle;
			}
			else if (_position != it_end)
			{
				base_ptr tmp = tree_successor(_base);
				if (tmp->parent == NULL)
					_position = it_end;
				else
					_base = tmp;
			}
			return *this;
		};

		rb_tree_const_iterator	operator++(int)
		{
			rb_tree_const_iterator current_base(*this);
			if (_position == it_bbegin)
			{
				_base = this->tree_minimum(*_tree_root);
				_position = it_middle;
			}
			else if (_position != it_end)
			{
				base_ptr tmp = tree_successor(_base);
				if (tmp->parent == NULL)
					_position = it_end;
				else
					_base = tmp;
			}
			return current_base;
		};

		rb_tree_const_iterator&	operator--()
		{
			if (_position == it_end)
			{
				_base = this->tree_maximum(*_tree_root);
				_position = it_middle;
			}
			else if (_position != it_bbegin)
			{
				base_ptr tmp = tree_predecessor(_base);
				if (tmp->parent == NULL)
					_position = it_bbegin;
				else
					_base = tmp;
			}
			return *this;
		};

		rb_tree_const_iterator	operator--(int)
		{
			rb_tree_const_iterator current_base(*this);
			if (_position == it_end)
			{
				_base = this->tree_maximum(*_tree_root);
				_position = it_middle;
			}
			else if (_position != it_bbegin)
			{
				base_ptr tmp = tree_predecessor(_base);
				if (tmp->parent == NULL)
					_position = it_bbegin;
				else
					_base = tmp;
			}
			return current_base;
		};
	
		private:
		base_ptr tree_minimum(base_ptr start) const
		{
			if (start == NULL || start->left == NULL)
				return NULL;
			base_ptr node = start;
			while (node->left->left != NULL)
			{
				node = node->left;
			}
			return node;
		};

		base_ptr tree_maximum(base_ptr start) const
		{
			if (start == NULL || start->right == NULL)
				return NULL;
			base_ptr node = start;
			while (node->right->right != NULL)
			{
				node = node->right;
			}
			return node;
		};

		base_ptr	tree_predecessor(base_ptr node) const
		{
			if (node == NULL || node->parent == NULL)
				return NULL;
			else if (node->left->parent != NULL) //Left node is not the sentinel
				return tree_maximum(node->left);
			else
			{
				while (node->parent->parent != NULL && node->parent->left == node)
				{
					node = node->parent;
				}
			}
			return node->parent;
		};

		base_ptr	tree_successor(base_ptr node) const
		{
			if (node->right->right != NULL)
			{
				return tree_minimum(node->right);
			}
			base_ptr parent = node->parent;
			while (parent->parent != NULL && parent->right == node)
			{
				node = parent;
				parent = parent->parent;
			}
			return parent;
		};

		friend
		bool	operator==(const rb_tree_const_iterator &lhs, const rb_tree_const_iterator &rhs)
		{
			if (lhs.get_position() == it_end && rhs.get_position() == it_end)
			{
				return true;
			}
			return (lhs._base == rhs._base) && (lhs._position == rhs._position);
		};
		
		friend
		bool	operator!=(const rb_tree_const_iterator &lhs, const rb_tree_const_iterator &rhs)
		{
			return !(lhs == rhs);
		};
	};
}

#endif
