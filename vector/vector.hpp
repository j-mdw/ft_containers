#ifndef VECTOR_H
# define VECTOR_H

# include <memory>
# include <cstddef> // for 'difference_type' type
namespace ft
{

template <typename T, typename Alloc = std::allocator<T> >
class Vector
{

    public:

        typedef T                               value_type;
        typedef Alloc                           allocator_type;
        typedef allocator_type::reference       reference; // Need to test this
        typedef allocator_type::const_reference const_reference;
        typedef allocator_type::pointer         pointer;
        typedef allocator_type::const_pointer   const_pointer;
        typedef value_type *                    iterator;
        typedef value_type * const              const_iterator;
        typedef value_type *                    reverse_iterator;   // Will try to handle this with operators overloads
        typedef value_type * const              const_reverse_iterator;
        typedef ptrdiff_t                       difference_type;
        typedef size_t                          size_type;

        explicit vector (const allocator_type& alloc = allocator_type());
        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	
        template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	

vector (const vector& x);

        Vector(void);
        Vector(int);
        ~Vector(void);




    private:

};




}
#endif