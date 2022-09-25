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
			typedef				std::bidirectional_iterator_tag				iterator_category;
			typedef typename	ft::iterator_traits<T*>::value_type			value_type;
			typedef typename	ft::iterator_traits<T*>::reference			reference;
			typedef typename	ft::iterator_traits<T*>::pointer			pointer;
			typedef typename	ft::iterator_traits<T*>::difference_type	difference_type;
			typedef				ft::Node<T>*								node_pointer;

		private:
			node_pointer		_node;

		public:
			RBTIterator() : _node(NULL) {}
			RBTIterator(node_pointer node) : _node(node) {}
			RBTIterator(const RBTIterator& other) : _node(other.base()) {}

			RBTIterator&	operator=(const RBTIterator& other)
			{
				_node = other.base();
				return (*this);
			}
			reference		operator*() const { return (*(_node->value)); }
			pointer			operator->() const { return (_node->value); }
			RBTIterator&	operator++()
			{
				if (!_node)
					return (*this);
				if (_node->right)
					_node = tree_min(_node->right);
				else
				{
					node_pointer	parent = _node->parent;
					while (parent && (_node == parent->right))
					{
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
				}
				return (*this);
			}
			RBTIterator		operator++(int)
			{
				node_pointer	temp = _node;
				if (!_node)
					return (*this);
				if (_node->right)
					_node = tree_min(_node->right);
				else
				{
					node_pointer	parent = _node->parent;
					while (parent && (_node == parent->right))
					{
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
				}
				return (temp);
			}
			RBTIterator&	operator--()
			{
				if (!_node)
					return (*this);
				if (_node->left)
					_node = tree_max(_node->left);
				else
				{
					node_pointer	parent = _node->parent;
					while (parent && (_node == parent->left))
					{
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
				}
				return (*this);
			}
			RBTIterator		operator--(int)
			{
				node_pointer	temp = _node;
				if (!_node)
					return (*this);
				if (_node->left)
					_node = tree_max(_node->left);
				else
				{
					node_pointer	parent = _node->parent;
					while (parent && (_node == parent->left))
					{
						_node = parent;
						parent = parent->parent;
					}
					_node = parent;
				}
				return (temp);
			}
			node_pointer	base(void) const { return (_node); }

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