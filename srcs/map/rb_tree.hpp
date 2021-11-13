#ifndef FT_RB_MAP_HPP
# define FT_RB_MAP_HPP

#include "map.hpp"

#define DEBUG 1 //Need makefile implementation
#ifdef DEBUG
# include <iostream> //For print methods --> DELETE
# include <queue> //Used for breadth_first_traversal
# include <cmath>
#endif

namespace ft
{
    template<typename T>
    class Node
    {
		public:
        typedef enum {
            red,
            black
        } color_t;

        color_t color;
		T       value;
        Node    *parent;
        Node    *left;
        Node    *right;
		#ifdef DEBUG
			int		id; //DEBUG
			int		parent_id; //DEBUG
		#endif

        Node(void) :
            color(black),
            parent(NULL),
            left(NULL),
            right(NULL) {
				#ifdef DEBUG
					id = 0; //DEBUG
					parent_id = 0; //DEBUG
				#endif
            };

        Node(color_t color, T val) :
            color(color),
            value(val),
            parent(NULL),
            left(NULL),
            right(NULL) {
				#ifdef DEBUG
					id = 0; //DEBUG
					parent_id = 0; //DEBUG
				#endif
            };

        ~Node(void) {};
    };

    template<
            class Value,
            class Comp,   
            class Alloc = std::allocator<Node<Value> >
            >
    class rb_tree
    {
		public:
        typedef Value   			value_type;
        typedef Comp    			value_compare;
		typedef	Alloc   			allocator_type;
		typedef Node<value_type>	tree_node;
		typedef typename allocator_type::template rebind<Node<value_type> >::other node_allocator;
		
        private:
        value_compare       			compare;
        allocator_type					allocator;
		node_allocator					node_alloc;
        tree_node					*_nil; //should be const
        tree_node						*_root;

		public:
        rb_tree(value_compare cmp, allocator_type alloc) : 
			compare(cmp),
			allocator(alloc),
			_nil(create_node()),
			_root(NULL) {
		};
        
		~rb_tree(void)
		{
			if (_root != NULL)
				delete_tree();

			delete_node(_nil);
        };

		void	insert(value_type val)
		{
			tree_node * to_insert = create_node(tree_node::red, val);
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
			rb_tree_fixup(to_insert);
			}
			std::cout << "Node inserted\n";
		};

		/*
			At this stage, 2 RB tree conditions might be violated:
			1. node's parent might be red
			2. root could be red

			Otherwise, we know that black depth property is respected
		*/

		void	rb_tree_fixup(tree_node *node)
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


		tree_node *search(value_type val)
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
				return NULL;
			return node;
		};

		void	remove(tree_node *to_delete)
		{
			tree_node::color_t original_color = to_delete->color;
			tree_node *to_fix;
			if (to_delete == NULL)
				return ;
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
				// if (subtitute->right != _nil)
				to_fix = subtitute->right;
				// else if (subtitute->parent != to_delete)
				// {
				// 	to_fix = subtitute->parent;
				// }
				// else
				// {
				// 	to_fix = subtitute;
				// }

				if (subtitute->parent != to_delete)
				{
					transplant(subtitute, subtitute->right);
					subtitute->right = to_delete->right;
					subtitute->right->parent = subtitute;
				}
				// else
				// {
				// 	subtitute->parent->right
				// }
				transplant(to_delete, subtitute);
				subtitute->left = to_delete->left;
				if (subtitute->left != _nil)
					subtitute->left->parent = subtitute;
				subtitute->color = to_delete->color;
			}
			delete_node(to_delete);
			if (to_fix == _nil)
			{
				to_fix = to_fix->parent;
				_nil->parent = NULL;
			}
			if (original_color == tree_node::black)
				remove_fixup(to_fix);
		};

		void	remove_fixup(tree_node) {};

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
		};

		tree_node *minimum(tree_node *start)
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

		tree_node *maximum(tree_node *start)
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
		}

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
				std::cout << "RED, ";
			else
				std::cout << "BLK, {";
			
			std::cout << node->value.first << " : " << node->value.second << "} ; ";
			
			if (node->parent == _nil)
				std::cout << "nil | ";
			else
				std::cout << node->parent_id << " | ";
			std::cout << node->id << " ]\t";
			// if (node->left == _nil)
			// 	std::cout << "nil | ";
			// else
			// 	std::cout << node->left << " | ";
			// if (node->right == _nil)
			// 	std::cout << "nil | ";
			// else
			// 	std::cout << node->right << " ] ";

			if (line_break)
				std::cout << '\n';
		};

		void	breadth_first_traversal(tree_node *node, void (rb_tree::*f)(tree_node *, bool))
		{
			if (node == NULL)
				return ;
			std::queue<tree_node *> queue;
			size_t current_level_node_count = 0;
			size_t next_level_node_count = 0;
			int	level = 1;
			queue.push(node);
			current_level_node_count++;
			node->id = 0;
			node->parent_id = 0;
			while (!queue.empty())
			{
				tree_node *current_node = queue.front();
				queue.pop();
				(this->*f)(current_node, false);
				if (current_node->left != _nil)
				{
					current_node->left->parent_id = current_node->id;
					current_node->left->id = pow(2, level) + next_level_node_count;

					queue.push(current_node->left);
					next_level_node_count++;
				}
				if (current_node->right != _nil)
				{
					current_node->right->parent_id = current_node->id;
					current_node->right->id = pow(2, level) + next_level_node_count;

					queue.push(current_node->right);
					next_level_node_count++;
				}
				current_level_node_count--;
				if (current_level_node_count == 0)
				{
					std::cout << '\n';
					current_level_node_count = next_level_node_count;
					next_level_node_count = 0;
					level++;
				}
			}
		}

		tree_node *get_root(void) { return _root; }

		private:
		void	delete_node(tree_node *node, bool flag = false)
		{
			node_alloc.destroy(node);
			node_alloc.deallocate(node, 1);
			(void)flag;
		};

		void	delete_tree(void)
		{
			post_order_walk(_root, &rb_tree::delete_node);
		};

		tree_node * create_node(void)
		{
			tree_node *node = node_alloc.allocate(1);
			node_alloc.construct(node, tree_node());
			return node;
		};

		tree_node * create_node(typename tree_node::color_t color, value_type val)
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
    };
}

#endif