/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:00:31 by npinheir          #+#    #+#             */
/*   Updated: 2022/09/23 00:15:54 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

#include "utils.hpp"

namespace ft
{
	/*
		##	ft::pair	##
	*/
	template <class T1, class T2>
	struct pair
	{
		public:
			typedef	T1	first_type;
			typedef	T2	second_type;

			first_type	first;
			second_type	second;

			pair() : first(), second() {}
			template <class U, class V>
			pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}
			pair(const first_type& a, const second_type& b) : first(a), second(b) {}

			pair&	operator=(const pair& pr)
			{
				if (*this == pr)
					return (*this);
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			}

			void	show(void)
			{
				std::cout << "first = " << first << " | second = " << second << std::endl;
			}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs<lhs; }

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs<rhs); }

	template <class T1,class T2>
	pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1,T2>(x,y));
	}

	/*
		##	Nodes	##
	*/
	template<typename T>
	class Node
	{
		public:
			typedef	T	value_type;

			value_type	value;
			Node*		parent;
			Node*		left;
			Node*		right;
			bool		color;

			Node() : value(), parent(NULL), left(NULL), right(NULL), color(false) {}
			Node(const value_type& val, Node* p, Node* l = NULL, Node* r = NULL, bool c = false) : value(val), parent(p), left(l), right(r), color(c) {}
			Node(const Node& other) : value(other.value), parent(other.parent), left(other.left), right(other.right), color(other.color) {}

			Node&	operator=(const Node& other)
		{
			if (*this == other)
				return (*this);
			this->value = other.value;
			this->parent = other.parent;
			this->left = other.left;
			this->right = other.right;
			this->color = other.color;
			return (*this);
		}

			void	show(void)
			{
				std::cout << "Value : ";
				value.show();
				std::cout << "Has parent : " << parent << std::endl;
				std::cout << "Has left child : " << left << std::endl;
				std::cout << "Has right child : " << right << std::endl;
				std::cout << "Colored : " << color << std::endl << std::endl;
			}
	};
	
	template <class T1>
	bool operator==(const Node<T1>& lhs, const Node<T1>& rhs) { return lhs.value==rhs.value && lhs.value==rhs.value; }

	template <class T1>
	bool operator!=(const Node<T1>& lhs, const Node<T1>& rhs) { return !(lhs==rhs); }

	/*
		##	Red Black Tree Iterators	**
	*/
	template<typename T>
	class RBIterator
	{
		public:
			typedef				std::bidirectional_iterator_tag				iterator_category;
			typedef typename	ft::iterator_traits<T*>::value_type			value_type;
			typedef typename	ft::iterator_traits<T*>::reference			reference;
			typedef typename	ft::iterator_traits<T*>::pointer			pointer;
			typedef typename	ft::iterator_traits<T*>::difference_type	difference_type;
			typedef				Node<T>*									node_pointer;

		private:
			node_pointer	_node;

		public:
			RBIterator() {}
			RBIterator(node_pointer node) : _node(node) {}
			RBIterator(const RBIterator& other) : _node(other._node) {}

			RBIterator&	operator=(const RBIterator& other)
			{
				if (*this == other)
					return (*this);
				this->_node = other.node();
				return (*this);
			}
			reference	operator*() const { return (_node->value); }
			pointer		operator->() const { return (&_node->value); }
			RBIterator&	operator++()
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
			RBIterator	operator++(int)
			{
				node_pointer	temp = *this;
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
			RBIterator&	operator--()
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
			RBIterator	operator--(int)
			{
				node_pointer	temp = *this;
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

			private:
				node_pointer	node(void) { return (_node); }
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
	bool	operator==(const RBIterator<A>& lhs, const RBIterator<B>& rhs) { return (lhs.node() == rhs.node()); }
	
	template<typename A, typename B>
	bool	operator!=(const RBIterator<A>& lhs, const RBIterator<B>& rhs) { return (lhs.node() != rhs.node()); }

	/*
		##	Red Black Tree	##
	*/
	
}

#endif