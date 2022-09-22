#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>

namespace ft
{
	/*
		## is_integral ##
	*/
	template<class T, bool v>
	struct integral_constant
	{
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }
	};

	template <class T> struct is_integral				: public ft::integral_constant<T, false> {};
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

	/*
		## enable_if ##
	*/

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	/*
		## lexicographical compares ##
	*/
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

	// /*
	// 	## std::pair implementation ##
	// */
	// template <class T1, class T2>
	// struct pair
	// {
	// 	// PUBLIC MEMBERS
	// 	public:
	// 		typedef	T1	first_type;
	// 		typedef	T2	second_type;

	// 		first_type	first;
	// 		second_type	second;

	// 	// PUBLIC METHODS
	// 	public:
	// 		pair() : first(), second() {}
	// 		template<class U, class V>
	// 		pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {}
	// 		pair (const first_type& a, const second_type& b) : first(a), second(b) {}
	// 		~pair () {}

	// 		pair& operator= (const pair& pr)
	// 		{
	// 			first = pr.first;
	// 			second = pr.second;
	// 			return (*this);
	// 		}
	// };

	// template <class T1, class T2>
	// bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	// {
	// 	return (lhs.first == rhs.first && lhs.second == rhs.second);
	// }
	// template <class T1, class T2>
	// bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs == rhs); }
	// template <class T1, class T2>
	// bool operator< (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	// {
	// 	return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	// }
	// template <class T1, class T2>
	// bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(rhs<lhs); }
	// template <class T1, class T2>
	// bool operator> (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return rhs<lhs; }
	// template <class T1, class T2>
	// bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) { return !(lhs<rhs); }

	// /*
	// 	## std::make_pair implementation ##
	// */
	// template <class T1,class T2>
	// ft::pair<T1,T2> make_pair (T1 x, T2 y) { return ( pair<T1,T2>(x,y) ); }

}

#endif