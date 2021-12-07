#ifndef FT_REVERSE_ITERATOR_HPP
# define FT_REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include <vector>

// std::vector<int>::reverse_iterator rit;


namespace ft
{

template <typename Iterator>
class reverse_iterator
{
    public:
        typedef Iterator													iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
        typedef typename ft::iterator_traits<Iterator>::reference			reference;

    private:
        iterator_type _base;

    public:
		reverse_iterator(void) {};

		explicit reverse_iterator(iterator_type it) :
        _base(it) {};
		
        template <typename Iter>
		reverse_iterator(const reverse_iterator<Iter> & rev_it) :
        _base(rev_it.base()) {};
        
        template<class Iter>
        reverse_iterator& operator=( const reverse_iterator<Iter> & rev_it)
        {
            _base = rev_it._base;
            return *this;
        };
        
        ~reverse_iterator(void) {};

        iterator_type base(void) const
        {
            return (this->_base);
        };

        reference operator* (void) const
        {
            iterator_type current = this->_base;
            return *(--current);
        };

        pointer operator-> (void) const
        {
            return &(this->operator*());
        };

        reference operator[] (difference_type n)
        {
            return *(*this + n);
        }

        reverse_iterator operator+ (difference_type val) const
        {
            return reverse_iterator(_base - val);
        };

        reverse_iterator operator- (difference_type val) const
        {
            return reverse_iterator(_base + val);
        };

        reverse_iterator & operator++ (void)
        {
            --this->_base;
            return (*this);
        };

        reverse_iterator operator++ (int)
        {
            reverse_iterator cpy = *this;
            --this->_base;
            return cpy;
        };

        reverse_iterator & operator-- (void)
        {
            ++this->_base;
            return (*this);
        };
        
        reverse_iterator operator-- (int)
        {
            reverse_iterator cpy = *this;
            ++this->_base;
            return cpy;
        };

        reverse_iterator & operator+= (difference_type val)
        {
            this->_base -= val;
            return *this;
        };

        reverse_iterator & operator-= (difference_type val)
        {
            this->_base += val;
            return *this;
        };
};

template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() == rhs.base());
};

template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return !(lhs == rhs);
};

template <class Iterator>
bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (rhs.base() < lhs.base());
};

template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs < rhs || lhs == rhs);
};

template <class Iterator>
bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (rhs < lhs);
};

template <class Iterator>
bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (rhs <= lhs);
};

template <class Iterator>
reverse_iterator<Iterator> operator+ (
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& rev_it)
{
    return reverse_iterator<Iterator>(rev_it + n);
}
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs)
{
    return rhs.base() - lhs.base();
}

}

#endif