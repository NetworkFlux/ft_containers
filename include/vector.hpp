/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:24:46 by npinheir          #+#    #+#             */
/*   Updated: 2022/08/31 00:30:46 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "random_access_iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >	// Template has 2 params
	class vector
	{
		/*	PUBLIC MEMBER TYPE
			In here we see some type name changes to make the program more readable
			by having one word to discribe each type	*/
		public:
			typedef				T											value_type;
			typedef				Alloc										allocator_type;
			typedef typename	allocator_type::reference					reference;
			typedef typename	allocator_type::const_reference				const_reference;
			typedef typename	allocator_type::pointer						pointer;
			typedef typename	allocator_type::const_pointer				const_pointer;
			typedef	random_access_iterator<value_type>						iterator;
			typedef	random_access_iterator<const value_type>				const_iterator;
			// typedef typename	reverseIterator<iterator>					reverse_iterator;
			// typedef typename	reverseIterator<const_iterator>				const_reverse_iterator;
			typedef typename	iterator_traits<iterator>::difference_type	difference_type;
			typedef typename	allocator_type::size_type					size_type;

			
		/*	PRIVATE MEMBER TYPE	*/
		private:
			pointer			_container;	// A pointer pointing to the actual vector
			size_type		_size;		// The actual size of the vector
			size_type		_capacity;	// The maximum size of the vector
			allocator_type	_allocator;	// Object responsible for allocation

		/*	 CONSTRUCTORS	*/
		public:
			explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc)
			{
				_container = _allocator.allocate(0);
			}


			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc)
			{
				_container = _allocator.allocate(n);
				for (size_type i = 0; i < n; i++)
					_container[i] = val;
			}

		/*	DESTRUCTOR	*/
			~vector()
			{
				if (!_capacity)
					delete[] _container;
			}

		/*	PUBLIC METHODS OF VECTORS	*/

		// -- ITERATORS --
		public:
			iterator begin() {return _container;}
			const_iterator begin() const {return _container;}
			iterator end() {return _container + _size;}
			const_iterator end() const {return _container + _size;}
			// reverse iterators ...

		// -- CAPACITY --
		public:
			size_type size() const { return _size; }

			size_type max_size() const { return allocator_type().max_size(); } // size_type is too small to take the big number needed

			// void resize (size_type n, value_type val = value_type())

			size_type capacity() const { return _capacity; }

			bool empty() const
			{
				if (_size == 0)
					return true;
				else
					return false;
			}

			void reserve (size_type n)
			{
				if (n > _capacity)
					reallocate(n);
			}

			void shrink_to_fit()
			{
				if (_capacity > _size)
					reallocate(_size);
			}

		// -- ELEMENTS ACCESS --
		public:
			reference operator[](size_type n) { return (_container[n]); }
			const_reference operator[](size_type n) const { return (_container[n]); }
			reference at(size_type n)
			{
				//exception
				if (n < _size)
					return *(_container + n);
			}
			const_reference at(size_type n) const
			{
				//exception
				if (n < _size)
					return *(_container + n);
			}
			reference front()
			{
				if (empty())
					return NULL;
				else
					return *_container;
			}
			const_reference front() const
			{
				if (empty())
					return NULL;
				else
					return *_container;
			}
			reference back()
			{
				if (empty())
					return NULL;
				else
					return *(_container + _size - 1);
			}
			const_reference back() const
			{
				if (empty())
					return NULL;
				else
					return *(_container + _size - 1);
			}

			pointer data() {return _container;}
			const pointer data() const {return _container;}

		// -- MODIFIERS --
			void push_back (const value_type& val)
			{
				if (_size >= _capacity)
					reallocate(_capacity * 2);
				_container[_size++] = val;
			}

		// -- ALLOCATOR --
			allocator_type get_allocator() const { return _allocator; }

		/*	HELPING FUNCTIONS	*/
		private:
			void reallocate(size_type new_capacity)
			{
				pointer	new_container;

				if (_capacity == 0)
					new_capacity = 1;
				else if (new_capacity <= _capacity)
					new_capacity = 2 * _capacity;
				new_container = _allocator.allocate(new_capacity);
				for (size_type i = 0; i < _size; i++)
					new_container[i] = _container[i];
				delete[] _container;
				_container = new_container;
				_capacity = new_capacity;
			}
		
	};
}

#endif