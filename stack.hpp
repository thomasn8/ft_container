#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> > 
	class stack
	{
		public :
		typedef T				value_type;
		typedef Container		container_type;
		typedef unsigned int	size_type;

		explicit stack(const container_type & ctnr = container_type()) : 
		c(ctnr), c_ptr(&c) {}
		~stack() {}

		bool empty() const { return c_ptr->empty(); }
		size_type size() const { return c_ptr->size(); }
		value_type & top() { return c_ptr->back(); }
		const value_type & top() const { return c_ptr->back(); }

		void push(const value_type & val) { c_ptr->push_back(val); }
		void pop() { c_ptr->pop_back(); }
		void swap(stack & x) { c_ptr->swap(*(x.getCtnrPtr())); }

		container_type * getCtnrPtr() const { return c_ptr; }

		protected :
		container_type c;
		container_type * c_ptr;
	};

// NON MEMBER FUNCTION
	template <class T, class Container>
  	void swap (stack<T,Container> & x, stack<T,Container> & y) { x.swap(y); }

// RELATIONAL OPERATORS
	template <class T, class Container>
  	bool operator==(const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return *(lhs.getCtnrPtr()) == *(rhs.getCtnrPtr());
	}
	template <class T, class Container>
	bool operator!=(const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return *(lhs.getCtnrPtr()) != *(rhs.getCtnrPtr());
	}

	template <class T, class Container>
	bool operator<(const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return *(lhs.getCtnrPtr()) < *(rhs.getCtnrPtr());
	}

	template <class T, class Container>
	bool operator<=(const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return *(lhs.getCtnrPtr()) <= *(rhs.getCtnrPtr());
	}
	template <class T, class Container>
	bool operator>(const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return *(lhs.getCtnrPtr()) > *(rhs.getCtnrPtr());
	}
	template <class T, class Container>
	bool operator>=(const stack<T,Container> & lhs, const stack<T,Container> & rhs)
	{
		return *(lhs.getCtnrPtr()) >= *(rhs.getCtnrPtr());
	}
}

#endif