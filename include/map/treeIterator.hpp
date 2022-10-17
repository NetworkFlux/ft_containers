#pragma once

#include "node.hpp"

namespace ft
{
	// -- RED BLACK TREE ITERATORS --
	template <typename T>
	class TreeIterator
	{
		// Type definitions
		public:
			typedef				std::bidirectional_iterator_tag						iterator_category;
			typedef typename	ft::iterator_traits<T*>::value_type 				value_type;
			typedef typename	ft::iterator_traits<T*>::reference 					reference;
			typedef typename	ft::iterator_traits<T*>::pointer					pointer;
			typedef typename	ft::iterator_traits<T*>::difference_type			difference_type;
			typedef 			Node<typename ft::remove_const<value_type>::type>*	node_pointer;
	
		// Member variables
		private:
			node_pointer	_node;
			node_pointer	_begin;
			node_pointer	_end;

		// Constructors
		public:
			TreeIterator() : _node(NULL), _begin(NULL), _end(NULL) {}
			TreeIterator(void* node, void* begin, void* end) : _node(static_cast<node_pointer>(node)),
				_begin(static_cast<node_pointer>(begin)), _end(static_cast<node_pointer>(end)) {}
			TreeIterator(const TreeIterator<typename ft::remove_const<value_type>::type >& other)
				: _node(other.base()), _begin(other.base2()), _end(other.base3()) {}

		// Operator Overloads
		public:
			TreeIterator&	operator= (const TreeIterator<T>& other)
			{
				_node = other._node;
				_begin = other._begin;
				_end = other._end;
				return (*this);
			}
			reference		operator*() const
			{
				return (*(_node->pair));
			}
			pointer			operator->() const
			{
				return (_node->pair);
			}
			TreeIterator&	operator++()
			{
				if (!_node)
					_node = _begin;
				else if (_node->right && !_node->right->is_nil)
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
				return (*this);
			}
			TreeIterator	operator++(int)
			{
				TreeIterator	temp = *this;
				if (!_node)
					_node = _begin;
				else if (!_node->right->is_nil)
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
				return (temp);
			}
			TreeIterator&	operator--()
			{
				if (!_node)
					_node = _end;
				else if (_node->left && !_node->left->is_nil)
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
				return (*this);
			}
			TreeIterator	operator--(int)
			{
				TreeIterator	temp = *this;
				if (!_node)
					_node = _end;
				else if (_node->left && !_node->left->is_nil)
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
				return (temp);
			}

		// Member Functions
		public:
			node_pointer	base(void) const { return (_node); }
			node_pointer	base2(void) const { return (_begin); }
			node_pointer	base3(void) const { return (_end); }

		// Helper Functions
		private:
			node_pointer	tree_min(node_pointer node)
			{
				node_pointer	n = node;
				while (n != NULL && !n->left->is_nil)
					n = n->left;
				return (n);
			}
			node_pointer	tree_max(node_pointer node)
 			{
				node_pointer	n = node;
				while (n != NULL && !n->left->is_nil)
					n = n->right;
				return (n);
			}
	};

	// Relational Operators for Tree Iterators
	template<typename A, typename B>
	bool	operator==(const TreeIterator<A>& lhs, const TreeIterator<B>& rhs) { return (lhs.base() == rhs.base()); }

	template<typename A, typename B>
	bool	operator!=(const TreeIterator<A>& lhs, const TreeIterator<B>& rhs) { return (lhs.base() != rhs.base()); }


	// -- RED BLACK TREE REVERSE ITERATORS --
	template <class Iterator>
	class ReverseTreeIterator
	{
		// Type definitions
		public:
			typedef				Iterator										iterator_type;
			typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;;
			typedef typename	iterator_traits<Iterator>::value_type			value_type;
			typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename	iterator_traits<Iterator>::pointer				pointer;
			typedef typename	iterator_traits<Iterator>::reference			reference;
	
		// Member variables
		private:
			iterator_type	_base_iterator;

		// Constructors
		public:
			ReverseTreeIterator() : _base_iterator() {}
			explicit ReverseTreeIterator(iterator_type it) : _base_iterator(it) {}
			template <class Iter>
			ReverseTreeIterator(const ReverseTreeIterator<Iter>& rev_it) : _base_iterator(rev_it._base_iterator) {}

		// Operator Overloads
		public:
			ReverseTreeIterator&	operator=(const ReverseTreeIterator& other)
			{
				_base_iterator = other._base_iterator;
			}
			reference				operator*() const
			{
				return (_base_iterator.operator*());
			}
			pointer					operator->() const
			{
				return (_base_iterator.operator->());
			}
			ReverseTreeIterator&	operator++()
			{
				--_base_iterator;
				return(*this);
			}
			ReverseTreeIterator		operator++(int)
			{
				ReverseTreeIterator temp = *this;
				--_base_iterator;
				return temp;	
			}
			ReverseTreeIterator&	operator--()
			{
				++_base_iterator;
				return(*this);
			}
			ReverseTreeIterator		operator--(int)
			{
				ReverseTreeIterator temp = *this;
				++_base_iterator;
				return temp;
			}
	
		// Member Functions
		public:
			void*	base() const
			{
				return (_base_iterator.base());
			}
	};

	// Relational Operators for Reverse Tree Iterators
	template <class Iterator>
	bool	operator==(const ReverseTreeIterator<Iterator>& lhs, const ReverseTreeIterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool	operator!=(const ReverseTreeIterator<Iterator>& lhs, const ReverseTreeIterator<Iterator>& rhs)
	{
		return(lhs.base() != rhs.base());
	}
}