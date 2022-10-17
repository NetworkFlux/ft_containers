#pragma once

#include "utils.hpp"

namespace ft
{
	// -- NODE --
	template <typename T, class Alloc = std::allocator<T> > // T should always be a Pair
	class Node
	{
		// Type definition
		public:
			typedef	T			pair_type;
			typedef	T*			pair_pointer;
			typedef	T&			pair_reference;
			typedef	Alloc		pair_allocator;
			typedef	Node<T>		node_type;
			typedef	Node<T>*	node_pointer;
			typedef	Node<T>&	node_reference;

		// Member variables
		public:
			pair_allocator	pair_alloc;
			pair_pointer	pair;
			node_pointer	parent;
			node_pointer	left;
			node_pointer	right;
			bool			color;
			bool			is_nil;

		// Constructors
		public:
			explicit Node(pair_pointer src_val = NULL) : pair_alloc(pair_allocator()), pair(src_val), parent(NULL), left(NULL),
				right(NULL), color(true), is_nil(false) {}
			Node(pair_type src_pair) : pair_alloc(pair_allocator()), parent(NULL), left(NULL),
				right(NULL), color(true), is_nil(false)
			{
				pair = pair_alloc.allocate(1);
				pair_alloc.construct(pair, src_pair);
			}
			Node(const Node<T>& other) : pair_alloc(other.pair_alloc), parent(other.parent),
				left(other.left), right(other.right), color(other.color), is_nil(other.is_nil)
			{
				pair = pair_alloc.allocate(1);
				pair_alloc.construct(pair, *(other.pair));
			}
			~Node()
			{
				pair_alloc.destroy(pair);
				pair_alloc.deallocate(pair, 1);
			}

		// Operator Overloads
		public:
			node_reference	operator=(const Node<T>& other)
			{
				pair_alloc = other.pair_alloc;
				pair = pair_alloc.allocate(1);
				pair_alloc.construct(pair, *(other.pair));
				parent = other.parent;
				left = other.left;
				right = other.right;
				color = other.color;
				is_nil = other.is_nil;
				return (*this);
			}
	};

	// Relationnal Operators for Node
	template <class T>
	bool	operator==(const Node<T>& lhs, const Node<T>& rhs)
	{
		return (*(lhs.pair) == *(rhs.pair));
	}
	template <class T>
	bool	operator!=(const Node<T>& lhs, const Node<T>& rhs)
	{
		return (*(lhs.pair) != *(rhs.pair));
	}
}