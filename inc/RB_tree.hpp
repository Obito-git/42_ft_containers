//
// Created by Anton on 22/06/2022.
//

#ifndef CONTAINERS_RB_TREE_HPP
#define CONTAINERS_RB_TREE_HPP
/* Useful links :
 * https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
 * https://medium.com/swlh/red-black-tree-rotations-and-color-flips-10e87f72b142
 * https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
 * https://www.programiz.com/dsa/deletion-from-a-red-black-tree
 * */
#include <ostream>
#include "utils/pair.hpp"
#include "iterator/RBT_iterator.hpp"
#include "iterator/reverse_iterator.hpp"

namespace ft {
	/*	Universal getter for
	*   ft::pair and other objects type; It will return key/val which depends on obj type */
	template <class Key, class Mapped> struct KeyValGetter {
		static Key get_key(const ft::pair<const Key, Mapped> &val) { return val.first; }
		static Key get_key(const Key &val) { return val; }
		static Mapped& get_value(ft::pair<const Key, Mapped> &val) { return val.second; }
		static Mapped& get_value(Key &val) { return val; }
	};


	/********************************************************************************************************/
	/************************************** NODE STRUCTURE **************************************************/
	/********************************************************************************************************/
	template <class ValueType, class Key, class Mapped>
	struct RB_node {
	public:
		/*	Node typedefs */
		typedef ValueType	value_type;
		typedef 			RB_node* node_pointer;

		/*	Variables */
		value_type  	node_data;
		node_pointer	left;
		node_pointer	right;
		node_pointer	parent;
		bool is_red;

		/* constructor for creating a null leaf node */
		RB_node(node_pointer par) : node_data(value_type()), left(null_pointer),
		                            right(null_pointer), parent(par), is_red(false) {
			}
		/* constructor for creation a new node */

		RB_node(const value_type &nodeData) : node_data(nodeData), left(null_pointer),
											  right(null_pointer), parent(null_pointer),
											  is_red(true) {
		}

		/* copy constructor */
		RB_node(const RB_node& other) : node_data(other.node_data), left(other.left),
										right(other.right), parent(other.parent), is_red(other.is_red) {
		}

		/*	Getters. Returns copy of key(it's const for pair) and value reference */
		Key key() { return KeyValGetter<const Key, Mapped>::get_key(node_data); }
		Mapped& value() { return KeyValGetter<const Key, Mapped>::get_value(node_data); }
	};


	/*******************************************************************************************************/
	/************************************** RED BLACK TREE CLASS *******************************************/
	/*******************************************************************************************************/

	template < class Key,							//map::key_type
			class Mapped,                         	// if ValueType is pair Mapped= map::mapped_value, otherwise Key
			class ValueType,                       	// content type, for map ft::pair, for set other
			class Compare = std::less<Key>,        	// map::key_compare
			class Alloc = std::allocator<ValueType>	// map::allocator_type
	> class RB_tree {
	public:
		/***************************************** TYPEDEFS *******************************************/
		class ValueCompare;
		/* Node	*/
		typedef 	RB_node<ValueType, Key, Mapped>			node;
		typedef 	node*										node_pointer;
		/* Regular */
		typedef		ValueType										value_type;
		typedef		ValueType*										value_pointer;
		typedef		typename Alloc::template rebind<node>::other	node_allocator_type;
		typedef		Compare											key_compare;
		typedef 	ValueCompare									value_compare;
		typedef		size_t											size_type;
		typedef		Key												key_type;
		typedef     KeyValGetter<const Key, Mapped>					type_helper;
		/*	Iterator */
		typedef 			RBT_iterator<node, value_type>			iterator;
		typedef 			RBT_iterator<node, const value_type>	const_iterator;
		typedef				ft::reverse_iterator<iterator>			reverse_iterator;
		typedef 			ft::reverse_iterator<const_iterator>	const_reverse_iterator;


		/*	Tree initialization constructor */
		explicit RB_tree (const key_compare& comp = key_compare(),
						  const node_allocator_type& alloc = node_allocator_type()) :
						  	_root(null_pointer), _node_alloc(alloc), _k_comp(comp), _size(0), is_copy(false) {
			_end_node = _node_alloc.allocate(1);
			_node_alloc.construct(_end_node, value_type());
			_root = _node_alloc.allocate(1);
			_node_alloc.construct(_root, _end_node);
			_root->parent = _end_node;
			_end_node->right = _root;
		}

		/*	No deepcopy copy constructor */
		RB_tree(const RB_tree& other): _root(other._root), _end_node(other._end_node), _node_alloc(other._node_alloc),
										_k_comp(other._k_comp), _size(other._size), is_copy(true) {
		}

		/* No destruction and deallocation assignment operator */
		RB_tree &operator=(const RB_tree& other) {
			if (&other != this) {
				_root = other._root;
				_end_node = other._end_node;
				_node_alloc = other._node_alloc;
				_k_comp = other._k_comp;
				_size = other._size;
			}
			return *this;
		}

		/*	Destructor */
		virtual ~RB_tree() {
			/*
			if (!is_copy) {
				clear();
				_node_alloc.destroy(_root);
				_node_alloc.deallocate(_root, 1);
				_node_alloc.destroy(_end_node);
				_node_alloc.deallocate(_end_node, 1);
			}
			 */
		}
		/************************************** VALUE COMPARE *************************************************/

		class ValueCompare
		{
			friend class RB_tree;
		protected:
			Compare comp;
			ValueCompare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(KeyValGetter<Key, Mapped>::get_key(x), KeyValGetter<Key, Mapped>::get_key(y));
			}
		};

		/************************************** VARIABLES *****************************************************/
	private:
		node_pointer _root;
		node_pointer _end_node;
		node_allocator_type _node_alloc;
		key_compare _k_comp;
		size_type _size;
		bool			is_copy;

		/************************* NODES ALLOCATION AND CREATION ***********************************************/

		/*	Destroying old node data and replacing it by new value */
	private:
		node_pointer replace_node_value(const value_type& value, node_pointer old) {
			node tmp(*old);
			_node_alloc.destroy(old);
			_node_alloc.construct(old, value);
			old->parent = tmp.parent;
			old->left= tmp.left;
			old->right = tmp.right;
			old->is_red = tmp.is_red;
			return old;
		}

		node_pointer add_new_node(const value_type& value, node_pointer par) {
			node_pointer new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, value);
			new_node->parent = par;
			return new_node;
		}

		/************************** OPERATION FOR BALANCE THE TREE **********************************************/
		/* all operations are based from this img:
			 * https://miro.medium.com/max/1196/1*v3n2S2CwZ9HcbTHGHLi-2w.png
			 * */

		/*		|BLACK|									|RED|		*
		*	|RED|		|RED|		------>		|BLACK|		|BLACK|	*/
	private:
		void color_flip(node_pointer n, node_pointer gp, node_pointer aunt) {
			n->parent->is_red = false;
			if (_root != gp)
				gp->is_red = true;
			aunt->is_red = false;
		}

		/*				|A|			RIGHT ROTATION			|B|				*
		 * 			|B|				------------>		|C|		|A|			*
		 * 		|C|															*/
	private:
		void right_rotation(node_pointer n, node_pointer gp, node_pointer aunt) {
			node_pointer parent_tmp = gp->parent;
			if (aunt && aunt->is_red) { //color flip
				color_flip(n, gp, aunt);
			} else {
				//relink node bcs of grandparent changing
				if (gp == _root)
					_root = n->parent;
				else {
					if (parent_tmp->left == gp)
						parent_tmp->left = n->parent;
					else
						parent_tmp->right = n->parent;
				}
				node_pointer tmp = n->parent->right; //saving pa right child
				if (tmp)
					tmp->parent = gp; //swap
				n->parent->right = gp;
				n->parent->right->parent = n->parent;
				n->parent->right->left = tmp;
				n->parent->right->is_red = true;
				n->parent->is_red = false;
				n->parent->parent = parent_tmp;
			}
		}

		/*		|A|					LEFT ROTATION			|B|				*
		* 			|B|				------------>		|A|		|C|			*
 		* 				|C|													*/
	private:
		void left_rotation(node_pointer n, node_pointer gp, node_pointer aunt) {
			node_pointer parent_tmp = gp->parent;
			if (aunt && aunt->is_red) { //color flip
				color_flip(n, gp, aunt);
			} else {
				if (gp == _root)
					_root = n->parent;
				else {
					if (parent_tmp->left == gp)
						parent_tmp->left = n->parent;
					else
						parent_tmp->right = n->parent;
				}
				node_pointer tmp = n->parent->left; //saving pa right child
				if (tmp)
					tmp->parent = gp;
				n->parent->left = gp;
				n->parent->left->parent = n->parent;
				n->parent->left->right = tmp;
				n->parent->left->is_red = true;
				n->parent->is_red = false;
				n->parent->parent = parent_tmp;
			}
		}

		/*			|A|			LEFT RIGHT ROTATION			|C|				*
 		* 		|B|					------------>		|B|		|A|			*
		* 			|C|														*/
	private:
		void left_right_rotation(node_pointer n, node_pointer gp, node_pointer aunt) {
			if (aunt && aunt->is_red) {
				color_flip(n, gp, aunt);
			} else {
				node_pointer tmp_left = n->left;
				if (tmp_left)
					tmp_left->parent = n->parent;
				n->left = n->parent;
				n->parent = gp;
				if (n->parent->left)
					n->parent->left->parent = n;
				n->parent->left = n;
				if (n->left)
					n->left->right = tmp_left;
				right_rotation(n->left, gp, aunt);
			}
		}

		/*			|A|			RIGHT LEFT ROTATION			|C|				*
 		* 				|B|			------------>		|A|		|B|			*
		* 			|C|														*/
	private:
		void right_left_rotation(node_pointer n, node_pointer gp, node_pointer aunt) {
			if (aunt && aunt->is_red) {
				color_flip(n, gp, aunt);
			} else {
				node_pointer tmp_right = n->right;
				if (tmp_right)
					tmp_right->parent = n->parent;
				n->right = n->parent;
				n->parent = gp;
				if (n->parent->right)
					n->parent->right->parent = n;
				n->parent->right = n;
				if (n->right)
					n->right->left = tmp_right;
				left_rotation(n->right, gp, aunt);
			}
		}

		/*	Respecting Reb black tree rules:
		* 1. Every node is either red or black.
		* 2. The root and leaves are black.
		* 3. If a node is red, then its parent is black. */
	private:
		void balance(node_pointer n) {
			while (n->parent && n->parent != _end_node) {
				check_basic_conditions(n);
				n = n->parent;
			}
		}

	private:
		void check_basic_conditions(node_pointer n) {
			node_pointer gp = get_gparent_node(n);
			node_pointer par = n->parent;
			if (gp && n->is_red && par->is_red) {
				if (par->left == n && gp->left == par)
					right_rotation(n, gp, get_aunt_node(n));
				else if (par->right == n && gp->left == par && (!par->left || !par->left->is_red))
					left_right_rotation(n, gp, get_aunt_node(n));
				else if (par->right == n && gp->right == par)
					left_rotation(n, gp, get_aunt_node(n));
				else if (par->left == n && gp->right == par && (!par->right || !par->right->is_red))
					right_left_rotation(n, gp, get_aunt_node(n));
			}
		}

	private:
		/* Good luck for deletion :DDD
		https://youtu.be/w5cvkTXY0vQ
		* */
		void balance_after_deletion(node_pointer replaced) {
			/*
			if (replaced && replaced != _root && !replaced->is_red) {
				node_pointer repBrother = get_brother_node(replaced);
				if (repBrother && !repBrother->is_nullLeaf() && !repBrother->is_red) {
					if (!repBrother->left->is_red && !repBrother->right->is_red) {
						replaced->parent->is_red = false;
						repBrother->is_red = true;
					} else if (repBrother->right->is_red) {
						repBrother->is_red = replaced->parent->is_red;
						replaced->parent->is_red = false;
						repBrother->right->is_red = false;
						if (replaced == replaced->parent->left) {
							after_deletion_left_turn(replaced);
						} else {
							after_deletion_right_turn(replaced);
						}
					} else if (repBrother->left->is_red) {
						repBrother->left->is_red = false;
						repBrother->is_red = true;
						if (replaced->parent->right == replaced)
							replaced->parent->left = repBrother->left;
						else
							replaced->parent->right = repBrother->left;
						repBrother->left->parent = replaced->parent;
						node_pointer tmp = repBrother->left->right;
						tmp->parent = repBrother;
						repBrother->left->right = repBrother;
						repBrother->parent = repBrother->left;
						repBrother->left = tmp;
					}
				} else if (repBrother && !repBrother->is_nullLeaf() && replaced->is_red) {
					replaced->parent->is_red = true;
					repBrother->is_red = false;
					if (replaced == replaced->parent->left) {
						after_deletion_left_turn(replaced);
					} else {
						after_deletion_right_turn(replaced);
					}
				}
			}
			 */
		}

		/********************************** TREE MODIFIERS ***********************************************/
	public:
		ft::pair<iterator, bool> insert_element(const value_type& val) {
			key_type key = type_helper::get_key(val);
			node_pointer current = _root;
			node_pointer new_element;
			if (!_size) {
				_size++;
				_root = replace_node_value(val, _root);
				_end_node->right = _root;
				return ft::make_pair(_root, true);
			}
			while (true) {
				if (key == current->key()) {
					return ft::make_pair(iterator(current), false);
				}
				if (_k_comp(key, current->key())) {
					if (current->left) { current = current->left; continue; }
					else { new_element = current->left = add_new_node(val, current); break; }
				}
				if (current->right) { current = current->right; continue; }
				new_element = current->right = add_new_node(val, current);
				break;
			}
			_size++;
			balance(new_element);
			_end_node->right = _root;
			return ft::make_pair(new_element, true);
		}

	public:
		void erase (iterator position) {
			(void) position;
			/*
			if (!_size)
				return;
			_size--;
			node_pointer toDelete = find_nodeptr(position);
			node_pointer replaced;
			if ((!toDelete->right && !toDelete->left) ||
					(toDelete->right->is_nullLeaf() && toDelete->left->is_nullLeaf()))
				replaced = delete_lonely_node(toDelete);
			else if (toDelete->right->is_nullLeaf() || toDelete->left->is_nullLeaf())
				replaced = delete_one_child_node(toDelete);
			else
				replaced = delete_two_child_node(toDelete);
			//balancing after deletion. can have 3 max rotations
			for (int i = 0; i < 3; i++)
				balance_after_deletion(replaced);
			if (_size == 0) {
				_root = _node_alloc.allocate(1);
				_node_alloc.construct(_root, _end_node);
			}
			_end_node->right = _root;
			 */
		}

	public:
		void clear() {
			while (_size > 0) {
				erase(begin());
			}
		}

		/* Good luck for deletion :DDD
		https://youtu.be/w5cvkTXY0vQ
		* */
		void after_deletion_left_turn(node_pointer replaced) {
			node_pointer repBrother = get_brother_node(replaced);
			if (get_gparent_node(replaced) == null_pointer)
				_root = repBrother;
			else if (get_gparent_node(replaced)->left == replaced->parent)
				get_gparent_node(replaced)->left = repBrother;
			else
				get_gparent_node(replaced)->right = repBrother;
			repBrother->parent = get_gparent_node(replaced);
			replaced->parent->parent = repBrother;

			replaced->parent->right = repBrother->left;
			repBrother->left->parent = replaced->parent;
			repBrother->left = replaced->parent;
		}

		/* Good luck for deletion :DDD
		https://youtu.be/w5cvkTXY0vQ
		* */
		void after_deletion_right_turn(node_pointer replaced) {
			node_pointer repBrother = get_brother_node(replaced);
			if (get_gparent_node(replaced) == null_pointer)
				_root = repBrother;
			else if (get_gparent_node(replaced)->left == replaced->parent)
				get_gparent_node(replaced)->left = repBrother;
			else
				get_gparent_node(replaced)->right = repBrother;
			repBrother->parent = get_gparent_node(replaced);
			replaced->parent->parent = repBrother->right;
			replaced->parent->left = repBrother->right->right;
			repBrother->right->right = replaced->parent;
		}

		/*	Swapping trees content */
	public:
		void swap (RB_tree& x) {
			RB_tree tmp(x);
			x = *this;
			*this = tmp;
		}

		/*************************************** OPERATIONS *******************************************/

	public:
		iterator find (const key_type& k) {
			node_pointer tmp = _root;
			while (tmp) {
				if (k == tmp->key())
					return iterator(tmp);
				if (_k_comp(k, tmp->key()))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return end();
		}

	public:
		const_iterator find (const key_type& k) const {
			node_pointer tmp = _root;
			while (tmp) {
				if (k == tmp->key())
					return const_iterator(tmp);
				if (_k_comp(k, tmp->key()))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return end();
		}

	public:
		size_type count (const key_type& k) const {
			return (find(k) == end() ? 0 : 1);
		}

	public:
		iterator lower_bound (const key_type& k) {
			iterator it = begin();
			while (it != end() && _k_comp(KeyValGetter<Key, Mapped>::get_key(*it), k))
				++it;
			return it;
		}

	public:
		const_iterator lower_bound (const key_type& k) const {
			const_iterator it = begin();
			while (it != end() && _k_comp(KeyValGetter<Key, Mapped>::get_key(*it), k))
				++it;
			return it;
		}

	public:
		iterator upper_bound (const key_type& k) {
			iterator it = begin();
			while (it != end()) {
				key_type it_key = KeyValGetter<Key, Mapped>::get_key(*it);
				if (_k_comp(k, it_key))
					return it;
				++it;
			}
			return it;
		}

	public:
		const_iterator upper_bound (const key_type& k) const {
			const_iterator it = begin();
			while (it != end()) {
				key_type it_key = KeyValGetter<Key, Mapped>::get_key(*it);
				if (_k_comp(k, it_key))
					return it;
				++it;
			}
			return it;
		}


		/*************************************** ITERATORS *******************************************/

	public:
		/*	Return iterator to beginning
		* Returns an iterator referring to the first element in the map container. */
		iterator begin(){
			if (!_size)
				return end();
			node_pointer tmp = _root;
			while (tmp->left)
				tmp = tmp->left;
			return iterator(tmp);
		}

	public:
		const_iterator begin() const{
			if (!_size)
				return end();
			node_pointer tmp = _root;
			while (tmp->left)
				tmp = tmp->left;
			return const_iterator(tmp);
		}

		/*	Return iterator to end
		* Returns an iterator referring to the past-the-end element in the map container. */
	public:
		iterator end(){
			return iterator(_end_node);
		}
		const_iterator end() const {
			return const_iterator(_end_node);
		}

		/*	Return reverse iterator to reverse beginning *
		Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning). */
	public:
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		/*	Return reverse iterator to reverse end *
		* Returns a reverse iterator pointing to the theoretical element right before the first element in the map
		* container (which is considered its reverse end). */
	public:
		reverse_iterator rend() {
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}


		/*************************************** UTILS ***************************************************/
	private:
		node_pointer get_gparent_node(node_pointer n) {
			if (n == _root || n->parent == _root)
				return null_pointer;
			return n->parent->parent;
		}
	private:
		node_pointer get_aunt_node(node_pointer n) {
			node_pointer gp;
			gp = get_gparent_node(n);
			if (!gp)
				return null_pointer;
			if (gp->right == n->parent)
				return gp->left;
			return gp->right;
		}
	private:
		node_pointer get_brother_node(node_pointer n) {
			if (n == _root)
				return null_pointer;
			return n->parent->left == n ? n->parent->right : n->parent->left;
		}

	private:
		node_pointer find_nodeptr (iterator ptr) { //FIXME need tests
			node_pointer tmp = _root;
			key_type k = KeyValGetter<Key, Mapped>::get_key(*ptr);
			while (tmp) {
				if (k == tmp->key())
					return tmp;
				if (_k_comp(k, tmp->key()))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return end();
		}

	public:
		size_type getSize() const {
			return _size;
		}

	public:
		node_allocator_type getAlloc() const {
			return _node_alloc;
		}
		/**************************************** OBSERVERS ***************************************************/

	public:
		/*	Return key comparison object *
		* Returns a copy of the comparison object used by the container to compare keys.*/

		key_compare key_comp() const {
			return _k_comp;
		}

		/*	Return value comparison object *
		* Returns a comparison object that can be used to compare two elements
		* to get whether the key of the first one goes before the second.*/

		value_compare value_comp() const {
			return value_compare(_k_comp);
		}

		/*************************************** DELETE/FREE ***************************************************/
	private:
		void destroy_and_deallocate(node_pointer p) {
			_node_alloc.destroy(p);
			_node_alloc.deallocate(p, 1);
		}

	private:
		node_pointer delete_lonely_node(node_pointer e) {
			/*
			node_pointer ret = null_pointer;
			if (!e->left && !e->right) {
				destroy_and_deallocate(e);
				return ret;
			}
			destroy_and_deallocate(e->left);
			if (e == _root) {
				destroy_and_deallocate(e->right);
				destroy_and_deallocate(e);
				//_root = _node_alloc.allocate(1);
				//_node_alloc.construct(_root, _end_node);
				return null_pointer;
			} else {
				if (e->parent->left == e)
					e->parent->left = e->right;
				else
					e->parent->right = e->right;
				e->right->parent = e->parent;
				ret = e->right;
			}
			destroy_and_deallocate(e);
			return ret;
			 */
			return null_pointer;
		}

	private:
		node_pointer delete_one_child_node(node_pointer e) {
			/*
			node_pointer child;
			if (e->left->is_nullLeaf()) {
				child = e->right;
				destroy_and_deallocate(e->left);
			} else {
				child = e->left;
				destroy_and_deallocate(e->right);
			}
			if (e == _root)
				_root = child;
			else if (e->parent->left == e)
				e->parent->left = child;
			else
				e->parent->right = child;
			child->parent = e->parent;
			destroy_and_deallocate(e);
			return child;
			 */
			return null_pointer;
		}

	private:
		node_pointer delete_two_child_node(node_pointer e) {
			/*
			node_pointer new_val = e->right;
			bool oldcolor = e->is_red;
			if (new_val->left->is_nullLeaf()) {
				e = replace_node_value(new_val->node_data, e);
				e->is_red = oldcolor;
				destroy_and_deallocate(new_val->left);
				new_val->right->parent = e;
				e->right = new_val->right;
				destroy_and_deallocate(new_val);
				return e->right;
			} else {
				node_pointer ret;
				while (!new_val->left->is_nullLeaf())
					new_val = new_val->left;
				e = replace_node_value(new_val->node_data, e);
				e->is_red = oldcolor;
				new_val->parent->left = new_val->right;
				new_val->right->parent = new_val->parent;
				ret = new_val->parent->left;
				destroy_and_deallocate(new_val->left);
				destroy_and_deallocate(new_val);
				return ret;
			}
			 */
			return null_pointer;
		}
	};
}
#endif //CONTAINERS_RB_TREE_HPP
