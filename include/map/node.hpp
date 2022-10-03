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
			typedef			T								pair_type;				// pair
			typedef			T*								pair_pointer;			// pointer to a pair
			typedef			T&								pair_reference;		// reference to a pair
			typedef			Alloc							pair_allocator;			// pair allocator
			typedef			Node<T>							node_type;				// node
			typedef			Node<T>*						node_pointer;				// pointer to node
			typedef			Node<T>&						node_reference;				// reference to node

			pair_pointer	pair;
			node_pointer	parent;
			node_pointer	left;
			node_pointer	right;
			bool			color;
		
		private:
			pair_allocator	_pair_alloc;

		public:
			Node() : pair(NULL), parent(NULL), left(NULL), right(NULL), color(false), _pair_alloc(pair_allocator())
			{
				// pair = _pair_alloc.allocate(1);
			}
			Node(pair_type val)
				: parent(NULL), left(NULL), right(NULL), color(false), _pair_alloc(pair_allocator())
			{
				pair = _pair_alloc.allocate(1);
				_pair_alloc.construct(pair, val);
			}
			Node(pair_type val, node_pointer p, node_pointer l = NULL, node_pointer r = NULL, bool c = false)
				: parent(p), left(l), right(r), color(c), _pair_alloc(pair_allocator())
			{
				pair = _pair_alloc.allocate(1);
				_pair_alloc.construct(pair, val);
			}
			Node(const Node& other)
				: pair(other.pair), parent(other.parent), left(other.left), right(other.right), color(other.color), _pair_alloc(other._pair_alloc) {}

			node_reference	operator=(const Node& other)
			{
				pair = other.pair;
				parent = other.parent;
				left = other.left;
				right = other.right;
				color = other.color;
				_pair_alloc = other._alloc;
				return (*this);
			}

			void	show(void)
			{
				std::cout << "Value : ";
				if (pair)
					pair->show();
				else
					std::cout << "Empty" << std::endl;
				std::cout << "Has parent : " << parent << std::endl;
				std::cout << "Has left child : " << left << std::endl;
				std::cout << "Has right child : " << right << std::endl;
				std::cout << "Colored : " << color << std::endl << std::endl;
			}
	};
	
	template <class T1>
	bool operator==(const Node<T1>& lhs, const Node<T1>& rhs) { return lhs.pair == rhs.pair && lhs.pair == rhs.pair; }

	template <class T1>
	bool operator!=(const Node<T1>& lhs, const Node<T1>& rhs) { return !(lhs == rhs); }
};