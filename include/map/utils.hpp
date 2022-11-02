#pragma once

#include "../utils.hpp"

namespace ft
{
	// -- PAIR --
	template <class T1, class T2>
	struct pair
	{
		// Type definition
		typedef	T1	first_type;
		typedef T2	second_type;

		// Member variables
		first_type	first;
		second_type	second;

		// Constructors
		pair() : first(), second() {}
		template <class U, class V>
		pair(const pair<U, V>& other) : first(other.first), second(other.second) {}
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		// Operator Overloads
		pair&	operator=(const pair& other)
		{
			first = other.first;
			second = other.second;
			return (*this);
		}
	};

	// Relationnal Operators for Pair
	template <class T1, class T2>
	bool	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return ((lhs.first == rhs.first) && (lhs.second == rhs.second)); }
	template <class T1, class T2>
	bool	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (!(lhs == rhs)); }
	template <class T1, class T2>
	bool	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }
	template <class T1, class T2>
	bool	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (!(rhs < lhs)); }
	template <class T1, class T2>
	bool	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (rhs < lhs); }
	template <class T1, class T2>
	bool	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (!(lhs < rhs)); }

	// -- MAKE_PAIR --
	template <class T1, class T2>
	ft::pair<T1, T2>	make_pair(T1 x, T2 y) { return (ft::pair<T1, T2>(x, y)); }
}