// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   binary_search_tree.hpp                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/20 13:35:11 by npinheir          #+#    #+#             */
// /*   Updated: 2022/09/22 14:43:13 by npinheir         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef BINARY_SEARCH_TREE_HPP
// # define BINARY_SEARCH_TREE_HPP

// #include "utils.hpp"

// namespace ft
// {
// 	/*
// 		## less (for the BST) ##
// 	*/
// 	template <class T>
// 	struct less // might need something here
// 	{
// 		bool operator() (const T& x, const T& y) const { return x < y; }
// 	};

// 	/*
// 		## BST Nodes (for the BST) ##
// 	*/
// 	template<typename T>
// 	struct bstNode
// 	{
// 		public:
// 			typedef	T	value_type;

// 			value_type	value;
// 			bstNode*	parent;
// 			bstNode*	left;
// 			bstNode*	right;

// 		public:
// 			bstNode() : value(NULL), parent(NULL), left(NULL), right(NULL) {}
// 			bstNode(bstNode* p = NULL, bstNode* l = NULL, bstNode* r = NULL) : value(NULL), parent(p), left(l), right(r) {}
// 			bstNode(const value_type& val, bstNode* p = NULL, bstNode* l = NULL, bstNode* r = NULL) : value(val), parent(p), left(l), right(r) {}
// 			bstNode(const bstNode& other) : value(other.value), parent(other.parent), left(other.left), right(other.right) {}
// 			virtual ~bstNode() {}

// 			bstNode&	operator=(const bstNode& other)
// 			{
// 				if (other == *this)
// 					return (*this);
// 				this->value = other.value;
// 				this->parent = other.parent;
// 				this->left = other.left;
// 				this->right = other.right;
// 				return (*this);
// 			}
// 			bool		operator==(const bstNode& other)
// 			{
// 				if (this->value == other.value)
// 					return (true);
// 				return (false);
// 			}
// 	};

// 	/*
// 		## Binary Search Tree Iterator ##
// 	*/
// 	template<typename T, class Compare>
// 	class bstIterator
// 	{
// 		public:
// 			typedef random_access_iterator_tag	iterator_category;
// 			typedef T 							value_type;
// 			typedef T*							pointer;
// 			typedef T&							reference;
// 			typedef size_t						size_type;
// 			typedef std::ptrdiff_t				difference_type;

// 			pointer								_node;
// 			Compare								_comp;

// 			bstIterator(const Compare& comp = Compare()) : _node(NULL), _comp(comp) {}
// 			bstIterator(pointer node, const Compare& comp = Compare()) : _node(node), _comp(comp) {}
// 			bstIterator(const bstIterator& it) : _node(it._node), _comp(it._comp) {}
// 			virtual ~bstIterator() {}

// 			bstIterator&	operator=(const bstIterator& other)
// 			{
// 				if (*this == other)
// 					return (*this);
// 				this->_node = other._node;
// 				this->_comp = other._comp;
// 				return (*this);
// 			}
// 			bool			operator==(const bstIterator& other) { return (_node == other._node); }
// 			bool			operator!=(const bstIterator& other) { return !(*this == other); }
// 			reference		operator*() const { return (this->_node->value); }
// 			pointer			operator->() const { return (&this->_node->value); }
// 			bstIterator&	operator++(void) { return (_node->right); }
// 			bstIterator		operator++(int)
// 			{
// 				bstIterator tmp(*this);

// 				operator++();
// 				return (tmp);
// 			}
// 			bstIterator&	operator--(void) { return (_node->left); }
// 			bstIterator		operator--(int)
// 			{
// 				bstIterator	tmp(*this);

// 				operator--();
// 				return (tmp);
// 			}

// 	};

// 	/*
// 		## Binary Search Tree (data structure used by map) ##
// 	*/
// 	template <class T, class Compare = ft::less<T>, class Node = ft::bstNode<T>,
// 				class TypeAlloc = std::allocator<T>, class NodeAlloc = std::allocator<Node> >
// 	class BinarySearchTree
// 	{
// 		public:
// 			typedef	T								value_type;
// 			typedef	ft::bstIterator<Node, Compare>	iterator;
// 			// typedef ft::const_bstIterator<Node, Compare>	iterator;

// 			Node*		root;
// 			NodeAlloc	alloc_node;
// 			size_t		nb_node;

// 			BinarySearchTree(const NodeAlloc& node_alloc_init = NodeAlloc()) : root(NULL), alloc_node(node_alloc_init), nb_node(0) {}
// 			~BinarySearchTree()
// 			{
// 				// fill;
// 			}
// 			ft::pair<iterator,bool>	insertPair (const value_type& val)
// 			{
// 				if (nb_node == 0)
// 				{
// 					root = alloc_node.allocate(1);
// 					root->value = val;
// 					nb_node++;
// 					return (ft::make_pair(iterator(root), true));
// 				}
// 				bool	is_placed = false;
// 				Node*	temp = root;
// 				Node*	new_node = alloc_node.allocate(1);
// 				new_node->value = val;
// 				while (!is_placed)
// 				{
// 					if (Compare(val.first, temp->value.first))
// 					{
// 						if (!temp->left)
// 						{
// 							temp->left = new_node;
// 							new_node->parent = temp;
// 							is_placed = true;
// 							nb_node++;
// 						}
// 						temp = temp->left;
// 					}
// 					else
// 					{
// 						if (!temp->right)
// 						{
// 							temp->reght = new_node;
// 							new_node->parent = temp;
// 							is_placed = true;
// 							nb_node++;
// 						}
// 						temp = temp->right;
// 					}
// 				}
// 				return (ft::make_pair(iterator(temp, true)));
// 			}
// 	};
// }


// #endif