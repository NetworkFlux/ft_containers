#pragma once

#include "RBTIterator.hpp"

namespace ft
{
	template < class P, class Compare = std::less<P>, class Alloc = std::allocator<P> >
	class RBTree
	{
		public:
			typedef				P										pair_type;
			typedef				Compare									compare_type;
			typedef				Alloc									allocator_type;
			typedef typename	Alloc::template rebind<Node<P> >::other	node_allocator;
			typedef				Node<P>									node_type;
			typedef				Node<P>*								node_pointer;
			typedef				Node<P>&								node_reference;
			typedef				RBTIterator<P>							iterator;
			typedef				RBTIterator<const P>					const_iterator;
			typedef				size_t									size_type;

		private:
			node_allocator	_alloc;
			compare_type	_comp;
			node_pointer	_root;
			size_t			_size;

		public:
			RBTree() : _alloc(node_allocator()), _comp(compare_type()), _root(NULL), _size(0) {}
			RBTree(const compare_type& comp, const node_allocator& alloc = node_allocator())
				: _alloc(alloc), _comp(comp), _root(NULL), _size(0) {}
			template<class InputIterator>
			RBTree(typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last,
				const compare_type& comp, const node_allocator& alloc = node_allocator()) : _alloc(alloc), _comp(comp)
			{
				for (; first != last; ++first)
					insert(*first);
			}

			~RBTree() { clear_node(_root); }

			RBTree&		operator=(const RBTree& other)
			{
				_alloc = other._alloc;
				_comp = other._comp;
				_root = other._root;
				_size = other._size;
				return (*this);
			}

			// CAPACITY
			bool		empty() const
			{
				if (_size > 0)
					return (false);
				return (true);
			}

			size_type	size() const { return (_size); }

			size_type	max_size() const { return (_alloc.max_size()); }

			// MODIFIERS
			ft::pair<iterator,bool> insert (const pair_type& val)
			{
				node_pointer	is_present = search(val, _root);
				if (is_present)
					return (ft::make_pair(iterator(is_present), false));
				else
				{
					node_pointer	new_node = NULL;
					
					new_node = _alloc.allocate(1);
					_alloc.construct(new_node, val);
					add_node_to_tree(new_node, _root);
					_size++;
					// fix_tree(); // correct the tree
					return (ft::make_pair(iterator(new_node), true));
				}
			}

			iterator insert(iterator position, const pair_type& value)
			{
				node_pointer new_node = search(value, _root);
				if (new_node)
					return (iterator(new_node));
				new_node = _alloc.allocate(1);
				_alloc.construct(new_node, Node<pair_type>(create_value(value)));
				if (position == begin())
				{
					if (position != end() && _compare(value, *position))
						add_node_to_tree(new_node, tree_min(_root));
					else
						add_node_to_tree(new_node, _root);
				}
				else if (position == end()){
					if (position != begin() && _compare(*(--position), value))
						add_node_to_tree(new_node, last_node());
					else
						add_node_to_tree(new_node, _root);
				}
				else
					add_node_to_tree(new_node, _root);
				_size++;
				return (iterator(new_node));
			}

			template<class InputIterator>
			void insert(typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last)
			{
				for (; first != last; ++first)
					insert(*first);
			}

			// OBSERVERS
			compare_type	value_comp() const { return (_comp); }

			// OPERATIONS
			iterator	find(const pair_type& k) { return (iterator(search(k, _root))); }
			iterator	find(const pair_type& k) const { return (iterator(search(k, _root))); }
			
			size_type	count(const pair_type& k) const { return (find(k) != end()); }

			iterator lower_bound(const pair_type& value)
			{
				iterator last = end();
				for (iterator first = begin(); first != last; first++)
				{
					if (!_comp(*first, value))
						return (first);
				}
				return (last);
			}

			const_iterator lower_bound(const pair_type& value) const
			{
				iterator last = end();
				for (iterator first = begin(); first != last; first++)
				{
					if (!_comp(*first, value))
						return (first);
				}
				return (last);
			}

			iterator upper_bound(const pair_type& value)
			{
				iterator last = end();
				for (iterator first = begin(); first != last; first++)
				{
					if (!_comp(value, *first))
						return (first);
				}
				return (last);
			}

			const_iterator upper_bound(const pair_type& value) const
			{
				iterator last = end();
				for (iterator first = begin(); first != last; first++)
				{
					if (!_comp(value, *first))
						return (first);
				}
				return (last);
			}

			node_pointer	tree_min(node_pointer n)
			{
				if (n == NULL)
					n = _root;
				while (n->left)
					n = n->left;
				return (n);
			}

			node_pointer	tree_max(node_pointer n)
			{
				if (!n)
					n = _root;
				while (n != NULL)
					n = n->right;
				return n;
			}

			node_pointer	root(void) { return (_root); }

			iterator	begin() { return (iterator(tree_min(_root))); }
			iterator	end() { return (iterator(NULL)); }
			iterator	end() const { return (iterator(NULL)); }

		private:
			node_pointer	search(const pair_type& k, node_pointer node) const
			{
				if (!node)
					return (NULL);
				if (_comp(k, *node->pair))
					return (search(k, node->left));
				if (_comp(*node->pair, k))
					return (search(k, node->right));
				return (node);
			}

			void	add_node_to_tree(node_pointer new_node, node_pointer node)
			{
				node_pointer	parent = NULL;
				node_pointer	temp = node;
				if (!node)
				{
					_root = new_node;
					return ;
				}
				while (temp)
				{
					parent = temp;
					if (_comp(*new_node->pair, *temp->pair))
						temp = temp->left;
					else
						temp = temp->right;
				}
				new_node->parent = parent;
				new_node->color = true;
				if (_comp(*new_node->pair, *parent->pair))
					parent->left = new_node;
				else
					parent->right = new_node;
				insertion_fixup(new_node);
			}

			void	insertion_fixup(node_pointer node)
			{
				if (node != _root && node->parent != _root)
				{
					while (node != _root && node->parent->color)
					{
						if (node->parent->parent->left && node->parent == node->parent->parent->left)
						{
							node_pointer	uncle = node->parent->parent->right;

							if (uncle && uncle->color)
							{
								node->parent->color = false;
								node->parent->parent->color = true;
								node = node->parent->parent;
							}
							else
							{
								if (node->parent->right && node == node->parent->right)
								{
									node = node->parent;
									rotate_left(node);
								}
								node->parent->color = false;
								node->parent->parent->color = true;
								rotate_right(node->parent->parent);
							}
						}
						else
						{
							node_pointer	uncle = node->parent->parent->left;

							if (uncle && uncle->color)
							{
								node->parent->color = false;
								if (uncle)
									uncle->color = false;
								node->parent->parent->color = true;
								node = node->parent->parent;
							}
							else
							{
								if (node == node->parent->left)
								{
									node = node->parent;
									rotate_right(node);
								}
								node->parent->color = false;
								node->parent->parent->color = true;
								rotate_left(node->parent->parent);
							}
						}
					}
				}
				_root->color = false;
			}

			void	rotate_right(node_pointer node)
			{
				node_pointer y;

				y = node->left;
				node->left = y->right;
				// if (!y->right)
				// 	y->right->parent = node;
				y->parent = node->parent;
				if (node->parent == NULL)
					_root = y;
				else if (node == node->parent->left)
					node->parent->left = y;
				else
					node->parent->right = y;
				y->right = node;
				node->parent = y;
			}

			void	rotate_left(node_pointer node)
			{
				node_pointer y;

				y = node->right;
				node->right = y->left;
				// if (!y->left)
				// 	y->left->parent = node;
				y->parent = node->parent;
				if (node->parent == NULL)
					_root = y;
				else if (node == node->parent->left)
					node->parent->left = y;
				else
					node->parent->right = y;
				y->left = node;
				node->parent = y;
			}

			void	clear_node(node_pointer node)
			{
				if (node)
				{
					clear_node(node->right);
					clear_node(node->left);
					allocator_type().destroy(node->pair);
					allocator_type().deallocate(node->pair, 1);
					_alloc.deallocate(node, 1);
				}
			}

			node_pointer	last_node(void) const
			{
				iterator	it = begin();
				iterator	next = it;

				next++;
				while (next != end())
				{
					it++;
					next++;
				}
				return (it.base());
			}
	};
};	