#pragma once

#include "../utils.hpp"

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
			virtual ~random_access_iterator() {}

			pointer base() const { return (this->_ptr); }

			// OPERATOR OVERLOADS
			random_access_iterator&	operator=(const random_access_iterator& other)
			{
				if (_ptr == other._ptr)
					return (*this);
				_ptr = other._ptr;
				return (*this);
			}

			reference	operator*(void) const { return (*_ptr); }
			pointer		operator->(void) { return &(this->operator*()); }
		
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

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		private:
			pointer	_ptr;

		public:
			reverse_iterator() : _ptr(NULL) {}
			explicit reverse_iterator(iterator_type it) : _ptr(&(*it)) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : _ptr(rev_it.base()) {}
			virtual ~reverse_iterator() {}

		public:
			iterator_type base() const { return _ptr; }
			reference operator*() const
			{
				iterator_type temp = _ptr;
				return (*(--temp));
			}
			reverse_iterator operator+(difference_type n) const { return (_ptr - n); }
			reverse_iterator& operator++()
			{
				_ptr--;
				return (*this);
			}
			reverse_iterator operator++(int)
			{
				reverse_iterator temp = *this;
				++(*this);
				return temp;
			}
			reverse_iterator operator+=(difference_type n)
			{
				_ptr -= n;
				return (*this);
			}

			reverse_iterator operator-(difference_type n) const { return (reverse_iterator(_ptr + n)); }
			reverse_iterator& operator--()
			{
				_ptr++;
				return (*this);
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator temp = *this;
				--(*this);
				return temp;
			}
			reverse_iterator operator-=(difference_type n)
			{
				_ptr += n;
				return (*this);
			}
			pointer operator->() const { return &(operator*()); }
			reference operator[](difference_type n) const { return (this->base()[-n - 1]); }
	};

	template <class Iterator>
		bool operator== (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator== (const reverse_iterator<Iterator_L>& lhs,
			const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() == rhs.base()); }

	template <class Iterator>
		bool operator!= (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator!= (const reverse_iterator<Iterator_L>& lhs,
			const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() != rhs.base()); }

	template <class Iterator>
		bool operator< (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator< (const reverse_iterator<Iterator_L>& lhs,
			const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() > rhs.base()); }

	template <class Iterator>
		bool operator<= (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator<= (const reverse_iterator<Iterator_L>& lhs,
			const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() >= rhs.base()); }

	template <class Iterator>
		bool operator> (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.bash()); }

 	template <class Iterator_L, class Iterator_R>
		bool operator> (const reverse_iterator<Iterator_L>& lhs,
			const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() < rhs.base()); }

	template <class Iterator>
		bool operator>= (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator>= (const reverse_iterator<Iterator_L>& lhs,
			const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() <= rhs.base()); }

	template <class Iterator>
		reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }

	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }

	template <class Iterator_L, class Iterator_R>
		bool operator- (const reverse_iterator<Iterator_L>& lhs,
			const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() - rhs.base()); }
}