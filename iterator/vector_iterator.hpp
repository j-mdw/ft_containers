#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"
#include <vector>

std::vector<int>::iterator vec_it;

namespace ft {

template <typename T>
class vector_iterator : public iterator<random_access_iterator_tag, T>
{
    private:
        T *_base_iterator;

	public:
        vector_iterator(T *it) : _base_iterator(it) {};
		vector_iterator(vector_iterator<T> src) : _base_iterator(src._base_iterator) {};
        ~vector_iterator(void);
		
		vector_iterator<T>	operator= (vector_iterator<T> src) { _base_iterator = src._base_iterator};

    // void base(void) const
    // {
    //     return (this->_base_iterator);
    // }

    T operator* (void) const
    {
        return *_base_iterator;
    };

    vector_iterator operator+ (int val) const
    {
        return (this->_base_iterator + val);
    };

	vector_iterator operator- (int val) const
    {
        return (this->_base_iterator - val);
    };

    void operator++ (void)
    {
        this->_base_iterator++;
    };

    void operator++ (int)
    {
        ++this->_base_iterator;
    };

    void operator-- (int)
    {
        --this->_base_iterator;
    };

    void operator+= (int val)
    {
        this->_base_iterator += val;
    };

    void operator-= (int val)
    {
        this->_base_iterator -= val;
    };

    T * operator-> (void) const
    {
        return (this->_base_iterator);
    };

    T operator[] (int index)
    {
        return (*(this->_base_iterator + index));
    };
};

//     template <class Iterator>
//     bool operator== (const iterator<Iterator>& lhs, const iterator<Iterator>& rhs)
//     {
//         if (lhs->_rev_iterator == rhs->_rev_iterator)
//             return true;
//         return false;
//     };

//     template <class Iterator>
//     bool operator!= (const iterator<Iterator>& lhs, const iterator<Iterator>& rhs)
//     {
//         return !(lhs == rhs);
//     };
// }

};

}

#endif