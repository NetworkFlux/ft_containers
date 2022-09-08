/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:24:46 by npinheir          #+#    #+#             */
/*   Updated: 2022/09/08 13:08:10 by npinheir         ###   ########.fr       */
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
			explicit vector (const allocator_type& alloc = allocator_type()) :_container(NULL), _size(0), _capacity(0), _allocator(alloc) {}

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc)
			{
				_container = _allocator.allocate(n);
				for (size_type i = 0; i < n; i++)
					_allocator.construct(_container + i, val);
			}

			vector (const vector& x) : _size(x._size), _capacity(x._size), _allocator(x._allocator)
			{
				_container = _allocator.allocate(x._size);
				for (size_t i = 0; i < _size; i++)
					_allocator.construct(_container + i, x._container[i]);
			}

			// template <class InputIterator>
			// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _allocator(alloc)
			// {
			// 	InputIterator	temp = first;
			// 	size_t			capacity = 0;
			// 	size_t			i = 0;

			// 	while (temp != last)
			// 		capacity++;
			// 	_container = _allocator.allocate(capacity);
			// 	_capacity = capacity;
			// 	_size = capacity;
			// 	while (first != last)
			// 	{
			// 		_allocator.construct(_container + i++, first);
			// 		first++;
			// 	}
			// }

		/*	DESTRUCTOR	*/
			~vector()
			{
				clearContainer();
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

			void resize (size_type n, value_type val = value_type())
			{
				if (n < _size)
					reallocate(n);
				else
				{
					for (size_t i = 0; i < (n - _size); i++)
						push_back(val);
				}
			}

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

		// -- ELEMENTS ACCESS --
		public:
			reference operator[](size_type n) { return (_container[n]); }
			const_reference operator[](size_type n) const { return (_container[n]); }
			reference at(size_type n)
			{
				//exception + verif n
				return *(_container + n);
			}
			const_reference at(size_type n) const
			{
				//exception + verif n
				return *(_container + n);
			}
			reference front()
			{
				return *_container;
			}
			const_reference front() const
			{
				return *_container;
			}
			reference back()
			{
				return *(_container + _size - 1);
			}
			const_reference back() const
			{
				return *(_container + _size - 1);
			}

			pointer data() {return _container;}
			const pointer data() const {return _container;}

		// -- MODIFIERS --

			// template <class InputIterator>
			// void assign(InputIterator first, InputIterator last)
			// {
				
			// }

			void assign(size_type n, const_reference val)
			{
				clearContainer();
				_size = 0;
				_capacity = 0;
				if (n == 0)
					return;
				_container = _allocator.allocate(n);
				_capacity = n;
				while (_size < n)
					_container[_size++] = val;
			}
		
			void push_back (const value_type& val)
			{
				if (_size >= _capacity)
					reallocate(_capacity * 2);
				_container[_size] = val;
				_size++;
			}

			void pop_back()
			{
				if (!empty())
					_allocator.destroy(_container + --_size);
			}

			iterator insert(iterator position, const_reference val)
			{
				pointer		new_container;
				iterator	first = begin();
				iterator	res;
				iterator	last = end(); 
				size_t		i = 0;

				
				if (_size >= _capacity)
					reallocate(_capacity * 2);
				new_container = _allocator.allocate(_capacity);
				while (first != position)
				{
					new_container[i++] = *first;
					++first;
				}
				new_container[i] = val;
				res = iterator(&new_container[i++]);
				while (position != last)
				{
					new_container[i++] = *position;
					++position;
				}
				clearContainer();
				_container = new_container;
				_size++;
				return (res);
			}

			iterator insert(iterator position, size_type n, const_reference val)
			{
				pointer	new_container;
				iterator	first = begin();
				iterator	res;
				iterator	last = end();
				size_t		i = 0;
				size_type	hold = n;

				
				if (_size + n > _capacity)
					reallocate(_capacity * 2); // might not be enough
				new_container = _allocator.allocate(_capacity);
				while (first != position)
				{
					new_container[i++] = *first;
					++first;
				}
				while (n > 0)
				{
					new_container[i] = val;
					if (n == hold)
						res = iterator(&new_container[i]);
					n--;
					i++;
					_size++;
				}
				while (position != last)
				{
					new_container[i++] = *position;
					++position;
				}
				clearContainer();
				_container = new_container;
				return (res);
			}

			// template <InputIterator>
			// void insert(iterator position, InputIterator first, InputIterator last)
			// {
				
			// }

		// -- ALLOCATOR --
			allocator_type get_allocator() const { return _allocator; }

		/*	HELPING FUNCTIONS	*/
		private:
			void reallocate(size_type new_capacity)
			{
				pointer	new_container = NULL;

				if (new_capacity == 0)
					new_capacity = 1;
				if (new_capacity < _capacity)
				{
					new_container = _allocator.allocate(new_capacity);
					for (size_t i = 0; i < new_capacity; i++)
						new_container[i] = _container[i];
					_size = new_capacity;
				}
				else if (new_capacity > _capacity)
				{
					new_container = _allocator.allocate(new_capacity);
					for (size_t i = 0; i < _size; i++)
						new_container[i] = _container[i];
				}
				clearContainer();
				_container = new_container;
				_capacity = new_capacity;
			}

			void	clearContainer(void)
			{
				if (_capacity)
				{
					for (size_t i = 0; i < _size; i++)
						_allocator.destroy(_container + i);
					_allocator.deallocate(_container, _capacity);
				}
			}
	};
}

#endif