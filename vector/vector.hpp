#ifndef VECTOR_H
# define VECTOR_H

# include <memory>
# include <cstddef> // for 'difference_type' type
# include <limits>


namespace ft
{

template <typename T, typename Alloc = std::allocator<T> >
class vector
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

        // CONSTRUCTORS

        explicit vector (const allocator_type& alloc = allocator_type());

        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

        template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

        vector (const vector& x);
        
        // DESTRUCTOR

        ~Vector(void);

        // COPY OPERATOR

        vector& operator= (const vector& x);

        vector<const int> v1;
        v1.push

    private:

        T *         _vector;
        size_type   _size;
        size_type   _capacity;

    public:

        // // GETTERS

        // T *         getVector(void) const   { return this->_vector; };
        // size_type   getSize(void) const     { return this->_size; };
        // size_type   getCapacity(void) const { return this->_capacity; };

        // // SETTERS

        // void        setVector(T *vec);
        // void        setSize(size_type size);
        // void        setCapacity(size_type capacity);

        // ITERATORS

        iterator        begin(void);
        const_iterator  begin(void) const;

        iterator        end(void);
        const_iterator  end(void) const;

        reverse_iterator        rbegin(void);
        const_reverse_iterator  rbegin(void) const;

        reverse_iterator        rend(void);
        const_reverse_iterator  rend(void) const;

        // CAPACITY

        size_type   size(void) const    { return this->_size; };
        size_type   max_size() const    { return std::numeric_limits<size_t>::max(); };
        
        void        resize (size_type n, value_type val = value_type())
        {
            if ()

        };
        size_type   capacity() const    { return this->_capacity; };
        bool        empty() const       { return (this->_size == 0); }; // IS 0 CONSIDERED BOOL?
        void        reserve (size_type n)
        {
            if (n > this->_capacity)
            {
                value_type *p = new value_type (n);
                std::memcpy(p, this->_vector, sizeof(value_type) * this->_size);
            }
        };

        // ELEMENT ACCESS

        reference       operator[] (size_type n);
        const_reference operator[] (size_type n) const;

        reference       at (size_type n);
        const_reference at (size_type n) const;

        reference       front(void);
        const_reference front(void) const;
      
        reference       back(void);
        const_reference back(void) const;

        // MODIFIERS

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last);

        void assign (size_type n, const value_type& val);

        void push_back (const value_type& val)
        {
            if (this->_size < this->_capacity)
            {
                this->_vector[this->_size] = val;
                this->_size++;
            }
            else
            
        };
        void pop_back(void);

        iterator    insert (iterator position, const value_type& val);	
        void        insert (iterator position, size_type n, const value_type& val);	

        template <class InputIterator>
        void        insert (iterator position, InputIterator first, InputIterator last);

        iterator erase (iterator position);
        iterator erase (iterator first, iterator last);

        void swap (vector& x);

        void clear(void);


};


        // NON-MEMBER FUNCTION OVERLOADS

        //  Relational operators

        template <class T, class Alloc>
        bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);


        template <class T, class Alloc>
        bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	

        template <class T, class Alloc>
        bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);


        template <class T, class Alloc>
        bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);


        template <class T, class Alloc>
        bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);


        template <class T, class Alloc>
        bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

        //  Swap

        template <class T, class Alloc>
        void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

}
#endif