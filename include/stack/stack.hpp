#pragma once

#include "../vector/vector.hpp"

namespace ft
{
	// -- STACK --
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		// Type definitions
		public:
			typedef	T			value_type;
			typedef	Container	container_type;
			typedef	size_t		size_type;

		// Member variable
		private:
			container_type	_container;

		// Constructors
		public:
			explicit stack (const container_type& ctnr = container_type()) : _container(ctnr) {}
			stack (const stack& other) : _container(other._container) {}

		// Operator Overloads
		public:
			stack&	operator=(const stack& other)
			{
				_container = other._container;
				return (*this);
			}

		// Member Functions
			bool				empty() const { return _container.empty(); }
			size_type			size() const { return _container.size(); }
			value_type&			top() { return _container.back(); }
			const value_type&	top() const { return _container.back(); }
			void				push(const value_type& val) { _container.push_back(val); }
			void				pop() { _container.pop_back(); }

		// Non Member Overloads
		public:
			template <class Tn, class ContainerN>
				friend bool	operator==(const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
			template <class Tn, class ContainerN>
				friend bool	operator!=(const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
			template <class Tn, class ContainerN>
				friend bool	operator<(const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
			template <class Tn, class ContainerN>
				friend bool	operator<=(const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
			template <class Tn, class ContainerN>
				friend bool	operator>(const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
			template <class Tn, class ContainerN>
				friend bool	operator>=(const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
	};

	template <class T, class Container>
	bool	operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs._container == rhs._container); }
	template <class T, class Container>
	bool	operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs._container != rhs._container); }
	template <class T, class Container>
	bool	operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs._container < rhs._container); }
	template <class T, class Container>
	bool	operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs._container <= rhs._container); }
	template <class T, class Container>
	bool	operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs._container > rhs._container); }
	template <class T, class Container>
	bool	operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) { return (lhs._container >= rhs._container); }
}