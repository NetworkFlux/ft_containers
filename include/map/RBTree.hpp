#pragma once

#include "RBTIterator.hpp"

namespace ft
{
	template < class P, class Compare = std::less<P>, class Alloc = std::allocator<P> >
	class RBTree
	{
		public:
			typedef				P										value_type;
			typedef				Compare									value_compare;
			typedef				Alloc									allocator_type;
			typedef typename	Alloc::template rebind<Node<P> >::other	node_allocator;
			typedef typename	node_allocator::pointer					node_pointer;
			typedef typename	allocator_type::reference				reference;
			typedef typename	allocator_type::const_reference			const_reference;
			typedef typename	allocator_type::pointer					pointer;
			typedef typename	allocator_type::const_pointer			const_pointer;
			typedef				RBTIterator<P>							iterator;
			typedef				RBTIterator<const P>					const_iterator;

		private:
			allocator_type	_alloc;
			value_compare	_comp;
			node_pointer	_root;
			size_t			_size;

		public:
			RBTree() : _alloc(allocator_type()), _comp(value_compare()), _root(NULL), _size(0) {}
			RBTree(const value_compare& comp, const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _comp(comp), _root(NULL), _size(0) {}
			~RBTree() {} // fill destruction

			RBTree&		operator=(const RBTree& other)
			{
				_alloc = other._alloc;
				_comp = other._comp;
				_root = other._root;
				_size = other._size;
				return (*this);
			}

		private:
			node_pointer	tree_min(node_pointer n)
				{
					while (n->left)
						n = n->left;
					return (n);
				}
			node_pointer	tree_max(node_pointer n)
				{
					while (n->right)
						n = n->right;
					return (n);
				}
	};
};