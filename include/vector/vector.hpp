#pragma once

#include "RAIterators.hpp"
#include <memory>
#include <iterator>

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
			typedef 			ft::reverse_iterator<iterator>				reverse_iterator;
			typedef 			ft::reverse_iterator<const_iterator>		const_reverse_iterator;
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
			explicit vector (const allocator_type& alloc = allocator_type()) : _container(NULL), _size(0), _capacity(0), _allocator(alloc) {}
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

		/*	DESTRUCTOR	*/
			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(_container + i);
				if (_capacity)
					_allocator.deallocate(_container, _capacity);
			}

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

		/*	PUBLIC METHODS OF VECTORS	*/

		// -- ITERATORS --
		public:
			iterator begin() { return (_container); }
			const_iterator begin() const { return (_container); }
			reverse_iterator rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator rbegin() const { return (reverse_iterator(this->end())); }
			iterator end() { return (_container + _size); }
			const_iterator end() const { return (_container + _size); }
			reverse_iterator rend() { return (reverse_iterator(this->begin())); }
			const_reverse_iterator rend() const { return (reverse_iterator(this->begin())); }

		// -- CAPACITY --
		public:
			size_type size() const { return (_size); }
			size_type max_size() const { return (allocator_type().max_size()); }
			void resize (size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
					while (_size > n)
						_allocator.destroy(_container + (_size-- - 1));
				}
				else
				{
					for (size_t i = _size; i < n; i++)
						push_back(val);
				}
			}
			size_type capacity() const { return (_capacity); }
			bool empty() const
			{
				if (_size == 0)
					return (true);
				else
					return (false);
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
				if (n > _size)
					throw std::out_of_range("vector at out of range");
				return (_container[n]);
			}
			const_reference at(size_type n) const
			{
				if (n > _size)
					throw std::out_of_range("vector at out of range");
				return (_container[n]);
			}
			reference front()
			{
				return (*_container);
			}
			const_reference front() const
			{
				return (*_container);
			}
			reference back()
			{
				return (_container[_size -1]);
			}
			const_reference back() const
			{
				return (_container[_size -1]);
			}
			pointer data() { return (_container); }
			const pointer data() const { return (_container); }

		// -- MODIFIERS --

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
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
			void assign(size_type n, const_reference val)
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
			void push_back (const value_type& val)
			{
				if (_size == _capacity)
					reallocate(_capacity * 2);
				_container[_size++] = val;
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
				{
					reallocate(_capacity * 2);
					new_container = _allocator.allocate(_capacity * 2);
				}
				else
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
			void insert(iterator position, size_type n, const_reference val)
			{
				pointer		new_container;
				iterator	first = begin();
				iterator	last = end();
				iterator	res;
				size_t		i = 0;

				while (_size + n > _capacity)
					reallocate(_capacity * 2);
				new_container = _allocator.allocate(_size + n);
				while (first != position)
				{
					new_container[i] = *first;
					first++;
					i++;
				}
				while (n)
				{
					new_container[i] = val;
					i++;
					n--;
				}
				while (position != last)
				{
					new_container[i] = *position;
					i++;
					++position;
				}
				clearContainer();
				_container = new_container;
				_size = i;
			}
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				pointer		new_container = NULL;
				iterator	f = begin();
				iterator	l = end();
				iterator	res;
				size_t		i = 0;

				while (_size + (last - first) > _capacity)
					_capacity = _capacity * 2;
				new_container = _allocator.allocate(_size + (last - first));
				while (f != position)
				{
					new_container[i++] = *f;
					f++;
				}
				while (first != last)
				{
					new_container[i++] = *first;
					first++;
				}
				while (position != l)
				{
					new_container[i++] = *position;
					++position;
				}
				clearContainer();
				_container = new_container;
				_size = i;
			}
			iterator erase(iterator position)
			{
				iterator tmp(position);
				++tmp;
				return (this->erase(position, tmp));
			}
			iterator erase(iterator first, iterator last)
			{
				iterator it = this->begin();
				size_type i = 0;
				while (it != first) {
					++it;
					++i;
				}
				if (it == this->end())
					return (this->end());
				size_type returnPosition = i;
				size_type deletedElements = 0;
				size_type stopPos = i;
				while (first != last) {
					(*first++).value_type::~value_type();
					++deletedElements;
					++stopPos;
				}
				// std::memmove ?
				for ( ; stopPos < this->_size; ++stopPos)
					this->copy_construct(i++, this->_container[stopPos]);
				this->_size -= deletedElements;
				return (iterator(&this->_container[returnPosition]));
			}
			void swap(vector& x)
			{
				ft::vector<value_type>	temp(x);
				x = *this;
				*this = temp;
			}
			void clear()
			{
				while (_size)
					_allocator.destroy(_container + _size--);
			}

		// -- ALLOCATOR --
			allocator_type get_allocator() const { return _allocator; }

		/*	HELPING FUNCTIONS	*/
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
			void copy_construct(size_type idx, const_reference val)
			{
				new(&this->_container[idx]) value_type(val);
			}
	};

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

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}