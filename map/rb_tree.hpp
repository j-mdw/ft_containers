#ifndef FT_RB_MAP_HPP
# define FT_RM_MAP_HPP

#include "map.hpp"

key/value types
compare function
allocator


template<
        class Key,
		class T,                
		class Compare = std::less<Key>,    
		class Alloc = std::allocator<pair<const Key, T> >
        >
    class rb_tree
    {
        private:

        typedef enum {
            red,
            black
        } color_t;

        typedef struct node_s {
            color   color;
            node_s *parent;
            node_s *left;
            node_s *right;
            Key     key;
            T       value;
        } node_t;

        const node_t    *nil;
        node_t          *root;

        rb_tree(void) : nil(new node_t(black, NULL, NULL, NULL)), root(NULL)
        {

        };
        ~rb_tree(void) {
            /*
                Delete all nodes
            */
        };
    }

#endif