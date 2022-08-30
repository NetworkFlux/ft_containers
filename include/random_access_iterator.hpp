/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:38:23 by npinheir          #+#    #+#             */
/*   Updated: 2022/08/31 00:30:27 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template<class T>
	class random_access_iterator
	{
		/*	PUBLIC MEMBER TYPE
			In here we see some type name changes to make the program more readable
			by having one word to discribe each type	*/
		public:
			typedef random_access_iterator_tag	iterator_category;
			typedef T 							value_type;
			typedef T*							pointer;
			typedef T&							reference;
			typedef size_t						size_type;
			typedef std::ptrdiff_t				difference_type;

		/*	PRIVATE MEMBER TYPE	*/
		protected:
			pointer	_ptr;

		/*	 CONSTRUCTORS	*/
		public:
			random_access_iterator() : _ptr(NULL) {}
			random_access_iterator(pointer p) : _ptr(p) {}
			random_access_iterator(const random_access_iterator &other) : _ptr(other._ptr) {}
			virtual ~random_access_iterator();

			pointer base() const {return (this->_elem);}

			// OPERATOR OVERLOADS
			random_access_iterator&	operator=(const random_access_iterator& other)
			{
				if (_ptr == other._ptr)
					return (*this);
				_ptr = other._ptr;
				return (*this);
			}

			reference	operator*(void) const {return (*_ptr);}
			pointer		operator->(void) {return &(this->operator*());}
		
			random_access_iterator&	operator++(void)
			{
				_ptr++;
				return (*this);
			}
		
			random_access_iterator	operator++(void) const
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

			random_access_iterator	operator--(void) const
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

			reference	operator[](difference_type n) {return (*(operator+(n)));}
	};

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator==(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type
		operator==(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator!=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type
		operator!=(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator<(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type
		operator<(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator>(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type
		operator>(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator<=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type
		operator<=(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator>=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type
		operator>=(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename T>
	ft::random_access_iterator<T>
		operator+(typename ft::random_access_iterator<T>::difference_type n,
			typename ft::random_access_iterator<T>& rai)
	{
		return (&(*rai) + n);
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type
		operator-(const ft::random_access_iterator<T> lhs,
			const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
		operator-(const ft::random_access_iterator<T_L> lhs,
			const ft::random_access_iterator<T_R> rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif