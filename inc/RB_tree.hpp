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
	template < class Key,							//map::ket_type
			class Mapped,                         	// if ValueType is pair Mapped= map::mapped_value, otherwise Key
			class ValueType,                       	// content type, for map ft::pair, for set other
			class Compare = std::less<Key>,        	// map::key_compare
			class Alloc = std::allocator<ValueType>	// map::allocator_type
	> class RB_tree {

		/************************************** NODE STRUCTURE **************************************************/
	public:
		struct RB_node {
			typedef ValueType	value_type;
			typedef 			RB_node* pointer;

			value_type node_data;
			pointer left;
			pointer right;
			pointer parent;
			bool is_red;

			/* constructor for creating a new null node */
			RB_node(pointer par) : left(null_pointer), right(null_pointer), parent(par), is_red(false) {}

			/*constructor for creationg a new node */
			RB_node(const value_type &nodeData) : node_data(nodeData), left(null_pointer),
													right(null_pointer), parent(null_pointer),
													is_red(true) {}

			RB_node &operator=(const RB_node &other) {
				if (this != &other) {
					node_data = other.node_data;
					is_red = true;
				}
				return *this;
			}

			bool is_nullLeaf() {
				return (!left && !right && !is_red);
			}

			Key& key(typename ft::enable_if<!ft::is_pair<Key, Mapped>::value >::type* = 0) { return node_data.first ; }
		};
		/******************************* TYPEDEFS *******************************************/
		/* Node	*/
		typedef 	RB_node node;
		typedef 	RB_node* pointer;
		/* Regular */
		typedef		ValueType										value_type;
		typedef		typename Alloc::template rebind<RB_node>::other	allocator_type;
		typedef		Compare											key_compare;
		typedef		size_t											size_type;
		typedef		Key												key_type;
		/*	Iterator */
		typedef 			RBT_iterator<node, value_type>			iterator;
		typedef 			RBT_iterator<node, const value_type>	const_iterator;


		/*	Tree initialization constructor */
		explicit RB_tree (const key_compare& comp = key_compare(),
						  const allocator_type& alloc = allocator_type()) : _root(null_pointer), _alloc(alloc),
																			_k_comp(comp), _size(0) {}

		virtual ~RB_tree() {}

	private:
		pointer _root;
		allocator_type _alloc;
		key_compare _k_comp;
		size_type _size;

		/************************* NODES ALLOCATION AND CREATION ***********************************************/

		node* create_root(const value_type& val, node* parent, bool red = true) {
			node *res = _alloc.allocate(1);
			_alloc.construct(res, val);
			res->parent = parent;
			res->is_red = red;
			create_null_leafs(res);

			return res;
		}

		void create_null_leafs(node* parent) {
			if (!parent->left) {
				parent->left = _alloc.allocate(1);
				_alloc.construct(parent->left, parent);
			}
			if (!parent->right){
				parent->right = _alloc.allocate(1);
				_alloc.construct(parent->right, parent);
			}
		}
		/************************** OPERATION FOR BALANCE THE TREE **********************************************/
		/* all operations are based from this img:
			 * https://miro.medium.com/max/1196/1*v3n2S2CwZ9HcbTHGHLi-2w.png
			 * */

		void color_flip(pointer n) {
			n->parent->is_red = false;
			if (_root != get_gparent_node(n))
				get_gparent_node(n)->is_red = true;
			get_aunt_node(n)->is_red = false;
		}

		void right_rotation(pointer n) {
			pointer parent_tmp = get_gparent_node(n)->parent;
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
				pointer tmp = n->parent->right; //saving pa right child
				tmp->parent = get_gparent_node(n); //swap
				n->parent->right = get_gparent_node(n);
				n->parent->right->parent = n->parent;
				n->parent->right->left = tmp;
				n->parent->right->is_red = true;
				n->parent->is_red = false;
				n->parent->parent = parent_tmp;
			}
		}

		void left_rotation(pointer n) {
			pointer parent_tmp = get_gparent_node(n)->parent;
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
				pointer tmp = n->parent->left; //saving pa right child
				tmp->parent = get_gparent_node(n); //swap
				n->parent->left = get_gparent_node(n);
				n->parent->left->parent = n->parent;
				n->parent->left->right = tmp;
				n->parent->left->is_red = true;
				n->parent->is_red = false;
				n->parent->parent = parent_tmp;
			}
		}

		void left_right_rotation(pointer n) {
			if (get_aunt_node(n)->is_red) {
				color_flip(n);
			} else {
				pointer tmp_left = n->left;
				tmp_left->parent = n->parent;
				n->left = n->parent;
				n->parent = get_gparent_node(n);
				n->parent->left->parent = n;
				n->parent->left = n;
				n->left->right = tmp_left;
				right_rotation(n->left);
			}
		}

		void right_left_rotation(pointer n) {
			if (get_aunt_node(n)->is_red) {
				color_flip(n);
			} else {
				pointer tmp_right = n->right;
				tmp_right->parent = n->parent;
				n->right = n->parent;
				n->parent = get_gparent_node(n);
				n->parent->right->parent = n;
				n->parent->right = n;
				n->right->left = tmp_right;
				left_rotation(n->right);
			}
		}

		void balance(pointer n) {
			while (n) {
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
				n = n->parent;
			}
		}

		/********************************** TREE MODIFIERS ***********************************************/
	public:
		void insert_element(const value_type& val) {
			node tmp(val);
			if (!_root) { _root = create_root(val, null_pointer, false); return; }
			node *current = _root;
			while (true) {
				if (tmp.key() == current->key()) { current->node_data.second = val.second; break; }
				if (_k_comp(tmp.key(), current->key())) {
					if (!current->left->is_nullLeaf()) { current = current->left; continue; }
					else {
						_size++;
						*(current->left) = tmp;
						create_null_leafs(current->left);
						balance(current->left);
						break; }
				}
				if (!current->right->is_nullLeaf()) { current = current->right; continue; }
				_size++;
				*(current->right) = tmp;
				create_null_leafs(current->right);
				balance(current->right);
				break;
			}
		}

		//size_type erase (const key_type& k) {}

		/*************************************** OPERATIONS *******************************************/

		iterator find (const key_type& k) {
			pointer tmp = _root;
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

		const_iterator find (const key_type& k) const {
			pointer tmp = _root;
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

		size_type count (const key_type& k) const {
			return (find(k) == end() ? 0 : 1);
		}

		iterator lower_bound (const key_type& k) {
			iterator it = begin();
			while (_k_comp(it->first, k) && it != end())
				++it;
			return it;
		}

		const_iterator lower_bound (const key_type& k) const {
			const_iterator it = begin();
			while (_k_comp(it->first, k) && it != end())
				++it;
			return it;
		}

		iterator upper_bound (const key_type& k) {
			iterator it = begin();
			while (_k_comp(k, it->first) && it != end())
				++it;
			return it;
		}

		const_iterator upper_bound (const key_type& k) const {
			const_iterator it = begin();
			while (_k_comp(k, it->first) && it != end())
				++it;
			return it;
		}


		/*************************************** ITERATORS *******************************************/

		iterator begin(){
			node* tmp = _root;
			while (!tmp->left->is_nullLeaf())
				tmp = tmp->left;
			return iterator(tmp);
		}

		iterator end(){
			node* tmp = _root;
			while (tmp->right)
				tmp = tmp->right;
			return iterator(tmp);
		}

		const_iterator begin() const{
			node* tmp = _root;
			while (!tmp->left->is_nullLeaf())
				tmp = tmp->left;
			return const_iterator(tmp);
		}

		const_iterator end() const {
			node* tmp = _root;
			while (tmp->right)
				tmp = tmp->right;
			return const_iterator(tmp);
		}

		/*************************************** UTILS ***************************************************/
	private:
		pointer get_gparent_node(pointer n) {
			if (!n->parent)
				return null_pointer;
			return n->parent->parent;
		}

		pointer get_aunt_node(pointer n) {
			if (!get_gparent_node(n))
				return null_pointer;
			if (get_gparent_node(n)->right == n->parent)
				return get_gparent_node(n)->left;
			return get_gparent_node(n)->right;
		}

	public:
		static bool is_nullLeaf(pointer n) {
			return (!n->left && !n->right && !n->is_red);
		}

		/*
		RB_node *getRoot() const {
			return _root;
		}
		 */

		size_type getSize() const {
			return _size;
		}

		allocator_type getAlloc() const {
			return _alloc;
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
