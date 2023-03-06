#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include <stdexcept>
#include <functional>
#include "red_black_tree.hpp"
#include "iterators_map.hpp"
#include "pair.hpp"
#include "utils.hpp"

namespace ft
{	
	template < class Key, class T, 
	class Compare = std::less<Key>, 
	class Alloc = std::allocator< ft::pair< const Key,T> > >
	class map
	{
		class value_compare;
		
		public:
		
	// MEMBER TYPES
		typedef	Key												key_type;
		typedef	T												mapped_type;
		typedef	ft::pair<const key_type, mapped_type>			value_type;
		typedef	Compare											key_compare;
		typedef map::value_compare								val_comp;
		typedef	Alloc											allocator_type;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef	typename allocator_type::pointer				pointer;
		typedef	typename allocator_type::const_pointer			const_pointer;
		typedef red_black_tree<Key,T,val_comp,Alloc>			rbt;
		typedef red_black_node<Key,T>							node;
		typedef	int												difference_type;
		typedef	unsigned int									size_type;
		typedef	ft::bidirectional_iterator<const Key,T,const node *,rbt *>	iterator;
		typedef	ft::bidirectional_iterator<const Key,T,const node *,rbt *>	const_iterator;
		typedef	ft::map_reverse_iterator<iterator>							reverse_iterator;
		typedef	ft::map_reverse_iterator<const_iterator>					const_reverse_iterator;

	// CONSTRUCTORS / DESTRUCTOR
		explicit map(const key_compare & comp = key_compare(), 
		const allocator_type & alloc = allocator_type()) :
		_alloc(alloc), _comp(comp), _tree(_comp, &_past_start_pair, &_past_end_pair), _rbt(&_tree) {}
		
		template <class InputIterator>
		map(InputIterator first, InputIterator last, 
		const key_compare & comp = key_compare(),
		const allocator_type & alloc = allocator_type()) :
		_alloc(alloc), _comp(comp), _tree(_comp, &_past_start_pair, &_past_end_pair), _rbt(&_tree)
		{
			size_type n = _distance<InputIterator>(first, last);
			if (n > 0)
			{
				while (first != last)
				{
					_ptr = _alloc.allocate(1);
					_alloc.construct(_ptr, *first++);
					_rbt->insertion(_ptr);
				}
			}
		}

		map(const map & x) :
		_alloc(x.get_allocator()), _comp(x.key_comp()),
		_tree(x.key_comp(), &_past_start_pair, &_past_end_pair), _rbt(&_tree)
		{
			const_iterator it = x.begin();
			const_iterator ite = x.end();
			while (it != ite)
			{
				_ptr = _alloc.allocate(1);
				_alloc.construct(_ptr, *it++);
				_rbt->insertion(_ptr);
			}
		}

		map & operator=(const map & x)
		{
			if (size())
				_rbt->free_tree();
			const_iterator it = x.begin();
			const_iterator ite = x.end();
			while (it != ite)
			{
				_ptr = _alloc.allocate(1);
				_alloc.construct(_ptr, *it++);
				_rbt->insertion(_ptr);
			}
			return *this;
		}

		~map() { clear(); }

		void print_tree() const { _rbt->print_tree(); }

	// ITERATORS
		iterator begin() 
		{
			return iterator(_rbt->get_left_most(_rbt->_root)->key_val(),
				_rbt->get_left_most(_rbt->_root),
				_rbt);
		}
		iterator end()
		{
			return iterator(_rbt->_past_end_node.key_val(),
				&_rbt->_past_end_node,
				_rbt);
		}
		const_iterator begin() const
		{
			return const_iterator(_rbt->get_left_most(_rbt->_root)->key_val(),
				_rbt->get_left_most(_rbt->_root),
				_rbt);
		}
		const_iterator end() const
		{
			return const_iterator(_rbt->_past_end_node.key_val(),
				&_rbt->_past_end_node,
				_rbt);
		}
		const_iterator cbegin() const
		{
			return const_iterator(_rbt->get_left_most(_rbt->_root)->key_val(),
				_rbt->get_left_most(_rbt->_root),
				_rbt);
		}
		const_iterator cend() const 
		{
			return const_iterator(_rbt->_past_end_node.key_val(),
				&_rbt->_past_end_node,
				_rbt);
		}
		reverse_iterator rbegin() 				
		{			
			return reverse_iterator(iterator(
				_rbt->get_right_most(_rbt->_root)->key_val(),
				_rbt->get_right_most(_rbt->_root),
				_rbt));
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(const_iterator(
				_rbt->get_right_most(_rbt->_root)->key_val(),
				_rbt->get_right_most(_rbt->_root),
				_rbt));
		}
		const_reverse_iterator crbegin() const
		{
			return const_reverse_iterator(const_iterator(
				_rbt->get_right_most(_rbt->_root)->key_val(),
				_rbt->get_right_most(_rbt->_root),
				_rbt));
		}
		reverse_iterator rend() 				
		{
			return reverse_iterator(iterator(
				_rbt->_past_start_node.key_val(),
				&_rbt->_past_start_node,
				_rbt));
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(const_iterator(
				_rbt->_past_start_node.key_val(),
				&_rbt->_past_start_node,
				_rbt));
		}
		const_reverse_iterator crend() const
		{
			return const_reverse_iterator(const_iterator(
				_rbt->_past_start_node.key_val(),
				&_rbt->_past_start_node,
				_rbt));
		}

	// CAPACITY
		size_type size() const			{ return _rbt->_n; }
		bool empty() const 				{ return bool(!_rbt->_n); }
		unsigned long max_size() const	{ return _alloc.max_size(); }

	// ELEMENT ACCESS
		mapped_type & operator[](const key_type & k)
		{
			value_type new_pr = ft::make_pair(k, mapped_type());
			pair<iterator,bool> checked = insert(new_pr);
			return (*checked.first).second;
		}

		mapped_type & at(const key_type & k)
		{
			const node * pos = _rbt->search(k);
			if (pos)
				return pos->key_val()->second;
			throw std::out_of_range("Out of range error");
			return _rbt->_past_start_pair->second;
		}
		const mapped_type & at(const key_type & k) const
		{
			const node * pos = _rbt->search(k);
			if (pos)
				return pos->key_val()->second;
			throw std::out_of_range("Out of range error");
			return _rbt->_past_start_pair->second;
		}

	// MODIFIERS
		void clear() { _rbt->free_tree();}

		void swap(map & x) 
		{ 
			rbt * tmp = _rbt;
			_rbt = x._rbt;
			x._rbt = tmp;
		}

		pair<iterator,bool> insert(const value_type & val)
		{
			const node * pos = _rbt->search(val.first);
			if (pos)
			{
				iterator it_pos(pos->key_val(), pos, _rbt);
				return pair<iterator,bool>(it_pos, false);
			}
			_ptr = _alloc.allocate(1);
			_alloc.construct(_ptr, val);
			pos = _rbt->insertion(_ptr);
			iterator it_pos(pos->key_val(), pos, _rbt);
			return pair<iterator,bool>(it_pos, true);
		}
		iterator insert(iterator position, const value_type & val)
		{
			(void) position;
			const node * pos = _rbt->search(val.first);
			if (pos)
				return iterator(pos->key_val(), pos, _rbt);
			_ptr = _alloc.allocate(1);
			_alloc.construct(_ptr, val);
			pos = _rbt->insertion(_ptr);
			return iterator(pos->key_val(), pos, _rbt);
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				if (!_rbt->search((*first).first))
				{
					_ptr = _alloc.allocate(1);
					_alloc.construct(_ptr, *first);
					_rbt->insertion(_ptr);
				}
				first++;
			}
		}

		void erase(iterator position)
		{
			node * n = const_cast<node *>(_rbt->search(position->first));
			if (n && position.getPair() == n->key_val())
				_rbt->deletion(position->first);
		}
		size_type erase(const key_type & k)
		{
			return _rbt->deletion(k);
		}
		void erase(iterator first, iterator last)
		{
			iterator next;
			while (first != last)
			{
				next = ++first;
				--first;
				erase(first);
				first = next;
			}
		}

	// OBSERVERS
		key_compare key_comp() const	{ return _comp.comp; }
		val_comp value_comp() const		{ return _comp; }

	// OPERATIONS
		iterator find(const key_type & k)
		{
			const node * pos = _rbt->search(k);
			if (pos)
				return iterator(pos->key_val(), pos, _rbt);
			return end();
		}
		const_iterator find(const key_type & k) const
		{
			const node * pos = _rbt->search(k);
			if (pos)
				return const_iterator(pos->key_val(), pos, _rbt);
			return end();
		}
		size_type count(const key_type & k) const
		{
			if (_rbt->search(k))
				return 1;
			return 0;
		}
		pair<iterator,iterator> equal_range(const key_type & k)
		{
			const node * pos = _rbt->search(k);
			if (!pos)
				return ft::make_pair<iterator,iterator>(upper_bound(k), upper_bound(k));
			iterator up(_rbt->get_next(pos)->key_val(), &_rbt->_past_end_node, _rbt);
			return ft::make_pair<iterator,iterator>(lower_bound(k), up);
		}
		pair<const_iterator,const_iterator> equal_range(const key_type & k) const
		{
			const node * pos = _rbt->search(k);
			if (!pos)
				return ft::make_pair<const_iterator,const_iterator>(upper_bound(k), upper_bound(k));
			const_iterator up(_rbt->get_next(pos).key_val(), &_rbt->_past_end_node, _rbt);
			return ft::make_pair<const_iterator,const_iterator>(lower_bound(k), up);
		}
		iterator lower_bound(const key_type & k)
		{
			const node * low = _rbt->search_bound(k, 'l');
			return iterator(low->key_val(), low, _rbt);
		}
		const_iterator lower_bound(const key_type & k) const
		{
			const node * low = _rbt->search_bound(k, 'l');
			return const_iterator(low->key_val(), low, _rbt);
		}
		iterator upper_bound(const key_type & k)
		{
			const node * up = _rbt->search_bound(k, 'u');
			return iterator(up->key_val(), up, _rbt);
		}
		const_iterator upper_bound(const key_type & k) const
		{
			const node * up = _rbt->search_bound(k, 'u');
			return iterator(up->key_val(), up, _rbt);
		}

	// ALLOCATOR
		allocator_type get_allocator() const { return _alloc; }

		private:

		allocator_type			_alloc;
		val_comp				_comp;
		rbt						_tree;
		rbt *					_rbt;
		pointer					_ptr;
		value_type				_past_start_pair;
		value_type				_past_end_pair;

		template <class InputIterator>
		size_type _distance(InputIterator first, InputIterator last) const
		{
			size_type n = 0;
			while (first != last)
			{
				first++;
				n++;
			}
			return n;
		}
	};

	// Class qui génère un objet pour stocker dans 'Compare comp' 
	// la fonction de comparaison binaire de deux pairs
	template <class Key, class T, class Compare, class Alloc>
	class map<Key,T,Compare,Alloc>::value_compare
	{
		friend class map;
		
		public:
		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;
		Compare comp;
		bool operator()(const value_type & x, const value_type & y) const
		{
			return comp(x.first, y.first);
		}

		protected:
		value_compare (Compare c) : comp(c) {}
	};
}

#endif
