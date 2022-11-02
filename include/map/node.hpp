#pragma once

#include "utils.hpp"

namespace ft
{
	// -- NODE --
	template <class Value>
	struct Node
	{

		// Member Variables
		public:
			Value	*value;
			Node*	parent;
			Node*	left;
			Node*	right;
			bool	is_black;
			bool	is_nil;

		// Constructor
		public:
			explicit Node(Value *srcval = 0) : value(srcval), parent(0), left(0), right(0), is_black(false), is_nil(0) {}
			Node( Node const & other)
			{
				is_black = other.is_black;
				value = other.value;
				parent = other.parent;
				is_nil = other.is_nil;
				right = other.right;
				left = other.left;
			}
			virtual ~Node() {}

		// Operator Overload
		public:
			Node& operator=(const Node& other)
			{
				is_black = other.is_black;
				value = other.value;
				is_nil = other.is_nil;
				parent = other.parent;
				right = other.right;
				left = other.left;
				return (*this);
			}
	};
}