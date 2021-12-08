#ifndef VECTOR_H
# define VECTOR_H

# include <memory>
# include <vector> //DELETE
# include <cstddef> // for 'difference_type' type
# include <iostream>
# include <stdexcept> // for out of range exception
# include "../utils/iterator/reverse_iterator.hpp"
# include "../utils/enable_if/enable_if.hpp"
# include "../utils/is_integral/is_integral.hpp" 
# include "../utils/lexicographical_compare/lexicographical_compare.hpp"
# include "../utils/equal/equal.hpp"

# define VECTOR_GROWTH 2
// # define VEC_MAX_SIZE std::numeric_limits<size_t>::max() >> 1

namespace ft
{

template <typename T, typename Alloc = std::allocator<T> >
class vector
{
    public:

        typedef T                                           		value_type;
        typedef Alloc                                       		allocator_type;
        typedef typename allocator_type::reference          		reference; // Need to test this
        typedef typename allocator_type::const_reference    		const_reference;
        typedef typename allocator_type::pointer            		pointer;
        typedef typename allocator_type::const_pointer      		const_pointer;
        // typedef typename allocator_type::pointer            		pointer;
        // typedef typename allocator_type::const_pointer      		const_pointer;
        typedef T*												iterator;
		typedef const T*										const_iterator;
        typedef typename ft::reverse_iterator<iterator>         	reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>   	const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type; // ft?
        typedef size_t                                      		size_type;

		// VARIABLES

    private:

        value_type *    _vector;
        size_type       _size;
        size_type       _capacity;
		Alloc			_allocator;

        // CONSTRUCTORS

	public:
        explicit vector(const allocator_type & alloc = allocator_type()): 
        _vector(NULL),
        _size(0),
        _capacity(0),
		_allocator(alloc)
        {
            reserve(0);
        };

        explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()):
        _vector(NULL),
        _size(0),
        _capacity(0),
		_allocator(alloc)
        {
            resize(n, val);
        };

        template <class InputIterator>
        vector(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type()): 
        _vector(NULL),
        _size(0),
        _capacity(0),
		_allocator(alloc)
        {
            assign(first, last);
        };

        vector(const vector & x):
		_vector(NULL),
		_size(x._size),
		_capacity(x._capacity),
		_allocator(x._allocator)
        {
			_vector = _allocator.allocate(x._capacity);
			for (size_t i = 0; i < x._size; ++i)
			{
				_allocator.construct(_vector + i, x._vector[i]);
			}
        };

        // DESTRUCTOR

        ~vector(void)
        {
            destroy_n(_vector, _size);
			_allocator.deallocate(_vector, _capacity);
        };

        // ASSIGNMENT OPERATOR -> The container preserves its current allocator

        vector& operator= (const vector & x)
		{
			// reserve(x._capacity);
			assign(x.begin(), x.end());
			return *this;
		};

    public:

        // ITERATORS

        iterator        begin(void)         { return this->_vector; };
        const_iterator  begin(void) const   { return this->_vector; };

        iterator        end(void)       { return (this->_vector + this->_size); };
        const_iterator  end(void) const { return (this->_vector + this->_size); };

        reverse_iterator    	rbegin(void) { return reverse_iterator(this->end()); };
        const_reverse_iterator  rbegin(void) const { return const_reverse_iterator(this->end()); };

        reverse_iterator        rend(void) { return reverse_iterator(this->begin()); };
        const_reverse_iterator  rend(void) const { return const_reverse_iterator(this->begin()); };

        // CAPACITY

        size_type   size(void) const    { return this->_size; };
        size_type   max_size(void) const
		{
			// long long max_size = std::numeric_limits<size_t>::max() >> 1;
			// int divisor = sizeof(T) / 2;
			// if (divisor > 1)
			// 	return max_size / divisor;
			// return max_size;
            return _allocator.max_size();
		};
        
        void        resize (size_type n, value_type val = value_type())
        {
            reserve(n);
            if (n > this->_size)
			{
				construct_n(this->_vector + this->_size, n - this->_size, val);
			}
            else if (n < this->_size)
            {
                destroy_n(this->_vector + n, this->_size - n);
            }
            this->_size = n;
        };

        size_type   capacity(void) const    { return this->_capacity; };
        bool        empty(void) const       { return (this->_size == 0); };
        
        void        reserve(size_type n)
        {
            if (n > this->_capacity)
            {
                value_type *p = _allocator.allocate(n);
				for (size_type i = 0; i < _size; ++i)
				{
					_allocator.construct(p + i, _vector[i]);
					_allocator.destroy(&_vector[i]);
				}
				if (p != NULL)
                	_allocator.deallocate(this->_vector, this->_capacity);
                this->_capacity = n;
				this->_vector = p;
            }
        };

        // ELEMENT ACCESS

        reference       operator[] (size_type n)        { return this->_vector[n]; };
        const_reference operator[] (size_type n) const  { return this->_vector[n]; };

        reference       at(size_type n)
        {
            if (n >= this->_size)
            {
                throw std::out_of_range("out of range");
            }
            return this->_vector[n];
        };
        
        const_reference at(size_type n) const
        {
            if (n >= this->_size)
            {
                throw std::out_of_range("out of range");
            }
            return this->_vector[n];
        };

        reference       front(void)         { return this->_vector[0]; };
        const_reference front(void) const   { return this->_vector[0]; };
      
        reference       back(void)          { return this->_vector[this->_size - 1]; };
        const_reference back(void) const    { return this->_vector[this->_size - 1]; };

        // MODIFIERS

        template <class InputIterator>
        void assign(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
        {
			destroy_n(_vector, _size);
            size_type inputRange = range(first, last);
			if (_capacity < inputRange)
			{
				_allocator.deallocate(_vector, _capacity);
				_vector = _allocator.allocate(inputRange);
				_capacity = inputRange;
			}
			for (size_t i = 0; first != last; ++first)
			{
				_allocator.construct(_vector + i, *first);
				i++;
			}
			_size = inputRange;
        };

        void assign(size_type n, const value_type & val)
        {
			destroy_n(_vector, _size);
			if (_capacity < n)
			{
				_allocator.deallocate(_vector, _capacity);
				_vector = _allocator.allocate(n);
				_capacity = n;
			}
			for (size_t i = 0; i < n; ++i)
			{
				_allocator.construct(_vector + i, val);
			}
			_size = n;
        };

        void push_back(const value_type & val)
        {
            resize(this->_size + 1, val);
            // if (this->_size == this->_capacity)
			// {
			// 	if (this->_size == 0)
			// 	{
			// 		reserve(1);
			// 	}
			// 	else
			// 	{
            //     	reserve(this->_capacity * VECTOR_GROWTH);
			// 	}
			// }
			// _allocator.construct(_vector + _size, val);
			// this->_size++;
        };

        void pop_back(void)
		{ 
			_allocator.destroy(_vector + _size - 1);
			this->_size--;
		};
    
        iterator    insert(iterator position, const value_type& val)
        {
            size_t index = position - begin();
            resize(this->_size + 1);
            memmove(this->_vector + index + 1, this->_vector + index, (this->_size - 1) - (index));
            this->_vector[index] = val;
            return (_vector + index);
        };

        void        insert(iterator position, size_type n, const value_type& val)
        {
            int index = position - begin();
            resize(this->_size + n);
            memmove(this->_vector + index + n, this->_vector + index, (this->_size - n) - (index));
            memset(this->_vector + index, n, val);
        };

        template <class InputIterator>
        void        insert(iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
        {
            // vector<T> store(first, last);
            int index = position - begin();
            size_type n = range(first, last);
            resize(this->_size + n);
            memmove(this->_vector + index + n, this->_vector + index, (this->_size - n) - (index));
            for (size_type i = 0; first != last; ++first)
            {
                this->_vector[index + i] = *first;
				++i;
            }
        };

        iterator erase(iterator position)
        {
            memmove(position, position + 1, range(position + 1, end()));
            _allocator.destroy(end() - 1);
            this->_size--;
            return (position);
        };

        iterator erase(iterator first, iterator last)
        {
            memmove(first, last, range(last, end()));
            size_t it_range = range(first, last);
            destroy_n(end() - it_range, it_range);
            this->_size -= it_range;
            return (first);
        };

        void swap(vector & x)
        {
            value_type *    vector_cpy = this->_vector;
            size_type       size_cpy = this->_size;
            size_type       capacity_cpy = this->_capacity;

            this->_vector = x._vector;
            this->_size = x._size;
            this->_capacity = x._capacity;
            x._vector = vector_cpy;
            x._size = size_cpy;
            x._capacity = capacity_cpy;
        };

        void clear(void)    { this->resize(0); };

	// GET ALLOCATOR
		allocator_type get_allocator() const { return _allocator; };

    private:

        template <class InputIterator>
        size_type    range(InputIterator first, InputIterator last)
        {
            size_type n = 0;
            for (; first != last; first++)
                n++;
            return (n);
        };

        void    memset(iterator dst, size_type n, const value_type &val)
        {
            for (size_type i = 0; i < n; i++)
                dst[i] = val;
        };

        void    memcpy(iterator dst, iterator src, size_type n)
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
            if (n > 0)
            {
                value_type *p = new value_type [n];
                for (size_type i = 0; i < n; i++)
                    p[i] = src[i];
                for (size_type i = 0; i < n; i++)
                    dst[i] = p[i];
                delete [] p;
            }
        };

		void	construct_n(pointer p, size_type n, value_type v)
		{
			for (size_type i = 0; i < n; ++i)
			{
				_allocator.construct(p + i, v);
			}
		}

		void	destroy_n(pointer p, size_type n)
		{
			for (size_type i = 0; i < n; ++i)
			{
				_allocator.destroy(p + i);
			}
		}
};


// NON-MEMBER FUNCTION OVERLOADS

//  Relational operators

template <class T, class Alloc>
bool operator== (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());

	// for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
	// {
	// 	if (rhs[i] != lhs[i])
	// 		return false;
	// }
	// return true;
};


template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs == rhs);
};


template <class T, class Alloc>
bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	// typename vector<T, Alloc>::const_iterator it1 = lhs.begin();
	// typename vector<T, Alloc>::const_iterator ite1 = lhs.end();

	// typename vector<T, Alloc>::const_iterator it2 = rhs.begin();
	// typename vector<T, Alloc>::const_iterator ite2 = rhs.end();

	// return ft::lexicographical_compare(it1, ite1, it2, ite2);

	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());


	// for(;it1 != ite1; it1++)
	// {
	// 	if (it2 == ite2)
	// 		return false; // rhs ends before lhs, rhs is less than lhs
	// 	if (*it1 != *it2)
	// 		return (*it1 < *it2);
	// 	else
	// 		it2++;
	// }
	// if (it2 != ite2)
	// 	return true;    // lhs ends before rhs
	// return false;
};


template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (lhs < rhs || lhs == rhs);
};

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs <= rhs);
};


template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs < rhs);
};

//  Swap

template <class T, class Alloc>
void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
{
	x.swap(y);
};

}

#endif