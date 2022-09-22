// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   map.hpp                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/19 16:29:42 by npinheir          #+#    #+#             */
// /*   Updated: 2022/09/22 14:44:12 by npinheir         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef MAP_HPP
// # define MAP_HPP

// # include "binary_search_tree.hpp"

// namespace ft
// {
// 	template< typename Key, typename T, class Compare = ft::less<Key>,
// 				class Allocator = std::allocator<std::pair<const Key, T> > >
// 	class map
// 	{
// 		// PUBLIC MEMBER
// 		public:
// 			typedef				Key											key_type;
// 			typedef				T											mapped_type;
// 			typedef				ft::pair<const key_type, mapped_type>		value_type;
// 			typedef				Compare										key_compare;
// 			typedef				Allocator									allocator_type;
// 			typedef typename	allocator_type::reference					reference;
// 			typedef typename	allocator_type::const_reference				const_reference;
// 			typedef typename	allocator_type::pointer						pointer;
// 			typedef typename	allocator_type::const_pointer				const_pointer;
// 			typedef 			bstIterator<value_type, key_compare>		const_iterator;
// 			typedef 			const_iterator								iterator;
// 			// typedef 			ft::reverse_iterator<iterator>				reverse_iterator;
// 			// typedef 			ft::reverse_iterator<const_iterator>		const_reverse_iterator;
// 			typedef typename	iterator_traits<iterator>::difference_type	difference_type;
// 			typedef typename	allocator_type::size_type					size_type;
// 			class value_compare
// 			{
// 				friend class map<key_type, mapped_type, key_compare, Alloc>;

// 				protected:
// 					Compare comp;

// 					value_compare( Compare c ) : comp(c) {}
				
// 				public:
// 					bool operator()( const value_type& lhs, const value_type& rhs ) const { return (comp(lhs.first, rhs.first)); }
// 			};

// 		private:
// 			allocator_type							_alloc;
// 			key_compare								_comp;
// 			BinarySearchTree<value_type, Compare>	_bst;

// 		public:
// 			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp) _bst() {}
// 			// template <class InputIterator>
// 			// map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {}
// 			// map (const map& x) : _alloc(x._alloc), _comp(x._comp) { }
// 			~map() {}

// 			map&	operator= (const map& x)
// 			{
// 				if (*this == x)
// 					return (*this);
// 				_alloc = x._alloc;
// 				_comp = x._comp;
// 				_bst = x._bst;
// 				return (*this);
// 			}

// 			ft::pair<iterator,bool>	insert (const value_type& val) { return (_bst.insertPair(val)); }
// 	};
// }

// #endif