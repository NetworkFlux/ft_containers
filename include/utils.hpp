#pragma once

#include <iostream>

namespace ft
{
	//-- ITERATOR TAGS --
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	// -- ITERATOR TRAITS --
	template <class Iter>
	struct iterator_traits
	{
		typedef typename	Iter::iterator_category		iterator_category;
		typedef typename	Iter::value_type			value_type;
		typedef typename	Iter::pointer				pointer;
		typedef typename	Iter::reference				reference;
		typedef typename	Iter::difference_type		difference_type;
	};
	template <class T>
	struct iterator_traits<T*>
	{
		typedef	random_access_iterator_tag	iterator_category;
		typedef	T							value_type;
		typedef	T*							pointer;
		typedef	T&							reference;
		typedef typename std::ptrdiff_t		difference_type;
	};
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef typename std::ptrdiff_t		difference_type;
	};

	// -- REVERSE ITERATORS --
	template <class Iterator>
	class reverse_iterator
	{
		// Type Definition
		public:
			typedef				Iterator										iterator_type;
			typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;;
			typedef typename	iterator_traits<Iterator>::value_type			value_type;
			typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename	iterator_traits<Iterator>::pointer				pointer;
			typedef typename	iterator_traits<Iterator>::reference			reference;

		// Member Variables
		private:
			iterator_type	base_iterator;

		// Constructors
		public:
			reverse_iterator() : base_iterator() {}
			explicit reverse_iterator (iterator_type it) : base_iterator(it) {}
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) { base_iterator = rev_it.base_iterator; }
			~reverse_iterator() {}

		// Operator Overloads
		public:
			reverse_iterator&	operator=(const reverse_iterator& other)
			{
				base_iterator = other.base_iterator;
				return (*this);
			}
			reference			operator[] (difference_type n) const { return (base_iterator[-n-1]); }
			reference			operator*() const
			{
				iterator_type	tmp = base_iterator;
				return (*--tmp);
			}
			pointer				operator->() const { return &(operator*()); }
			reverse_iterator	operator+ (difference_type n) const { return (reverse_iterator(base_iterator - n)); }
			reverse_iterator&	operator++()
			{
				--base_iterator;
				return (*this);
			}
			reverse_iterator	operator++(int)
			{
				reverse_iterator	temp = *this;
				++(*this);
				return (temp);
			}
			reverse_iterator&	operator+= (difference_type n)
			{
				base_iterator -= n;
				return (*this);
			}
			reverse_iterator	operator- (difference_type n) const { return (reverse_iterator(base_iterator + n)); }
			reverse_iterator&	operator--()
			{
				++base_iterator;
				return (*this);
			}
			reverse_iterator	operator--(int)
			{
				reverse_iterator	temp = *this;
				--(*this);
				return (temp);
			}
			reverse_iterator&	operator-= (difference_type n)
			{
				base_iterator += n;
				return (*this);
			}

		// Member Functions
		public:
			iterator_type	base() const { return (base_iterator); }
	};

	// Relational Operators Overloads for Reverse Iterators
	template <class Iter>
	bool	operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) { return(lhs.base() == rhs.base()); }
	template <class Iter>
	bool	operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) { return(lhs.base() != rhs.base()); }
	template <class Iter>
	bool	operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
	template <class Iter>
	bool	operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
	template <class Iter>
	bool	operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
	template <class Iter>
	bool	operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
	template <class Iter>
	reverse_iterator<Iter>	operator+( typename reverse_iterator<Iter>::difference_type n,
		const reverse_iterator<Iter>& rev_it) { return(rev_it + n); }
	template <class Iter>
	typename reverse_iterator<Iter>::difference_type	operator-( const reverse_iterator<Iter>& lhs,
		const reverse_iterator<Iter>& rhs) {return(lhs.base() - rhs.base()); }

	// -- ENABLE_IF --
	template <bool B, class T = void>
	struct enable_if {};
	template <class T>
	struct enable_if<true, T> { typedef T type; };

	// -- IS_INTEGRAL --
	template <class T, bool v>
	struct integral_constant
	{
		typedef	T					value_type;
		typedef	integral_constant	type;
		static const bool			value = v;
		operator value_type() const { return value; }
	};

	template <class T>
	struct is_integral									: public ft::integral_constant<T, false> {};
	template <> struct is_integral<bool>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<char>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<signed char>			: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<wchar_t>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<char16_t>			: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<short>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<int>					: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<long>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long long>	: public ft::integral_constant<bool, true> {};

	// -- LEXICOGRAPHICAL COMPARE --
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1)
				return false;
			else if (*first1<*first2)
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1!=last1)
		{
			if (first2==last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	// -- EQUAL --
	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1!=last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	// -- REMOVE CONST --
	template<class T>
	struct remove_const { typedef T type; };
	template<class T>
	struct remove_const <const T> { typedef T type; };
}