#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "iterators.hpp"
#include "utils.hpp"
#include <iostream>
namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public :
	// MEMBER TYPES
		typedef T 												value_type;
		typedef unsigned int 									size_type;
		typedef long int 										size_type2;
		typedef std::allocator<value_type> 						allocator_type;
		typedef typename allocator_type::reference 				reference;			// T &
		typedef typename allocator_type::const_reference 		const_reference;	// const T &
		typedef	typename allocator_type::pointer 				pointer;			// T *
		typedef	typename allocator_type::const_pointer 			const_pointer;		// const T *
		typedef int												difference_type;	// pour marquer les distances entre 2 ptr
		typedef	ft::random_access_iterator<value_type>			iterator;
		typedef	ft::random_access_iterator<const value_type>	const_iterator;
		typedef	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		
	// CONSTRUCTEURS/DESTRUCTEUR
		explicit vector(const allocator_type & alloc = allocator_type()) :
			_alloc(alloc), _n(0), _c(0), _capacityFactor(2), _first(NULL), _last(NULL) {}

		explicit vector(size_type2 n, const value_type & val = value_type(),
			const allocator_type & alloc = allocator_type()) :
			_alloc(alloc), _n(n), _c(n), _capacityFactor(2), _first(NULL), _last(NULL)
		{
			if (n < 0)
			{
				throw std::exception();
				return;
			}
			if (capacity_error(n))
				return;
			if (_n)
			{
				_first = _alloc.allocate(_c + 1);
				_ptr = _first;
				for (size_type i = 0; i < _n; i++)
					_alloc.construct(_ptr++, val);
				_last = --_ptr;
			}
		}
		
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, 
			const allocator_type & alloc = allocator_type(),
			typename std::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) : 
			_alloc(alloc), _n(0), _c(0), _capacityFactor(2), _first(NULL), _last(NULL)
		{
			_n = last - first;
			_c = _n;
			if (last - first < 0)
			{
				throw std::exception();
				return;
			}
			if (capacity_error(_c))
				return;
			if (_n)
			{
				_first = _alloc.allocate(_c + 1);
				_ptr = _first;
				while (first != last)
					_alloc.construct(_ptr++, *first++);
				_last = --_ptr;
			}
		}

		vector(const vector & x) :
			_alloc(x.get_allocator()), _n(x.size()), _c(x.size()),
			_capacityFactor(2), _first(NULL), _last(NULL)
		{
			if (_n)
			{
				if (capacity_error(_c))
					return;
				const_iterator first = x.begin();
				const_iterator last = x.end();
				_first = _alloc.allocate(_c + 1);
				_ptr = _first;
				while (first != last)
					_alloc.construct(_ptr++, *first++);
				_last = --_ptr;
			}
		}

		vector & operator=(const vector & x)
		{
			assign(x.begin(), x.end());
			return *this;
		}

		virtual ~vector()
		{
			if (_c)
			{
				for (size_type i = 0; i < _n; i++)
					_alloc.destroy(_first + i);
				_alloc.deallocate(_first, _c + 1);
			}
		}

	// ITERATORS
		iterator begin() 						{ return iterator(_first); }
		const_iterator begin() const 			{ return const_iterator(_first); }
		const_iterator cbegin() const 			{ return const_iterator(_first); }
		iterator end() 							{ if (_n) return iterator(_last + 1); return _last; }
		const_iterator end() const 				{ if (_n) return const_iterator(_last + 1);  return _last; }
		const_iterator cend() const 			{ if (_n) return const_iterator(_last + 1); return _last; }			
		reverse_iterator rbegin() 				{ return reverse_iterator(_last); }
		const_reverse_iterator rbegin() const 	{ return const_reverse_iterator(_last); }
		const_reverse_iterator crbegin() const	{ return const_reverse_iterator(_last); }
		reverse_iterator rend() 				{ return reverse_iterator(_first); }
		const_reverse_iterator rend() const 	{ return const_reverse_iterator(_first); }
		const_reverse_iterator crend() const	{ return const_reverse_iterator(_first); }

	// ELEMENT ACCESS
		reference operator[](size_type index)				{ return _first[index]; }
		const_reference operator[](size_type index) const	{ return _first[index]; }
		reference front() 									{ return *_first; }
		const_reference front() const 						{ return *_first; }
		reference back() 									{ return *_last; }
		const_reference back() const 						{ return *_last; }
		value_type * data() 								{ return _first; }
		const value_type * data() const 					{ return _first; }
		reference at(size_type n)
		{
			if (n >= _n)
				throw std::out_of_range("Out of range error");
			return *(_first + n);
		}
		const_reference at(size_type n) const
		{
			if (n >= _n)
				throw std::out_of_range("Out of range error");
			return *(_first + n);
		}

	// CAPACITY
		size_type size() const 			{ return _n; }
		bool empty() const 				{ return bool(!_n); }
		size_type capacity() const		{ return _c; }
		long unsigned max_size() const	{ return _alloc.max_size(); }
		
		void shrink_to_fit()
		{
			size_type distance = _c - _n;
			if (distance > 0)
			{
				iterator old_first = begin();
				iterator old_last = end();
				_ptr = _alloc.allocate(_n + 1);
				pointer new_first = _ptr;
				while (old_first != old_last)
					_alloc.construct(_ptr++, *old_first++);
				size_type n = _n;
				clear_dealloc();
				_first = new_first;
				_last = --_ptr;
				_n = n;
				_c = _n;
			}
		}

		void reserve(size_type n)
		{
			if (capacity_error(n))
				return;
			if (n > _c)
			{
				iterator old_first = begin();
				iterator old_last = end();
				_ptr = _alloc.allocate(n + 1);
				pointer new_first = _ptr;
				while (old_first != old_last)
				{
					_alloc.construct(_ptr++, *old_first);
					_alloc.destroy(&*old_first++);
				}
				size_type size = _n;
				clear_dealloc();
				_first = new_first;
				_last = --_ptr;
				_n = size;
				_c = n;
			}
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n == 0)
				clear_dealloc();
			else if (n < _n)
			{
				iterator first(_first + n);
				erase(first, end());
			}
			else if (n > _n)
				insert(end(),n - _n, val);
		}

	// MODIFIERS
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
		typename std::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
		{
			size_type size = last - first;
			if (!size)
				clear_dealloc();
			else
			{
				if (size <= _c)
				{
					_ptr = _first;
					while (first != last)
						_alloc.construct(_ptr++, *first++);
					_last = --_ptr;
					int to_destroy = _n - size;
					for (int i = 0; i < to_destroy; i++)
						_alloc.destroy(++_ptr + i);
					_n = size;
				}
				else
				{
					if (capacity_error(_n))
						return;
					clear_dealloc();
					_first = _alloc.allocate(size + 1);
					_ptr = _first;
					while (first != last)
						_alloc.construct(_ptr++, *first++);
					_last = --_ptr;
					_n = size;
					_c = size;
				}
			}
		}

		void assign(size_type n, const value_type & val)
		{
			if (!n)
				clear_dealloc();
			else
			{
				if (n <= _c)
				{
					_ptr = _first;
					for (size_type i = 0; i < n; i++)
					{
						_alloc.destroy(_ptr);
						_alloc.construct(_ptr++, val);
					}
					_last = --_ptr;
					int to_destroy = _n - n;
					for (int i = 0; i < to_destroy; i++)
						_alloc.destroy(++_ptr + i);
					_n = n;
				}
				else
				{
					if (capacity_error(_n))
						return;
					clear_dealloc();
					_first = _alloc.allocate(n + 1);
					_ptr = _first;
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_ptr++, val);
					_last = --_ptr;
					_n = n;
					_c = n;
				}
			}
		}

		void push_back(const value_type & val)
		{
			if (_n + 1 <= _c)
			{
				if (!_n)
					_alloc.construct(_last, val);
				else
					_alloc.construct(++_last, val);
			}
			else
			{
				size_type n = _n * _capacityFactor;
				iterator old_first = begin();
				iterator old_last = end();
				_ptr = _alloc.allocate(n + 1);
				pointer new_first = _ptr;
				while (old_first != old_last)
				{
					_alloc.construct(_ptr++, *old_first);
					_alloc.destroy(&*old_first++);
				}
				size_type size = _n;
				clear_dealloc();
				_first = new_first;
				_last = --_ptr;
				_n = size;
				_c = n;
				_alloc.construct(++_last, val);
			}
			_n++;
		}

		void pop_back()
		{
			if (_n > 0)
			{
				_alloc.destroy(_last--);
				_n--;
			}
		}

		iterator insert(iterator position, const value_type & val)
		{
			iterator itr;
			if (!_n && position == _first)
			{
				assign(1, val);
				return _first;
			}
			if (_n + 1 > _c)
			{
				iterator it = begin();
				if (capacity_error(_n * _capacityFactor))
					return 0;
				_ptr = _alloc.allocate(_n * _capacityFactor + 1);
				pointer f = _ptr;
				while (it != position)
					_alloc.construct(_ptr++, *it++);
				itr = _ptr;
				_alloc.construct(_ptr++, val);
				while (it != _last + 1)
					_alloc.construct(_ptr++, *it++);
				size_type n = _n;
				clear_dealloc();
				_c = n * _capacityFactor;
				_n = n + 1;
				_last = _ptr - 1;
				_first = f;
			}
			else
			{
				itr = position;
				value_type tmp = *position;
				value_type tmp2;
				_alloc.destroy(&*position);
				_alloc.construct(&*position, val);
				while (position != _last + 1)
				{
					tmp2 = *(++position);
					_alloc.destroy(&*position);
					_alloc.construct(&*position, tmp);
					tmp = tmp2;
				}
				_last++;
				_n++;
			}
			return itr;
		}

		void insert(iterator position, size_type n, const value_type & val)
		{
			if (!_n && position == _first)
				assign(n, val);
			else if (_n + n > _c)
			{
				size_type c;
				_n + n > _c * _capacityFactor ? c = _n + n : c = _c * _capacityFactor;
				if (capacity_error(c))
					return;
				_ptr = _alloc.allocate(c + 1);
				pointer f = _ptr;
				iterator it = begin();
				while (it != position)
					_alloc.construct(_ptr++, *it++);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_ptr++, val);
				while (it != _last + 1)
					_alloc.construct(_ptr++, *it++);
				size_type s = _n;
				clear_dealloc();
				_c = c;
				_n = s + n;
				_last = _ptr - 1;
				_first = f;
			}
			else
			{
				iterator it = begin();
				vector<T> cpy(it, end());
				iterator it_cpy = cpy.begin();
				size_type index = get_index(position);
				size_type dist = _last - position + 1;
				size_type new_index;
				pointer shift;
				for (size_type i = 0; i < dist; i++)
				{
					new_index = index + n + i;
					shift = _first + new_index;
					_alloc.destroy(shift);
					_alloc.construct(shift, *(it_cpy + new_index - n));
				}
				if (dist)
					_last = shift;
				for (size_type i = 0; i < n; i++)
				{
					shift = &_first[get_index(position)];
					_alloc.destroy(shift);
					_alloc.construct(shift, val);
					position++;
				}
				if (!dist)
					_last = shift;
				_n += n;
			}
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
		typename std::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
		{
			size_type n = last - first;
			if (!_n && position == _first)
				assign(first, last);
			else if (_n + n > _c)
			{
				size_type c;
				_n + n > _c * _capacityFactor ? c = _n + n : c = _c * _capacityFactor;
				if (capacity_error(c))
					return;
				_ptr = _alloc.allocate(c + 1);
				pointer f = _ptr;
				iterator it = begin();
				while (it != position)
					_alloc.construct(_ptr++, *it++);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_ptr++, *first++);
				while (it != _last + 1)
					_alloc.construct(_ptr++, *it++);
				size_type s = _n;
				clear_dealloc();
				_c = c;
				_n = s + n;
				_last = _ptr - 1;
				_first = f;
			}
			else
			{
				iterator it = begin();
				vector<T> cpy(it, end());
				iterator it_cpy = cpy.begin();
				size_type index = get_index(position);
				size_type dist = _last - position + 1;
				size_type new_index;
				pointer shift;
				for (size_type i = 0; i < dist; i++)
				{
					new_index = index + n + i;
					shift = _first + new_index;
					_alloc.destroy(shift);
					_alloc.construct(shift, *(it_cpy + new_index - n));
				}
				if (dist)
					_last = shift;
				for (size_type i = 0; i < n; i++)
				{
					shift = &_first[get_index(position)];
					_alloc.destroy(shift);
					_alloc.construct(shift, *first++);
					position++;
				}
				if (!dist)
					_last = shift;
				_n += n;
			}
		}

		iterator erase(iterator position)
		{
			iterator itr = position;
			size_type dist = _last - position;
			_alloc.destroy(&*position);
			_alloc.construct(&*position, *(position++ + 1));
			while (--dist)
			{
				_alloc.destroy(&*position);
				_alloc.construct(&*position, *(position++ + 1));
			}
			_alloc.destroy(_last--);
			_n--;
			return itr;
		}

		iterator erase(iterator first, iterator last)
		{
			iterator itr = first;						
			if (last - first > 0)
			{
				size_type dist = _last - last + 2;
				while (--dist)
				{
					_alloc.destroy(&*first);
					_alloc.construct(&*first++, *last++);
				}
				size_type erased = last - first;
				_last -= erased;
				_n -= erased;
				while (erased)
					_alloc.destroy(_last - erased-- + 1);
			}
			return itr;
		}

		void swap(vector & x)
		{
			size_type n = _n;
			size_type c = _c;
			pointer f = _first;
			pointer l = _last;
			_n = x._n;
			_c = x._c;
			_first = x._first;
			_last = x._last;
			x._n = n;
			x._c = c;
			x._first = f;
			x._last = l;
		}

		void clear()
		{
			if (_n != 0)
			{
				for (size_type i = 0; i < _n; i++)
					_alloc.destroy(_first + i);
				_last = _first;
				_n = 0;
			}
		}

	// ALLOCATOR
		allocator_type get_allocator() const { return _alloc; }

		protected:
		Alloc			_alloc;				// the default allocator
		size_type		_n;					// size: number of elements in container
		size_type		_c;					// capacity: storage space expressed in terms of elements
		size_type		_capacityFactor;	// incremental factor for capacity reallocation
		pointer			_first;				// first element
		pointer			_last;				// real last element (not = end)
		pointer			_ptr;				// random pointer for multi-usage

		size_type get_index(pointer p) const	{ return p - _first; }
		size_type get_index(iterator it)		{ return it - begin(); }
		
		bool	capacity_error(unsigned long c)
		{
			if (c + 1 > max_size())
			{
				throw std::bad_alloc();
				return true;
			}
			return false;
		}

		void clear_dealloc()
		{
			if (_n != 0)
			{
				for (size_type i = 0; i < _n; i++)
					_alloc.destroy(_first + i);
				_alloc.deallocate(_first, _c + 1);
				_last = _first;
				_n = 0;
				_c = 0;
			}
		}
	};

// NON MEMBER FUNCTION
	template <class T, class Alloc>
	void swap(vector<T,Alloc> & x, vector<T,Alloc> & y) { x.swap(y); }

// RELATIONAL OPERATORS
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> & lhs, const vector<T,Alloc> & rhs)
	{
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (!(rhs < lhs));
	}
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
