#pragma once

#include "../utils.hpp"

namespace ft
{
	// -- RANDOM ACCESS ITERATORS --
	template<class T>
	class random_access_iterator
	{
		// Type definitions
		public:
			typedef				T*										iterator_type;
			typedef	typename	iterator_traits<T*>::value_type 		value_type;
			typedef	typename	iterator_traits<T*>::pointer			pointer;
			typedef	typename	iterator_traits<T*>::reference			reference;
			typedef	typename	iterator_traits<T*>::difference_type	difference_type;
			typedef				std::random_access_iterator_tag			iterator_category;

		// Member variable
		protected:
			pointer	_ptr;

		// Constructors
		public:
			random_access_iterator() : _ptr(NULL) {}
			random_access_iterator(pointer p) : _ptr(p) {}
			random_access_iterator(const random_access_iterator &other) : _ptr(other._ptr) {}
			virtual ~random_access_iterator() {}


		// Overload Operators
		public:
			random_access_iterator&	operator=(const random_access_iterator& other)
			{
				if (_ptr == other._ptr)
					return (*this);
				_ptr = other._ptr;
				return (*this);
			}
			reference				operator[](difference_type n) {return (*(operator+(n)));}
			reference				operator*(void) const { return (*_ptr); }
			pointer					operator->(void) { return &(this->operator*()); }
			random_access_iterator&	operator++(void)
			{
				_ptr++;
				return (*this);
			}
			random_access_iterator	operator++(int)
			{
				random_access_iterator	temp(*this);
				operator++();
				return (temp);
			}
			random_access_iterator&	operator--(void)
			{
				_ptr--;
				return (*this);
			}
			random_access_iterator	operator--(int)
			{
				random_access_iterator	temp(*this);
				operator--();
				return (temp);
			}
			random_access_iterator	operator+(difference_type n) const {return (_ptr + n);}
			random_access_iterator	operator-(difference_type n) const {return (_ptr - n);}
			random_access_iterator&	operator+=(difference_type n)
			{
				_ptr += n;
				return (*this);
			}
			random_access_iterator&	operator-=(difference_type n)
			{
				_ptr -= n;
				return (*this);
			}

		// Helper Functions
		public:
			pointer base() const { return (this->_ptr); }
	};

	// Relational operators for Random Access Iterators
	template <typename T>
	typename ft::random_access_iterator<T>::difference_type	operator==(const ft::random_access_iterator<T> lhs,
		const ft::random_access_iterator<T> rhs) { return (lhs.base() == rhs.base()); }
	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type	operator==(const ft::random_access_iterator<T1> lhs,
		const ft::random_access_iterator<T2> rhs) { return (lhs.base() == rhs.base()); }
	template <typename T>
	typename ft::random_access_iterator<T>::difference_type	operator!=(const ft::random_access_iterator<T> lhs,
		const ft::random_access_iterator<T> rhs) { return (lhs.base() != rhs.base()); }
	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type	operator!=(const ft::random_access_iterator<T1> lhs,
		const ft::random_access_iterator<T2> rhs) { return (lhs.base() != rhs.base()); }
	template <typename T>
	typename ft::random_access_iterator<T>::difference_type	operator<(const ft::random_access_iterator<T> lhs,
		const ft::random_access_iterator<T> rhs) { return (lhs.base() < rhs.base()); }
	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type	operator<(const ft::random_access_iterator<T1> lhs,
		const ft::random_access_iterator<T2> rhs) { return (lhs.base() < rhs.base()); }
	template <typename T>
	typename ft::random_access_iterator<T>::difference_type	operator>(const ft::random_access_iterator<T> lhs,
		const ft::random_access_iterator<T> rhs) { return (lhs.base() > rhs.base()); }
	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type	operator>(const ft::random_access_iterator<T1> lhs,
		const ft::random_access_iterator<T2> rhs) { return (lhs.base() > rhs.base()); }
	template <typename T>
	typename ft::random_access_iterator<T>::difference_type	operator<=(const ft::random_access_iterator<T> lhs,
		const ft::random_access_iterator<T> rhs) { return (lhs.base() <= rhs.base()); }
	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type	operator<=(const ft::random_access_iterator<T1> lhs,
		const ft::random_access_iterator<T2> rhs) { return (lhs.base() <= rhs.base()); }
	template <typename T>
	typename ft::random_access_iterator<T>::difference_type	operator>=(const ft::random_access_iterator<T> lhs,
		const ft::random_access_iterator<T> rhs) { return (lhs.base() >= rhs.base()); }
	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type	operator>=(const ft::random_access_iterator<T1> lhs,
		const ft::random_access_iterator<T2> rhs) { return (lhs.base() >= rhs.base()); }
	template<typename T>
	ft::random_access_iterator<T>	operator+(typename ft::random_access_iterator<T>::difference_type n,
		typename ft::random_access_iterator<T>& rai) { return (&(*rai) + n); }
	template <typename T>
	typename ft::random_access_iterator<T>::difference_type	operator-(const ft::random_access_iterator<T> lhs,
		const ft::random_access_iterator<T> rhs) { return (lhs.base() - rhs.base()); }
	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type	operator-(const ft::random_access_iterator<T_L> lhs,
		const ft::random_access_iterator<T_R> rhs) { return (lhs.base() - rhs.base()); }
}