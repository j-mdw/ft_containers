#ifndef FT_TREE_TREENODE_HPP
# define FT_TREE_TREENODE_HPP

# define DEBUG 1

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
		int		id; //DEBUG
		int		parent_id; //DEBUG
	#endif

        TreeNode(void) :
            color(black),
            parent(NULL),
            left(NULL),
            right(NULL) {
			#ifdef DEBUG
				id = 0; //DEBUG
				parent_id = 0; //DEBUG
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
        ~TreeNode(void) {};
    };
}

#endif
