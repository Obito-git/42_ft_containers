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
	/*	Universal getter for
	*   ft::pair and other objects type; It will return key/val which depends on obj type */
	template <class Key, class Mapped> struct KeyValGetter {
		static Key get_key(const ft::pair<const Key, Mapped> &val) { return val.first; }
		static Key get_key(const Key &val) { return val; }
		static Mapped get_value(const ft::pair<const Key, Mapped> &val) { return val.second; }
		static Mapped get_value(const Key &val) { return val; }
	};

	/************************************** NODE STRUCTURE **************************************************/
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

		/* constructor for creating a new null pointer */
		RB_node(node_pointer par) : left(null_pointer), right(null_pointer), parent(par), is_red(false) {
		}

		/*constructor for creation a new pointer */
		RB_node(const value_type &nodeData) : node_data(nodeData), left(null_pointer),
											  right(null_pointer), parent(null_pointer),
											  is_red(true) {
		}

		/*	Destructor */
		~RB_node() {}

		bool is_nullLeaf() {
			return (!left && !right && !is_red);
		}

		Key key() { return KeyValGetter<const Key, Mapped>::get_key(node_data); }
		Mapped value() { return KeyValGetter<const Key, Mapped>::get_value(node_data); }
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


		/*	Tree initialization constructor */
		explicit RB_tree (const key_compare& comp = key_compare(),
						  const node_allocator_type& alloc = node_allocator_type()) : _root(null_pointer), _node_alloc(alloc),
																					  _k_comp(comp), _size(0) {}

		virtual ~RB_tree() {
			clear();
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
				return comp(x.first, y.first);
			}
		};

		/************************************** VARIABLES *****************************************************/
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


	private:
		node_pointer add_element(const value_type& elem, node_pointer old) {
			node_pointer new_elem = _node_alloc.allocate(1);
			_node_alloc.construct(new_elem, elem);
			new_elem->parent = old->parent;
			if (old->parent) {
				if (old == old->parent->left)
					old->parent->left = new_elem;
				else
					old->parent->right = new_elem;
			}
			else
				_root = new_elem;
			if (old->left) { old->left->parent = new_elem; new_elem->left = old->left; }
			if (old->right) { old->right->parent = new_elem; new_elem->right = old->right; }
			destroy_and_deallocate(old);
			create_null_leafs(new_elem);
			balance(new_elem);
			return new_elem;
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
			key_type key = type_helper::get_key(val);
			node_pointer current = _root;
			node_pointer new_element;
			if (!_root) { _root = create_root(val, null_pointer, false); return ft::make_pair(_root, true); }
			while (true) {
				if (key == current->key()) {
					//current->value() = type_helper::get_value(val); //FIXME
					_size--;
					return ft::make_pair(iterator(current), false);
				}
				if (_k_comp(key, current->key())) {
					if (!current->left->is_nullLeaf()) { current = current->left; continue; }
					else { new_element = add_element(val, current->left); break; }
				}
				if (!current->right->is_nullLeaf()) { current = current->right; continue; }
				new_element = add_element(val, current->right);
				break;
			}
			return ft::make_pair(new_element, true);
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
		}

		void clear() {
			//FIXME optimise
			while (_size > 0) {
				erase(begin());
			}
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
		/*	Return iterator to beginning
		* Returns an iterator referring to the first element in the map container. */
		iterator begin(){
			node_pointer tmp = _root;
			while (!tmp->left->is_nullLeaf())
				tmp = tmp->left;
			return iterator(tmp);
		}

	public:
		const_iterator begin() const{
			node_pointer tmp = _root;
			while (!tmp->left->is_nullLeaf())
				tmp = tmp->left;
			return const_iterator(tmp);
		}

		/*	Return iterator to end
		* Returns an iterator referring to the past-the-end element in the map container. */
	public:
		iterator end(){
			node_pointer tmp = _root;
			while (tmp->right)
				tmp = tmp->right;
			return iterator(tmp);
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
			if (e->left->is_nullLeaf()) {
				child = e->right;
				destroy_and_deallocate(e->left);
			} else {
				child = e->left;
				destroy_and_deallocate(e->right);
			}
			if (e->parent == null_pointer)
				_root = child;
			else if (e->parent->left == e)
				e->parent->left = child;
			else
				e->parent->right = child;
			child->parent = e->parent;
			destroy_and_deallocate(e);
			return child;
		}

	private:
		node_pointer delete_two_child_node(node_pointer e) {
			node_pointer new_val = e->right;
			bool oldcolor = e->is_red;
			if (new_val->left->is_nullLeaf()) {
				e = add_element(new_val->node_data, e);
				e->is_red = oldcolor;
				destroy_and_deallocate(new_val->left);
				new_val->right->parent = e;
				e->right = new_val->right;
				destroy_and_deallocate(new_val);
				return e->right;
			} else {
				node_pointer ret;
				while (!new_val->left->is_nullLeaf()) //FIXME POSSIBLE BUG
					new_val = new_val->left;
				e = add_element(new_val->node_data, e);
				e->is_red = oldcolor;
				new_val->parent->left = new_val->right;
				new_val->right->parent = new_val->parent;
				ret = new_val->parent->left;
				destroy_and_deallocate(new_val->left);
				destroy_and_deallocate(new_val);
				return ret;
			}
		}
	};
}
#endif //CONTAINERS_RB_TREE_HPP
