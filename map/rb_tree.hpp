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
		
		// typedef typename std::allocator_traits<Alloc>::template rebind_alloc<Node<Value> > node_allocator;
        private:
        value_compare       			compare;
        allocator_type					allocator;
		node_allocator					node_alloc;
        tree_node						*_nil; //should be const
        tree_node						*_root;

		public:
        rb_tree(value_compare cmp, allocator_type alloc) : 
			compare(cmp),
			allocator(alloc)
		{
			// node_alloc = allocator_type::template rebind<Node<value_type> >::other;
			// alloc::template rebind<Node<value_type> >::other;
			_nil = create_node();
			_root = NULL;
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