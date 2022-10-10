#pragma once

#include "node.hpp"

namespace ft
{
	/*
		##	Red Black Tree Iterators	**
	*/
	template<typename T>
	class RBTIterator
	{
		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef typename ft::iterator_traits<T*>::value_type 		value_type;
			typedef typename ft::iterator_traits<T*>::reference 		reference;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef Node<typename ft::remove_const<value_type>::type >* node_pointer;

		private:
			node_pointer		_node;

		public:
			RBTIterator() : _node(NULL) {}
			RBTIterator(void *node): _node(static_cast<node_pointer>(node)) {}
			RBTIterator(const RBTIterator<typename std::remove_const<value_type>::type > & other) : _node(other.base()) {}

			RBTIterator&		operator=(const RBTIterator<typename ft::remove_const<value_type>::type>& other)
			{
				_node = other.base();
				return (*this);
			}
			reference			operator*() const { return (*(_node->pair)); }
			pointer				operator->() const { return (_node->pair); }
			RBTIterator&		operator++()
			{
				if (_node->right)
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
				return *this;
			}
			RBTIterator			operator++(int)
			{
				RBTIterator<value_type> temp = *this;
				if (_node->right)
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
				return temp;
			}
			RBTIterator&		operator--()
			{
				if (_node->left)
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
				return *this;
			}
			RBTIterator			operator--(int) {
				RBTIterator<value_type> temp = *this;
				if (_node->left)
					_node = tree_max(_node->left);
				else
				{
					node_pointer y = _node->parent;
					while (y != NULL && _node == y->left) {
						_node = y;
						y = y->parent;
					}
					_node = y;
				}
				return temp;
			}

			node_pointer	base(void) const { return (_node); }
			value_type		content(void) const { return (*_node); }

			private:
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
	bool operator==(const RBTIterator<A> & lhs, const RBTIterator<B> & rhs) { return (lhs.base() == rhs.base()); }

	template<typename A, typename B>
	bool operator!=(const RBTIterator<A> & lhs, const RBTIterator<B> & rhs) { return (lhs.base() != rhs.base()); }


	template <class Iterator>
	class reverse_RBTIterator
{
	public:
		typedef	Iterator	iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
	private:
		iterator_type	base_iterator;
	public:
		reverse_RBTIterator() : base_iterator() {}
		explicit reverse_RBTIterator (iterator_type it) : base_iterator(it) {}
		template <class Iter>
			reverse_RBTIterator (const reverse_RBTIterator<Iter>& rev_it){
			base_iterator = rev_it.base_iterator;
		}
		iterator_type base() const
		{
			return (base_iterator.base());
		}
		reference operator*() const
		{
			return (base_iterator.operator*());
		}
		reverse_RBTIterator operator+ (difference_type n) const
		{
			return (reverse_RBTIterator(base_iterator - n));	
		}
		reverse_RBTIterator& operator++()
		{
			--base_iterator;
			return(*this);
		}
		reverse_RBTIterator  operator++(int)
		{
			reverse_RBTIterator temp = *this;
			++(*this);
			return temp;	
		}
		reverse_RBTIterator& operator+= (difference_type n){
			base_iterator -= n;
			return (*this);
		}
		reverse_RBTIterator operator- (difference_type n) const{
			return (reverse_RBTIterator(base_iterator + n)); 
		}
		reverse_RBTIterator& operator--()
		{
			++base_iterator;
			return(*this);
		}
		reverse_RBTIterator  operator--(int){
			reverse_RBTIterator temp = *this;
			--(*this);
			return temp;
		}
		reverse_RBTIterator& operator-= (difference_type n){
			base_iterator += n;
			return (*this);
		}
		pointer operator->() const{
			return (base_iterator.operator->());
		}
};


template <class Iterator>
  bool operator== (const reverse_RBTIterator<Iterator>& lhs,
                   const reverse_RBTIterator<Iterator>& rhs){
		return(lhs.base() == rhs.base());
}
template <class Iterator>
  bool operator!= (const reverse_RBTIterator<Iterator>& lhs,
                   const reverse_RBTIterator<Iterator>& rhs){
		return(lhs.base() != rhs.base());
}
template <class Iterator>
  bool operator<  (const reverse_RBTIterator<Iterator>& lhs,
                   const reverse_RBTIterator<Iterator>& rhs);
template <class Iterator>
  bool operator<= (const reverse_RBTIterator<Iterator>& lhs,
                   const reverse_RBTIterator<Iterator>& rhs);
template <class Iterator>
  bool operator>  (const reverse_RBTIterator<Iterator>& lhs,
                   const reverse_RBTIterator<Iterator>& rhs);
template <class Iterator>
  bool operator>= (const reverse_RBTIterator<Iterator>& lhs,
                   const reverse_RBTIterator<Iterator>& rhs);
template <class Iterator>
  reverse_RBTIterator<Iterator> operator+ (
             typename reverse_RBTIterator<Iterator>::difference_type n,
             const reverse_RBTIterator<Iterator>& rev_it){
	return(rev_it + n);
}
template <class Iterator>
  typename reverse_RBTIterator<Iterator>::difference_type operator- (
    const reverse_RBTIterator<Iterator>& lhs,
    const reverse_RBTIterator<Iterator>& rhs){
	return(lhs.base() - rhs.base());
}
};