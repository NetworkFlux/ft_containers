#pragma once

#include "tree.hpp"

namespace ft
{
	// -- MAP --
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
		// Type Definition
		public:
			typedef				Key								key_type;
			typedef				T								mapped_type;
			typedef				Compare							key_compare;
			typedef				Allocator						allocator_type;
			typedef				pair<const Key, T>				value_type;
			typedef				value_type&						reference;
			typedef				const value_type&				const_reference;
			typedef typename	allocator_type::pointer			pointer;
			typedef typename	allocator_type::const_pointer	const_pointer;

		private:
			class pair_compare
			{
				private:
					key_compare _compare;
				public:
					pair_compare(const key_compare& compare) : _compare(compare) {}
					bool	operator()(const value_type& x, const value_type& y) const
					{
						return (_compare(x.first, y.first));
					}
		};
		public:
			typedef				pair_compare										value_compare;
			typedef				RBTree<value_type, pair_compare, allocator_type>	tree_type;
			typedef typename	tree_type::iterator									iterator;
			typedef typename	tree_type::const_iterator							const_iterator;
			typedef typename	tree_type::reverse_iterator							reverse_iterator;
			typedef typename	tree_type::const_reverse_iterator					const_reverse_iterator;
			typedef				std::size_t											size_type;
			typedef				std::ptrdiff_t										difference_type;

		// Member Variables
		private:
			allocator_type	_alloc;
			tree_type		_tree;
			key_compare		_compare;

		// Constructors
		public:
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), _tree(comp, alloc), _compare(comp) {}
			template<class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), _tree(first, last, _compare, _alloc), _compare(comp) {}
			// map(const map& x) : _alloc(x._alloc), _tree(), _compare(x._compare) { insert(x.begin(), x.end()); }

		// Operator Overload
		public:
			map&	operator=(const map& x)
			{
				_alloc = x._alloc;
				_compare = x._compare;
				clear();
				insert(x.begin(), x.end());
				return (*this);
			}

		// Member Functions
		public:
			// Iterators
			iterator			begin() { return (_tree.begin()); }
			iterator			end() { return (_tree.end()); }
			reverse_iterator	rbegin() { return(_tree.rbegin()); }
			reverse_iterator	rend() { return(_tree.rend()); }

			const_iterator			begin() const { return (_tree.begin()); }
			const_iterator			end() const { return (_tree.end()); }
			const_reverse_iterator	rbegin() const { return(_tree.rbegin()); }
			const_reverse_iterator	rend() const { return(_tree.rend()); }

			// Capacity
			bool		empty() const { return (_tree.empty()); }
			size_type	size() const { return (_tree.size()); }
			size_type	max_size() const { return (_tree.max_size()); }

			// Element Access
			mapped_type&		operator[](const key_type& key) { return (*((this->insert(ft::make_pair(key,mapped_type()))).first)).second; }
			mapped_type&		at(const key_type& key)
			{
				iterator	res = _tree.find(ft::make_pair(key, mapped_type()));
				if (res == _tree.end())
					throw std::out_of_range("map::at: key not found");
				return (res->second);
			}
			const mapped_type&	at(const key_type& key) const
			{
				iterator	res = _tree.find(ft::make_pair(key, mapped_type()));
				if (res == _tree.end())
					throw std::out_of_range("map::at: key not found");
				return (res->second);
			}

			// Modifiers
			pair<iterator, bool>	insert(const value_type& val) { return (_tree.insert(val)); }
			iterator 				insert(iterator position, const value_type& val) { return (_tree.insert(position, val)); }
			template<class InputIterator>
			void					insert(typename enable_if< !is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last)
			{
				_tree.insert(first, last);
			}
			void		erase(iterator position) { _tree.erase(position); }
			size_type	erase(const key_type& k) { return (_tree.erase(ft::make_pair(k, mapped_type()))); }
			void		erase(iterator first, iterator last) { _tree.erase(first, last); }
			void	swap(map& other)
			{
				std::swap(_compare, other._compare);
				_tree.swap(other._tree);
			}
			void	clear() { _tree.clear(); }

			// Observers
			key_compare		key_comp() const { return (_compare); }
			value_compare	value_comp() const { return (_tree.value_comp()); }

			// Operations
			iterator		find(const key_type& k) { return _tree.find(ft::make_pair(k, mapped_type())); }
			const_iterator	find(const key_type& k) const { return _tree.find(ft::make_pair(k, mapped_type())); }
			size_type		count(const key_type& k ) const { return (_tree.count(ft::make_pair(k, mapped_type()))); }
			iterator		lower_bound(const key_type& k) { return (_tree.lower_bound(ft::make_pair(k, mapped_type()))); }
			const_iterator	lower_bound(const key_type& k) const { return (_tree.lower_bound(ft::make_pair(k, mapped_type()))); }
			iterator		upper_bound(const key_type& k) { return (_tree.upper_bound(ft::make_pair(k, mapped_type()))); }
			const_iterator	upper_bound(const key_type& k) const { return (_tree.upper_bound(ft::make_pair(k, mapped_type()))); }
			pair<iterator, iterator>	equal_range(const key_type& k) { return (_tree.equal_range(ft::make_pair(k, mapped_type()))); }
			pair<const_iterator, const_iterator>	equal_range(const key_type& k) const { return (_tree.equal_range(ft::make_pair(k, mapped_type()))); }

			// Allocator
			allocator_type	get_allocator() const { return (_tree.get_allocator()); }

		// Relational Operator Overloads
		public:
			template<class _Key, class _T, class _Compare, class _Alloc>
			friend bool	operator==(const map<_Key, _T, _Compare, _Alloc>& lhs, const map<_Key, _T, _Compare, _Alloc>& rhs);

			template<class _Key, class _T, class _Compare, class _Alloc>
			friend bool	operator<(const map<_Key, _T, _Compare, _Alloc>& lhs, const map<_Key, _T, _Compare, _Alloc>& rhs);
	};

	// Relational Operators Overloads
	template<class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs._tree == rhs._tree);
	}
	template<class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs); 
	}
	template<class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs._tree < rhs._tree);
	}
	template<class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template<class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs > rhs);
	}
	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	// Swap Non Member
	template<class Key, class T, class Compare, class Alloc>
	void	swap(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { lhs.swap(rhs); }
}