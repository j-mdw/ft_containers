#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

class Category;

namespace ft {

template <class Category,              // iterator::iterator_category
          class T,                     // iterator::value_type
          class Distance = ptrdiff_t,  // iterator::difference_type
          class Pointer = T*,          // iterator::pointer
          class Reference = T&         // iterator::reference
          >
class iterator
{
	public:
		typedef Category  iterator_category;
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
};

}

#endif