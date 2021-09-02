#ifndef ITERATOR_H
# define ITERATOR_H

namespace ft
{

template <typename T>
class iterator
{
    public:
        iterator(T *it) : _base_iterator(it)
        {};

        ~iterator(void);

    void base(void) const
    {
        return (this->_base_iterator);
    }

    T operator* (void) const
    {
        return *_base_iterator;
    };

    iterator operator+ (int val) const
    {
        iterator r(this->_base_iterator + val);
        return r;
    };

    void operator++ (void)
    {
        this->_base_iterator++;
    };

    void operator+= (int val)
    {
        this->_base_iterator + val;
    };

    iterator operator- (int val) const
    {
        iterator r(this->_base_iterator - val);
        return r;
    };

    void operator-- (void)
    {
        this->_base_iterator--;
    };

    void operator-= (int val)
    {
        this->_base_iterator - val;
    };

    T * operator-> (void) const
    {
        return &(*this->_base_iterator);
    };

    T operator[] (int index)
    {
        return (this->_base_iterator + index);
    }

    private:
        T *_base_iterator;
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
#endif