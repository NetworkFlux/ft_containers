#pragma once

#include "treeIterator.hpp"

namespace ft
{
	// -- RED BLACK TREE --
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >	// T should always be a Pair
	class Tree
	{
		// Type definition
			public:
			typedef	T									pair_type;
			typedef	Compare								compare_type;
			typedef	Alloc								allocator_type;
			typedef typename	allocator_type::pointer	pointer;
			typedef typename Alloc::template
					rebind<Node<pair_type> >::other		node_allocator;
			typedef	Node<T>								node_type;
			typedef	Node<T>*							node_pointer;
			typedef	Node<T>&							node_reference;
			typedef	TreeIterator<T>						iterator;
			typedef	TreeIterator<const T>				const_iterator;
			typedef	ReverseTreeIterator<iterator>		reverse_iterator;
			typedef	ReverseTreeIterator<const_iterator>	const_reverse_iterator;
			typedef	size_t								size_type;

		// Member variables
		private:
			compare_type	_comp;
			allocator_type	_val_alloc;
			node_allocator	_alloc;
			node_pointer	_root;
			node_pointer	_begin;
			node_pointer	_end;
			node_pointer	_nil;
			size_type		_size;

		// Constructors
		public:
			Tree() : _comp(compare_type()), _val_alloc(allocator_type()), _alloc(node_allocator()), _root(NULL), _begin(NULL), _end(NULL), _size(0)
			{
				init_nil();
			}
			Tree(const compare_type& comp, const allocator_type& alloc = allocator_type())
			: _comp(comp), _val_alloc(alloc), _alloc(node_allocator()), _root(NULL), _begin(NULL), _end(NULL), _size(0)
			{
				init_nil();
			}
			template <class InputIterator>
			Tree(typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last,
				const compare_type& comp, const node_allocator& alloc = node_allocator()) : _comp(comp), _alloc(alloc), _root(NULL),
				_begin(NULL), _end(NULL), _size(0)
			{
				init_nil();
				for (; first != last; ++first)
					insert(ft::make_pair(first->first, first->second));
			}



			~Tree()
			{
				erase(begin(), end());
				_alloc.deallocate(_nil, 1);
			}

		// Operator Overloads
		public:
			Tree&	operator=(const Tree& other)
			{
				_comp = other._comp;
				_val_alloc = other._val_alloc;
				_alloc = other._alloc;
				_root = other._root;
				_begin = other._begin;
				_end = other._end;
				_nil = other._nil;
				_size = other._size;
				return (*(this));
			}

		// Member Functions
		public:
			// Iterators
			iterator		begin() { return (iterator(tree_min(_root), _begin, _end)); }
			const_iterator	begin() const { return (const_iterator(_begin, _begin, _end)); }
			iterator		end() { return (iterator(NULL, _begin, _end)); }
			const_iterator	end() const { return (const_iterator(NULL, _begin, _end)); }

			reverse_iterator		rbegin() { return (reverse_iterator(iterator(tree_max(_root), tree_min(_root), tree_max(_root)))); }
			const_reverse_iterator	rbegin() const { return (const_iterator(tree_max(_root), tree_min(_root), tree_max(_root))); }
			reverse_iterator		rend() { return (reverse_iterator(iterator(NULL, tree_min(_root), tree_max(_root)))); }
			const_reverse_iterator	rend() const { return (const_iterator(NULL, tree_min(_root), tree_max(_root))); }

			// Capacity
			bool		empty() const
			{
				if (_size > 0)
					return (false);
				return (true);
			}
			size_type	size() const { return (_size); }
			size_type	max_size() const { return (_alloc.max_size()); }

			// Modfiers
			ft::pair<iterator,bool>	insert (const pair_type& val)
			{
				node_pointer find_val = search(val, _root);
				if (find_val)
					return (ft::pair<iterator, bool>(iterator(find_val, _begin, _end), false));
				node_pointer new_node = _alloc.allocate(1);
				_alloc.construct(new_node, Node<pair_type>(create_value(val)));
				// if (new_node)
				// 	std::cout << "new_node : (" << new_node->pair->first << "; " << new_node->pair->second << ")\n";
				new_node->left = _nil;
				new_node->right = _nil;
				add_node_to_tree(new_node, _root);
				insertion_fixup(new_node);
				_size++;
				_begin = tree_min(_root);
				_end = tree_max(_root);
				// if (_begin)
				// 	std::cout << "_begin : (" << _begin->pair->first << "; " << _begin->pair->second << ")\n";
				// if (_end)
				// 	std::cout << "_end : (" << _end->pair->first << "; " << _end->pair->second << ")\n";
				return (ft::pair<iterator, bool>(iterator(new_node, _begin, _end), true));
			}
			iterator				insert(iterator position, const pair_type& value)
			{
				(void)position;
				return (insert(value).first);
			}
			template<class InputIterator>
			void					insert(typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first, InputIterator last)
			{
				for (; first != last; ++first)
					insert(ft::make_pair(first->first, first->second));
			}

			void		erase(iterator position)
			{
				delete_node(position.base());
				_begin = tree_min(_root);
				_end = tree_max(_root);
			}
			size_type	erase(const pair_type& k)
			{
				iterator	key = find(k);
				size_t		count = 0;
				while (key.base())
				{
					erase(key);
					count++;
					key = find(k);
				}
				return (count);
			}
			void		erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			}

			void		clear(void)
			{
				erase(begin(), end());
			}

			// Observers
			compare_type	value_comp() const { return (_comp); }

			// Operations
			iterator		find(const pair_type& k) { return (iterator(search(k, _root), tree_min(_root), tree_max(_root))); }
			const_iterator	find(const pair_type& k) const { return (iterator(search(k, _root), tree_min(_root), tree_max(_root))); }
			size_type		count(const pair_type& k) const { return (find(k) != end()); }
			iterator		lower_bound(const pair_type& value)
			{
				iterator last = end();
				for (iterator first = begin(); first != last; first++)
				{
					if (!_comp(*first, value))
						return (first);
				}
				return (last);
			}
			const_iterator	lower_bound(const pair_type& value) const
			{
				iterator last = end();
				for (iterator first = begin(); first != last; first++)
				{
					if (!_comp(*first, value))
						return (first);
				}
				return (last);
			}
			iterator 		upper_bound(const pair_type& value)
			{
				iterator last = end();
				for (iterator first = begin(); first != last; first++)
				{
					if (_comp(value, *first))
						return (first);
				}
				return (last);
			}
			const_iterator	upper_bound(const pair_type& value) const
			{
				iterator last = end();
				for (iterator first = begin(); first != last; first++)
				{
					if (_comp(value, *first))
						return (first);
				}
				return (last);
			}
			void			swap(Tree& other)
			{
				std::swap(_root, other._root);
				std::swap(_nil, other._nil);
				std::swap(_end, other._end);
				std::swap(_begin, other._begin);
				std::swap(_size, other._size);
				std::swap(_alloc, other._alloc);
				std::swap(_val_alloc, other._val_alloc);
				std::swap(_comp, other._comp);
			}
		// Helper Functions
		private:
			bool	is_nil(node_pointer node) const
			{
				return (node == _nil);
			}
			void	init_nil(void)
			{
				_nil = _alloc.allocate(1);
				_alloc.construct(_nil, pair_type());
				_val_alloc.deallocate(_nil->pair, 1);
				_nil->pair = NULL;
				_nil->is_nil = true;
				_nil->color = false;
			}
			// Min, max
			node_pointer	tree_min(node_pointer node) const
			{
				node_pointer	n = node;
				while (n != NULL && !is_nil(n->left))
					n = n->left;
				return (n);
			}
			node_pointer	tree_max(node_pointer node) const
 			{
				node_pointer	n = node;
				while (n != NULL && !is_nil(n->right))
					n = n->right;
				return (n);
			}

			// Additions
			pointer	create_value(const pair_type& value)
			{
				pointer	new_val = _val_alloc.allocate(1);
				_val_alloc.construct(new_val, value);
				return (new_val);
			}
			void	add_node_to_tree(node_pointer new_node, node_pointer node)
			{
				if (!_root)
					_root = new_node;
				else
				{
					if (_comp(*new_node->pair, *node->pair))
					{
						if (!is_nil(node->left))
							return (add_node_to_tree(new_node, node->left));
						node->left = new_node;
					}
					else
					{
						if (!is_nil(node->right))
							return (add_node_to_tree(new_node, node->right));
						node->right = new_node;
					}
					new_node->parent = node;
				}
			}
			void	insertion_fixup(node_pointer node)
			{
				if (node != _root && node->parent != _root)
				{
					while (node != _root && node->parent->color)
					{
						if (node->parent == node->parent->parent->left)
						{
							node_pointer uncle = node->parent->parent->right;
							if (uncle->color)
							{
								node->parent->color = false;
								uncle->color = false;
								node->parent->parent->color = true;
								node = node->parent->parent;
							}
							else
							{
								if (node == node->parent->right)
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
							node_pointer uncle = node->parent->parent->left;
							if (uncle->color)
							{
								node->parent->color = false;
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
			void	rotate_left(node_pointer node)
			{
				node_pointer y;

				y = node->right;
				node->right = y->left;
				if (!is_nil(y->left))
					y->left->parent = node;
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
			void	rotate_right(node_pointer node)
			{
				node_pointer y;

				y = node->left;
				node->left = y->right;
				if (!is_nil(y->right))
					y->right->parent = node;
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

			// Searching
			node_pointer	search(const pair_type& k, node_pointer node) const
			{
				if (!node || is_nil(node))
					return (NULL);
				if (_comp(k, *(node->pair)))
					return (search(k, node->left));
				if (_comp(*(node->pair), k))
					return (search(k, node->right));
				return (node);
			}
			node_pointer	root(void) { return (_root); }

			// Deletion
			node_pointer	last_node(void)
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
			void			transplant(node_pointer u, node_pointer v)
			{
				if (!u->parent)
					_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}
			void			delete_node(node_pointer node)
			{
				node_pointer	x = NULL;
				bool	original_color = node->color;
				if (is_nil(node->left))
				{
					x = node->right;
					transplant(node, node->right);
				}
				else if (is_nil(node->right))
				{
					x = node->left;
					transplant(node, node->left);
				}
				else
				{
					node_pointer y = NULL;
					y = tree_min(node->right);
					original_color = y->color;
					x = y->right;
					if (y->parent == node)
						x->parent = y;
					else
					{
						transplant(y, y->right);
						y->right = node->right;
						y->right->parent = y;
						y->color = node->color;
					}
					transplant(node, y);
					y->left = node->left;
					y->left->parent = y;
					y->color = node->color;
				}
				free_node(node);
				if (!original_color)
					delete_fixup(x);
				_size--;
			
			}
			void			delete_fixup(node_pointer x)
			{
				node_pointer	w;
				while (x != _root && !x->color)
				{
					if (x == x->parent->left)
					{
						w = x->parent->right;
						if (w->color)
						{
							w->color = false;
							x->parent->color = true;
							rotate_left(x->parent);
							w = x->parent->right;
						}
						if (!w->left->color && !w->right->color)
						{
							w->color = true;
							x = x->parent;
						}
						else
						{
							if (!w->right->color)
							{
								w->left->color = false;
								w->color = true;
								rotate_right(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = false;
							w->right->color = false;
							rotate_left(x->parent);
							x = _root;
						}
					}
					else
					{
						w = x->parent->left;
						if (w->color)
						{
							w->color = false;
							x->parent->color = true;
							rotate_right(x->parent);
							w = x->parent->left;
						}
						if (!w->right->color && !w->left->color)
						{
							w->color = true;
							x = x->parent;
						}
						else
						{
							if (!w->left->color)
							{
								w->right->color = false;
								w->color = true;
								rotate_left(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = false;
							w->left->color = false;
							rotate_right(x->parent);
							x = _root;
						}
					}
				}
				x->color = false;
			}
			void 			free_node(node_pointer node)
			{
				_val_alloc.destroy(node->pair);
				_val_alloc.deallocate(node->pair, 1);
				_alloc.deallocate(node, 1);
			}
	};
}