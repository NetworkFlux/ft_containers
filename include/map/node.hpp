#pragma once

#include "utils.hpp"

namespace ft
{
	/*
		##	Nodes	##
	*/
	template<typename T, class Alloc = std::allocator<T> >	// T should always be a ft::pair when using with map
	class Node
	{
		public:
			typedef			T		node_value_type;	// pair
			typedef			T*		node_pointer;		// pointer to a pair
			typedef			T&		node_reference;		// reference to a pair
			typedef			Alloc	node_allocator_type;

			node_value_type			value;
			node_pointer			parent;
			node_pointer			left;
			node_pointer			right;
			bool					color;
		
		private:
			node_allocator_type	_alloc;

		public:
			Node() : value(), parent(NULL), left(NULL), right(NULL), color(false), _alloc(node_allocator_type()) {}
			Node(const node_value_type& val, node_pointer p, node_pointer l = NULL, node_pointer r = NULL, bool c = false)
				: value(val), parent(p), left(l), right(r), color(c), _alloc(node_allocator_type()) {}
			Node(const node_value_type& other)
				: value(other.value), parent(other.parent), left(other.left), right(other.right), color(other.color), _alloc(other._alloc) {}

			node_reference	operator=(const node_value_type& other)
		{
			value = other.value;
			parent = other.parent;
			left = other.left;
			right = other.right;
			color = other.color;
			_alloc = other._alloc;
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
};