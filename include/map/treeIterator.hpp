#pragma once

#include "node.hpp"

namespace ft
{
	// -- RED BLACK TREE ITERATORS --
	template <typename T>
	class TreeIterator
	{
		// Type Definition
		public:
			typedef				std::bidirectional_iterator_tag						iterator_category;
			typedef typename	ft::iterator_traits<T*>::value_type					value_type;
			typedef typename	ft::iterator_traits<T*>::reference					reference;
			typedef typename	ft::iterator_traits<T*>::pointer					pointer;
			typedef typename	ft::iterator_traits<T*>::difference_type			difference_type;
			typedef				Node<typename ft::remove_const<value_type>::type >*	node_pointer;

		// Member Variables
		private:
			node_pointer _node;

		// Constructors
		public:
			TreeIterator() {}
			TreeIterator(void *node) : _node(static_cast<node_pointer>(node)) {}
			TreeIterator(const TreeIterator<typename ft::remove_const<value_type>::type > & other)
			{
				*this = other;
			}
			~TreeIterator() {}

		// Operator Overloads
		public:
			TreeIterator&	operator=(const TreeIterator<typename ft::remove_const<value_type>::type>& other)
			{
				_node = other.node();
				return (*this);
			}
			reference		operator*() const { return (*(_node->value)); }
			pointer			operator->() const { return (_node->value); }
			TreeIterator&	operator++()
			{
				if (_node->right && !_node->right->is_nil)
					_node = tree_min(_node->right);
				else 
				{
					node_pointer	y = _node->parent;
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
				TreeIterator<value_type>	temp = *this;
				if (!_node->right->is_nil)
					_node = tree_min(_node->right);
				else
				{
					node_pointer	y = _node->parent;
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
				if (_node->left && !_node->left->is_nil)
					_node = tree_max(_node->left);
				else
				{
					node_pointer	y = _node->parent;
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
				TreeIterator<value_type>	temp = *this;
				if (_node->left && !_node->left->is_nil)
					_node = tree_max(_node->left);
				else
				{
					node_pointer	y = _node->parent;
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
			node_pointer	node() const { return _node; }
			node_pointer	tree_min(node_pointer n) const
			{
				while(n->left != NULL && !n->left->is_nil)
					n = n->left;
				return n;
			}
			node_pointer	tree_max(node_pointer n) const
			{
				while (!n->right->is_nil)
					n = n->right;
				return n;
			}
		};

	// Relational Operator Overloads for Iterators
	template<typename A, typename B>
	bool	operator==(const TreeIterator<A> & lhs, const TreeIterator<B> & rhs) { return (lhs.node() == rhs.node()); }
	template<typename A, typename B>
	bool	operator!=(const TreeIterator<A> & lhs, const TreeIterator<B> & rhs) { return (lhs.node() != rhs.node()); }

	// -- RED BLACK TREE REVERSE ITERATORS --
	template <class Iterator>
	class reverse_iterator
	{
		// Type Definition
		public:
			typedef				Iterator										iterator_type;
			typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;;
			typedef typename	iterator_traits<Iterator>::value_type			value_type;
			typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename	iterator_traits<Iterator>::pointer				pointer;
			typedef typename	iterator_traits<Iterator>::reference			reference;

		// Member Variables
		private:
			iterator_type	base_iterator;

		// Constructors
		public:
			reverse_iterator() : base_iterator() {}
			explicit reverse_iterator (iterator_type it) : base_iterator(it) {}
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) { base_iterator = rev_it.base_iterator; }
			~reverse_iterator() {}

		// Operator Overloads
		public:
			reverse_iterator&	operator=(const reverse_iterator& other)
			{
				base_iterator = other.base_iterator;
				return (*this);
			}
			reference			operator*() const
			{
				iterator_type	tmp = base_iterator;
				return (*--tmp);
			}
			reverse_iterator	operator+ (difference_type n) const { return (reverse_iterator(base_iterator - n)); }
			reverse_iterator&	operator++()
			{
				--base_iterator;
				return (*this);
			}
			reverse_iterator	operator++(int)
			{
				reverse_iterator	temp = *this;
				++(*this);
				return (temp);
			}
			reverse_iterator&	operator+= (difference_type n)
			{
				base_iterator -= n;
				return (*this);
			}
			reverse_iterator	operator- (difference_type n) const { return (reverse_iterator(base_iterator + n)); }
			reverse_iterator&	operator--()
			{
				++base_iterator;
				return (*this);
			}
			reverse_iterator	operator--(int)
			{
				reverse_iterator	temp = *this;
				--(*this);
				return (temp);
			}
			reverse_iterator&	operator-= (difference_type n)
			{
				base_iterator += n;
				return (*this);
			}
			pointer				operator->() const { return &(operator*()); }
			reference			operator[] (difference_type n) const { return (base_iterator[-n-1]); }

		// Member Functions
		public:
			iterator_type	base() const { return (base_iterator); }
	};

	// Relational Operators Overloads for Reverse Iterators
	template <class Iter>
	bool	operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) { return(lhs.base() == rhs.base()); }
	template <class Iter>
	bool	operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) { return(lhs.base() != rhs.base()); }
	template <class Iter>
	bool	operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
	template <class Iter>
	bool	operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
	template <class Iter>
	bool	operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
	template <class Iter>
	bool	operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
	template <class Iter>
	reverse_iterator<Iter>	operator+( typename reverse_iterator<Iter>::difference_type n,
		const reverse_iterator<Iter>& rev_it) { return(rev_it + n); }
	template <class Iter>
	typename reverse_iterator<Iter>::difference_type	operator-( const reverse_iterator<Iter>& lhs,
		const reverse_iterator<Iter>& rhs) {return(lhs.base() - rhs.base()); }
}