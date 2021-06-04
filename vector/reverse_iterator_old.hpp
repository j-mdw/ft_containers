#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H

# include "iterator.hpp"

namespace ft
{

template <typename Iter>
class reverse_iterator
{
    private:
        Iter m_iter;

    public:
        reverse_iterator(Iter iter) :
        m_iter(iter)
        {};

        ~reverse_iterator(void);

    void base(void) const
    {
        return (this->_base_iterator);
    }

    void operator* (void) const
    {
        return *_rev_iterator;
    };

    reverse_iterator operator+ (int val) const
    {
        reverse_iterator r(this->_base_iterator - val);
        return r;
    };

    void operator++ (void)
    {
        this->_base_iterator--;
        this->_rev_iterator--;
    };

    void operator+= (int val)
    {
        this->_base_iterator - val;
        this->_rev_iterator- val;
    };

    reverse_iterator operator- (int val) const
    {
        reverse_iterator r(this->_base_iterator + val);
        return r;
    };

    void operator-- (void)
    {
        this->_base_iterator++;
        this->_rev_iterator++;
    };

    void operator-= (int val)
    {
        this->_base_iterator + val;
        this->_rev_iterator+ val;
    };

    void operator-> (void) const
    {
        return &(*this->_rev_iterator);
    };

    void operator[] (int index)
    {
        return (this->_rev_iterator - index);
    }

};


    template <class Iterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs->_rev_iterator > rhs);
    };

    template <class Iterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs->_rev_iterator >= rhs->_rev_iterator);
    };

    template <class Iterator>
    bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs->_rev_iterator < rhs->_rev_iterator);
    };

    template <class Iterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs->_rev_iterator <= rhs->_rev_iterator);
    };

}

#endif