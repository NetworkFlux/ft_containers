#pragma once

#include "node.hpp"

namespace ft
{
	/*
		##	Red Black Tree Iterators	**
	*/
	template<typename T>
	class RBTIterator
	{
		public:
			typedef		T			pair_type;
			typedef		T*			pair_pointer;
			typedef		T&			pair_reference;
			typedef		Node<T>		node_type;
			typedef		Node<T>*	node_pointer;
			typedef		Node<T>&	node_reference;

		private:
			node_pointer		_node;

		public:
			RBTIterator() : _node(NULL) {}
			RBTIterator(node_pointer node) : _node(node) {}
			RBTIterator(const RBTIterator& other) : _node(other.base()) {}

			RBTIterator&		operator=(const RBTIterator& other)
			{
				_node = other.base();
				return (*this);
			}
			pair_reference		operator*() const { return (*(_node->pair)); }
			pair_pointer		operator->() const { return (_node->pair); }
			RBTIterator&		operator++()
			{
				if (_node->right)
					_node = tree_min(_node->right);
				else
				{
					node_pointer y = _node->parent;
					while (y != NULL && _node == y->right)
					{
						_node = y;
						y = y->parent;
					}
					_node = y;
				}
				return *this;
			}
			RBTIterator			operator++(int)
			{
				RBTIterator<pair_type> temp = *this;
				if (_node->right)
					_node = tree_min(_node->right);
				else
				{
					node_pointer y = _node->parent;
					while (y != NULL && _node == y->right)
					{
						_node = y;
						y = y->parent;
					}
					_node = y;
				}
				return temp;
			}
			RBTIterator&		operator--() {
				if (_node->left)
					_node = tree_max(_node->left);
				else
				{
					node_pointer y = _node->parent;
					while (y != NULL && _node == y->left)
					{
						_node = y;
						y = y->parent;
					}
					_node = y;
				}
				return *this;
			}
			RBTIterator			operator--(int) {
				RBTIterator<pair_type> temp = *this;
				if (_node->left)
					_node = tree_max(_node->left);
				else
				{
					node_pointer y = _node->parent;
					while (y != NULL && _node == y->left) {
						_node = y;
						y = y->parent;
					}
					_node = y;
				}
				return temp;
			}

			node_pointer	base(void) const { return (_node); }
			node_type		content(void) const { return (*_node); }

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

	template<typename A, typename B>
	bool operator==(const RBTIterator<A> & lhs, const RBTIterator<B> & rhs) { return (lhs.base() == rhs.base()); }

	template<typename A, typename B>
	bool operator!=(const RBTIterator<A> & lhs, const RBTIterator<B> & rhs) { return (lhs.base() != rhs.base()); }
};