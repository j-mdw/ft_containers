#ifndef FT_RB_MAP_HPP
# define FT_RB_MAP_HPP

#include "map.hpp"
#include "../utils/iterator/iterator.hpp"
#include "rb_tree_iterator.hpp"
# include <queue> //Used for breadth_first_traversal

// #define DEBUG 1 //TBU --> Need makefile implementation
#ifdef DEBUG
	# include <iostream> //For print methods --> DELETE
	# include <cmath>
#endif

namespace ft
{
    template<
            class Value,
            class Comp,   
            class Alloc = std::allocator<TreeNode<Value> >
            >
    class rb_tree
    {
		public:
        typedef Value   			value_type;
        typedef Comp    			value_compare;
		typedef	Alloc   			allocator_type;
		typedef TreeNode<value_type>	tree_node;
		typedef typename allocator_type::template rebind<TreeNode<value_type> >::other node_allocator;
		typedef rb_tree_iterator<value_type>		iterator;
		typedef rb_tree_const_iterator<value_type>	const_iterator;

		private:
		typedef rb_tree<value_type, value_compare, allocator_type>	self;

        private:
        value_compare       compare;
        allocator_type		allocator;
		node_allocator		node_alloc;
        tree_node			*_nil; //should be const
        tree_node			*_root;
		size_t				_size;

		public:
        rb_tree(value_compare cmp, allocator_type alloc) : 
			compare(cmp),
			allocator(alloc),
			_nil(create_node()),
			_root(NULL),
			_size(0)
		{
		#ifdef DEBUG
			_nil->id = -1;
			_nil->parent_id = -1;
		#endif
		};

		rb_tree(const rb_tree &x):
			compare(x.compare),
			allocator(x.allocator),
			node_alloc(x.node_alloc),
			_nil(create_node()),
			_root(NULL),
			_size(x._size)
		{
			if (x._size > 0)
			{
				_root = new tree_node(*x._root);
				copy_tree(_root, x._root, x._nil);
			}
		};

		rb_tree& operator= (const rb_tree& x)
		{
			if (_size > 0)
			{
				delete_tree();
			}
			compare = x.compare;
			_size = x._size;
			_root = new tree_node(*x._root);
			copy_tree(_root, x._root, x._nil);
			return *this;
		}
        
		~rb_tree(void)
		{
			if (_root != NULL)
				delete_tree();
			delete_node(_nil);
        };

		size_t			size(void) const { return _size; };
		size_t			max_size(void) const { return node_alloc.max_size(); };

		iterator		begin(void)
		{
			if (_size == 0)
				return this->end();
			return iterator(this->minimum(_root), &_root, it_middle);
		};

		const_iterator	begin(void) const
		{
			if (_size == 0)
				return this->end();
			return const_iterator(this->minimum(_root), &_root, it_middle);
		};

		iterator		end(void) {	return iterator(this->maximum(_root), &_root, it_end);};
		const_iterator	end(void) const { return const_iterator(this->maximum(_root), &_root, it_end); };

		void		swap(self &tree)
		{
			tree_node	*tmp_root = this->_root;
			tree_node	*tmp_nil = this->_nil;
			size_t		tmp_size = this->_size;

			this->_root = tree._root;
			this->_nil = tree._nil;
			this->_size = tree._size;

			tree._root = tmp_root;
			tree._nil = tmp_nil;
			tree._size = tmp_size;
		};

		pair<iterator, bool>	insert(const value_type &val)
		{
			ft::pair<iterator, bool> ret;
			tree_node *to_insert = this->search(val);
			if (to_insert != NULL)
			{
				ret.first = iterator(to_insert, &_root, it_middle);
				ret.second = false;
			}
			else
			{
				_size++;
				to_insert = create_node(tree_node::red, val);
				to_insert->right = _nil;
				to_insert->left = _nil;
				if (_root == NULL)
				{
					_root = to_insert;
					_root->parent = _nil;
					to_insert->color = tree_node::black;
				}
				else
				{
					tree_node *parent = _root;
					while (1)
					{
						if (compare(to_insert->value, parent->value) == true)
						{
							if (parent->left == _nil)
							{
								parent->left = to_insert;
								to_insert->parent = parent;
								break ;
							}
							parent = parent->left;
						}
						else
						{
							if (parent->right == _nil)
							{
								parent->right = to_insert;
								to_insert->parent = parent;
								break ;
							}
							parent = parent->right;
						}
					}
					insert_fixup(to_insert);
				}
				ret.first = iterator(to_insert, &_root, it_middle);
				ret.second = true;
			}
			return ret;
		};

		/*
			At this stage, 2 RB tree conditions might be violated:
			1. node's parent might be red
			2. root could be red

			Otherwise, we know that black depth property is respected
		*/

		void	insert_fixup(tree_node *node)
		{
			tree_node *current_node = node;

			while (current_node->parent->color == tree_node::red)
			{
				if (current_node->parent == current_node->parent->parent->left)
				{
					if (right_uncle(current_node)->color == tree_node::red)
					{
						current_node->parent->color = tree_node::black;
						right_uncle(current_node)->color = tree_node::black;
						current_node->parent->parent->color = tree_node::red;
						current_node = current_node->parent->parent;
					}
					else
					{
						if (current_node == current_node->parent->right)
						{
							current_node = current_node->parent;
							left_rotate(current_node);
						}
						if (current_node == current_node->parent->left)
						{
							current_node->parent->color = tree_node::black;
							current_node->parent->parent->color = tree_node::red;
							right_rotate(current_node->parent->parent);
						}
					}
				}
				else
				{
					if (left_uncle(current_node)->color == tree_node::red)
					{
						current_node->parent->color = tree_node::black;
						left_uncle(current_node)->color = tree_node::black;
						current_node->parent->parent->color = tree_node::red;
						current_node = current_node->parent->parent;
					}
					else
					{
						if (current_node == current_node->parent->left)
						{
							current_node = current_node->parent;
							right_rotate(current_node);
						}
						if (current_node == current_node->parent->right)
						{
							current_node->parent->color = tree_node::black;
							current_node->parent->parent->color = tree_node::red;
							left_rotate(current_node->parent->parent);
						}
					}
				}
			}
			if (current_node->parent == _nil)
			{
				_root = current_node;
			}
			_root->color = tree_node::black;
		};
		
		tree_node *right_uncle(tree_node *node)
		{
			return node->parent->parent->right;
		};
		tree_node *left_uncle(tree_node *node)
		{
			return node->parent->parent->left;
		};

		iterator	find(value_type &val)
		{
			tree_node *node = this->search(val);
			if (node != NULL)
				return iterator(node, &_root);
			return this->end();
		};

		const_iterator	find(value_type &val) const
		{
			tree_node *node = this->search(val);
			if (node != NULL)
				return const_iterator(node, &_root);
			return this->end();
		};

		tree_node *search(value_type val) const
		{
			if (_root == NULL)
				return NULL;
			tree_node *node = _root;
			while (node != _nil)
			{
				if (compare(val, node->value) == true)
					node = node->left;
				else if (compare(node->value, val) == false) //values are equal
					return node;
				else
					node = node->right;
			}
			if (node == _nil)
				node = NULL;
			return node;
		};

		bool	remove(value_type &val)
		{
			tree_node *node = this->search(val);
			if (node != NULL)
			{
				_size--;
				// std::cout << "Removing node: " << node->value.first << " ; " << node->value.second << '\n';
				this->remove_node(node);
				return true;
			}
			return false;
		};

		void	remove_node(tree_node *to_delete)
		{
			typename tree_node::color_t original_color = to_delete->color;
			tree_node *to_fix;
			if (to_delete == NULL)
				return ;
			if (
				to_delete == _root &&
				to_delete->right == _nil &&
				to_delete->left == _nil
			) {
				delete_node(_root);
				_root = NULL;
				return;
			}
			if (to_delete->right == _nil)
			{
				to_fix = to_delete->left;
				transplant(to_delete, to_delete->left);
			}
			else if (to_delete->left == _nil)
			{
				to_fix = to_delete->right;
				transplant(to_delete, to_delete->right);
			}
			else
			{
				tree_node *subtitute = minimum(to_delete->right);
				original_color = subtitute->color;

				to_fix = subtitute->right;

				if (subtitute->parent != to_delete)
				{
					transplant(subtitute, subtitute->right);
					subtitute->right = to_delete->right;
					subtitute->right->parent = subtitute;
				}
				else
				{
					to_fix->parent = subtitute; //in case to_fix is nil
				}

				transplant(to_delete, subtitute);
				subtitute->left = to_delete->left;
				subtitute->left->parent = subtitute;
				subtitute->color = to_delete->color;
			}
			delete_node(to_delete);
			if (original_color == tree_node::black)
			{
				remove_fixup(to_fix);
			}
			_nil->parent = NULL;
		};

		void	remove_fixup(tree_node *node)
		{
			tree_node *to_fix = node;
			while (to_fix != _root && to_fix->color == tree_node::black)
			{
				if (to_fix == to_fix->parent->left)
				{
					tree_node *sibling = to_fix->parent->right;
					if (sibling->color == tree_node::red)
					{
						sibling->color = tree_node::black;
						to_fix->parent->color = tree_node::red;
						left_rotate(to_fix->parent);
						sibling = to_fix->parent->right;
					}
					if (sibling->left->color == tree_node::black &&
					sibling->right->color == tree_node::black)
					{
						sibling->color = tree_node::red;
						to_fix = to_fix->parent;
					}
					else
					{
						if (sibling->right->color == tree_node::black)
						{
							sibling->left->color = tree_node::black;
							sibling->color = tree_node::red;
							right_rotate(sibling);
							sibling = to_fix->parent->right;
						}
						sibling->color = to_fix->parent->color;
						to_fix->parent->color = tree_node::black;
						sibling->right->color = tree_node::black;
						left_rotate(to_fix->parent);
						to_fix = _root;
					}
				}
				else
				{
					tree_node *sibling = to_fix->parent->left;
					if (sibling->color == tree_node::red)
					{
						sibling->color = tree_node::black;
						to_fix->parent->color = tree_node::red;
						right_rotate(to_fix->parent);
						sibling = to_fix->parent->left;
					}
					if (sibling->right->color == tree_node::black &&
					sibling->left->color == tree_node::black)
					{
						sibling->color = tree_node::red;
						to_fix = to_fix->parent;
					}
					else
					{
						if (sibling->left->color == tree_node::black)
						{
							sibling->right->color = tree_node::black;
							sibling->color = tree_node::red;
							left_rotate(sibling);
							sibling = to_fix->parent->left;
						}
						sibling->color = to_fix->parent->color;
						to_fix->parent->color = tree_node::black;
						sibling->left->color = tree_node::black;
						right_rotate(to_fix->parent);
						to_fix = _root;
					}
				}
			}
			to_fix->color = tree_node::black;
		};

		void	transplant(tree_node *current, tree_node *transplanted)
		{
			if (current == _root)
			{
				_root = transplanted;
			}
			else if (current == current->parent->right)
			{
				current->parent->right = transplanted;
			}
			else
			{
				current->parent->left = transplanted;
			}
			transplanted->parent = current->parent;
			
		#ifdef DEBUG
			transplanted->parent_id = current->parent_id;
		#endif
		};

		tree_node *minimum(tree_node *start) const
		{
			if (start == NULL || start == _nil)
				return NULL;
			tree_node *node = start;
			while (node->left != _nil)
			{
				node = node->left;
			}
			return node;
		}

		tree_node *maximum(tree_node *start) const
		{
			if (start == NULL || start == _nil)
				return NULL;
			tree_node *node = start;
			while (node->right != _nil)
			{
				node = node->right;
			}
			return node;
		}

		tree_node *predecessor(tree_node *node) const
		{
			// if (node == _nil) //Handling the case where a user asks for _nil-- (maybe not the right place to do this)
			// {
			// 	return this->maximum(_root);
			// }
			if (node->left != _nil)
			{
				return maximum(node->left);
			}
			tree_node *parent = node->parent;
			// while (parent != _nil && parent->left == node)
			while (parent != _nil && parent->left == node)
			{
				node = parent;
				parent = parent->parent;
			}
			if (parent->left)
			{
				return maximum(parent->left);
			}
			return parent;
		};

		tree_node *successor(tree_node *node) const
		{
			if (node->right != _nil)
			{
				return minimum(node->right);
			}
			tree_node *parent = node->parent;
			while (parent != _nil && parent->right == node)
			{
				node = parent;
				parent = parent->parent;
			}
			return parent;
		};
		public:
		iterator lower_bound (value_type &val)
		{
			tree_node *lower = get_lower_bound(_root, val);
			if (lower == _nil)
				return iterator(maximum(_root), &_root, it_end);
			return iterator(lower, &_root);
		};

		const_iterator lower_bound (value_type &val) const
		{
			tree_node *lower = get_lower_bound(_root, val);
			if (lower == _nil)
				return const_iterator(maximum(_root), &_root, it_end);
			return const_iterator(lower, &_root);
		};

		private:
		tree_node *get_lower_bound(tree_node *node, value_type &val) const
		{
			if (node == _nil)
				return _nil;
			tree_node * bound = get_lower_bound(node->left, val);
			if (bound != _nil)
				return bound;
			if (compare(val, node->value))
				return node;
			else if (!(compare(node->value, val)))
				return node;
			return get_lower_bound(node->right, val);
		};

		public:
		iterator upper_bound (value_type &val)
		{
			tree_node *lower = get_upper_bound(_root, val);
			if (lower == _nil)
				return iterator(maximum(_root), &_root, it_end);
			return iterator(lower, &_root);
		};

		const_iterator upper_bound (value_type &val) const
		{
			tree_node *lower = get_upper_bound(_root, val);
			if (lower == _nil)
				return const_iterator(maximum(_root), &_root, it_end);
			return const_iterator(lower, &_root);
		};

		private:
		tree_node *	get_upper_bound(tree_node *node, value_type &val) const
		{
			if (node == _nil)
				return _nil;

			tree_node * bound = get_upper_bound(node->left, val);
			if (bound != _nil)
				return bound;
			if (compare(val, node->value))
				return node;
			bound = get_upper_bound(node->right, val);
			return bound;
		};

	
		/*
		 ### ROTATIONS ###
		*/

		void	left_rotate(tree_node *old_parent)
		{
			if (!old_parent || old_parent->right == _nil) //Not sure about the nil check
			{
			#ifdef DEBUG
				std::cout << "Rotate received unexpected parameter: NULL node or non-rotable node\n";
			#endif
				return ;
			}
			
			tree_node *new_parent = old_parent->right;

			//Set new_parent as old_parent's parent, and then set new_parent as old_parent's parent left or right child
			new_parent->parent = old_parent->parent;
			if (old_parent->parent == _nil)
			{
				_root = new_parent;
			}
			else if (old_parent == old_parent->parent->left)
			{
				old_parent->parent->left = new_parent;
			}
			else
			{
				old_parent->parent->right = new_parent;
			}
			old_parent->parent = new_parent;

			old_parent->right = new_parent->left;
			if (new_parent->left != _nil)
			{
				old_parent->right->parent = old_parent;
			}
			new_parent->left = old_parent;
			old_parent->parent = new_parent;
		};

		void	right_rotate(tree_node *old_parent)
		{
			if (!old_parent || old_parent->left == _nil) //Not sure about the nil check
			{
			#ifdef DEBUG
				std::cout << "Rotate received unexpected parameter: NULL node or non-rotable node\n";
			#endif
				return ;
			}
			
			tree_node *new_parent = old_parent->left;

			//Set new_parent as old_parent's parent, and then set new_parent as old_parent's parent left or right child
			new_parent->parent = old_parent->parent;
			if (old_parent->parent == _nil)
			{
				_root = new_parent;
			}
			else if (old_parent == old_parent->parent->left)
			{
				old_parent->parent->left = new_parent;
			}
			else
			{
				old_parent->parent->right = new_parent;
			}
			old_parent->parent = new_parent;

			old_parent->left = new_parent->right;
			if (new_parent->right != _nil)
			{
				old_parent->left->parent = old_parent;
			}
			new_parent->right = old_parent;
			old_parent->parent = new_parent;
		}

		void	print_tree(void) // DELETE --> Testing only
		{
			// in_order_walk(_root, &rb_tree::print_pair);
			breadth_first_traversal(_root, &rb_tree::print_pair);
		};
		
		void	print_pair(tree_node *node, bool line_break = true) // DELETE --> Only for map testing 
		{
			if (!node)
				return ;
			std::cout << "[ ";
			if (node->color == tree_node::red)
				std::cout << "RED, {";
			else
				std::cout << "BLK, {";
			
			std::cout << node->value.first << " : " << node->value.second << "} ; ";
			
			if (node->parent == _nil)
				std::cout << "nil | ";
		#ifdef DEBUG
			else
				std::cout << node->parent_id << " | ";
			std::cout << node->id;
		#endif
			std::cout << " ]\t";

			if (line_break)
				std::cout << '\n';
		};

		void	breadth_first_traversal(tree_node *node, void (rb_tree::*f)(tree_node *, bool))
		{
			if (node == NULL || node == _nil)
				return ;
			std::queue<tree_node *> queue;
		#ifdef DEBUG
			size_t current_level_node_count = 0;
			size_t next_level_node_count = 0;
			int	level = 1;
		#endif
			queue.push(node);
		#ifdef DEBUG
			current_level_node_count++;
			node->id = 0;
			node->parent_id = 0;
		#endif
			while (!queue.empty())
			{
				tree_node *current_node = queue.front();
				queue.pop();
				(this->*f)(current_node, false);
				if (current_node->left != _nil)
				{
				#ifdef DEBUG
					current_node->left->parent_id = current_node->id;
					current_node->left->id = pow(2, level) + next_level_node_count;
					next_level_node_count++;
				#endif
					queue.push(current_node->left);
				}
				if (current_node->right != _nil)
				{
				#ifdef DEBUG
					current_node->right->parent_id = current_node->id;
					current_node->right->id = pow(2, level) + next_level_node_count;
					next_level_node_count++;
				#endif
					queue.push(current_node->right);
				}
			#ifdef DEBUG
				current_level_node_count--;
				if (current_level_node_count == 0)
				{
					std::cout << '\n';
					current_level_node_count = next_level_node_count;
					next_level_node_count = 0;
					level++;
				}
			#endif
			}
		};

		tree_node *get_root(void) { return _root; }

		private:
		void	delete_node(tree_node *node, bool flag = false)
		{
			node_alloc.destroy(node);
			node_alloc.deallocate(node, 1);
			(void)flag;
		};
		
		public:
		void	delete_tree(void)
		{
			post_order_walk(_root, &rb_tree::delete_node);
			_root = NULL;
			_size = 0;
		};

		private:
		tree_node * create_node(void)
		{
			tree_node *node = node_alloc.allocate(1);
			node_alloc.construct(node, tree_node());
			return node;
		};

		tree_node * create_node(typename tree_node::color_t color, const value_type &val)
		{
			tree_node * node = node_alloc.allocate(1);
			node_alloc.construct(node, tree_node(color, val));
			return node;
		};
        
		void post_order_walk(tree_node *node, void (rb_tree::*f)(tree_node *, bool))
		{
			if (node == _nil)
				return ;

			post_order_walk(node->left, f);
			post_order_walk(node->right, f);
			(this->*f)(node, false);
		};
		
		void in_order_walk(tree_node *node, void (rb_tree::*f)(tree_node *, bool))
		{
			if (node == _nil)
				return ;

			in_order_walk(node->left, f);
			(this->*f)(node, false);
			in_order_walk(node->right, f);
		};
		
		void	copy_tree(tree_node *my_node, tree_node *cpy_node, tree_node *cpy_nil)
		{
			std::queue<tree_node *> my_queue;
			std::queue<tree_node *> cpy_queue;
			my_queue.push(my_node);
			cpy_queue.push(cpy_node);

			while (!cpy_queue.empty())
			{
				tree_node *my_current_node = my_queue.front();
				my_queue.pop();
				
				tree_node *cpy_current_node = cpy_queue.front();
				cpy_queue.pop();

				if (cpy_current_node->left != cpy_nil)
				{
					my_current_node->left = new tree_node(*cpy_current_node->left);
					my_current_node->left->parent = my_current_node;
					cpy_queue.push(cpy_current_node->left);
					my_queue.push(my_current_node->left);
				}
				else
				{
					my_current_node->left = _nil;
				}
				if (cpy_current_node->right != cpy_nil)
				{
					my_current_node->right = new tree_node(*cpy_current_node->right);
					my_current_node->right->parent = my_current_node;
					cpy_queue.push(cpy_current_node->right);
					my_queue.push(my_current_node->right);
				}
				else
				{
					my_current_node->right = _nil;
				}
			}
		};
	};
}

#endif