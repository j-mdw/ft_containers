#ifndef FT_RB_MAP_HPP
# define FT_RB_MAP_HPP

#include "map.hpp"
#include <iostream> //For print methods --> DELETE
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

        Node(void) :
            color(black),
            parent(NULL),
            left(NULL),
            right(NULL) {
            };

        Node(color_t color, T val) :
            color(color),
            value(val),
            parent(NULL),
            left(NULL),
            right(NULL) {
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
        const tree_node					*_nil; //should be const
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
			}
		};
		
		/*
		 ### ROTATIONS ###
		*/
		/*
		void	right_rotate(tree_node *node)
		{
			if (!node || node->parent == _nil)
				return ;
			tree_node *node_right = node->right;
			node->right = node->parent;
			node->parent = node->parent->parent;
			node->right->left = node_right;
		}

		void	left_rotate(tree_node *node)
		{
			if (!node || node->parent == _nil)
				return ;
			tree_node *node_left = node->left;
			node->left = node->parent;
			node->parent = node->parent->parent;
			node->left->right = node_left;
		}

		void	left_rotate(tree_node *old_parent)
		{
			if (!old_parent || old_parent->right == _nil) //Not sure about the nil check
				return ;
			
			tree_node *new_parent = old_parent->right;

			//Set new_parent as old_parent's parent, and then set new_parent as old_parent's parent left or right child
			new_parent->parent = old_parent->parent;
			if (old_parent->parent != _nil)
			{
				if (old_parent == old_parent->parent->left)
				{
					old_parent->parent->left = new_parent;
				}
				else
				{
					old_parent->parent->right = new_parent;
				}
			}
			old_parent->parent = new_parent;

			old_parent->right = new_parent->left;
			if (new_parent->left != _nil)
			{
				old_parent->right->parent = old_parent;
			}
			new_parent->left = old_parent;
		}
		*/
		void	print_tree(void) // DELETE --> Testing only
		{
			in_order_walk(_root, &rb_tree::print_pair);
		};
		
		void	print_pair(tree_node *node) // DELETE --> Only for map testing 
		{
			std::cout << "key: " << node->value.first << " value: " << node->value.second << '\n';
		};

		private:
		void	delete_node(tree_node *node)
		{
			node_alloc.destroy(node);
			node_alloc.deallocate(node, 1);
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
        
		void post_order_walk(tree_node *node, void (rb_tree::*f)(tree_node *))
		{
			if (node == _nil)
				return ;

			post_order_walk(node->left, f);
			post_order_walk(node->right, f);
			(this->*f)(node);
		};
		
		void in_order_walk(tree_node *node, void (rb_tree::*f)(tree_node *))
		{
			if (node == _nil)
				return ;

			in_order_walk(node->left, f);
			(this->*f)(node);
			in_order_walk(node->right, f);
		};
    };
}

#endif