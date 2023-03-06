#ifndef ITERATORS_SET_HPP
# define ITERATORS_SET_HPP

#include "../iterators.hpp"

namespace ft
{
	class bidirectional_iterator_tag {};

	template <typename Key, typename Node_ptr, typename Tree_ptr>
	class bidirectional_iterator
	{
		public:
	// MEMBER TYPES
		typedef Key							value_type;
		typedef int							difference_type;
		typedef value_type *				pointer;
		typedef value_type &				reference;
		typedef bidirectional_iterator	 	iterator_category;
		typedef	iterator_category			it;
		typedef int 						SFINAE_condition;
	// CONSTRUCTEURS/DESTRUCTEUR
		bidirectional_iterator() : _p(0) {}
		bidirectional_iterator(pointer p, Node_ptr node, Tree_ptr tree) : _p(p), _node(node), _tree(tree) {}
		bidirectional_iterator(reference src) : _p(src.getPair()), _node(src.getNode()), _tree(src.getTree()) {}
		virtual ~bidirectional_iterator() {}
	// SURCHARGES
		it & operator=(it const & src)
		{
			_p = src.getPair();
			_node = src.getNode();
			_tree = src.getTree();
			return *this;
		}
		bool operator==(const it & rhs) const { return _p == rhs._p; }
		bool operator!=(const it & rhs) const { return _p != rhs._p; }
		pointer operator->()		{ return _p;  }
		reference operator*()		{ return *_p; }
		reference operator*() const	{ return *_p; }

		it & operator++()
		{
			if (_node == _tree->get_past_start())
			{
				_node = _tree->get_left_most(_tree->get_root());
				_p = _node->key();
			}
			else
			{
				_node = _tree->get_next(_node);
				_p = _node->key();
			}
			return *this;
		}
		it operator++(int) 
		{ 
			it tmp(*this);
			if (_node == _tree->get_past_start())
			{
				_node = _tree->get_left_most(_tree->get_root());
				_p = _node->key();
			}
			else
			{
				_node = _tree->get_next(_node);
				_p = _node->key();
			}
			return tmp;
		}
		it & operator--() 
		{
			if (_node == _tree->get_past_end())
			{
				_node = _tree->get_right_most(_tree->get_root());
				_p = _node->key();
			}
			else
			{
				_node = _tree->get_prev(_node);
				_p = _node->key();
			}
			return *this;
		}
		it operator--(int) 
		{
			it tmp(*this);
			if (_node == _tree->get_past_end())
			{
				_node = _tree->get_right_most(_tree->get_root());
				_p = _node->key();
			}
			else
			{
				_node = _tree->get_prev(_node);
				_p = _node->key();
			}
			return tmp;
		}

		pointer getPair() const		{ return _p; }
		Node_ptr getNode() const	{ return _node; }

		protected:
		pointer 	_p;
		Node_ptr	_node;
		Tree_ptr	_tree;
		Tree_ptr getTree() const	{ return _tree; }
	};

	template <typename Iterator>
	class set_reverse_iterator : public ft::iterator_traits<Iterator>
	{
		public:
	// MEMBER TYPES
		typedef	Iterator													iterator_type;
		typedef	typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef	typename ft::iterator_traits<Iterator>::difference_type 	difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef	typename ft::iterator_traits<Iterator>::reference			reference;
		typedef set_reverse_iterator<Iterator>								iterator_category;
		typedef	iterator_category											rev_it;

	// CONSTRUCTEURS/DESTRUCTEUR
		set_reverse_iterator(void) { _iterator = iterator_type(); }
		explicit set_reverse_iterator(iterator_type it) : _iterator(it) {}
		set_reverse_iterator(const set_reverse_iterator<iterator_type> & rev_it) { _iterator = rev_it._iterator; }
		virtual ~set_reverse_iterator() {}
	// MEMBER FUNCTION
		iterator_type base() const { return _iterator; }
	// SURCHARGES
		rev_it & operator=(const iterator_type & src) { _iterator = src; return *this; }
		rev_it & operator=(const set_reverse_iterator<Iterator> & src) { _iterator = src._iterator; return *this; }
		value_type operator*() { return *_iterator; }
		value_type operator*() const { return *_iterator; }
		iterator_type operator->() { return _iterator ; }
		rev_it & operator++() { --_iterator; return *this; }
		rev_it operator++(int)
		{
			iterator_type tmp = _iterator;
			_iterator--;
			return set_reverse_iterator<iterator_type>(tmp);
		}
		rev_it & operator--() { ++_iterator; return *this; }
		rev_it operator--(int) 
		{
			iterator_type tmp = _iterator;
			_iterator++;
			return set_reverse_iterator<iterator_type>(tmp);
		}
	// NON-MEMBER FUNCTION OVERLOADS
		friend bool operator==(const set_reverse_iterator<Iterator>& lhs,
			const set_reverse_iterator<Iterator>& rhs) { return lhs._iterator == rhs._iterator; }
		friend bool operator!=(const set_reverse_iterator<Iterator>& lhs,
			const set_reverse_iterator<Iterator>& rhs) { return lhs._iterator != rhs._iterator; }

		private :
		iterator_type	_iterator;
	};
}

#endif
