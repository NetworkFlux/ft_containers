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
			typedef typename	RBT_type::reverse_iterator							reverse_iterator;
			typedef typename	RBT_type::const_reverse_iterator					const_reverse_iterator;


		private:
			allocator_type	_alloc;
			RBT_type		_tree;
			key_compare		_compare;
	};
};