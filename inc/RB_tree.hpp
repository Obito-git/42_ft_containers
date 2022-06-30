//
// Created by Anton on 22/06/2022.
//

#ifndef CONTAINERS_RB_TREE_HPP
#define CONTAINERS_RB_TREE_HPP
/* Used links :
 * https://medium.com/swlh/red-black-tree-rotations-and-color-flips-10e87f72b142
 * https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
 * */
#include <ostream>
#include "pair.hpp"
#define RED     "\033[31m"      /* Red */
#define RESET   "\033[0m"
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */

namespace ft {
	/************************************** NODE STRUCTURE **************************************************/

	template <class Key, class Mapped> struct KeyValGetter {
		static Key get_key(ft::pair<const Key, Mapped> &val) { return val.first; }
		static Key get_key(const Key &val) { return val; }
		static Mapped &get_value(ft::pair<const Key, Mapped> &val) { return val.second; }
		static Mapped &get_value(const Key &val) { return val; }
	};

	template <class ValueType, class Key, class Mapped, class Alloc>
	struct RB_node {
	public:
		/*	Node typedefs */
		typedef ValueType	value_type;
		typedef ValueType*	value_pointer;
		typedef 			RB_node* node_pointer;

		/*	Variables */
		value_pointer	node_data;
		node_pointer	left;
		node_pointer	right;
		node_pointer	parent;
		Alloc _alloc; //FIXME typedef
		bool is_red;

		/* constructor for creating a new null pointer */
		RB_node(node_pointer par) : left(null_pointer), right(null_pointer), parent(par), is_red(false) {
			node_data = _alloc.allocate(1);
			_alloc.construct(node_data);
		}

		/*constructor for creationg a new pointer */
		RB_node(const value_type &nodeData) : left(null_pointer),
											  right(null_pointer), parent(null_pointer),
											  is_red(true) {
			node_data = _alloc.allocate(1);
			_alloc.construct(node_data, nodeData);
		}

		~RB_node() {
			_alloc.destroy(node_data);
			_alloc.deallocate(node_data, 1);
		}

		RB_node &operator=(const RB_node &other) {
			if (this != &other) {
				_alloc.destroy(node_data);
				_alloc.construct(node_data, *other.node_data);
				is_red = other.is_red;
			}
			return *this;
		}

		bool is_nullLeaf() {
			return (!left && !right && !is_red);
		}

		bool without_childs() {
			return (left->is_nullLeaf() && right->is_nullLeaf());
		}

		Key key() { return KeyValGetter<const Key, Mapped>::get_key(*node_data); }
		Mapped& value() { return KeyValGetter<const Key, Mapped>::get_value(*node_data); }
	};


	/****************************************** RB TREE CLASS **********************************************/

	template < class Key,							//map::ket_type
			class Mapped,                         	// if ValueType is pair Mapped= map::mapped_value, otherwise Key
			class ValueType,                       	// content type, for map ft::pair, for set other
			class Compare = std::less<Key>,        	// map::key_compare
			class Alloc = std::allocator<ValueType>	// map::allocator_type
	> class RB_tree {
	public:
		/******************************* TYPEDEFS *******************************************/
		/* Node	*/
		typedef 	RB_node<ValueType, Key, Mapped, Alloc>			node;
		typedef 	node*										node_pointer;
		/* Regular */
		typedef		ValueType										value_type;
		typedef		ValueType*										value_pointer;
		typedef		typename Alloc::template rebind<node>::other	node_allocator_type;
		typedef		Compare											key_compare;
		typedef		size_t											size_type;
		typedef		Key												key_type;
		/*	Iterator */
		typedef 			RBT_iterator<node, value_type>			iterator;
		typedef 			RBT_iterator<node, const value_type>	const_iterator;


		/*	Tree initialization constructor */
		explicit RB_tree (const key_compare& comp = key_compare(),
						  const node_allocator_type& alloc = node_allocator_type()) : _root(null_pointer), _node_alloc(alloc),
																					  _k_comp(comp), _size(0) {}

		virtual ~RB_tree() {}

		/******************************** VARIABLES ***********************************************************/
	private:
		node_pointer _root;
		node_allocator_type _node_alloc;
		key_compare _k_comp;
		size_type _size;

		/************************* NODES ALLOCATION AND CREATION ***********************************************/


	private:
		node_pointer create_root(const value_type& val, node_pointer parent, bool red = true) {
			node_pointer res = _node_alloc.allocate(1);
			_node_alloc.construct(res, val);
			res->parent = parent;
			res->is_red = red;
			create_null_leafs(res);

			return res;
		}

	private:
		void create_null_leafs(node_pointer parent) {
			if (!parent->left) {
				parent->left = _node_alloc.allocate(1);
				_node_alloc.construct(parent->left, parent);
			}
			if (!parent->right){
				parent->right = _node_alloc.allocate(1);
				_node_alloc.construct(parent->right, parent);
			}
		}
		/************************** OPERATION FOR BALANCE THE TREE **********************************************/
		/* all operations are based from this img:
			 * https://miro.medium.com/max/1196/1*v3n2S2CwZ9HcbTHGHLi-2w.png
			 * */

	private:
		void color_flip(node_pointer n) {
			n->parent->is_red = false;
			if (_root != get_gparent_node(n))
				get_gparent_node(n)->is_red = true;
			get_aunt_node(n)->is_red = false;
		}

	private:
		void right_rotation(node_pointer n) {
			node_pointer parent_tmp = get_gparent_node(n)->parent;
			// if (aunt red) color flip
			if (get_aunt_node(n)->is_red) { //color flip
				color_flip(n);
			} else {
				//relink node bcs of grandparent changing
				if (!get_gparent_node(n)->parent)
					_root = n->parent;
				else {
					if (get_gparent_node(n)->parent->left == get_gparent_node(n))
						get_gparent_node(n)->parent->left = n->parent;
					else
						get_gparent_node(n)->parent->right = n->parent;
				}
				node_pointer tmp = n->parent->right; //saving pa right child
				tmp->parent = get_gparent_node(n); //swap
				n->parent->right = get_gparent_node(n);
				n->parent->right->parent = n->parent;
				n->parent->right->left = tmp;
				n->parent->right->is_red = true;
				n->parent->is_red = false;
				n->parent->parent = parent_tmp;
			}
		}

	private:
		void left_rotation(node_pointer n) {
			node_pointer parent_tmp = get_gparent_node(n)->parent;
			// if (aunt red) color flip
			if (get_aunt_node(n)->is_red) { //color flip
				color_flip(n);
			} else {
				//relink node bcs of grandparent changing
				if (!get_gparent_node(n)->parent)
					_root = n->parent;
				else {
					if (get_gparent_node(n)->parent->left == get_gparent_node(n))
						get_gparent_node(n)->parent->left = n->parent;
					else
						get_gparent_node(n)->parent->right = n->parent;
				}
				node_pointer tmp = n->parent->left; //saving pa right child
				tmp->parent = get_gparent_node(n); //swap
				n->parent->left = get_gparent_node(n);
				n->parent->left->parent = n->parent;
				n->parent->left->right = tmp;
				n->parent->left->is_red = true;
				n->parent->is_red = false;
				n->parent->parent = parent_tmp;
			}
		}

	private:
		void left_right_rotation(node_pointer n) {
			if (get_aunt_node(n)->is_red) {
				color_flip(n);
			} else {
				node_pointer tmp_left = n->left;
				tmp_left->parent = n->parent;
				n->left = n->parent;
				n->parent = get_gparent_node(n);
				n->parent->left->parent = n;
				n->parent->left = n;
				n->left->right = tmp_left;
				right_rotation(n->left);
			}
		}

	private:
		void right_left_rotation(node_pointer n) {
			if (get_aunt_node(n)->is_red) {
				color_flip(n);
			} else {
				node_pointer tmp_right = n->right;
				tmp_right->parent = n->parent;
				n->right = n->parent;
				n->parent = get_gparent_node(n);
				n->parent->right->parent = n;
				n->parent->right = n;
				n->right->left = tmp_right;
				left_rotation(n->right);
			}
		}

	private:
		void balance(node_pointer n) {
			while (n) {
				check_basic_conditions(n);
				n = n->parent;
			}
		}

	private:
		void check_basic_conditions(node_pointer n) {
			if ((get_gparent_node(n)) && (n->is_red && n->parent->left == n)
				&& (n->parent->is_red && get_gparent_node(n)->left == n->parent))
				right_rotation(n);
			else if ((get_gparent_node(n)) && (n->is_red && n->parent->right == n)
					 && (n->parent->is_red && get_gparent_node(n)->left == n->parent)
					 && (!n->parent->left->is_red))
				left_right_rotation(n);
			else if ((get_gparent_node(n)) && (n->is_red && n->parent->right == n)
					 && (n->parent->is_red && get_gparent_node(n)->right == n->parent))
				left_rotation(n);
			else if ((get_gparent_node(n)) && (n->is_red && n->parent->left == n)
					 && (n->parent->is_red && get_gparent_node(n)->right == n->parent)
					 && (!n->parent->right->is_red))
				right_left_rotation(n);
		}

	private:
		void balance_after_deletion(node_pointer replaced) {
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
		}

		/********************************** TREE MODIFIERS ***********************************************/
	public:
		ft::pair<iterator, bool> insert_element(const value_type& val) {
			_size++;
			node tmp(val);
			if (!_root) { _root = create_root(val, null_pointer, false); return ft::make_pair(_root, true); }
			node_pointer current = _root;
			while (true) {
				if (tmp.key() == current->key()) {
					current->value() = tmp.value();
					_size--;
					return ft::make_pair(iterator(current), false);
				}
				if (_k_comp(tmp.key(), current->key())) {
					if (!current->left->is_nullLeaf()) { current = current->left; continue; }
					else {
						*(current->left) = tmp;
						create_null_leafs(current->left);
						balance(current->left);
						return ft::make_pair(current->left, true);
					}
				}
				if (!current->right->is_nullLeaf()) { current = current->right; continue; }
				*(current->right) = tmp;
				create_null_leafs(current->right);
				balance(current->right);
				return ft::make_pair(current->right, true);
			}
			//return ft::make_pair(end(), false);
		}

		void erase (iterator position) {
			_size--;
			node_pointer toDelete = find_nodeptr(position);
			node_pointer replaced;
			if (toDelete->right->is_nullLeaf() && toDelete->left->is_nullLeaf())
				replaced = delete_lonely_node(toDelete);
			else if (toDelete->right->is_nullLeaf() || toDelete->left->is_nullLeaf())
				replaced = delete_one_child_node(toDelete);
			else
				replaced = delete_two_child_node(toDelete);
			//balancing after deletion. can have 3 max rotations
			for (int i = 0; i < 3; i++)
				balance_after_deletion(replaced);
			/*
			if (replaced && !replaced->is_nullLeaf()) {
				iterator it;
				if (replaced->key() <= _root->key()) {
					it = begin();
					while (find_nodeptr(it) != _root) {
						balance(find_nodeptr(it));
						it++;
					}
				} else {
					it = end();
					while (find_nodeptr(it) != _root) {
						balance(find_nodeptr(it));
						it--;
					}
				}
			}
			 */
		}

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

		/*************************************** OPERATIONS *******************************************/

	public:
		iterator find (const key_type& k) {
			node_pointer tmp = _root;
			while (tmp && !tmp->is_nullLeaf()) {
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
			while (tmp && !tmp->is_nullLeaf()) {
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
			while (_k_comp(it->first, k) && it != end())
				++it;
			return it;
		}

	public:
		const_iterator lower_bound (const key_type& k) const {
			const_iterator it = begin();
			while (_k_comp(it->first, k) && it != end())
				++it;
			return it;
		}

	public:
		iterator upper_bound (const key_type& k) {
			iterator it = begin();
			while (_k_comp(k, it->first) && it != end())
				++it;
			return it;
		}

	public:
		const_iterator upper_bound (const key_type& k) const {
			const_iterator it = begin();
			while (_k_comp(k, it->first) && it != end())
				++it;
			return it;
		}


		/*************************************** ITERATORS *******************************************/

	public:
		iterator begin(){
			node_pointer tmp = _root;
			while (!tmp->left->is_nullLeaf())
				tmp = tmp->left;
			return iterator(tmp);
		}

	public:
		iterator end(){
			node_pointer tmp = _root;
			while (tmp->right)
				tmp = tmp->right;
			return iterator(tmp);
		}

	public:
		const_iterator begin() const{
			node_pointer tmp = _root;
			while (!tmp->left->is_nullLeaf())
				tmp = tmp->left;
			return const_iterator(tmp);
		}

	public:
		const_iterator end() const {
			node_pointer tmp = _root;
			while (tmp->right)
				tmp = tmp->right;
			return const_iterator(tmp);
		}

		/*************************************** UTILS ***************************************************/
	private:
		node_pointer get_gparent_node(node_pointer n) {
			if (!n->parent)
				return null_pointer;
			return n->parent->parent;
		}
	private:
		node_pointer get_aunt_node(node_pointer n) {
			if (!get_gparent_node(n))
				return null_pointer;
			if (get_gparent_node(n)->right == n->parent)
				return get_gparent_node(n)->left;
			return get_gparent_node(n)->right;
		}
	private:
		node_pointer get_brother_node(node_pointer n) {
			if (!n->parent)
				return null_pointer;
			return n->parent->left == n ? n->parent->right : n->parent->left;
		}

	private:
		node_pointer find_nodeptr (iterator ptr) { //FIXME need tests
			node_pointer tmp = _root;
			//key_type k = *ptr.first;
			value_type kk = *ptr;
			key_type k = kk.first; //FIXME
			while (tmp && !tmp->is_nullLeaf()) {
				if (k == tmp->key())
					return tmp;
				if (_k_comp(k, tmp->key()))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return tmp;
		}

	public:
		static bool is_nullLeaf(node_pointer n) {
			return (!n->left && !n->right && !n->is_red);
		}

	public:
		size_type getSize() const {
			return _size;
		}

	public:
		node_allocator_type getAlloc() const {
			return _node_alloc;
		}
		/*************************************** DELETE/FREE ***************************************************/
	private:
		void destroy_and_deallocate(node_pointer p) {
			_node_alloc.destroy(p);
			_node_alloc.deallocate(p, 1);
		}

	private:
		node_pointer delete_lonely_node(node_pointer e) {
			node_pointer ret;
			destroy_and_deallocate(e->left);
			if (e->parent == null_pointer) {
				_root = null_pointer;
				destroy_and_deallocate(e->right);
				ret = null_pointer;
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
		}

	private:
		node_pointer delete_one_child_node(node_pointer e) {
			node_pointer child;
			child = e->left->is_nullLeaf() ? e->right : e->left;
			if (e->parent == null_pointer)
				_root = child;
			else if (e->parent->left == e)
				e->parent->left = child;
			else
				e->parent->right = child;
			child->parent = e->parent;
			if (e->left == child)
				destroy_and_deallocate(e->right);
			else
				destroy_and_deallocate(e->left);
			return child;
		}

	private:
		node_pointer delete_two_child_node(node_pointer e) {
			node_pointer new_val = e->right;
			bool oldcolor = e->is_red;
			if (new_val->left->is_nullLeaf()) {
				*e = *new_val->node_data;
				e->is_red = oldcolor;
				destroy_and_deallocate(new_val->left);
				new_val->right->parent = e;
				e->right = new_val->right;
				destroy_and_deallocate(new_val);
			} else {
				while (!new_val->left->is_nullLeaf())
					new_val = new_val->left;
				*e = *new_val->node_data;
				e->is_red = oldcolor;
				new_val->parent->left = new_val->left;
				new_val->left->parent = new_val->parent;
				destroy_and_deallocate(new_val->right);
				destroy_and_deallocate(new_val);
			}
			return e->right;
		}




		/*
		friend std::ostream &operator<<(std::ostream &os, const RB_node &node) {
			if (is_nullLeaf(&node))
				return os;
			else {
				os << (node.is_red ? RED : BOLDCYAN);
				os << "((K:[" << node.node_data.first << "]" << " P:[";
				if (node.parent)
					os << node.parent->node_data.first;
				else
					os << "ROOT";
				os << "]))" << RESET;
			}
			return os;
		}
		 */
	};
}
#endif //CONTAINERS_RB_TREE_HPP
