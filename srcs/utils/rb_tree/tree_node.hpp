#ifndef FT_TREE_TREENODE_HPP
# define FT_TREE_TREENODE_HPP

// # define DEBUG 1

namespace ft
{
    template<typename T>
    class TreeNode
    {
		public:
        typedef enum {
            red,
            black
        } color_t;

        color_t color;
		T			value;
        TreeNode    *parent;
        TreeNode    *left;
        TreeNode    *right;
	#ifdef DEBUG
		int		id;
		int		parent_id;
	#endif

        TreeNode(void) :
            color(black),
            parent(NULL),
            left(NULL),
            right(NULL) {
			#ifdef DEBUG
				id = 0;
				parent_id = 0;
			#endif
            };

        TreeNode(color_t color, const T &val) :
            color(color),
            value(val),
            parent(NULL),
            left(NULL),
            right(NULL) {
		#ifdef DEBUG
			id = 0;
			parent_id = 0;
		#endif
            };

        TreeNode(const TreeNode &x) :
            color(x.color),
            value(x.value),
            parent(x.parent),
            left(x.left),
            right(x.right)
        #ifdef DEBUG
            ,id(x.id),
            parent_id(x.parent_id)
        #endif
        {};

        ~TreeNode(void) {};
    };
}

#endif
