/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:32:09 by npinheir          #+#    #+#             */
/*   Updated: 2022/09/19 16:08:01 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		// PUBLIC MEMBERS
		public:
			typedef	T			value_type;
			typedef	Container	container_type;
			typedef	size_t		size_type;

		// PRIVATE MEMBERS
		private:
			container_type	_container;

		// PUBLIC METHODS
		public:
			explicit stack (const container_type& ctnr = container_type()) : _container(ctnr) {}
			stack (const stack& other) : _container(other._container) {}
			~stack () {}
		
			bool empty() const { return _container.empty();}
			size_type size() const { return _container.size(); }
			value_type& top() { return _container.back(); }
			const value_type& top() const { return _container.back(); }
			void push(const value_type& val) { _container.push_back(val); }
			void pop() { _container.pop_back(); }

			container_type& getContainer() { return _container; }
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._container == rhs._container); }
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._container != rhs._container); }
	template <class T, class Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._container > rhs._container); }
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._container >= rhs._container); }
	template <class T, class Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._container < rhs._container); }
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._container <= rhs._container); }
}

#endif