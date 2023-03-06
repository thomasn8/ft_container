#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

#include <iostream>
#include <memory>
#include "red_black_node.hpp"

# define B 0
# define R 1
# define LEAF 0

# define MARGIN 8

# define RED "\033[0;31m"
# define WHI "\033[0m"

namespace ft
{
	template<class Key, class Comp, class Alloc_p, class Alloc = std::allocator< red_black_node<Key> > >
	class red_black_tree
	{
		public:

		typedef	Key											value_type;
		typedef red_black_node<Key>							node;
		typedef	Alloc										allocator_type;
		typedef Comp										val_comp;
		typedef	typename allocator_type::reference			reference;
		typedef	typename allocator_type::const_reference	const_reference;
		typedef	typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		typedef	unsigned int								size_type;
		typedef	int											difference_type;

	// PRINT
		void print_tree()
		{
			print_tree_recursiv(_root, 0);
			std::cout << std::endl;
		}
	
	// GETTERS
		const node * get_root() const		{ return _root; }
		const node * get_past_start() const	{ return &_past_start_node; }
		const node * get_past_end() const	{ return &_past_end_node; }
		const node * get_left_most(const node * n) const
		{
			if (!n)
				return &_past_end_node;
			while (n->left())
				n = n->left();
			return n;
		}
		const node * get_right_most(const node * n) const
		{
			if (!n)
				return &_past_end_node;
			while (n->right())
				n = n->right();
			return n;
		}
		const node * get_next(const node * n) const
		{
			node * parent;
			if (!n)
				return &_past_end_node;
			if (n->right() && n->right()->key())
				return get_left_most(n->right());
			else if (n->parent() && n == n->parent()->left())
				return n->parent();
			else if (n->parent())
			{
				parent = n->parent();
				while (parent != NULL && n == parent->right()) 
				{
					n = parent;
					parent = parent->parent();
					if (!parent)
						return &_past_end_node;
				}
				return parent;
			}
			else
				return &_past_end_node;
		}
		const node * get_prev(const node * n) const
		{
			node * parent;
			if (!n)
				return &_past_start_node;
			if (n == &_past_start_node)
				return get_right_most(_root);
			if (n->left() && n->left()->key())
				return get_right_most(n->left());
			else if (n->parent() && n == n->parent()->right())
				return n->parent();
			else if (n->parent())
			{
				parent = n->parent();
				while (parent != NULL && n == parent->left()) 
				{
					n = parent;
					parent = parent->parent();
					if (!parent)
						return &_past_start_node;
				}
				return parent;
			}
			else
				return &_past_start_node;
		}

	// VARIABLES

		size_type		_n;
		node *			_root;
		node *			_ptr;
		Alloc			_alloc;
		Alloc_p			_alloc_p;
		Comp			_comp;
		node 			_past_start_node;
		value_type *	_past_start_pair;
		node 			_past_end_node;
		value_type *	_past_end_pair;

	// CONSTR/DESTR
		red_black_tree(val_comp comp, value_type *past_start, value_type *past_end,
			const allocator_type & alloc = allocator_type()) : 
		_alloc(alloc), _comp(comp), _n(0), _root(NULL),
		_past_end_pair(past_end),
		_past_start_node(past_start),
		_past_end_node(past_end) {}
		~red_black_tree() {}

	// SEARCH
		const node * search(const Key & key) const 
		{
			node * root = _root;
			while (root)
			{
				if (_comp.comp(key, *root->key()))
				{
					if (root->left())
						root = root->left();
					else
						return NULL;
				}
				else if (_comp.comp(*root->key(), key))
				{
					if (root->right())
						root = root->right();
					else
						return NULL;
				}
				else
					return root;
			}
			return NULL;
		}
		const node * search_bound(const Key & key, const char type) const
		{
			node * root = _root;
			const node * last_low = &_past_end_node;
			while (root)
			{
				if (_comp.comp(key, *root->key()))
				{
					last_low = root;
					if (root->left())
						root = root->left();
					else
						return last_low;
				}
				else if (_comp.comp(*root->key(), key))
				{
					if (root->right())
						root = root->right();
					else
						return last_low;
				}
				else if (type == 'l')
					return root;
				else if (type == 'u')
					return last_low;
			}
			return last_low;
		}

	// INSERTION
		node * insertion(value_type * pair)
		{
			_ptr = _alloc.allocate(1);
			_alloc.construct(_ptr, pair);
			insertion_recursiv(_root, _ptr);
			insertion_repare_tree(_ptr);
			_root = _ptr;
			while (_root->parent() != NULL)
				_root = _root->parent();
			_n++;
			return _ptr;
		}
		void insertion_recursiv(node * root, node * n) 
		{
			if (root != NULL && _comp.comp(*n->key(), *root->key())) 
			{
				if (root->left() != LEAF) 
				{
					insertion_recursiv(root->left(), n);
					return;
				}
				else
					root->setLeft(n);
			} 
			else if (root != NULL) 
			{
				if (root->right() != LEAF) 
				{
					insertion_recursiv(root->right(), n);
					return;
				}
				else
					root->setRight(n);
			}
			n->setParent(root);
			n->setLeft(LEAF);
			n->setRight(LEAF);
			n->setColor(R);
		}
		void insertion_repare_tree(node * n) 
		{
			if (n->parent() == NULL)
				insertion_case1(n);
			else if (n->parent() && n->parent()->color() == B)
				insertion_case2(n);
			else if (n->uncle() && n->uncle()->color() == R)
				insertion_case3(n);
			else
				insertion_case4(n);
		}
		void insertion_case1(node * n)
		{
			if (n->parent() == NULL)
				n->setColor(B);
		}
		void insertion_case2(node * n) { (void) n; return; }
		void insertion_case3(node * n)
		{
			n->parent()->setColor(B);
			n->uncle()->setColor(B);
			node * g = n->grandparent();
			g->setColor(R);
			insertion_repare_tree(g);
		}
		void insertion_case4(node * n) 
		{
			node * p = n->parent();
			node * g = n->grandparent();
			if (g->left() && n == g->left()->right()) 
			{
				rotation_left(p);
				n = n->left();
			} 
			else if (g->right() && n == g->right()->left()) 
			{
				rotation_right(p);
				n = n->right();
			}
			insertion_case5(n);
		}
		void insertion_case5(node * n)
		{
			node * p = n->parent();
			node * g = n->grandparent();
			if (n == p->left())
				rotation_right(g);
			else
				rotation_left(g);
			p->setColor(B);
			g->setColor(R);
		}
	
	// DELETION
		void deletion(node * n)
		{
			if (!n || !_root)
				return ;
			node * parent = n->parent();
			if (n == _root)
				parent = _root;
			remove_node(parent, n, *n->key());
        }
		int deletion(Key k) 
		{
            node * n = _root;
            node * parent = n;
            if (!n)
				return 0;
            while(n)
			{
                if (_comp.comp(k, *n->key()))
				{
					parent = n;
					n = n->left();
				}
                else if (_comp.comp(*n->key(), k))
				{
					parent = n;
					n = n->right();
				}
				else
				{
					remove_node(parent, n, k);
					return 1;
				}
            }
			return 0;
        }
		void remove_node(node * parent, node * n, Key k) 
		{
            if (n == NULL)
				return ;
            if (!_comp.comp(*n->key(), k) && !_comp.comp(k, *n->key())) 
			{
                if (n->left() == NULL && n->right() == NULL)
				{
            		if (!_comp.comp(*parent->key(), *n->key()) && !_comp.comp(*n->key(), *parent->key())) 
					{
						free_node(_root);
						_root = NULL;
					}
                    else if (parent->right() == n) 
					{
                        deletion_repare_tree(n);
						free_node(n);
                        parent->setRight(NULL);
                    } 
                    else 
					{
                        deletion_repare_tree(n);
						free_node(n);
                        parent->setLeft(NULL);
                    }
                }
                else if (n->left() != NULL && n->right() == NULL)
				{
					n->swapKey(n->left());
                    remove_node(n, n->left(), k);
                }
                else if (n->left() == NULL && n->right() != NULL)
				{
					n->swapKey(n->right());
                    remove_node(n, n->right(), k);
                }
                else
				{
                    bool flag = false;
                    node * tmp = n->left();
                    while (tmp->right())
					{
						flag = true;
						parent = tmp;
						tmp = tmp->right();
					}
                    if (!flag)
						parent = n;
					n->swapKey(tmp);
                    remove_node(parent, tmp, *tmp->key());
                }
            }
        }
        void deletion_repare_tree(node * n) 
		{
            while ((_comp.comp(*n->key(),*_root->key()) || _comp.comp(*_root->key(), *n->key())) 
				&& n->color() == B)
			{
                node * sibling = _root;
                if (n->parent()->left() == n) 
				{
                    if (n->parent()->right())
						sibling = n->parent()->right();
                    if (sibling)
					{
                        if (sibling->color() == R)
						{
                            sibling->setColor(B);
                            n->parent()->setColor(R);
                            rotation_left(n->parent());
                            sibling = n->parent()->right();
                        }
						if ((sibling->left() == NULL  || sibling->left()->color() == B)
						&&  (sibling->right() == NULL || sibling->right()->color() == B))
						{
                            sibling->setColor(R);
                            n = n->parent();
                        }
                        else if (sibling->right() && sibling->right()->color() == B)
						{
                            sibling->left()->setColor(B);
                            sibling->setColor(R);
                            rotation_right(sibling);
                            sibling = n->parent()->right();
                        }
						else
						{
                            sibling->setColor(n->parent()->color());
                            n->parent()->setColor(B);
                            if (sibling->right())
								sibling->right()->setColor(B);
                            rotation_left(n->parent());
                            n = _root;
                        }
                    } 
                } 
				else
				{
                    if (n->parent()->right() == n)
					{
                        if (n->parent()->left())
							sibling = n->parent()->left();
                        if (sibling)
						{
                            if (sibling->color() == R)
							{
                                sibling->setColor(B);
                                n->parent()->setColor(R);
                                rotation_right(n->parent());
                                sibling = n->parent()->left();
                            }
							if ((sibling->left() == NULL  || sibling->left()->color() == B)
							&&  (sibling->right() == NULL || sibling->right()->color() == B))
							{
								sibling->setColor(R);
								n = n->parent();
							}
                            else if (sibling->left() && sibling->left()->color() == B)
							{
                                sibling->right()->setColor(B);
                                sibling->setColor(R);
                                rotation_right(sibling);
                                sibling = n->parent()->left();
                            }
							else
							{
                                sibling->setColor(n->parent()->color());
                                n->parent()->setColor(B);
                                if (sibling->left())
									sibling->left()->setColor(B);
                                rotation_left(n->parent());
                                n = _root;
                            }
                        } 
                    }
                }
            }
            n->setColor(B);
        }
		void free_node(node * n)
		{
			_alloc_p.destroy(n->key());
			_alloc_p.deallocate(n->key(), 1);
			_alloc.destroy(n);
			_alloc.deallocate(n, 1);
			_n--;
		}

	// ROTATIONS
		void rotation_left(node * x) 
		{
			node * y = x->right();
			x->setRight(y->left());
			if (y->left() != LEAF)
				y->left()->setParent(x);
			y->setParent(x->parent());
			if (x->parent() == NULL)
				_root = y;
			else
			{
				if (x->parent()->left() == x)
					x->parent()->setLeft(y);
				else
					x->parent()->setRight(y);
			}
			y->setLeft(x);
			x->setParent(y);
		}
		void rotation_right(node * x) 
		{
			node * y = x->left();
			x->setLeft(y->right());
			if (y->right() != LEAF)
				y->right()->setParent(x);
			y->setParent(x->parent());

			if (x->parent() == NULL)
				_root = y;
			else
			{
				if (x->parent()->right() == x)
					x->parent()->setRight(y);
				else
					x->parent()->setLeft(y);
			}
			y->setRight(x);
			x->setParent(y);
		}

	// PRINT-FREE
		void print_tree_recursiv(node * root, int space)
		{
			if (root == NULL)
				return;
			space += MARGIN;
			print_tree_recursiv(root->right(), space);
			std::cout<<std::endl;
			for (int i = MARGIN; i < space; i++)
				std::cout<<" ";
			if (root->color() == 1)
			std::cout << RED;
			std::cout << root->key() << WHI;
			if (root->parent())
				std::cout << " ("<< *root->parent()->key() << ")";
			std::cout << std::endl;
			print_tree_recursiv(root->left(), space);
		}

		void free_tree()
		{
			free_tree_recursiv(_root);
			_root = NULL;
		}
		void free_tree_recursiv(node * root)
		{
			if (root == NULL)
				return;
			free_tree_recursiv(root->left());
			_alloc_p.destroy(root->key());
			_alloc_p.deallocate(root->key(), 1);
			free_tree_recursiv(root->right());
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
			_n--;
		}
	};
}

#endif
