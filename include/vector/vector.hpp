#pragma once

#include "RAIterators.hpp"
#include <memory>
#include <iterator>

namespace ft
{
	// -- VECTOR --
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		// Type definitions
		public:
			typedef				T											value_type;
			typedef				Alloc										allocator_type;
			typedef typename	allocator_type::reference					reference;
			typedef typename	allocator_type::const_reference				const_reference;
			typedef typename	allocator_type::pointer						pointer;
			typedef typename	allocator_type::const_pointer				const_pointer;
			typedef				random_access_iterator<value_type>			iterator;
			typedef				random_access_iterator<const value_type>	const_iterator;
			typedef 			ft::reverse_iterator<iterator>				reverse_iterator;
			typedef 			ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename	iterator_traits<iterator>::difference_type	difference_type;
			typedef typename	allocator_type::size_type					size_type;

			
		// Member variables
		private:
			pointer			_container;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_allocator;

		// Constructors
		public:
			explicit vector (const allocator_type& alloc = allocator_type()) : _container(NULL), _size(0), _capacity(0), _allocator(alloc) {}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc)
			{
				if (n > 0)
				{
					_container = _allocator.allocate(n);
					for (size_type i = 0; i < n; i++)
						_allocator.construct(_container + i, val);
				}
			}
			vector (const vector& x) : _size(0), _capacity(0)
			{
				*this = x;
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _allocator(alloc)
			{
				_size = last - first;
				_capacity = _size;
				_container = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_container + i, *(first + i));
			}
			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_container + i);
				if (_capacity)
					_allocator.deallocate(_container, _capacity);
			}

		// Operator Overloads
		public:
			vector& operator= (const vector& x)
			{
				if (this == &x)
					return *this;
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_container + i);
				this->_size = x._size;
				if(_capacity < _size){
					if (_capacity != 0)
						_allocator.deallocate(_container, _capacity);
					_capacity = _size;
					_container = _allocator.allocate(_capacity);
				}
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(_container + i, x[i]);
				return *this;
		}

		// Member Functions
		public:
			// Iterators
			iterator		begin() { return (_container); }
			iterator 		end() { return (_container + _size); }
			const_iterator	begin() const { return (_container); }
			const_iterator	end() const { return (_container + _size); }
			
			reverse_iterator		rbegin() { return (reverse_iterator(end())); }
			reverse_iterator		rend() { return (reverse_iterator(this->begin())); }
			const_reverse_iterator	rbegin() const { return (reverse_iterator(this->end())); }
			const_reverse_iterator	rend() const { return (reverse_iterator(this->begin())); }

			// Capacity
			size_type	size() const { return (_size); }
			size_type	max_size() const { return (allocator_type().max_size()); }
			void		resize (size_type n, value_type val = value_type())
			{
				if(n < _size)
				{
					for(size_type i = n; i < _size; i++)
						_allocator.destroy(_container + i);
					_size = n;
				}
				else if (n > _size)
				{
					if (_capacity < n)
						reserve(_capacity * 2 > n ? _capacity * 2 : n);
					for (size_type i = _size; i < n; i++)
					{
						_allocator.construct(_container + i, val);
						_size++;
					}
				}
			}
			size_type	capacity() const { return (_capacity); }
			bool		empty() const
			{
				if (_size == 0)
					return (true);
				else
					return (false);
			}
			void		reserve (size_type n)
			{
				if (n > _capacity)
					reallocate(n);
			}

			// Element Access
			reference		operator[](size_type n) { return (_container[n]); }
			const_reference	operator[](size_type n) const { return (_container[n]); }
			reference		at(size_type n)
			{
				if (n > _size)
					throw std::out_of_range("vector at out of range");
				return (_container[n]);
			}
			const_reference	at(size_type n) const
			{
				if (n > _size)
					throw std::out_of_range("vector at out of range");
				return (_container[n]);
			}
			reference		front()
			{
				return (*_container);
			}
			const_reference	front() const
			{
				return (*_container);
			}
			reference		back()
			{
				return (_container[_size -1]);
			}
			const_reference	back() const
			{
				return (_container[_size -1]);
			}
			pointer			data() { return (_container); }
			const pointer	data() const { return (_container); }

			// Modifiers

			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_container + i);
				_size = 0;
				if (last - first > static_cast<difference_type>(_capacity))
				{
					_allocator.deallocate(_container, _capacity);
					_container = _allocator.allocate(last - first);
					_capacity = last - first;
				}
				for (; first != last; first++)
					push_back(*first);
			}
			void		assign(size_type n, const_reference val)
			{
				for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_container + i);
				_size = 0;
				if (n > _capacity)
				{
					_allocator.deallocate(_container, _capacity);
					_container = _allocator.allocate(n);
					_capacity = n;
				}
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}
			void		push_back (const value_type& val)
			{
				if (_size == _capacity)
					reallocate(_capacity * 2);
				_container[_size++] = val;
			}
			void		pop_back()
			{
				if (!empty())
					_allocator.destroy(_container + --_size);
			}
			iterator	insert(iterator position, const_reference val)
			{ 
				if (position < begin() || position > end())
					throw (std::logic_error("vector"));
				difference_type	start = position - begin();
				if (_size == _capacity)
				{
					_capacity = _capacity * 2 + (_capacity == 0);
					pointer new_arr = _allocator.allocate(_capacity);
					std::uninitialized_copy(begin(), position, iterator(new_arr));
					_allocator.construct(new_arr + start, val);
					std::uninitialized_copy(position, end(), iterator(new_arr + start + 1));
					for (size_t i = 0; i < _size; i++)
						_allocator.destroy(_container + i);
					if (_size)
						_allocator.deallocate(_container, _size);
					_size++;
					_container = new_arr;
				}
				else
				{
					for (size_type i = _size; i > static_cast<size_type>(start); i--)
					{
						_allocator.destroy(_container + i);
						_allocator.construct(_container + i, *(_container + i - 1));
					}
					_allocator.destroy(&(*position));
					_allocator.construct(&(*position), val);
					_size++;
				}
				return (begin() + start);
			}
			void		insert(iterator position, size_type n, const_reference val)
			{
				if (n == 0)
					return ;
				else if (max_size() - _size < n)
					throw std::length_error("vector");
				difference_type start = position - begin();
				if (_size + n > _capacity)
				{
					size_type new_cap = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
					pointer new_arr = _allocator.allocate(new_cap);
					std::uninitialized_copy(begin(), position, iterator(new_arr));
					for (size_type i = 0; i < n; i++)
						_allocator.construct(new_arr + start + i, val);
					std::uninitialized_copy(position, end(), iterator(new_arr + start + n));
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_container + i);
					_allocator.deallocate(_container, _capacity);
					_size += n;
					_capacity = new_cap;
					_container = new_arr;
				}
				else
				{
					for (size_type i = _size; i > static_cast<size_type>(start); i--) {
						_allocator.destroy(_container + i + n - 1);
						_allocator.construct(_container + i + n - 1, *(_container + i - 1));
					}
					for (size_type i = 0; i < n; i++){
						_allocator.destroy(_container + i + start);
						_allocator.construct(_container + i + start, val);
					}
					_size += n;
				}
			}
			template <class InputIterator>
			void		insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				if (position < begin() || position > end() || first > last)
					throw std::logic_error("vector");
				size_type start = static_cast<size_type>(position - begin());
				size_type count = static_cast<size_type>(last - first);
				if (_size + count > _capacity)
				{
					size_type new_cap = _capacity * 2 >= _size + count ? _capacity * 2 : _size + count;
					pointer new_arr = _allocator.allocate(new_cap);
					std::uninitialized_copy(begin(), position, iterator(new_arr));
					try
					{
						for (size_type i = 0; i < static_cast<size_type>(count); i++, first++)
							_allocator.construct(new_arr + start + i, *first);
					}
					catch (...)
					{
						for (size_type i = 0; i < count + start; ++i)
							_allocator.destroy(new_arr + i);
						_allocator.deallocate(new_arr, new_cap);
						throw;
					}
					std::uninitialized_copy(position, end(), iterator(new_arr + start + count));
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_container + i);
					_allocator.deallocate(_container, _capacity);
					_size += count;
					_capacity = new_cap;
					_container = new_arr;
				}
				else
				{
					for (size_type i = _size; i > static_cast<size_type>(start); i--) {
						_allocator.destroy(_container + i + count - 1);
						_allocator.construct(_container + i + count - 1, *(_container + i - 1));
					}
					for (size_type i = 0; i < static_cast<size_type>(count); i++, first++) {
						_allocator.destroy(_container + i + count);
						_allocator.construct(_container + start + i, *first);
					}
					_size += count;
				}
			}
			iterator	erase(iterator position)
			{
				size_type d = static_cast<size_type>(std::distance(begin(), position));
				for (size_type i = d; i < _size - 1; ++i)
				{
					_allocator.destroy(_container + i);
					_allocator.construct(_container + i, *(_container + i + 1));
				}
				_size--;
				_allocator.destroy(_container + _size - 1);
				return iterator(_container + d);
			}
			iterator	erase(iterator first, iterator last)
			{
				difference_type start = std::distance(begin(), first);
				difference_type need_to_copy = std::distance(last, end());
				bool last_is_end = (last == end());
				while (first != last)
				{
					_allocator.destroy(&(*first));
					first++;
				}
				size_type i = start;
				while (last < end())
				{
					if (this->_container + start)
						_allocator.destroy(_container + i);
					_allocator.construct(_container + i, *last);
					i++;
					last++;
				}
				for (size_type i = start + need_to_copy; i < _size; i++)
					_allocator.destroy(_container + i);
				_size = start + need_to_copy;
				return last_is_end ? end() : iterator(_container + start);
			}
			void		swap(vector& x)
			{
				std::swap(_container, x._container);
				std::swap(_size, x._size);
				std::swap(_capacity, x._capacity);
			}
			void		clear()
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_container + i);
				_size = 0;
			}

			// Allocator
			allocator_type	get_allocator() const { return _allocator; }

		// Helper Functions
		private:
			void	reallocate(size_type new_capacity)
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
			void	copy_construct(size_type idx, const_reference val)
			{
				new(&this->_container[idx]) value_type(val);
			}
	};

	// Relational operators for vector
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs));}
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(rhs < lhs)); }
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs)); }

	// Swap
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}