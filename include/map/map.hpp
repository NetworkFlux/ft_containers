#pragma once

#include "RBTree.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair< const Key, T> > >
	class map
	{
		public:
			typedef				Key													key_type;
			typedef				T													mapped_type;
			typedef				ft::pair<const key_type, mapped_type>				value_type;
			typedef				Compare												key_compare;
			typedef				Alloc												allocator_type;

		private:
			class pair_compare
			{
				key_compare _compare;

				public:
					pair_compare(const key_compare & compare) : _compare(compare) {}

					bool operator()(const value_type & x, const value_type & y) const { return (_compare(x.first, y.first)); }
		};

		public:
			typedef				pair_compare										value_compare;
			typedef				RBTree<value_type, value_compare, allocator_type>	RBT_type;
			typedef typename	allocator_type::reference							reference;
			typedef typename	allocator_type::const_reference						const_reference;
			typedef typename	allocator_type::pointer								pointer;
			typedef typename	allocator_type::const_pointer						const_pointer;
			typedef typename	RBT_type::iterator									iterator;
			typedef typename	RBT_type::const_iterator							const_iterator;
			// typedef typename	RBT_type::reverse_iterator							reverse_iterator;
			// typedef typename	RBT_type::const_reverse_iterator					const_reverse_iterator;
			typedef				size_t												size_type;


		private:
			allocator_type	_alloc;
			RBT_type		_tree;
			key_compare		_compare;

		public:
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _tree(RBT_type(comp, alloc)), _compare(comp) {}
			// template <class InputIterator>
			// map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			// 	: _alloc(alloc), _compare(comp)
			// {
			// 	for (; first != last; first++)
			// 		// add to tree;
			// }
			map(const map& other)
			{
				_alloc = other._alloc;
				_compare = other._compare;
				_tree = other._tree;
			}
			~map() {} //Free everything;

			// ITERATORS
			iterator		begin() { return (_tree.tree_min(_tree._root)); }
			iterator		end() { return (_tree.tree_max(_tree._root)); }

			// CAPACITY
			bool		empty() const { return (_tree.empty()); }
			size_type	size() const { return (_tree.size()); }
			size_type	max_size() const { return (_tree.max_size()); }

			// ELEMENT ACCESS
			mapped_type&	operator[](const key_type& k);		// NEED ADD AND SEARCH
			mapped_type& at (const key_type& k);				// NEED ADD AND SEARCH
			const mapped_type& at (const key_type& k) const;	// NEED ADD AND SEARCH

			// MODIFIERS
			pair<iterator,bool> insert (const value_type& val);			// NEED ADD AND SEARCH
			iterator insert (iterator position, const value_type& val);	// NEED ADD AND SEARCH
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last);		// NEED ADD AND SEARCH

			void erase (iterator position);								// NEED DELETION AND SEARCH
			size_type erase (const key_type& k);						// NEED DELETION AND SEARCH
			void erase (iterator first, iterator last);					// NEED DELETION AND SEARCH

			void swap (map& x)
			{
				_alloc = x._alloc;
				_comp = x._comp;
				_tree = x._tree;
			}

			void clear();	// NEED DELETION

			// OBSERVERS
			key_compare key_comp() const;
			value_compare value_comp() const;

			// OPERATIONS
			iterator find (const key_type& k);												// NEED SEARCH
			size_type count (const key_type& k) const;										// NEED SEARCH
			iterator lower_bound (const key_type& k);										// NEED SEARCH
			const_iterator lower_bound (const key_type& k) const;							// NEED SEARCH
			iterator upper_bound (const key_type& k);										// NEED SEARCH
			const_iterator upper_bound (const key_type& k) const;							// NEED SEARCH
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const;		// NEED SEARCH
			pair<iterator,iterator> equal_range (const key_type& k);						// NEED SEARCH

			// ALLOCATOR
			allocator_type get_allocator() const;
	};
};