#ifndef VECTOR_H
# define VECTOR_H

# include <memory>
# include <cstddef> // for 'difference_type' type
# include <limits>

# define VECTOR_GROWTH 2

namespace ft
{

template <typename T, typename Alloc = std::allocator<T> >
class vector
{

    public:

        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference; // Need to test this
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef value_type *                                iterator;
        typedef value_type * const                          const_iterator;
        typedef value_type *                                reverse_iterator;   // Will try to handle this with operators overloads
        typedef value_type * const                          const_reverse_iterator;
        typedef ptrdiff_t                                   difference_type;
        typedef size_t                                      size_type;

        // CONSTRUCTORS

        explicit vector (const allocator_type& alloc = allocator_type()) : 
        _vector(NULL),
        _size(0),
        _capacity(0)
        {
            (void)alloc;
            reserve(0);
        };

        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
        _vector(NULL),
        _size(0),
        _capacity(0)
        {
            (void)alloc;
            resize(n, val);
        };

        template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : 
        _vector(NULL),
        _size(0),
        _capacity(0)
        {
            (void)alloc;
            assign(first, last);
        };

        // vector (const vector& x);

        // DESTRUCTOR

        ~vector(void)
        {
            delete [] this->_vector;
        };

        // COPY OPERATOR

        vector& operator= (const vector& x);

    private:

        T *         _vector;
        size_type   _size;
        size_type   _capacity;

    public:

        // ITERATORS

        iterator        begin(void)         { return this->_vector; };
        const_iterator  begin(void) const   { return this->_vector; };

        iterator        end(void)       { return (this->_vector + this->_size); };
        const_iterator  end(void) const { return (this->_vector + this->_size); };

        // reverse_iterator        rbegin(void);
        // const_reverse_iterator  rbegin(void) const;

        // reverse_iterator        rend(void);
        // const_reverse_iterator  rend(void) const;

        // CAPACITY

        size_type   size(void) const    { return this->_size; };
        size_type   max_size() const    { return std::numeric_limits<size_t>::max(); };
        
        void        resize (size_type n, value_type val = value_type())
        {
            reserve(n);
            if (n > this->_size)
                memset(this->_vector + this->_size, val, (n - this->_size));
            this->_size = n;
        };

        size_type   capacity() const    { return this->_capacity; };
        bool        empty() const       { return (this->_size == 0); }; // IS 0 CONSIDERED BOOL?
        
        void        reserve (size_type n)
        {
            if (n > this->_capacity)
            {
                value_type *p = new value_type [n];
                this->_capacity = n;
                memcpy(p, this->_vector, this->_size);
                delete [] this->_vector;
                this->_vector = p;
            }
        };

        // ELEMENT ACCESS

        reference       operator[] (size_type n)        { return this->_vector[n]; };
        const_reference operator[] (size_type n) const  { return this->_vector[n]; };

        reference       at (size_type n)        { return this->_vector[n]; };
        const_reference at (size_type n) const  { return this->_vector[n]; };

        reference       front(void)         { return this->_vector[0]; };
        const_reference front(void) const   { return this->_vector[0]; };
      
        reference       back(void)          { return this->_vector[this->_size - 1]; };
        const_reference back(void) const    { return this->_vector[this->_size - 1]; };

        // MODIFIERS

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last)
        {
            size_type range = range(first, last);
            if (range > this->_capacity)
                reserve(range);
            this->_size = range;
            for (size_type i = 0; i < range; i++)
                this->_vector[i] = *first;
        };

        void assign (size_type n, const value_type& val)
        {
            this->_size = 0;
            resize(n, val);
        };

        void push_back (const value_type& val)
        {
            if (this->_size == this->_capacity)
                reserve(this->_capacity * VECTOR_GROWTH);

            this->_vector[this->_size] = val;
            this->_size++;
        };

        void pop_back(void) { this->_size--; };
    
        iterator    insert (iterator position, const value_type& val)	
        {
            resize(this->_size + 1);
            memmove(position + 1, position, end() - position);
            *position = val;
            return (position);
        };

        void        insert (iterator position, size_type n, const value_type& val)
        {
            resize(this->_size + n);
            memmove(position + n, position, end() - position);
            memset(position, val, n);
        };

        template <class InputIterator>
        void        insert (iterator position, InputIterator first, InputIterator last)
        {
            iterator startPosition = position;
            size_type inputSize = range(first, last);
            resize(this->_size + inputSize);
            memmove(position + inputSize, position, end() - position);
            while (first != last)
            {
                *position = *first;
                position++;
                first++;
            }
            return (startPosition);
        };

        // iterator erase (iterator position);
        // iterator erase (iterator first, iterator last);

        // void swap (vector& x);

        // void clear(void);


    private:

        template <class InputIterator>
        size_type    range (InputIterator first, InputIterator last)
        {
            size_type n = 0;
            for (; first != last; first++)
                n++;
            return (n);
        };

        void    memset (iterator dst, size_type n, const value_type &val)
        {
            for (size_type i = 0; i < n; i++)
            {
                *dst = val;
                dst++;
            }
        };

        void    memcpy (iterator dst, iterator src, size_type n)
        {
            for (size_type i = 0; i < n; i++)
            {
                *dst = *src;
                dst++;
                src++;
            }
        };

        void    memmove(iterator dst, iterator src, size_type n)
        {
            value_type *p = new value_type [n];
            for (value_type i = 0; i < n; i++)
                p[i] = src[i];
            for (value_type i = 0; i < n; i++)
                dst[i] = p[i];
            delete [] p;
        };
};


        // NON-MEMBER FUNCTION OVERLOADS

        //  Relational operators

        // template <class T, class Alloc>
        // bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);


        // template <class T, class Alloc>
        // bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	

        // template <class T, class Alloc>
        // bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);


        // template <class T, class Alloc>
        // bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);


        // template <class T, class Alloc>
        // bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);


        // template <class T, class Alloc>
        // bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

        // //  Swap

        // template <class T, class Alloc>
        // void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

}
#endif