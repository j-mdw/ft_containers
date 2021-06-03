#ifndef ENABLE_IF_H
# define ENABLE_IF_H


template<bool Cond, class T = void> 
struct enable_if {};


template<class T>
struct enable_if<true, T> 
{ 
    typedef T type;
};

typename enable_if<is_integral<T>::value, T>::type mytype;

template <typename T>
struct is_integral
{
	bool value;
	// template <typename T>
	void isint(T val)
	{
		value = false;
	}

	void isint(int val)
	{
		value = true;
	}

	void foo(void)
	{
		return true;
	};

	return (a + b);
};

class name
{
	name(void) :



	{};	
}

#endif
