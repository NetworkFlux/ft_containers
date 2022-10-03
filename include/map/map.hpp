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
			template< class InputIterator >
			map(InputIterator first, InputIterator last, const key_compare& compare = key_compare(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _tree(first, last, compare, _alloc), _compare(compare) {}
			map(const map& other)
			{
				_alloc = other._alloc;
				_compare = other._compare;
				_tree = other._tree;
			}
			~map() {}

			// ITERATORS
			iterator		begin() { return (_tree.begin()); }
			iterator		end() { return (_tree.end()); }

			// CAPACITY
			bool		empty() const { return (_tree.empty()); }
			size_type	size() const { return (_tree.size()); }
			size_type	max_size() const { return (_tree.max_size()); }

			// ELEMENT ACCESS
			mapped_type&	operator[](const key_type& k) { return ((*((_tree.insert(ft::make_pair(k, mapped_type()))).first)).second); }
			mapped_type& at (const key_type& k)
			{
				iterator res = _tree.find(ft::make_pair(k, mapped_type()));
				if (res == _tree.end())
					throw std::out_of_range("map::at: key not found");
				return (res->second);
			}
			const mapped_type& at (const key_type& k) const
			{
				iterator res = _tree.find(ft::make_pair(k, mapped_type()));
				if (res == _tree.end())
					throw std::out_of_range("map::at: key not found");
				return (static_cast<const mapped_type>(res->second));
			}

			// MODIFIERS
			ft::pair<iterator,bool> insert (const value_type& val) { return (_tree.insert(val)); }
			iterator insert (iterator position, const value_type& val) { return (_tree.insert(position, val)); }
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last) { return (_tree.insert(first, last)); }

			void erase (iterator position);								// NEED DELETION AND SEARCH
			size_type erase (const key_type& k);						// NEED DELETION AND SEARCH
			void erase (iterator first, iterator last);					// NEED DELETION AND SEARCH

			void swap (map& x)
			{
				_alloc = x._alloc;
				_compare = x._compare;
				_tree = x._tree;
			}

			void clear();	// NEED DELETION

			// OBSERVERS
			key_compare key_comp() const { return (_compare); }
			value_compare value_comp() const { return (_tree.value_comp()); }

			// OPERATIONS
			iterator find (const key_type& k) { return (_tree.find(ft::make_pair(k, mapped_type()))); }
			size_type count (const key_type& k) const { return (_tree.count(ft::make_pair(k, mapped_type()))); }
			iterator lower_bound (const key_type& k) { return (_tree.lower_bound(ft::make_pair(k, mapped_type()))); }
			const_iterator lower_bound (const key_type& k) const { return (_tree.lower_bound(ft::make_pair(k, mapped_type()))); }
			iterator upper_bound (const key_type& k) { return (_tree.upper_bound(ft::make_pair(k, mapped_type()))); }
			const_iterator upper_bound (const key_type& k) const { return (_tree.upper_bound(ft::make_pair(k, mapped_type()))); }
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return (ft::make_pair(lower_bound(k), upper_bound(k))); }
			pair<iterator,iterator> equal_range (const key_type& k) { return (ft::make_pair(lower_bound(k), upper_bound(k))); }

			// ALLOCATOR
			allocator_type get_allocator() const { return (_alloc); }

			// UTILS
			void		show(void)
			{
				for (iterator it = begin(); it != end(); it++)
					it.content().show();
			}

			void		print(void)
			{
				for (iterator it = begin(); it != end(); it++)
					it->show();
			}
	};
};