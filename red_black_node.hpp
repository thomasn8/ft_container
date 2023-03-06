#ifndef RED_BLACK_NODE_HPP
# define RED_BLACK_NODE_HPP

#include "pair.hpp"
#define B 0
#define R 1
#define LEAF 0

namespace ft
{	
	template<class Key, class T>
	class red_black_node
	{
		public:
		typedef	red_black_node				node;
		typedef	ft::pair<const Key,T>		value_type;
		typedef	value_type *				pointer;
		typedef	value_type &				reference;

		red_black_node(pointer pair) :
		_key_val(pair), _color(LEAF), _left(NULL), _right(NULL), _parent(NULL) {}

		void setLeft(node * n)			{ _left = n; }
		void setRight(node * n)			{ _right = n; }
		void setParent(node * n)		{ _parent = n; }
		void setColor(int c)			{ _color = c; }
		void setKeyVal(pointer pr)		{ _key_val = pr; }
		void swapKeyVal(node * other)
		{
			pointer tmp = other->key_val();
			other->setKeyVal(_key_val);
			setKeyVal(tmp);
		}

		int color() const			{ return _color; }
		pointer key_val() const		{ return _key_val; }
		node * left() const			{ return _left; }
		node * right() const		{ return _right; }
		node * parent() const		{ return _parent; }
		node * grandparent() const
		{
			node * p = parent();
			if (p == NULL)
				return NULL;
			return p->parent();
		}
		node * brother() const
		{
			node * p = parent();
			if (p == NULL)
				return NULL;
			if (this == p->left())
				return p->right();
			else
				return p->left();
		}
		node * uncle() const
		{
			node * p = parent();
			node * g = grandparent();
			if (g == NULL)
				return NULL;
			return p->brother();
		}

		private :
		node *			_left; 				// Pointeur vers fils left
		node *			_right; 			// Pointeur vers fils right 
		node *			_parent; 			// Pointeur vers père
		int				_color; 			// RED ou BLACK
		pointer			_key_val;			// pointeur sur la key_value pair du noeud
	};
}

#endif
